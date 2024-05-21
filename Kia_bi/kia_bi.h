#ifndef KIA_BI_H
#define KIA_BI_H
#include <QObject>
#include <iostream>
#include "mainStruct.h"

class Kia_bi : public QObject
{
    Q_OBJECT
public:
    struct Kia_bi_data
    {
        std::vector<uint16_t> m_kc;
        std::vector<uint16_t> m_kp;
        std::vector<uint16_t> m_1s;
        std::vector<float> m_td;
        std::string m_date_time{};
        std::pair<uint16_t, uint16_t> m_num_bi;
        QString hex_data;
        std::vector<uint16_t> m_term_group;
        uint16_t m_count_channel{};
    };

    Kia_bi();
    virtual void init(uint16_t num_bi, std::shared_ptr<Kia_settings> kia_settings) = 0;
    virtual uint16_t on_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t off_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) = 0;

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

    virtual void set_sec_mark_pulse_time(uint16_t sec_mark_pulse_time) = 0;

    virtual void create_bi_telemetry_list() = 0;


    Kia_bi_data m_kia_bi_data;
signals:
    void send_to_client(quint16, QStringList);

    void send_data_to_db_bi(qint16, quint16);
    void send_to_save_protocol(Kia_protocol_parametrs);
protected:
    ;
};

#endif // KIA_BI_H
