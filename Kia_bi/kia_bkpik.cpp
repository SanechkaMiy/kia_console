#include "kia_bkpik.h"

Kia_bkpik::Kia_bkpik(uint16_t num_bi, shared_ptr<WorkWithStruct> wws,
                     std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
                     shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings) :
    m_wws(wws)
  , m_kia_db(kia_db)
  , m_kia_protocol(kia_protocol)
  , m_kia_settings(kia_settings)
{
    m_num_bi = num_bi;
    set_bkpik_settings();
    std::cout << "num port " << m_kia_settings->m_data_for_bi->m_num_bi[m_num_bi] << std::endl;
    m_serial_port.reset(new mn::CppLinuxSerial::SerialPort("/dev/ttyS" + to_string(m_kia_settings->m_data_for_bi->m_num_bi[m_num_bi]), mn::CppLinuxSerial::BaudRate::B_9600));
    //serialPort->SetTimeout(100); // Block for up to 100ms to receive data
    m_serial_port->Open();
    std::vector<uint8_t> commandBKC = {0xf1};//
    m_serial_port->WriteBinary(commandBKC);
    std::vector<uint8_t> m_commandToCom = {0x9};
    m_serial_port->WriteBinary(m_commandToCom);
    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bokz->m_count_bokz; ++num_ch)
        on_1s_bi(num_ch, num_ch);
    start_1s_mark_bkpik();
}

Kia_bkpik::~Kia_bkpik()
{
    m_serial_port->Close();
}



void Kia_bkpik::change_command_bkpik(std::vector<uint8_t> command)
{
    std::vector<uint8_t> m_commandToCom = {0x9};
    m_serial_port->WriteBinary(m_commandToCom);
    m_serial_port->WriteBinary(command);
    std::vector<uint8_t> m_commandToCicle = {0x8};
    m_serial_port->WriteBinary(m_commandToCicle);
    is_change_state = 0;
    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bokz->m_count_bokz; num_ch++)
    {
        switch(((m_kia_data->m_data_bi->m_is_1s_on >> (num_ch * 2)) & 0x0003))
        {
        case BIS1M_BOTH_OFF:
            m_kia_data->m_data_bi->m_1s[num_ch] = BIS1M_BOTH_OFF;
            break;
        case BIS1SM_MAIN_ON:
            m_kia_data->m_data_bi->m_1s[num_ch] = BIS1SM_MAIN_ON;
            break;
        case BIS1SM_REZERV_ON:
            m_kia_data->m_data_bi->m_1s[num_ch] = BIS1SM_REZERV_ON;
            break;
        case BIS1SM_BOTH_ON:
            m_kia_data->m_data_bi->m_1s[num_ch] = BIS1SM_BOTH_ON;
            break;
        }
    }
}

void Kia_bkpik::start_1s_mark_bkpik()
{
    m_start_1s_mark = std::async([this]()
    {
        m_stop_1s_mark = true;
        QStringList empty_list;
        // set real-time priority
        struct sched_param schedparm;
        memset(&schedparm, 0, sizeof(schedparm));
        schedparm.sched_priority = 99; // highest rt priority
        sched_get_priority_max(99);
        sched_setscheduler(0, SCHED_FIFO, &schedparm);
        // set timer slack equal to 1 nanosecond
        prctl(PR_SET_TIMERSLACK, 1);
        uint16_t command_size = 4;
        std::vector<uint8_t> buffer;
        is_change_state = 0;
        while (m_stop_1s_mark)
        {
            std::vector<uint8_t> commandR;
            m_serial_port->ReadBinary(commandR);
            if (is_change_state > 0)
            {
                for (auto &el : commandR)
                {
                    buffer.push_back(el);
                }
                commandR.clear();
                while (buffer.size() >= command_size)
                {
                    m_kia_data->m_data_bi->m_commandR = buffer;
                    m_kia_data->m_data_bi->m_commandR.resize(command_size);
                    m_count++;
                    m_cv.notify_all();
                    m_kia_data->m_data_db->m_datetime = m_wws->currentDateTime();
                    send_telemetry();
                    m_parser_db->send_to_bkpik(m_num_bi);
                    buffer.erase(buffer.begin(), buffer.begin() + command_size);
                }
            }
            else
                commandR.clear();
            is_change_state++;
        }
    });
}

void Kia_bkpik::stop_1s_mark()
{
    m_stop_1s_mark = false;
    m_start_1s_mark.get();
}

void Kia_bkpik::send_telemetry()
{

    QStringList data_for_client;
    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bokz->m_count_bokz; ++num_ch)
    {
        data_for_client.push_back(QString::number(m_num_bi));
        data_for_client.push_back(QString::number(num_ch));
        data_for_client.push_back(QString::number(m_kia_data->m_data_bi->m_kp[num_ch]));
        data_for_client.push_back(QString::number(m_kia_data->m_data_bi->m_kc[num_ch]));
        data_for_client.push_back(QString::number(m_kia_data->m_data_bi->m_td[num_ch]));
        data_for_client.push_back(QString::number(m_kia_data->m_data_bi->m_1s[num_ch]));
        emit send_to_client(SEND_DATA_TO_STATE_WINDOW, data_for_client);
        data_for_client.clear();
    }
    m_kia_data->m_data_db->data = QString('\\') + QString('\\') + "x";
    for (unsigned int i = 0; i < m_kia_data->m_data_bi->m_commandR.size(); i++)
    {
        m_kia_data->m_data_db->data = m_kia_data->m_data_db->data + QString("%1").arg(QString::number(m_kia_data->m_data_bi->m_commandR[i], 16), 4, '0').toUpper();
    }
}

