#include "orc.h"

Orc::Orc(const std::string& name, float x, float y) : NPC(name, x, y) {}
std::string Orc::getType() const { return "Orc"; }

bool Orc::canFightWith(const NPC& other) const {
    return other.getType() == "Orc" || other.getType() == "Bear";
}

bool Orc::willWin(const NPC& other) const {
    if (other.getType() == "Orc") {
        return true; // Орки погибают оба
    }
    return other.getType() == "Bear"; // Орк выигрывает у медведя
}
