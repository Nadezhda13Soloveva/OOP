#ifndef NPC_H
#define NPC_H

#include <string>
#include <cmath>

class NPC {
protected:
    std::string name;
    float x, y;

public:
    NPC(const std::string& name, float x, float y);
    virtual ~NPC();

    virtual std::string getType() const = 0;
    virtual bool canFightWith(const NPC& other) const = 0;
    virtual bool willWin(const NPC& other) const = 0;

    const std::string& getName() const;
    float getX() const;
    float getY() const;
    float distanceTo(const NPC& other) const;
};

#endif 
