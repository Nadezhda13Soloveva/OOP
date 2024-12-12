#include "fightVisitor.h"
#include <algorithm>
#include <random>

FightVisitor::FightVisitor(float range) : range(range) {}

void FightVisitor::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void FightVisitor::fight(std::vector<std::shared_ptr<NPC>>& npcs) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dice(1, 6);

    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            auto& npc1 = npcs[i];
            auto& npc2 = npcs[j];

            if (npc1->distanceTo(*npc2) <= range &&
                npc1->canFightWith(*npc2) && npc2->canFightWith(*npc1)) {

                // броски 6-гранного кубика для силы атаки и защиты
                int npc1_attack = dice(gen);  
                int npc2_defense = dice(gen); 
                int npc2_attack = dice(gen);  
                int npc1_defense = dice(gen); 

                bool npc1Wins = npc1_attack > npc2_defense && npc1->willWin(*npc2);
                bool npc2Wins = npc2_attack > npc1_defense && npc2->willWin(*npc1);

                std::string fightLog = npc1->getName() + " (" + npc1->getType() + 
                    ")[A:" + std::to_string(npc1_attack) + ",D:" + std::to_string(npc1_defense) + 
                    "] fights " + npc2->getName() + " (" + npc2->getType() + 
                    ")[A:" + std::to_string(npc2_attack) + ",D:" + std::to_string(npc2_defense) + 
                    "] -> ";
                
                if (npc1Wins && npc2Wins) {
                    fightLog += "Both died.";
                    npc1->kill();
                    npc2->kill();
                } else if (npc1Wins) {
                    fightLog += npc1->getName() + " won.";
                    npc2->kill();
                } else if (npc2Wins) {
                    fightLog += npc2->getName() + " won.";
                    npc1->kill();
                } else {
                    fightLog += "No one won.";
                }

                for (auto& observer : observers) {
                    observer->notify(fightLog);
                }
            }
        }
    }
}
