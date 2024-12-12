#include "npcFactory.h"
#include <stdexcept>
#include <fstream>

bool NPCFactory::areCorrectCoords(float x, float y) {
    return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}

bool NPCFactory::isUnique(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& name, float x, float y) {
    for (const auto& npc : npcs) {
        if (npc->getName() == name || (npc->getX() == x && npc->getY() == y)) {
            return false; // Имя или координаты уже заняты
        }
    }
    return true;
}

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, float x, float y,
                                           const std::vector<std::shared_ptr<NPC>>& npcs) {
    if (!areCorrectCoords(x, y)) {
        throw std::out_of_range("Coordinates must be within 0 <= x, y <= 500.");
    }
    if (!isUnique(npcs, name, x, y)) {
        throw std::runtime_error("Name or coordinates are not unique.");
    }

    if (type == "Orc") return std::make_shared<Orc>(name, x, y);
    if (type == "Squirrel") return std::make_shared<Squirrel>(name, x, y);
    if (type == "Bear") return std::make_shared<Bear>(name, x, y);
    throw std::invalid_argument("Unknown NPC type!");
}

std::vector<std::shared_ptr<NPC>> NPCFactory::loadFromFile(const std::string& filename,
                                                          const std::vector<std::shared_ptr<NPC>>& existingNpcs) {
    std::vector<std::shared_ptr<NPC>> npcs = existingNpcs; // Копируем уже существующих NPC
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string type, name;
    float x, y;

    while (file >> type >> name >> x >> y) {
        if (!areCorrectCoords(x, y)) {
            throw std::runtime_error("Invalid NPC coordinates in file: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        }
        if (!isUnique(npcs, name, x, y)) {
            throw std::runtime_error("Duplicate name or coordinates in file: " + name);
        }

        npcs.push_back(createNPC(type, name, x, y, npcs));
    }

    file.close();
    return npcs;
}
