#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer {
public:
    virtual void notify(const std::string& message) = 0;
    virtual ~Observer() {}
};

#endif 
