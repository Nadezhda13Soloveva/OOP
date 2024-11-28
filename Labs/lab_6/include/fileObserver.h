#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include "observer.h"
#include <fstream>

class FileObserver : public Observer {
    std::ofstream logFile;

public:
    FileObserver(const std::string& filename);
    ~FileObserver();
    void notify(const std::string& message) override;
};

#endif
