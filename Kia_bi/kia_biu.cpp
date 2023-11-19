#include "kia_biu.h"

Kia_biu::Kia_biu(uint16_t num_bi, shared_ptr<WorkWithStruct> wws, std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
                 shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings) :
    m_wws(wws)
  , m_kia_db(kia_db)
  , m_kia_protocol(kia_protocol)
  , m_kia_settings(kia_settings)
{
    m_num_bi = num_bi;
    set_bi_settings();
    init_bi();
    get_synch_status();
    get_relay_command_pulse_time();
    for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]; ++num_ch)
    {
        on_1s_bi(num_ch, num_ch);
    }
    set_sinchronize_event();
    set_sec_mark_pulse_time(50);
    start_1s_mark();
}


std::vector<int64_t> m_count(constants::max_count_bi);
std::vector<std::condition_variable> m_cv(constants::max_count_bi);
std::vector<std::mutex> m(constants::max_count_bi);


void Kia_biu::set_sec_mark_period(uint16_t sec_mark_period)
{

    int16_t (*set_period)(int16_t, uint16_t);
    set_period = (int16_t(*)(int16_t, uint16_t))dlsym(m_handle,"SetSecMarkPeriod");
    printf("SetSecMarkPeriod: %d\n", (*set_period)(m_device_id, sec_mark_period));
}

void Kia_biu::wait_for_event()
{
    std::mutex m;
    std::unique_lock lk(m);
    auto mw_count = m_count[m_num_bi];
    m_cv[m_num_bi].wait(lk, [this, &mw_count]
    {
        return mw_count != m_count[m_num_bi];
    });
}

void Kia_biu::stop_event()
{
    std::lock_guard lock(m[m_num_bi]);
    m_count[m_num_bi]++;
    m_cv[m_num_bi].notify_all();
}

void Kia_biu::set_relay_command(uint16_t relay_command)
{
    //set_relay_polarity(TP_NEG);
    //set_relay_command_pulse_time(100);
    int16_t (*set_relay_com)(int16_t,uint16_t);
    set_relay_com = (int16_t(*)(int16_t,uint16_t))dlsym(m_handle,"SetRelayCommand");
    printf("SetRelayCommand: %d\n", (*set_relay_com)(m_device_id, relay_command));
}

void Kia_biu::set_relay_polarity(uint16_t relay_command)
{
    int16_t (*set_relay_pol)(int16_t,uint16_t);
    set_relay_pol = (int16_t(*)(int16_t,uint16_t))dlsym(m_handle,"SetRelayPolarity");
    printf("SetRelayPolarity: %d\n", (*set_relay_pol)(m_device_id, relay_command));
    get_relay_polarity();
}

void Kia_biu::set_relay_command_pulse_time(uint16_t relay_command)
{
    int16_t (*set_relay_pul_time)(int16_t,uint16_t);
    set_relay_pul_time = (int16_t(*)(int16_t,uint16_t))dlsym(m_handle,"SetRelayCommandPulseTime");
    printf("SetRelayCommandPulseTime: %d\n", (*set_relay_pul_time)(m_device_id, relay_command));
    get_relay_command_pulse_time();
}

void Kia_biu::wait_1s_biu_0()
{
    std::lock_guard lock(m[0]);
    m_count[0]++;
    m_cv[0].notify_all();
}

void Kia_biu::wait_1s_biu_1()
{
    std::lock_guard lock(m[1]);
    m_count[1]++;
    m_cv[1].notify_all();
}

void Kia_biu::wait_1s_biu_2()
{
    std::lock_guard lock(m[2]);
    m_count[2]++;
    m_cv[2].notify_all();
}

void Kia_biu::wait_1s_biu_3()
{
    std::lock_guard lock(m[3]);
    m_count[3]++;
    m_cv[3].notify_all();
}

void Kia_biu::wait_1s_biu()
{

}

void Kia_biu::get_relay_polarity()
{
    uint16_t relay_command = 0x0000;
    int16_t (*get_relay_pol)(int16_t,uint16_t*);
    get_relay_pol = (int16_t(*)(int16_t,uint16_t*))dlsym(m_handle,"GetRelayPolarity");
    printf("GetRelayPolarity: %d\n", (*get_relay_pol)(m_device_id, &relay_command));
    printf("%04x\n", relay_command);
}

