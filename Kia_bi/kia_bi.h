#ifndef KIA_BI_H
#define KIA_BI_H
#include <QObject>
#include <iostream>
#include "mainStruct.h"

class Kia_bi : public QObject
{
    Q_OBJECT
public:
    Kia_bi();

    virtual void on_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;
    virtual void off_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;

    virtual void on_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;
    virtual void off_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;

    virtual void on_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;
    virtual void off_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;

    virtual void on_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL) = 0;
    virtual void off_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL) = 0;

    virtual void stop_1s_mark() = 0;
    virtual void send_telemetry() = 0;
    virtual void wait_for_event() = 0;
    virtual void stop_event() = 0;

    virtual void set_relay_command(uint16_t relay_command) = 0;
    virtual void set_relay_polarity(uint16_t relay_command) = 0;
    virtual void set_relay_command_pulse_time(uint16_t relay_command) = 0;

    std::shared_ptr<Kia_data> m_kia_data;
    uint16_t m_num_bi;
};

#endif // KIA_BI_H
