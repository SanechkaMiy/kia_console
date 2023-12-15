#ifndef KIA_BKPIK_H
#define KIA_BKPIK_H
#include <CppLinuxSerial/SerialPort.hpp>
#include <QSerialPortInfo>
#include <vector>
#include <string.h>
#include <thread>
#include <atomic>
#include "simpletimer.h"
#include <condition_variable>
#include "kia_protocol.h"
#include "mainStruct.h"
#include <mutex>
#include "parsetodb.h"
#include <array>
#include <QObject>
#include "kia_bi.h"
#include <filesystem>
#include "Kia_modules/kia_db.h"
namespace fs = std::filesystem;

class Kia_bkpik : public Kia_bi
{
    Q_OBJECT
public:
    Kia_bkpik(uint16_t num_bi, std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
              shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings);
    ~Kia_bkpik();
    std::condition_variable& getEvent();
    int64_t inSleep();
    void change_command_bkpik(std::vector<uint8_t> command);

    void start_1s_mark_bkpik();
    uint16_t on_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch = 0, uint16_t parametr = EP_DOALL) override;
    uint16_t off_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL, uint16_t off_1_ch = 0) override;

    void on_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL, uint16_t off_1_ch = 0) override;
    void off_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL, uint16_t off_1_ch = 0) override;

    void on_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL, uint16_t off_1_ch = 0) override;
    void off_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL, uint16_t off_1_ch = 0) override;

    void on_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL) override;
    void off_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr = EP_DOALL) override;

    void stop_1s_mark() override;
    void send_telemetry() override;
    void wait_for_event() override;
    void stop_event() override;

    void set_relay_command(uint16_t relay_command) override;
    void set_relay_polarity(uint16_t relay_command) override;
    void set_relay_command_pulse_time(uint16_t relay_command) override;

    void set_sec_mark_pulse_time(uint16_t sec_mark_pulse_time) override;

signals:
    void send_to_client(quint16, QStringList);
private:
    void set_bkpik_settings();
    std::vector<std::string> m_list_com_port;
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_db;
    shared_ptr<ParseToDB> m_parser_db;
    shared_ptr<Kia_protocol> m_kia_protocol;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr <mn::CppLinuxSerial::SerialPort> m_serial_port;
    std::condition_variable m_cv;
    int64_t m_count = 0;
    std::atomic_int16_t is_change_state;
    Flags_for_thread m_ffThread;
    uint8_t m_off_1_ch;
    std::future<void> m_start_1s_mark;
    std::atomic_bool m_stop_1s_mark{false};
    std::atomic_bool m_check{true};
};

#endif // KIA_BKPIK_H