void Kia_biu::get_relay_command_pulse_time()
{
    uint16_t relay_command = 0x0000;
    int16_t (*get_relay_pul_time)(int16_t,uint16_t*);
    get_relay_pul_time = (int16_t(*)(int16_t,uint16_t*))dlsym(m_handle,"GetRelayCommandPulseTime");
    printf("GetRelayCommandPulseTime: %d\n", (*get_relay_pul_time)(m_device_id, &relay_command));
    printf("%d\n", relay_command);
}

void Kia_biu::parse_data(uint16_t num_ch, DevTelemetry *dev_tel)
{
    m_td_on_ch[num_ch].clear();
    m_td_on_ch[num_ch].push_back(dev_tel->Temperature1g1);
    m_td_on_ch[num_ch].push_back(dev_tel->Temperature1g2);
    m_td_on_ch[num_ch].push_back(dev_tel->Temperature1g3);
    m_td_on_ch[num_ch].push_back(dev_tel->Temperature1g4);
    m_td_on_ch[num_ch].push_back(dev_tel->Temperature1g5);
    m_td_on_ch[num_ch].push_back(dev_tel->Temperature1g6);
    m_kia_data->m_data_bi->m_kc[num_ch] = dev_tel->LinkControl;

    m_kia_data->m_data_bi->m_kp[num_ch] = dev_tel->PrimaryPower;

    m_kia_data->m_data_bi->m_td[num_ch] = m_td_on_ch[num_ch][m_kia_data->m_data_bi->m_term_group[num_ch] - 1];

    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->PowerVoltageRaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->VIPVoltageRaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->DeviceFider1ARaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->DeviceFider2ARaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->ImitatorFider1ARaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->ImitatorFider2ARaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->Temperature1Raw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->Temperature2Raw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->Temperature3Raw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->Temperature4Raw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->DeviceVoltage1ARaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->DeviceVoltage2ARaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->ImitatorVoltage1ARaw);
    m_kia_data->m_data_bi->m_raw_data.push_back(dev_tel->ImitatorVoltage2ARaw);

    m_kia_data->m_data_db->data = QString('\\') + QString('\\') + "x";
    for (unsigned int i = 0; i < m_kia_data->m_data_bi->m_raw_data.size(); i++)
    {
        m_kia_data->m_data_db->data = m_kia_data->m_data_db->data + QString("%1").arg(QString::number(m_kia_data->m_data_bi->m_raw_data[i], 16), 4, '0').toUpper();
    }
}

void Kia_biu::set_bi_settings()
{

    m_kia_data.reset(new Kia_data());
    m_kia_data->m_data_bi->m_term_group.resize(m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]);
    std::fill(m_kia_data->m_data_bi->m_term_group.begin(), m_kia_data->m_data_bi->m_term_group.end(), 1);
    m_kia_data->m_data_bi->m_1s.resize(m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]);
    m_kia_data->m_data_bi->m_kc.resize(m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]);
    m_kia_data->m_data_bi->m_kp.resize(m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]);
    m_kia_data->m_data_bi->m_td.resize(m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]);
    m_td_on_ch.resize(m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi]);

    m_kia_db[TYPE_RAW]->add_device_to_experiment(m_kia_settings->m_data_for_db->m_type_bi[m_kia_settings->m_type_bi], m_num_bi);
    m_parser_db.reset(new ParseToDB(m_kia_db, m_kia_data, m_kia_settings));
}

Kia_biu::~Kia_biu()
{
    close_bi();
}

uint16_t Kia_biu::init_bi()
{
    int16_t (*setSerialPrefix)(char*);
    int16_t (*init)(void);
    int16_t (*getDeviceID)(uint16_t);
    int16_t (*config)(int16_t);
    m_handle = dlopen ("/usr/local/lib/BiLib_20230914_1659/BiLibNE.so", RTLD_LAZY);
    setSerialPrefix = (int16_t(*)(char*))dlsym(m_handle, "SetSerialPrefix");
    printf("setSerialPrefix: %d\n", (*setSerialPrefix)("BI_U"));
    init = (int16_t(*)(void))dlsym(m_handle, "Init");
    m_count_dev = (*init)();
    auto result =  m_count_dev;
    printf("Init: %d\n", m_count_dev);

    if (!m_handle) {
        printf("have problem!");
    }

    getDeviceID = (int16_t(*)(uint16_t))dlsym(m_handle, "GetDeviceID");
    m_device_id = (*getDeviceID)(m_num_bi);
    m_kia_settings->m_data_for_bi->m_num_bi[m_num_bi] = m_device_id;
    printf("GetDeviceID: %d\n", m_device_id);
    config = (int16_t(*)(int16_t))dlsym(m_handle, "Config");
    printf("Config: %d\n", (*config)(m_device_id));

    get_master_state();

    m_devTel_1 = new DevTelemetry();
    m_devTel_2 = new DevTelemetry();

    return result;
}

