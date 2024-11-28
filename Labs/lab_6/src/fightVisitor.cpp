#include "fightVisitor.h"
#include <algorithm>

FightVisitor::FightVisitor(float range) : range(range) {}

void FightVisitor::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void FightVisitor::fight(std::vector<std::shared_ptr<NPC>>& npcs) {
    std::vector<std::shared_ptr<NPC>> toRemove;

    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            auto& npc1 = npcs[i];
            auto& npc2 = npcs[j];

            if (npc1->distanceTo(*npc2) <= range &&
                npc1->canFightWith(*npc2) && npc2->canFightWith(*npc1)) {

                bool npc1Wins = npc1->willWin(*npc2);
                bool npc2Wins = npc2->willWin(*npc1);

                std::string fightLog = npc1->getName() + " (" + npc1->getType() + ") fights " +
                                       npc2->getName() + " (" + npc2->getType() + ") -> ";

                if (npc1->getType() == "Orc" && npc2->getType() == "Orc") {
                    // Специальное условие для сражения орков
                    fightLog += "Both Orcs died.";
                    toRemove.push_back(npc1);
                    toRemove.push_back(npc2);
                } else if (npc1Wins && npc2Wins) {
                    fightLog += "Both died.";
                    toRemove.push_back(npc1);
                    toRemove.push_back(npc2);
                } else if (npc1Wins) {
                    fightLog += npc1->getName() + " won.";
                    toRemove.push_back(npc2);
                } else if (npc2Wins) {
                    fightLog += npc2->getName() + " won.";
                    toRemove.push_back(npc1);
                }

                for (auto& observer : observers) {
                    observer->notify(fightLog);
                }
            }
        }
    }

    for (auto& npc : toRemove) {
        npcs.erase(std::remove(npcs.begin(), npcs.end(), npc), npcs.end());
    }
}
