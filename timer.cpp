#include "timer.h"

Timer::Timer(uint16_t num_timer, int32_t interval, int16_t divider, std::shared_ptr<Kia_settings> kia_settings) :
    m_interval(interval)
  , m_divider(divider)
  , m_kia_settings(kia_settings)
{
    m_num_timer = num_timer;
    cout<<"start_timer " << m_num_timer <<endl;
    m_kia_settings->m_timer_interval = m_interval / m_divider;
    m_interval_divider = m_kia_settings->m_timer_interval;
    //    m_sum_filter_el = 0;
    //    m_dovInterval = 2;
    //    for(auto &el : m_arr_for_synch)
    //    {
    //        el = m_interval;
    //        m_sum_filter_el += el;
    //    }
}

Timer::~Timer()
{
    cout<<"Destructor Timer"<<endl;
}


//void Timer::start()
//{
//    m_start_timer = std::async([this]
//    {
//        m_stop_timer = true;
//        // set real-time priority
//        struct timespec deadline;
//        clock_gettime(CLOCK_MONOTONIC, &deadline);
//        // Add the time you want to sleep
//        struct sched_param schedparm;
//        memset(&schedparm, 0, sizeof(schedparm));
//        schedparm.sched_priority = 99; // highest rt priority
//        sched_get_priority_max(99);
//        sched_setscheduler(0, SCHED_FIFO, &schedparm);
//        // set timer slack equal to 1 nanosecond
//        prctl(PR_SET_TIMERSLACK, 1);
//        m_start_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
//        while (m_stop_timer)
//        {
//            auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
//            std::lock_guard lock(m);
//            deadline.tv_nsec += (m_interval_divider + m_shift_interval) * m_to_ms;

//            if (deadline.tv_nsec >= m_kia_settings->m_timer_interval * m_to_ms)
//            {
//                deadline.tv_nsec -= m_kia_settings->m_timer_interval * m_to_ms;
//                deadline.tv_sec++;
//            }
//            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
//            m_now_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
//            m_kia_settings->m_data_for_db->bshv++;
//            auto delta = (m_now_time - m_curr_time) / m_to_ms;
//            if (delta < (m_kia_settings->m_timer_interval / m_divider))
//                m_interval_divider  = (m_kia_settings->m_timer_interval / m_divider) - (delta - m_shift_interval);
//            std::cout << m_interval_divider << " " << delta <<  (start - m_now_time) / m_to_ms << std::endl;
//            m_count++;
//            m_cv.notify_all();
//            emit reset_protocol();
//            //t_action();
//        }

//    });
//}

void Timer::start()
{
    m_start_timer = std::async([this]
    {
        m_stop_timer = true;
        // set real-time priority
        struct timespec deadline;
        clock_gettime(CLOCK_MONOTONIC, &deadline);
        // Add the time you want to sleep
        struct sched_param schedparm;
        memset(&schedparm, 0, sizeof(schedparm));
        schedparm.sched_priority = 99; // highest rt priority
        sched_get_priority_max(99);
        sched_setscheduler(0, SCHED_FIFO, &schedparm);
        // set timer slack equal to 1 nanosecond
        prctl(PR_SET_TIMERSLACK, 1);
        while (m_stop_timer)
        {
            std::lock_guard lock(m);
            auto start = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            std::this_thread::sleep_for(std::chrono::milliseconds((m_interval_divider + m_shift_interval) - 1));
            while (m_now_time - start <= (m_interval_divider + m_shift_interval) * m_to_ms)
            {
                m_now_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            }
            m_kia_settings->m_data_for_db->bshv[m_num_timer]++;
            auto delta = (m_now_time - m_curr_time) / m_to_ms;
            if (delta <= (m_kia_settings->m_timer_interval + m_shift_interval))
                m_interval_divider = m_kia_settings->m_timer_interval - delta / m_divider;
            //std::cout << m_interval_divider << " " << delta << " " << m_kia_settings->m_data_for_db->bshv[m_num_timer] << std::endl;
            m_count++;
            m_cv.notify_all();
        }

    });
}

void Timer::synchronize()
{
    m_curr_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    //cout<<"curtime: "<<currTime< <endl;
    //    if (m_prev_time != 0)
    //    {
    //        if (m_delta == 0)
    //        {
    //            m_shift_interval = 5;
    //        }
    //        //cout<<"prevtime: "<<prevTime<<endl;
    //        m_delta = (m_curr_time - m_prev_time) / m_to_ms;
    //        //cout<< m_delta<<" "<<m_interval<<" "<<m_interval_divider<< endl;
    //        if (abs(m_delta - m_interval) <= m_dovInterval)
    //        {
    //            m_sum_filter_el = m_sum_filter_el - m_arr_for_synch[0] + m_delta;

    //            for(uint16_t i = 1; i < constants::FILTER_LENGTH; ++i)
    //            {
    //                m_arr_for_synch[i - 1] = m_arr_for_synch[i];
    //            }
    //            m_arr_for_synch[constants::FILTER_LENGTH - 1] = m_delta;
    //            m_interval = round(m_sum_filter_el / constants::FILTER_LENGTH);
    //            m_interval_divider = m_interval / m_divider;
    //        }
    //        else
    //        {
    //            //m_interval = m_delta + (shift_interval + delta);
    //            m_interval_divider = m_interval / m_divider;
    //        }
    //    }
    //    m_prev_time = m_curr_time;

}



void Timer::closeTimerThread()
{
    m_stop_timer = false;
    m_start_timer.get();
}

condition_variable &Timer::getEvent()
{
    return m_cv;
}

int64_t Timer::inSleep()
{
    return m_count;
}

int64_t Timer::getBSHV()
{
    return m_bshv;
}

int Timer::getDelta()
{
    return m_interval;
}

void Timer::change_1s_mark(const int32_t& interval)
{
    m_shift_interval = interval;
}

void Timer::change_divider(int32_t &divider)
{
    m_kia_settings->m_timer_interval = m_interval / divider;
    m_divider = divider;
}
