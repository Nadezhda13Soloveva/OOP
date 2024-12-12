#ifndef SQUIRREL_H
#define SQUIRREL_H

#include "npc.h"

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, float x, float y);
    std::string getType() const override;
    bool canFightWith(const NPC& other) const override;
    bool willWin(const NPC& other) const override;
    float getMoveDistance() const override { return 5.0f; }
    float getKillDistance() const override { return 5.0f; }
};

#endif 
