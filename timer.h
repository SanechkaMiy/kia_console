#ifndef TIMER_H
#define TIMER_H
#include <thread>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <chrono>
#include <functional>
#include <cstdio>
#include <atomic>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>
#include <time.h>
#include <random>
#include <mutex>
#include <condition_variable>
#include <QObject>
#include <memory>
#include <simpletimer.h>
#include <array>
#include <unistd.h>
#include "mainStruct.h"
#include <errno.h>
class Timer : public QObject
{
    Q_OBJECT
public:
    struct Kia_data_timer
    {
        uint16_t m_timer_interval{1000};
        int32_t m_divider{1};
    };
    Timer(uint16_t num_timer, int32_t interval, int16_t divider, std::shared_ptr<Kia_settings> kia_settings);
    Timer(Kia_data_timer* kia_data_timer);
    ~Timer();

    void start();
    void synchronize();
    void closeTimerThread();
    void change_interval(int32_t shift);
    std::condition_variable& getEvent();
    int64_t inSleep();
    int64_t getBSHV();
    uint16_t get_timer_interval()
    {
        return m_kia_data_timer->m_timer_interval;
    }
    int getDelta();
public slots:
    void change_divider(int32_t divider);
private:
    Kia_data_timer* m_kia_data_timer;
    uint16_t m_num_timer = 0;
    double m_start_time  = 0;
    double m_now_time  = 0;
    int32_t m_interval;
    int32_t m_divider;
    int32_t m_shift_interval = 25;
    uint32_t m_to_ms = 1000000;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::condition_variable m_cv;
    std::thread m_thread{};
    float m_sum_filter_el = 0;
    int  t_sleepforparam;
    int32_t m_interval_divider;
    int64_t m_curr_time = 0;
    int64_t m_prev_time = 0;
    int64_t m_count = 0;
    int64_t m_bshv = 0;
    int64_t m_delta = 0;
    int64_t t_missDelta = 0;
    int16_t m_corrInterval = 0;
    int16_t m_dovInterval = 0;
    std::mutex m;
    std::future<void> m_start_timer;
    std::atomic_bool m_stop_timer{false};
};

#endif // TIMER_H
