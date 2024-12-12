#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "npc.h"
#include "npcFactory.h"
#include "observer.h"

// Структурка сражающейся пары
struct CombatPair {
    std::shared_ptr<NPC> npc1;
    std::shared_ptr<NPC> npc2;
};

class GameManager {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::mutex npcs_mutex; // для защиты вектора NPC
    std::mutex cout_mutex; // синхронизация вывода
    std::atomic<bool> running{false}; // флаг состояния игры
    std::queue<CombatPair> combat_queue;
    std::mutex queue_mutex; // защита очереди боев
    std::condition_variable combat_cv; // CV для уведомления о новых боях в очереди
    std::vector<std::shared_ptr<Observer>> observers;

    void movementThread();
    void combatThread();
    void displayThread();
    void printMap();
    void initializeNPCs();

public:
    GameManager();
    void start();
    void stop();
    void addObserver(std::shared_ptr<Observer> observer);

    static constexpr int INITIAL_NPC_COUNT = 50;
    static constexpr int GAME_DURATION_SECONDS = 30;
};

#endif 