#ifndef COROUTINE_GAME_MANAGER_H
#define COROUTINE_GAME_MANAGER_H

#include <coroutine>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include "npc.h"
#include "npcFactory.h"
#include "observer.h"

// Структурка управления корутиной
struct GameTick {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        GameTick get_return_object() {
            return GameTick(handle_type::from_promise(*this));
        } // создание корутины
        std::suspend_never initial_suspend() { return {}; } // корутина должна продолжать выполнение после создания
        std::suspend_never final_suspend() noexcept { return {}; } // корутина должна продолжать выполнение после завершения
        void return_void() {} // корутина завершает выполнение без возврата значения
        void unhandled_exception() {} // корутина завершает выполнение с необработанным исключением
    };

    handle_type handle;
    
    GameTick(handle_type h) : handle(h) {}
    ~GameTick() {
        if (handle) handle.destroy();
    }

    // возобновляем выполнение корутины, если она не завершена
    bool resume() {
        if (!handle.done())
            handle.resume();
        return !handle.done();
    }
};

class CoroutineGameManager {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::mutex npcs_mutex;
    std::mutex cout_mutex;
    std::atomic<bool> running{false};
    std::vector<std::shared_ptr<Observer>> observers;

    void initializeNPCs();
    void printMap();
    GameTick gameLoop(); // управление игровым циклом
    void processCombat(std::shared_ptr<NPC>& npc1, std::shared_ptr<NPC>& npc2); // управление боем
    void moveNPC(std::shared_ptr<NPC>& npc); // перемещение персонажей

public:
    CoroutineGameManager();
    void start();
    void stop();
    void addObserver(std::shared_ptr<Observer> observer);

    static constexpr int INITIAL_NPC_COUNT = 50;
    static constexpr int GAME_DURATION_SECONDS = 30;
};

#endif 