#ifndef CONSOLEOBSERVER_H
#define CONSOLEOBSERVER_H

#include "observer.h"
#include <iostream>

class ConsoleObserver : public Observer {
public:
    void notify(const std::string& message) override;
};

#endif 