void Kia_biu::set_sinchronize_event()
{
    switch(m_num_bi)
    {
    case 0:
        m_func = &Kia_biu::wait_1s_biu_0;
        break;
    case 1:
        m_func = &Kia_biu::wait_1s_biu_1;
        break;
    case 2:
        m_func = &Kia_biu::wait_1s_biu_2;
        break;
    case 3:
        m_func = &Kia_biu::wait_1s_biu_3;
        break;
    };
    int16_t (*set_sinch_event)(int16_t, void (Kia_biu::*)());
    set_sinch_event = (int16_t(*)(int16_t, void (Kia_biu::*)()))dlsym(m_handle, "SetSinchronizeEvent");
    printf("SinchronizeEvent: %d\n", (*set_sinch_event)(m_device_id, m_func));

}

void Kia_biu::get_master_state()
{
    int16_t (*getMasterState)(int16_t);
    getMasterState = (int16_t(*)(int16_t))dlsym(m_handle,"GetMasterState");
    (*getMasterState)(m_device_id);
}

void Kia_biu::start_1s_mark()
{
    m_start_1s_mark = std::async([this]
    {
        m_stop_1s_mark = true;
        // set real-time priority
        struct sched_param schedparm;
        memset(&schedparm, 0, sizeof(schedparm));
        schedparm.sched_priority = 99; // highest rt priority
        sched_get_priority_max(99);
        sched_setscheduler(0, SCHED_FIFO, &schedparm);
        // set timer slack equal to 1 nanosecond
        prctl(PR_SET_TIMERSLACK, 1);
        //SimpleTimer st("biu");
        while(m_stop_1s_mark)
        {
            //st.start();
            wait_for_event();
            if (m_stop_1s_mark)
            {
                m_kia_data->m_data_db->m_datetime = m_wws->currentDateTime();
                get_sec_mark_telemetry();
                send_telemetry();
                m_parser_db->send_to_bi(m_num_bi);
            }
            //st.end();
        }
    });
}

void Kia_biu::stop_1s_mark()
{
    stop_event();
    m_stop_1s_mark = false;
    m_start_1s_mark.get();
}

void Kia_biu::send_telemetry()
{
    m_kia_data->m_data_bi->m_raw_data.clear();
    parse_data(0, m_devTel_1);
    parse_data(1, m_devTel_2);
    preset_telemetry(0, m_devTel_1);
    preset_telemetry(1, m_devTel_2);

}

void Kia_biu::preset_telemetry(uint16_t num_ch, struct DevTelemetry* dev_tel)
{

    QStringList data_for_client;
    data_for_client.push_back(QString::number(m_num_bi));
    data_for_client.push_back(QString::number(num_ch));
    data_for_client.push_back(QString::number(m_device_id));
    data_for_client.push_back(QString::number(dev_tel->LinkControl));
    data_for_client.push_back(QString::number(dev_tel->Consumption));
    data_for_client.push_back(QString::number(dev_tel->ProtectionModule));
    data_for_client.push_back(QString::number(dev_tel->PrimaryPower));
    data_for_client.push_back(QString::number(dev_tel->SecondaryPower));
    data_for_client.push_back(QString::number(dev_tel->PowerVoltage));
    data_for_client.push_back(QString::number(dev_tel->VIPVoltage));
    data_for_client.push_back(QString::number(dev_tel->DeviceFider1A));
    data_for_client.push_back(QString::number(dev_tel->DeviceFider2A));
    data_for_client.push_back(QString::number(dev_tel->ImitatorFider1A));
    data_for_client.push_back(QString::number(dev_tel->ImitatorFider2A));
    QString td;
    if (dev_tel->Temperature1Raw == 0x7fff)
        td = "---";
    else
        td = QString::number(m_td_on_ch[num_ch][m_kia_data->m_data_bi->m_term_group[num_ch] - 1]);
    data_for_client.push_back(td);
    data_for_client.push_back(QString::number(m_kia_data->m_data_bi->m_1s[num_ch]));
    for (uint16_t num_data = 1; num_data < 6; ++num_data)
    {
        if (data_for_client[num_data + 2] == "0")
            data_for_client[num_data + 2] = "нет";
        else
            data_for_client[num_data + 2] = "есть";
    }
    emit send_to_client(SEND_DATA_TO_STATE_WINDOW, data_for_client);
    data_for_client.clear();
}

