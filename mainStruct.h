#ifndef MAINSTRUCT_H
#define MAINSTRUCT_H
#include <iostream>
#include <QString>
#include <QFile>
#include "Kia_enums.h"

#include <QtGlobal>
#include <QVector>
#include <future>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;
#define PI    3.141592653589793f
#define RTS   206264.8062470964f
#define PI2  6.283185307179587f

namespace constants
{
const uint16_t MAX_TMK_NUMBER =  7;
constexpr const double tarTD[6][2] = {{4.465309361, 235.5450688},{4.456359845, 235.5186178},{4.447446551, 235.4922949},{4.438569256, 235.466099},{4.429727741, 235.4400294},{4.420921788, 235.4140852}};
const static uint32_t FILTER_LENGTH= 10;
const static uint16_t max_tmk_dev = MAX_TMK_NUMBER * 2 + 1;
const static uint32_t packetSize = 34;
const static uint32_t protocol_count = 5;
const static uint16_t count_type_bi = 2;
const static uint16_t count_type_bokz = 6;
const static uint16_t size_qa = 4;
const static uint16_t size_w = 3;
const static uint16_t m_count_lpi = 2;
const static uint16_t max_avalable_address = 31;
const static uint16_t max_count_param = 3;
const static uint16_t max_count_bi = 4;
const static uint16_t max_count_same_connection = 2;
const uint32_t microsecond_in_second = 1000 * 1000;
}


#pragma pack(push, 1)
struct Data_for_mpi
{
    uint16_t m_num_bokz = 0;

    uint16_t m_code_word = 0;
    uint16_t m_address = 0;
    uint16_t m_word_data = 1;
    uint16_t m_sub_address = 0;
    uint16_t m_format = 0;
    uint16_t m_direction = 0;
    uint16_t m_base = 0;
    uint16_t m_lpi = 0;
    uint16_t m_nInt = 0;
    uint16_t m_wResult = 0;
    uint16_t m_mpi_result = 0;
    uint16_t m_wOs = 0;
    uint16_t m_status_exchange = 0;
    uint16_t m_mpi_index = 0;

    float m_epsilon;
    std::array<float, 3> m_focus_data;
    uint16_t m_texp;

    array<uint16_t, constants::packetSize> m_data_to_exc;
    array<uint16_t, constants::packetSize> m_data_word;
    array<uint16_t, constants::packetSize> m_prev_data_word;
    array<uint16_t, constants::packetSize> m_qa;
    array<uint16_t, constants::packetSize> m_w;
    array<uint16_t, constants::packetSize> m_data_upn;

    uint16_t m_num_used_channel = 0;

