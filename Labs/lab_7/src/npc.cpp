#include "npc.h"
#include <algorithm>

NPC::NPC(const std::string& name, float x, float y) 
    : name(name), x(std::clamp(x, 0.0f, MAP_SIZE)), y(std::clamp(y, 0.0f, MAP_SIZE)), alive(true) {}

NPC::~NPC() {}

const std::string& NPC::getName() const {
    std::shared_lock lock(mutex);
    return name;
}

float NPC::getX() const {
    std::shared_lock lock(mutex);
    return x;
}

float NPC::getY() const {
    std::shared_lock lock(mutex);
    return y;
}

bool NPC::isAlive() const {
    std::shared_lock lock(mutex);
    return alive;
}

void NPC::kill() {
    std::unique_lock lock(mutex);
    alive = false;
}

float NPC::distanceTo(const NPC& other) const {
    std::shared_lock lock1(mutex);
    std::shared_lock lock2(other.mutex);
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

void NPC::move(float dx, float dy) {
    std::unique_lock lock(mutex);
    if (!alive) return;
    
    x = std::clamp(x + dx, 0.0f, MAP_SIZE);
    y = std::clamp(y + dy, 0.0f, MAP_SIZE);
}


