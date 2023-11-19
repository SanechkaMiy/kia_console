#include "simpletimer.h"

SimpleTimer::SimpleTimer(std::string nameTimer): m_nameTimer(nameTimer)
{

}

SimpleTimer::~SimpleTimer()
{

}

void SimpleTimer::start()
{
    // set real-time priority
    struct sched_param schedparm;
    memset(&schedparm, 0, sizeof(schedparm));
    schedparm.sched_priority = 99; // highest rt priority
    sched_get_priority_max(99);
    sched_setscheduler(0, SCHED_FIFO, &schedparm);
    // set timer slack equal to 1 nanosecond
    prctl(PR_SET_TIMERSLACK, 1);
    m_start = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void SimpleTimer::end()
{
    m_end = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    auto diff = m_end - (m_start);
    std::cout<<"Duration " + m_nameTimer + " - " << diff << std::endl;
}
