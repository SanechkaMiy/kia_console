#ifndef KIA_SYNCH_TIMER_H
#define KIA_SYNCH_TIMER_H
#include "mainStruct.h"
#include "kia_bi.h"
#include "timer.h"
#include "kia_protocol.h"
class Kia_synch_timer : public QObject
{
    Q_OBJECT
public:
    Kia_synch_timer(uint16_t num_timer, shared_ptr<Timer> timer, shared_ptr<Kia_bi> kia_bi,
                    std::shared_ptr<Kia_settings> kia_settings,
                    shared_ptr<Kia_protocol> kia_protocol);
    template <typename T>
    void wait_for_event(T& ev);
    void stop_timer();
signals:
    void send_to_client(quint16, QStringList);
private:
    uint16_t m_num_timer = 0;
    void start_timer();
    void start_synch_timer();
    shared_ptr<Timer> m_timer;
    shared_ptr<Kia_bi> m_kia_bi;
    std::shared_ptr<Kia_settings> m_kia_settings;
    shared_ptr<Kia_protocol> m_kia_protocol;

    std::future<void> m_start_synch_1s_mark;
    std::atomic_bool m_stop_synch_1s_mark{false};
    bool m_is_first = true;
    std::future<void> m_start_timer;
    std::atomic_bool m_stop_timer{false};
};

#endif // KIA_SYNCH_TIMER_H
