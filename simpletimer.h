#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H
#include <chrono>
#include <time.h>
#include <iostream>
#include <memory>
#include <sys/prctl.h>
#include <string.h>
class SimpleTimer
{
public:
    SimpleTimer(std::string nameTimer);
    ~SimpleTimer();
    void start();
    void end();
private:
    double m_end;
    double m_start;
    std::string m_nameTimer;
};

#endif // SIMPLETIMER_H
