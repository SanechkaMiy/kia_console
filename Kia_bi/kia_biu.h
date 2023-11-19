#ifndef KIA_BIU_H
#define KIA_BIU_H
#include "BiLibNE.h"
#include "mainStruct.h"
#include "workwithstruct.h"
#include "kia_protocol.h"
#include "parsetodb.h"
#include <condition_variable>
#include <dlfcn.h>
#include "kia_bi.h"
#include "Kia_modules/kia_db.h"
void wait_1s();
class Kia_biu : public Kia_bi
{
    Q_OBJECT
public:
    Kia_biu(uint16_t num_bi, shared_ptr<WorkWithStruct> wws,
            std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
            shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings);
    ~Kia_biu();

    void on_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) override;
    void off_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) override;

    void on_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) override ;
    void off_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) override;

    void on_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) override;
    void off_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) override;

    void on_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL) override;
    void off_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL) override;

    void stop_1s_mark() override;
    void send_telemetry() override;
    void wait_for_event() override;
    void stop_event() override;

    void set_relay_command(uint16_t relay_command) override;
    void set_relay_polarity(uint16_t relay_command) override;
    void set_relay_command_pulse_time(uint16_t relay_command) override;
signals:
    void send_to_client(quint16, QStringList);
private:
    void (Kia_biu::*m_func)();
    void wait_1s_biu_0();
    void wait_1s_biu_1();
    void wait_1s_biu_2();
    void wait_1s_biu_3();
    void wait_1s_biu();
    void set_sec_mark_period(uint16_t sec_mark_period);
    void get_relay_polarity();
    void get_relay_command_pulse_time();
    void parse_data(uint16_t num_ch, struct DevTelemetry* dev_tel);
    void set_bi_settings();
    uint16_t init_bi();
    uint16_t close_bi();
    void start_1s_mark();
    void set_power(uint16_t command);
    void get_power(uint16_t status_power);
    void set_synch_status(uint16_t synch_status);
    void get_synch_status();
    void set_sec_mark_pulse_time(uint16_t sec_mark_pulse_time);
    void get_sec_mark_telemetry();
    void get_telemetry();
    void set_synchro(void(*func)(uint16_t));
    void get_sec_mark_status(uint16_t sec_mark_status);
    void set_sinchronize_event();
    void set_sec_mark_status(uint16_t &num_ch, uint16_t sec_mark_status);
    void get_master_state();
    void preset_telemetry(uint16_t num_ch, struct DevTelemetry* dev_tel);
    shared_ptr<ParseToDB> m_parser_db;
    shared_ptr<WorkWithStruct> m_wws;
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_db;
    shared_ptr<Kia_protocol> m_kia_protocol;
    std::shared_ptr<Kia_settings> m_kia_settings;
    int16_t m_device_id = 0;
    uint16_t m_count_dev = 0;
    DevTelemetry* m_devTel_1;
    DevTelemetry* m_devTel_2;
    void *m_handle;
    uint16_t m_sec_mark_status = 0x0000;
    uint16_t m_power_status = 0x0000;
    uint16_t m_off_1_ch = 0x0000;
    std::vector<std::vector<float>> m_td_on_ch;
    std::future<void> m_start_1s_mark;
    std::atomic_bool m_stop_1s_mark{false};

};

#endif // KIA_BIU_H
