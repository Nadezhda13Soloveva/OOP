#include "coroutineGameManager.h"
#include "consoleObserver.h"
#include "fileObserver.h"

int main() {
    CoroutineGameManager game;
    
    game.addObserver(std::make_shared<ConsoleObserver>());
    game.addObserver(std::make_shared<FileObserver>("battle_log.txt"));
    
    game.start();
    
    return 0;
}