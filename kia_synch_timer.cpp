#include "kia_synch_timer.h"

Kia_synch_timer::Kia_synch_timer(uint16_t num_timer, shared_ptr<Timer> timer, shared_ptr<Kia_bi> kia_bi,
                                 std::shared_ptr<Kia_settings> kia_settings) :
    m_timer(timer),
    m_kia_bi(kia_bi),
    m_kia_settings(kia_settings)
{
    m_num_timer = num_timer;
    start_timer();
    start_synch_timer();
}

void Kia_synch_timer::stop_timer()
{
    m_kia_bi->stop_event();
    m_stop_timer = false;
    //m_start_timer.get();
    m_stop_synch_1s_mark = false;
    //m_start_synch_1s_mark.get();
}

void Kia_synch_timer::start_timer()
{
    m_start_timer = std::async([this]
    {
        m_stop_timer = true;
        // set real-time priority
        struct sched_param schedparm;
        memset(&schedparm, 0, sizeof(schedparm));
        schedparm.sched_priority = 99; // highest rt priority
        sched_get_priority_max(99);
        sched_setscheduler(0, SCHED_FIFO, &schedparm);
        // set timer slack equal to 1 nanosecond
        prctl(PR_SET_TIMERSLACK, 1);
        while (m_stop_timer)
        {
            m_kia_bi->wait_for_event();
            if (m_is_first)
            {
                m_kia_settings->m_data_for_db->bshv[m_num_timer] = 0;
                m_is_first = false;
            }
            m_timer->synchronize();
        }
    });
}

void Kia_synch_timer::start_synch_timer()
{
    m_start_synch_1s_mark = std::async([this]
    {
        m_stop_synch_1s_mark = true;
        // set real-time priority
        struct sched_param schedparm;
        memset(&schedparm, 0, sizeof(schedparm));
        schedparm.sched_priority = 99; // highest rt priority
        sched_get_priority_max(99);
        sched_setscheduler(0, SCHED_FIFO, &schedparm);
        // set timer slack equal to 1 nanosecond
        prctl(PR_SET_TIMERSLACK, 1);
        QStringList list_status_1s_mark;
        QStringList bshv_for_table;
        while (m_stop_synch_1s_mark)
        {
            wait_for_event(m_timer);
            m_kia_settings->m_data_for_db->bshv[m_num_timer]++;
            for (uint16_t num_ch = 0; num_ch < m_kia_bi->m_kia_bi_data.m_count_channel; ++num_ch)
            {
                bshv_for_table.push_back(QString::number(ST_BSHV));
                bshv_for_table.push_back(QString::number(num_ch + m_num_timer * m_kia_bi->m_kia_bi_data.m_count_channel));
                bshv_for_table.push_back(QString::number(m_kia_settings->m_data_for_db->bshv[m_num_timer]));
                emit send_to_client(SEND_STATUS_INFO, bshv_for_table);
                bshv_for_table.clear();
            }
            list_status_1s_mark.push_back(QString::number(m_kia_bi->m_kia_bi_data.m_num_bi.first));
            emit send_to_client(SET_STATUS_1S_MARK, list_status_1s_mark);
            list_status_1s_mark.clear();
        }
    });
}

//template<typename T>
//void Kia_synch_timer::wait_for_event(T &ev)
//{
//    std::mutex m;
//    std::unique_lock lk(m);
//    auto& event = ev->getEvent();
//    auto mw_count = ev->inSleep();
//    event.wait(lk, [&ev, &mw_count]
//    {
//        return mw_count != ev->inSleep();
//    });
//}

void Kia_synch_timer::wait_for_event(shared_ptr<Timer> timer)
{
    std::mutex m;
    std::unique_lock lk(m);
    auto& event = timer->getEvent();
    auto mw_count = timer->inSleep();
    event.wait(lk, [&timer, &mw_count]
    {
        return mw_count != timer->inSleep();
    });
}
