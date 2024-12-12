#ifndef NPC_H
#define NPC_H

#include <string>
#include <cmath>
#include <random>
#include <mutex>
#include <shared_mutex>

class NPC {
protected:
    std::string name;
    float x, y;
    bool alive;
    mutable std::shared_mutex mutex;

public:
    NPC(const std::string& name, float x, float y);
    virtual ~NPC();

    virtual std::string getType() const = 0;
    virtual bool canFightWith(const NPC& other) const = 0;
    virtual bool willWin(const NPC& other) const = 0;
    virtual float getMoveDistance() const = 0;
    virtual float getKillDistance() const = 0;

    const std::string& getName() const;
    float getX() const;
    float getY() const;
    bool isAlive() const;
    void kill();
    float distanceTo(const NPC& other) const;
    void move(float dx, float dy);

    static constexpr float MAP_SIZE = 100.0f;
};

#endif 
