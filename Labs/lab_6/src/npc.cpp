#include "npc.h"

NPC::NPC(const std::string& name, float x, float y) : name(name), x(x), y(y) {}
NPC::~NPC() {}

const std::string& NPC::getName() const { return name; }
float NPC::getX() const { return x; }
float NPC::getY() const { return y; }

float NPC::distanceTo(const NPC& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}
