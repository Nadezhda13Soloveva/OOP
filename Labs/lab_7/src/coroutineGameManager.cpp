#include "coroutineGameManager.h"
#include "fightVisitor.h"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cmath>
#include <algorithm>

// Аналогично реализации многопоточностью 
CoroutineGameManager::CoroutineGameManager() {
    initializeNPCs();
}

void CoroutineGameManager::initializeNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, NPC::MAP_SIZE);
    std::uniform_int_distribution<> type_dis(0, 2);

    for (int i = 0; i < INITIAL_NPC_COUNT; ++i) {
        float x = dis(gen);
        float y = dis(gen);
        std::string name = "NPC_" + std::to_string(i);
        
        try {
            auto npc = NPCFactory::createNPC(
                type_dis(gen) == 0 ? "Orc" : 
                type_dis(gen) == 1 ? "Bear" : "Squirrel",
                name, x, y, npcs
            );
            npcs.push_back(npc);
        } catch (const std::exception& e) {
            --i;
        }
    }
}

// Перемещение 
void CoroutineGameManager::moveNPC(std::shared_ptr<NPC>& npc) {
    if (!npc->isAlive()) return;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> angle_dis(0, 2 * M_PI);

    float angle = angle_dis(gen);
    float distance = npc->getMoveDistance();
    float dx = distance * std::cos(angle);
    float dy = distance * std::sin(angle);
    
    npc->move(dx, dy);
}

// Управление боем
void CoroutineGameManager::processCombat(std::shared_ptr<NPC>& npc1, std::shared_ptr<NPC>& npc2) {
    if (!npc1 || !npc2 || !npc1->isAlive() || !npc2->isAlive()) return;

    if (npc1->distanceTo(*npc2) <= npc1->getKillDistance()) {
        static FightVisitor visitor(npc1->getKillDistance());
        
        visitor = FightVisitor(npc1->getKillDistance());
        for (const auto& observer : observers) {
            visitor.addObserver(observer);
        }

        std::vector<std::shared_ptr<NPC>> combatants = {npc1, npc2};
        visitor.fight(combatants);
    }
}

// 
GameTick CoroutineGameManager::gameLoop() {
    auto start_time = std::chrono::steady_clock::now();
    
    while (running) {
        {
            std::unique_lock<std::mutex> lock(npcs_mutex);
            
            // Зачистка мертвых
            npcs.erase(
                std::remove_if(npcs.begin(), npcs.end(),
                    [](const auto& npc) { return !npc || !npc->isAlive(); }),
                npcs.end()
            );
            
            // Перемещение
            for (auto& npc : npcs) {
                moveNPC(npc);
            }

            // Бои
            for (size_t i = 0; i < npcs.size(); ++i) {
                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    if (npcs[i] && npcs[j]) { 
                        processCombat(npcs[i], npcs[j]);
                    }
                }
            }
        }

        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            current_time - start_time).count();
            
        if (elapsed_seconds >= GAME_DURATION_SECONDS) {
            running = false;
        }

        co_await std::suspend_always{};
    }
}


void CoroutineGameManager::start() {
    running = true;
    auto game_coroutine = gameLoop();
    
    while (running) {
        printMap();
        if (!game_coroutine.resume()) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // Вывод выживших
    std::unique_lock<std::mutex> cout_lock(cout_mutex);
    std::cout << "\nSurvivors after " << GAME_DURATION_SECONDS << " seconds:\n";
    
    int survivor_count = 0;
    for (const auto& npc : npcs) {
        if (npc && npc->isAlive()) {
            std::cout << npc->getName() << " (" << npc->getType() << ")\n";
            survivor_count++;
        }
    }
    std::cout << "\nTotal survivors: " << survivor_count << "\n";
}

void CoroutineGameManager::printMap() {
    
    std::unique_lock<std::mutex> cout_lock(cout_mutex);
    std::unique_lock<std::mutex> npcs_lock(npcs_mutex);

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

void CoroutineGameManager::stop() {
    running = false;
}

void CoroutineGameManager::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
} 