#include <iostream>
#include <vector>
#include <memory>
#include "npcFactory.h"
#include "fightVisitor.h"
#include "consoleObserver.h"
#include "fileObserver.h"

int main() {
    std::vector<std::shared_ptr<NPC>> npcs;
    FightVisitor fightVisitor(0.0f); // дальность задается пользователем
    fightVisitor.addObserver(std::make_shared<ConsoleObserver>());
    fightVisitor.addObserver(std::make_shared<FileObserver>("log.txt"));

    while (true) {
        std::cout << "\nВыберите действие:\n"
                  << "1. Добавить нового NPC вручную\n"
                  << "2. Загрузить NPC из файла\n"
                  << "3. Сохранить текущие NPC в файл\n"
                  << "4. Напечатать перечень объектов\n"
                  << "5. Запустить боевой режим\n"
                  << "6. Выход\n"
                  << "Введите ваш выбор: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Добавить нового NPC вручную
            std::string type, name;
            float x, y;

            std::cout << "Введите тип NPC (Orc, Bear, Squirrel): ";
            std::cin >> type;
            std::cout << "Введите имя NPC: ";
            std::cin >> name;
            std::cout << "Введите координаты NPC (x y): ";
            std::cin >> x >> y;

            try {
                auto newNPC = NPCFactory::createNPC(type, name, x, y, npcs);
                npcs.push_back(newNPC);
                std::cout << "NPC успешно добавлен: " << name << " (" << type << ") на координатах (" << x << ", " << y << ").\n";
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при добавлении NPC: " << e.what() << "\n";
            }
        
        } else if (choice == 2) {
            // Загрузить NPC из файла
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;

            try {
                auto loadedNPCs = NPCFactory::loadFromFile(filename, npcs);
                for (size_t i = npcs.size(); i < loadedNPCs.size(); ++i) {
                    std::cout << "NPC загружен: " << loadedNPCs[i]->getName()
                              << " (" << loadedNPCs[i]->getType() << ") на координатах ("
                              << loadedNPCs[i]->getX() << ", " << loadedNPCs[i]->getY() << ").\n";
                }
                npcs = std::move(loadedNPCs);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при загрузке из файла: " << e.what() << "\n";
            }
        
        } else if (choice == 3) {
            // Сохранить текущие NPC в файл
            std::string filename;
            std::cout << "Введите имя файла для сохранения: ";
            std::cin >> filename;

            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Ошибка: невозможно открыть файл для записи.\n";
                continue;
            }

            for (const auto& npc : npcs) {
                file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
            }
            file.close();
            std::cout << "NPC успешно сохранены в файл " << filename << ".\n";
        
        } else if (choice == 4) {
            // Напечатать перечень объектов
            if (npcs.empty()) {
                std::cout << "Нет добавленных NPC.\n";
            } else {
                std::cout << "Список NPC:\n";
                for (const auto& npc : npcs) {
                    std::cout << npc->getType() << " " << npc->getName()
                              << " (" << npc->getX() << ", " << npc->getY() << ")\n";
                }
            }
        
        } else if (choice == 5) {
            // Запустить боевой режим
            float range;
            std::cout << "Введите дальность для сражений NPC: ";
            std::cin >> range;

            if (range <= 0) {
                std::cerr << "Ошибка: дальность должна быть положительным числом.\n";
                continue;
            }

            fightVisitor = FightVisitor(range); // обновляем дальность
            fightVisitor.addObserver(std::make_shared<ConsoleObserver>());
            fightVisitor.addObserver(std::make_shared<FileObserver>("log.txt"));

            fightVisitor.fight(npcs);
            std::cout << "Боевое сражение завершено.\n";
        } else if (choice == 6) {
            // Выход
            std::cout << "Завершение программы.\n";
            break;
        } else {
            std::cerr << "Ошибка: некорректный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
