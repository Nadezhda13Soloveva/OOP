#include "consoleObserver.h"

void ConsoleObserver::notify(const std::string& message) {
    std::cout << message << std::endl;
}
