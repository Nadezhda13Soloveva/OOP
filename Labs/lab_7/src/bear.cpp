#include "bear.h"

Bear::Bear(const std::string& name, float x, float y) : NPC(name, x, y) {}
std::string Bear::getType() const { return "Bear"; }

bool Bear::canFightWith(const NPC& other) const {
    return other.getType() == "Orc" || other.getType() == "Squirrel";
}

bool Bear::willWin(const NPC& other) const {
    return other.getType() == "Squirrel";
}
