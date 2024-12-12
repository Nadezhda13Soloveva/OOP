#ifndef ORC_H
#define ORC_H

#include "npc.h"

class Orc : public NPC {
public:
    Orc(const std::string& name, float x, float y);
    std::string getType() const override;
    bool canFightWith(const NPC& other) const override;
    bool willWin(const NPC& other) const override;
};

#endif 