void Kia_bkpik::wait_for_event()
{
    std::mutex m;
    std::unique_lock lk(m);
    auto mw_count = m_count;
    m_cv.wait(lk, [this, &mw_count]
    {
        return mw_count != m_count;
    });
}

void Kia_bkpik::stop_event()
{

}

void Kia_bkpik::set_relay_command(uint16_t relay_command)
{

}

void Kia_bkpik::set_relay_polarity(uint16_t relay_command)
{

}

void Kia_bkpik::set_relay_command_pulse_time(uint16_t relay_command)
{

}

void Kia_bkpik::set_bkpik_settings()
{
    m_kia_data.reset(new Kia_data());
    m_kia_data->m_data_bi->m_term_group.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    std::fill(m_kia_data->m_data_bi->m_term_group.begin(), m_kia_data->m_data_bi->m_term_group.end(), 1);
    m_kia_data->m_data_bi->m_1s.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    m_kia_data->m_data_bi->m_kc.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    m_kia_data->m_data_bi->m_kp.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    m_kia_data->m_data_bi->m_td.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);

    m_kia_db[TYPE_RAW]->add_device_to_experiment(m_kia_settings->m_data_for_db->m_type_bi[m_kia_settings->m_type_bi], m_num_bi);

    m_parser_db.reset(new ParseToDB(m_kia_db, m_kia_data, m_kia_settings));
}


void Kia_bkpik::on_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Включаем питание ");
    m_off_1_ch = 0x00;
    std::vector<uint8_t> on_power_arr = {0x3c, 0x33, 0xcf};
    if (off_1_ch != 0)
    {
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на основной канал "));
        else
            str_info_1s.push_back(QString("на резервный канал "));
        m_off_1_ch = m_off_1_ch | (0x01 << (num_channel * 2 + off_1_ch - 1));
    }
    str_info_1s.push_back("для канала №" + QString::number(num_channel + 1) + "\n");
    //m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_kia_data->m_data_bi->m_is_channel_on = m_kia_data->m_data_bi->m_is_channel_on & (on_power_arr[num_channel] | m_off_1_ch);
    change_command_bkpik({0x01, m_kia_data->m_data_bi->m_is_channel_on});//0x3c для БОКЗ М60; 0x33 для БОКЗ М60/1000
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}

void Kia_bkpik::off_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Выключаем питание ");
    m_off_1_ch = 0x3f;
    std::vector <uint8_t> off_power_arr = {0x03, 0x0c, 0x30};
    if (off_1_ch != 0)
    {
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на основной канал "));
        else
            str_info_1s.push_back(QString("на резервный канал "));
        m_off_1_ch = m_off_1_ch & ~(0x01 << (num_channel * 2 + off_1_ch - 1));
    }
    str_info_1s.push_back("для канала №" + QString::number(num_channel + 1) + "\n");
    //m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_kia_data->m_data_bi->m_is_channel_on = m_kia_data->m_data_bi->m_is_channel_on | (off_power_arr[num_channel] & m_off_1_ch);
    change_command_bkpik({0x01, m_kia_data->m_data_bi->m_is_channel_on});
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}

void Kia_bkpik::on_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Включаем секундную метку ");
    m_off_1_ch = 0x00;
    std::vector<uint8_t> on_power_arr = {0x3c, 0x33, 0xcf};
    if (off_1_ch != 0)
    {
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на основной канал "));
        else
            str_info_1s.push_back(QString("на резервный канал "));
        m_off_1_ch = m_off_1_ch | (0x01 << (num_channel * 2 + off_1_ch - 1));
    }
    str_info_1s.push_back("для канала №" + QString::number(num_channel + 1) + "\n");
    //m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_kia_data->m_data_bi->m_is_1s_on = m_kia_data->m_data_bi->m_is_1s_on & (on_power_arr[num_channel] | m_off_1_ch);
    printf("on %04x\n", m_kia_data->m_data_bi->m_is_1s_on);
    change_command_bkpik({0x02, m_kia_data->m_data_bi->m_is_1s_on});//0x3c для БОКЗ М60; 0x33 для БОКЗ М60/1000
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}

void Kia_bkpik::off_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Выключаем секундную метку ");
    m_off_1_ch = 0x3f;
    std::vector <uint8_t> off_power_arr = {0x03, 0x0c, 0x30};
    if (off_1_ch != 0)
    {
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на основной канал "));
        else
            str_info_1s.push_back(QString("на резервный канал "));
        m_off_1_ch = m_off_1_ch & ~(0x01 << (num_channel * 2 + off_1_ch - 1));
    }
    str_info_1s.push_back("для прибора №" + QString::number(num_channel + 1) + "\n");
    //m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_kia_data->m_data_bi->m_is_1s_on = m_kia_data->m_data_bi->m_is_1s_on | (off_power_arr[num_channel] & m_off_1_ch);
    printf("off %04x\n", m_kia_data->m_data_bi->m_is_1s_on);
    change_command_bkpik({0x02, m_kia_data->m_data_bi->m_is_1s_on});
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}

void Kia_bkpik::on_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    std::vector <uint8_t> on_imitator = {0x15, 0x25, 0x35};
    change_command_bkpik({on_imitator[num_channel], 0x00});
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}

void Kia_bkpik::off_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    std::vector <uint8_t> off_imitator = {0x15, 0x25, 0x35};
    change_command_bkpik({off_imitator[num_channel], 0xff});
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}

void Kia_bkpik::on_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();

    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}

void Kia_bkpik::off_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();

    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
}


std::condition_variable &Kia_bkpik::getEvent()
{
    return m_cv;
}

int64_t Kia_bkpik::inSleep()
{
    return m_count;
}