void Kia_biu::set_power(uint16_t command)
{
    int16_t (*setPowerStatus)(int32_t,uint16_t);
    setPowerStatus = (int16_t(*)(int32_t,uint16_t))dlsym(m_handle,"SetPowerStatus");
    (*setPowerStatus)(m_device_id, command);
}

void Kia_biu::get_power(uint16_t status_power)
{
    int16_t (*getPowerStatus)(int32_t,uint16_t*);
    getPowerStatus = (int16_t(*)(int32_t,uint16_t*))dlsym(m_handle,"GetPowerStatus");
    (*getPowerStatus)(m_device_id, &status_power);
}

void Kia_biu::set_synch_status(uint16_t synch_status)
{
    int16_t (*set_synch)(int16_t,uint16_t);
    set_synch = (int16_t(*)(int16_t,uint16_t))dlsym(m_handle,"SetSynchStatus");
    printf("SetSynchStatus: %d\n", (*set_synch)(m_device_id, synch_status));
}

void Kia_biu::get_synch_status()
{
    uint16_t synch_status = 100;
    int16_t (*get_synch)(uint16_t, uint16_t*);
    get_synch = (int16_t(*)(uint16_t, uint16_t*))dlsym(m_handle,"GetSynchStatus");
    auto out = (*get_synch)(m_device_id, &synch_status);
    printf("get_synch %d\n", out);
    printf("get_ synch_status %d\n", synch_status);
}

void Kia_biu::set_sec_mark_pulse_time(uint16_t sec_mark_pulse_time)
{
    int16_t (*set_sec_mark_pulse_t)(int16_t,uint16_t);
    set_sec_mark_pulse_t = (int16_t(*)(int16_t,uint16_t))dlsym(m_handle,"SetSecMarkPulseTime");
    (*set_sec_mark_pulse_t)(m_device_id, sec_mark_pulse_time);
    printf("SetSecMarkPulseTime: %d\n", (*set_sec_mark_pulse_t)(m_device_id, sec_mark_pulse_time));
}

void Kia_biu::get_sec_mark_telemetry()
{
    int16_t (*getSecTelemetry)(int16_t, DevTelemetry*, DevTelemetry*);
    getSecTelemetry = (int16_t(*)(int16_t, DevTelemetry*, DevTelemetry*))dlsym(m_handle,"GetSecMarkTelemetry");
    (*getSecTelemetry)(m_device_id, m_devTel_1, m_devTel_2);

    //printf("GetSecMarkTelemetry: %d\n", );
    //        printf("LinkControl: %d\n", m_devTel_1->LinkControl);
    //        printf("Consumption: %d\n", m_devTel_1->Consumption);
    //        printf("ProtectionModule: %d\n", m_devTel_1->ProtectionModule);
    //        printf("SecondaryPower: %d\n", m_devTel_1->SecondaryPower);
    //        printf("PrimaryPower: %d\n", m_devTel_1->PrimaryPower);
    //        printf("SecondaryPower: %d\n", m_devTel_1->SecondaryPower);

    //        printf("Temperature1g1: %f\n", m_devTel_2->Temperature1g1);
    //        printf("Temperature2g1: %f\n", m_devTel_2->Temperature2g1);
    //        printf("Temperature3g1: %f\n", m_devTel_2->Temperature3g1);
    //        printf("Temperature4g1: %f\n", m_devTel_2->Temperature4g1);
    //        printf("Temperature1Raw: %i\n", m_devTel_1->Temperature1Raw);
    //        printf("DeviceFider1A %f\n", m_devTel_1->DeviceFider1A);
    //        printf("DeviceFider2A %f\n", m_devTel_1->DeviceFider2A);
    //        printf("ImitatorFider1A %f\n", m_devTel_1->ImitatorFider1A);
    //        printf("ImitatorFider2A %f\n", m_devTel_1->ImitatorFider2A);

    //        printf("Temperature1g1: %f\n", m_devTel_2->Temperature1g1);
    //        printf("Temperature2g1: %f\n", m_devTel_2->  Temperature2g1);
    //        printf("Temperature3g1: %f\n", m_devTel_2->Temperature3g1);
    //        printf("Temperature4g1: %f\n", m_devTel_2->Temperature4g1);
    //        printf("Temperature1Raw: %i\n", m_devTel_2->Temperature1Raw);
    //        printf("DeviceFider1A %f\n", m_devTel_2->DeviceFider1A);
    //        printf("DeviceFider2A %f\n", m_devTel_2->DeviceFider2A);
    //        printf("ImitatorFider1A %f\n", m_devTel_2->ImitatorFider1A);
    //        printf("ImitatorFider2A %f\n", m_devTel_2->ImitatorFider2A);
    //        printf("DeviceVoltage1A %f\n", m_devTel_1->DeviceVoltage1A);
    //        printf("PowerVoltage %f\n", m_devTel_1->PowerVoltage);
}