    QString m_is_error;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct Data_for_bokz
{
    std::vector<uint32_t> m_count_fail;
    std::vector<std::pair<QString, uint32_t>> m_count_fail_descr;
    std::vector<std::tuple<uint16_t, uint16_t, QStringList>> m_chpn_data;

    uint16_t m_bokz_status_in_cycl = KCS_SUCCES;
    uint16_t m_type_orient = 0;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct Data_for_db
{
    string m_extype_id;
    string m_description;
    string experiment_id;
    uint16_t serial_num;
    string m_datetime;
    string struct_id;
    string struct_id_dop;
    string struct_id_desc;
    string struct_id_dop_desc;
    string frame_name;
    string true_host;
    uint16_t subarray_id;
    uint16_t m_error_code;
    uint32_t m_exchange_counter = 0;
    string send_time;
    std::vector<int32_t> bshv;
    uint16_t error_code;
    string receive_time;
    uint16_t waw1;
    uint16_t waw2;
    uint16_t os;
    QString data;

    double m_norm_qaor;
    double m_alpha;
    double m_delta;
    double m_azimuth;

    double m_average;
    uint32_t m_min;
    uint32_t m_max;
    double m_variance;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct Flags_for_thread
{
    std::mutex m_mtx;
    std::mutex m_mtx_cyclogram;
    std::vector<bool>m_stop_cyclogram;
    std::vector<bool>m_stop_command;
    atomic_bool m_stop_cyclogram_for_one_launch{false};

    std::vector<std::future<void>> m_stop_cyclogram_thread;
    std::vector<std::future<void>> m_stop_command_thread;
    std::future<void> m_stop_cyclogram_for_one_launch_thread;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct Data_to_protocols
{
    uint16_t m_is_sql_protocol_used;
    uint16_t m_is_frames_protocol_used;
    bool m_save_binary = DO_BINARY_FALSE;
    std::array<uint16_t, constants::protocol_count> m_is_protocol_used;
    std::vector<bool> m_stop_spam_in_system_info;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct Frame_settings
{
    uint16_t m_type_frame_recieve;
    uint16_t m_type_frame;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Format_for_description
{
    int16_t shift_for_numbers = -8;
    int16_t shift_for_dtmi = -12;
    int16_t shift_description = -50;
    int16_t shift_count_of_fail = -40;
    int16_t shift_date_time = -25;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Data_for_bi
{
    std::vector<uint16_t> m_term_group;
    bool m_is_bkpik;
    std::vector<int> m_num_bi;
    int m_count_bi;
    std::array<int, constants::count_type_bi> m_count_channel_bi = {3, 2};//0 - БКПИК; 1 - БИ;
    uint16_t m_num_used_bi;
    std::vector<uint8_t> m_commandR;
    std::vector<uint16_t> m_raw_data;
    std::vector<float> m_td;
    std::vector<uint16_t> m_kc;
    std::vector<uint16_t> m_kp;
    std::vector<uint16_t> m_1s;
    uint8_t m_is_channel_on = 0x3f;
    uint8_t m_is_1s_on = 0x3f;
    uint16_t m_is_powered = IS_NOT_POWERED;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Wait_and_param_for_cyclogram
{
    std::vector<uint16_t> m_do_mpi_command_in_cyclogram;
    std::vector<uint16_t> m_do_cyclogram_in_tp;
    std::vector<uint16_t> m_count_to_do_cyclogram_in_tp;

    std::vector<std::vector<uint64_t>> m_sleep_to_command_in_do_cyclogram;

    std::vector<uint16_t> m_do_cyclogram_in_ai;
    std::vector<std::vector<uint16_t>> m_do_cyclogram_in_do;

    std::vector<std::vector<uint16_t>> m_do_in_power_cycl;
    std::map<uint16_t, int32_t> m_wait_time_for_cyclogram;
    int16_t m_count_cyclogram_technical_run = 2;
    std::vector<std::array<uint16_t, constants::max_count_param>> m_param_for_run_a_lot;
    int16_t m_count_do_dtmi_in_state_off = 2;
    int16_t m_shift_bshv = 100;
    std::vector<QString> m_is_error;
    uint16_t m_skip_fails_for_continue = 1;
    uint16_t m_off_power_for_tp = 0;

    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t >> m_mpi_command;
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t >> m_mpi_other_command;
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t cound_do_cyclogram, uint16_t parametr)>, QString, uint16_t>> m_cyclograms_tp;
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t >> m_cyclograms_state_work;
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>> m_cyclograms_ai;
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>> m_cyclograms_ri;

    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t >> m_cyclograms_power;
    std::vector<std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>>> m_command_do_in_cycl_power;

    std::vector<std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>>> m_command_cycl_do;

    std::vector<std::tuple<QString, QString, uint16_t, uint16_t>> m_commands_to_pn;


};
#pragma pack(pop)

struct Kia_protocol_parametrs
{
    int16_t num_mpi_command = -1;
    uint16_t num_bokz;
    QString data_to_out;
    uint16_t type_window;
    uint16_t type_protocol;
    uint16_t parametr = EP_DOALL;

}; Q_DECLARE_METATYPE(Kia_protocol_parametrs)

struct Kia_frame_parametrs
{
    uint16_t num_bokz;
    int32_t bshv;
    uint32_t resulution;
    void* lvp_buf;
    uint32_t buf_size;

}; Q_DECLARE_METATYPE(Kia_frame_parametrs)


#pragma pack(push, 1)
struct Kia_settings
{
    Kia_settings()
    {

        m_data_for_db.reset(new Data_for_db());
        m_flags_for_thread.reset(new Flags_for_thread());
        m_data_to_protocols.reset(new Data_to_protocols());
        m_data_for_bi.reset(new Data_for_bi());
    }
    std::shared_ptr<Data_for_db> m_data_for_db;
    std::shared_ptr<Flags_for_thread> m_flags_for_thread;
    std::shared_ptr<Data_to_protocols> m_data_to_protocols;
    Format_for_description m_format_for_desc;
    std::shared_ptr<Data_for_bi> m_data_for_bi;
    Frame_settings m_frame_settings;
    uint16_t m_type_bokz;
    uint16_t m_type_bi;
    uint16_t m_timer_interval;
    int m_count_bokz;//0 - БОКЗМ60; 1 - БОКЗМ60/1000; 2 - БОКЗМР; 3 - АИС-2К; 4 - БОКЗНК.
    int m_freq_bokz;
    uint16_t m_is_con_to_internet = CS_IS_OFF;
    uint16_t m_is_con_to_tg = CS_IS_OFF;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Kia_data
{
    Kia_data()
    {
        m_data_mpi.reset(new Data_for_mpi());
        m_data_db.reset(new Data_for_db());
        m_data_bi.reset(new Data_for_bi());
        m_data_bokz.reset(new Data_for_bokz());
    }
    std::shared_ptr<Data_for_mpi> m_data_mpi;
    std::shared_ptr<Data_for_db> m_data_db;
    std::shared_ptr<Data_for_bi> m_data_bi;
    std::shared_ptr<Data_for_bokz> m_data_bokz;
}; Q_DECLARE_METATYPE(Kia_data)
#pragma pack(pop)

#pragma pack(push, 1)
struct Kia_data_cyclogram
{
    Kia_data_cyclogram()
    {
        m_wait_and_param_for_cyclogram.reset(new Wait_and_param_for_cyclogram());
    }
    std::shared_ptr<Wait_and_param_for_cyclogram> m_wait_and_param_for_cyclogram;
};
#pragma pack(pop)
#endif // MAINSTRUCT_H
