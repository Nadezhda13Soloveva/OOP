#include "squirrel.h"

Squirrel::Squirrel(const std::string& name, float x, float y) : NPC(name, x, y) {}
std::string Squirrel::getType() const { return "Squirrel"; }

bool Squirrel::canFightWith(const NPC& other) const {
    return other.getType() == "Bear"; // Белки могут сражаться только с медведями
}

bool Squirrel::willWin(const NPC& other) const {
    return false; // Белки не участвуют в боях
}