void Kia_biu::get_telemetry()
{
    int16_t (*getTelemetry)(int16_t, DevTelemetry*, DevTelemetry*);
    getTelemetry = (int16_t(*)(int16_t, DevTelemetry*, DevTelemetry*))dlsym(m_handle,"GetTelemetry");
    printf("getTel %d\n", (*getTelemetry)(m_device_id, m_devTel_1, m_devTel_2));
    std::cout << m_devTel_1->Temperature1Ohm << std::endl;
}

void Kia_biu::get_sec_mark_status(uint16_t sec_mark_status)
{
    int16_t (*get_sec_mark)(int16_t, uint16_t*);
    get_sec_mark = (int16_t(*)(int16_t, uint16_t*))dlsym(m_handle,"GetSecMarkStatus");
    (*get_sec_mark)(m_device_id, &sec_mark_status);
    //printf("%04x\n", m_kia_data->m_data_bi->m_sec_mark_status);

}

void Kia_biu::set_sec_mark_status(uint16_t &num_ch, uint16_t sec_mark_status)
{
    int16_t (*set_synch)(int16_t,uint16_t);
    set_synch = (int16_t(*)(int16_t,uint16_t))dlsym(m_handle,"SetSecMarkStatus");
    (*set_synch)(m_device_id, sec_mark_status);
    printf("SetSecMarkStatus: %d\n", (*set_synch)(m_device_id, sec_mark_status));
    switch(((sec_mark_status >> (num_ch * 2)) & 0x0003))
    {
    case BIS1M_BOTH_OFF:
        m_kia_data->m_data_bi->m_1s[num_ch] = BIS1SM_BOTH_ON;
        break;
    case BIS1SM_MAIN_ON:
        m_kia_data->m_data_bi->m_1s[num_ch] = BIS1SM_REZERV_ON;
        break;
    case BIS1SM_REZERV_ON:
        m_kia_data->m_data_bi->m_1s[num_ch] = BIS1SM_MAIN_ON;
        break;
    case BIS1SM_BOTH_ON:
        m_kia_data->m_data_bi->m_1s[num_ch] = BIS1M_BOTH_OFF;
        break;
    }
}

uint16_t Kia_biu::close_bi()
{
    int16_t (*done)(int16_t);
    done = (int16_t(*)(int16_t))dlsym(m_handle, "Done");
    printf("Done: %d\n", (*done)(m_device_id));
    int16_t (*close)(void);
    close = (int16_t(*)(void))dlsym(m_handle, "Close");
    auto result = (*close)();
    printf("Close: %d\n", result);
    dlclose(m_handle);
    return result;
}

void Kia_biu::on_power_bi(uint16_t& num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    get_power(m_power_status);
    printf("power_status %04x\n", m_power_status);
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Включаем питание ");
    std::vector<uint16_t> on_power_arr = {0x0306, 0x3060};
    m_off_1_ch = 0xffff;
    if (off_1_ch != 0)
    {
        m_off_1_ch = 0x0000;
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на основной канал "));
        else
            str_info_1s.push_back(QString("на резервный канал "));
        m_off_1_ch = m_off_1_ch | (0x0102 << (num_channel * 4 + off_1_ch - 1));
    }
    str_info_1s.push_back("для канала №" + QString::number(num_channel + 1) + "\n");
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_power_status = m_power_status | (on_power_arr[num_channel] & m_off_1_ch);
    set_power(m_power_status);
}

