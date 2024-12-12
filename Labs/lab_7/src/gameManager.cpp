#include "gameManager.h"
#include "fightVisitor.h"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
#include <algorithm>

GameManager::GameManager() {
    initializeNPCs();
}

void GameManager::initializeNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, NPC::MAP_SIZE);
    std::uniform_int_distribution<> type_dis(0, 2);

    for (int i = 0; i < INITIAL_NPC_COUNT; ++i) {
        // генерация случайного расположения
        float x = dis(gen);
        float y = dis(gen);
        std::string name = "NPC_" + std::to_string(i);
        
        try {
            // генерация случайного типа и создание NPC
            auto npc = NPCFactory::createNPC(
                type_dis(gen) == 0 ? "Orc" : 
                type_dis(gen) == 1 ? "Bear" : "Squirrel",
                name, x, y, npcs
            );
            npcs.push_back(npc);
        } catch (const std::exception& e) {
            // Если не удалось создать итерация повторяется, чтобы было ровно 50 NPC
            --i;
        }
    }
}

// Обновление позиций и (если позволяет расстояние) постановка в очередь на бой
void GameManager::movementThread() {
    // генератор угла направления движения
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angle_dis(0, 2 * M_PI);

    while (running) {
        {
            std::unique_lock<std::mutex> lock(npcs_mutex);
            
            // Зачистка мертвых (звучит странно без контекста)
            npcs.erase(
                std::remove_if(npcs.begin(), npcs.end(),
                    // Удаляем, если nullptr или NPC мёртв
                    [](const auto& npc) { return !npc || !npc->isAlive(); }),
                npcs.end()
            );
            
            for (auto& npc : npcs) {
                if (!npc->isAlive()) continue;

                // генерирую угол перемещения и считаю изменения координат
                float angle = angle_dis(gen);
                float distance = npc->getMoveDistance();
                float dx = distance * std::cos(angle);
                float dy = distance * std::sin(angle);
                
                npc->move(dx, dy);

                // Чек возможности боя
                for (auto& other : npcs) {
                    // Если это один и тот же NPC или мертвый -> пропускаем
                    if (npc == other || !other->isAlive()) continue;

                    // Чек по расстоянию и правилу совместимости
                    if (npc->distanceTo(*other) <= npc->getKillDistance() &&
                        npc->canFightWith(*other) && other->canFightWith(*npc)) {
                        std::unique_lock<std::mutex> queue_lock(queue_mutex);
                        // добавляем NPC в очередь и уведомляем поток боя о новой паре
                        combat_queue.push({npc, other});
                        combat_cv.notify_one();
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


// Управление боем
void GameManager::combatThread() {
    FightVisitor visitor(10.0f);

    while (running) {
        CombatPair combat_pair;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // ожидаем новую пару или конец игры
            if (combat_cv.wait_for(lock, std::chrono::milliseconds(100), 
                [this]() { return !combat_queue.empty() || !running; })) {
                
                // Если очередь непуста или конец игры -> проверка состояния и наличия боев в очереди
                if (!running && combat_queue.empty()) {
                    break;
                }
                // берем первую пару если очередь непуста
                if (!combat_queue.empty()) {
                    combat_pair = combat_queue.front();
                    combat_queue.pop();
                }
            }
        }

        // если nullptr или NPC мертв -> пропускаем
        if (!combat_pair.npc1 || !combat_pair.npc2 || 
            !combat_pair.npc1->isAlive() || !combat_pair.npc2->isAlive()) {
            continue;
        }

        // сброс состояния наблюдателя
        visitor = FightVisitor(10.0f);
        for (const auto& observer : observers) {
            visitor.addObserver(observer);
        }
        // запуск боя
        std::vector<std::shared_ptr<NPC>> combatants = {combat_pair.npc1, combat_pair.npc2};
        {
            std::unique_lock<std::mutex> lock(npcs_mutex);
            visitor.fight(combatants);
        }
    }
}

// Отрисовка состояния карты
void GameManager::printMap() {
    std::unique_lock<std::mutex> cout_lock(cout_mutex);
    std::unique_lock<std::mutex> npcs_lock(npcs_mutex);

    // очистки экрана и перемещения курсора в верхний левый угол
    std::cout << "\033[2J\033[1;1H";
    
    const char BORDER_HOR = '-';
    const char BORDER_VER = '|';
    const char BORDER_CORNER = '+';
    
    std::cout << BORDER_CORNER;
    for (size_t i = 0; i < NPC::MAP_SIZE; ++i) {
        std::cout << BORDER_HOR;
    }
    std::cout << BORDER_CORNER << '\n';

    std::vector<std::vector<char>> map(NPC::MAP_SIZE, 
        std::vector<char>(NPC::MAP_SIZE, ' '));

    // Размещаю живых NPC по 1-й букве типа 
    for (const auto& npc : npcs) {
        if (!npc->isAlive()) continue;
        
        int x = static_cast<int>(npc->getX());
        int y = static_cast<int>(npc->getY());
        
        if (x >= 0 && x < NPC::MAP_SIZE && y >= 0 && y < NPC::MAP_SIZE) {
            map[y][x] = npc->getType()[0];
        }
    }

    for (const auto& row : map) {
        std::cout << BORDER_VER;
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << BORDER_VER << '\n';
    }

    std::cout << BORDER_CORNER;
    for (size_t i = 0; i < NPC::MAP_SIZE; ++i) {
        std::cout << BORDER_HOR;
    }
    std::cout << BORDER_CORNER << '\n';
}

void GameManager::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void GameManager::start() {
    running = true;
    
    // Поток перемещения и проверки пары NPC для возможности боя
    std::thread move_thread(&GameManager::movementThread, this);
    // ПОток управления боем
    std::thread combat_thread(&GameManager::combatThread, this);
    // время старта
    auto start_time = std::chrono::steady_clock::now();

    while (running) {
        printMap();
        
        // Считаем время с начала игры и завершаем через 30 сек
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            current_time - start_time).count();
            
        if (elapsed_seconds >= GAME_DURATION_SECONDS) {
            running = false;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // ожидаем завершения потоков перемещения и боя
    move_thread.join();
    combat_thread.join();
    
    std::unique_lock<std::mutex> cout_lock(cout_mutex);
    std::cout << "\nSurvivors after " << GAME_DURATION_SECONDS << " seconds:\n";
    
    // вывод выживших
    int survivor_count = 0;
    for (const auto& npc : npcs) {
        if (npc && npc->isAlive()) {
            std::cout << npc->getName() << " (" << npc->getType() << ")\n";
            survivor_count++;
        }
    }
    std::cout << "\nTotal survivors: " << survivor_count << "\n";
}

void GameManager::stop() {
    running = false;
    combat_cv.notify_all(); // уведомляем потоки, чтобы они могли завершиться
} 