void Kia_biu::off_power_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    get_power(m_power_status);
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Выключаем питание ");
    std::vector<uint16_t> off_power_arr = {0xfcf9, 0xcf9f};
    m_off_1_ch = 0x0000;
    if (off_1_ch != 0)
    {
        m_off_1_ch = 0xffff;
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на резервный канал "));
        else
            str_info_1s.push_back(QString("на основной канал "));
        m_off_1_ch = m_off_1_ch & (0x0204 << (num_channel * 4 + off_1_ch - 1));
    }
    str_info_1s.push_back("для канала №" + QString::number(num_channel + 1) + "\n");
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_power_status = m_power_status & (off_power_arr[num_channel] | m_off_1_ch);
    set_power(m_power_status);
}

void Kia_biu::on_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    get_sec_mark_status(m_sec_mark_status);
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Включаем секундную метку ");
    m_off_1_ch = 0xffff;
    std::vector<uint16_t> on_1s = {0x0003, 0x000c};
    if (off_1_ch != 0)
    {
        m_off_1_ch = 0x0000;
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на основной канал "));
        else
            str_info_1s.push_back(QString("на резервный канал "));
        m_off_1_ch = m_off_1_ch | (0x01 << (num_channel * 2 + off_1_ch - 1));
    }
    str_info_1s.push_back("для канала №" + QString::number(num_channel + 1) + "\n");
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_sec_mark_status = m_sec_mark_status | (on_1s[num_channel] & m_off_1_ch);
    printf("%04x\n", m_sec_mark_status);
    set_sec_mark_status(num_channel, m_sec_mark_status);
}

void Kia_biu::off_1s_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    get_sec_mark_status(m_sec_mark_status);
    QString str_info_1s = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Выключаем секундную метку ");
    std::vector<uint16_t> off_1s = {0x000c, 0x0003};
    m_off_1_ch = 0x0000;
    if (off_1_ch != 0)
    {
        m_off_1_ch = 0x0000;
        if (off_1_ch == 1)
            str_info_1s.push_back(QString("на основной канал "));
        else
            str_info_1s.push_back(QString("на резервный канал "));
        m_off_1_ch = ~(m_off_1_ch | (0x01 << (num_channel * 2 + off_1_ch - 1)));
    }
    str_info_1s.push_back("для канала №" + QString::number(num_channel + 1) + "\n");
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, str_info_1s, parametr);
    m_sec_mark_status = m_sec_mark_status & (off_1s[num_channel] | m_off_1_ch);
    set_sec_mark_status(num_channel, m_sec_mark_status);
}

void Kia_biu::on_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    get_power(m_power_status);
    std::vector<uint16_t> on_power_arr = {0x0C09, 0xC090};
    m_power_status = m_power_status | (on_power_arr[num_channel]);
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                                              + QString("Включаем имитатор для канала №") + QString::number(num_channel + 1) + "\n", parametr);
    set_power(m_power_status);
}

void Kia_biu::off_imitator_bi(uint16_t &num_bokz, uint16_t &num_channel, uint16_t off_1_ch, uint16_t parametr)
{
    get_power(m_power_status);
    std::vector<uint16_t> off_power_arr = {0xf3f6, 0x3f6f};
    m_power_status = m_power_status & (off_power_arr[num_channel]);
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                                              + QString("Выключаем имитатор для канала №") + QString::number(num_channel + 1) + "\n", parametr);
    set_power(m_power_status);
}

void Kia_biu::on_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr)
{
    uint16_t polar = 0x0000;
    set_relay_polarity(polar);
    uint16_t pulse_time = 150;
    set_relay_command_pulse_time(pulse_time);
    uint16_t command = 0x0001;
    command = command << (num_channel * 8);
    printf("command %04x\n", command);
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                                              + QString("Включаем реле для канала №") + QString::number(num_channel + 1) + "\n", parametr);
    set_relay_command(command);
}

void Kia_biu::off_contol_command(uint16_t &num_bokz, uint16_t &num_channel, uint16_t parametr)
{
    uint16_t polar = 0x0000;
    set_relay_polarity(polar);
    uint16_t pulse_time = 150;
    set_relay_command_pulse_time(pulse_time);
    uint16_t command = 0x0002;
    command = command << (num_channel * 8);
    printf("%04x\n", command);
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] = KiaS_FAIL;
    m_kia_protocol->save_and_out_to_system_error_ai_protocols(num_bokz, m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                                              + QString("Выключаем реле для канала №") + QString::number(num_channel + 1) + "\n", parametr);
    set_relay_command(command);
}

