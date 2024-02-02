#include "bokzm60.h"
BokzM60::BokzM60(uint16_t num_bokz, shared_ptr <Kia_mpi> kia_mpi,
                 std::shared_ptr<Kia_settings> kia_settings, shared_ptr<Kia_ftdi> kia_ftdi) :
    m_kia_mpi(kia_mpi)
  , m_kia_settings(kia_settings)
  , m_kia_ftdi(kia_ftdi)
{
    m_num_bokz = num_bokz;
    set_bokz_settings();
    set_type_frame_functions();
    set_type_frame_recieve();
    set_type_upn_func();
    set_type_chpn_func();
}

BokzM60::~BokzM60()
{
    cout<<"destructor bokzm60"<<endl;
}

void BokzM60::set_bokz_settings()
{
    m_kia_data.reset(new Kia_data());
    m_kia_data->m_data_mpi->m_num_bokz = m_num_bokz;
    m_kia_mko_struct.reset(new Kia_mko_struct());
    m_pio_bokz.reset(new Pio_bokzm60(m_kia_mko_struct, m_kia_settings));
    create_count_of_exc_fail();
}


uint16_t BokzM60::shtmi1(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Запрашиваем ШТМИ1!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 2;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "shtmi1";
        m_kia_data->m_data_db->struct_id_desc = "ШТМИ1";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);

    //    for (int i = 0; i <= 3; i++)
    //    {
    //        for (int j = 0; j<=7; j++)
    //        {
    //            printf("%04x  ", m_kia_data->m_data_mpi->m_data_word[i * 8 + j]);
    //        }
    //        printf("\n");
    //    }
    m_pio_bokz->decrypt_shtmi1(m_kia_data->m_data_mpi->m_data_word);
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        set_data_to_device_protocol(str_protocol);
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_shtmi1.shtmi1_list_name, m_kia_mko_struct->st_shtmi1.shtmi1_list_data));
        str_protocol.push_back("\n\n");
    }
    emit send_data_to_db_bokz(M60_SHTMI1, m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], *m_kia_mko_struct.get());
    save_to_specific_protocol(str_protocol, M60_SHTMI1, SET_WINDOW_INFO_DEVICE_PROTOCOL, SP_DO_DEV, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, M60_NONE, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address,  uint16_t word_data,
                                    string struct_id, string struct_id_desc, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Запрашиваем ") + QString::fromStdString(struct_id_desc) + "!";
    preset_before_exchange();
    m_set_control_word = [this, direction, format, sub_address, word_data, struct_id, struct_id_desc]()
    {
        m_kia_data->m_data_mpi->m_direction = direction;
        m_kia_data->m_data_mpi->m_format = format;
        m_kia_data->m_data_mpi->m_sub_address = sub_address;
        m_kia_data->m_data_mpi->m_word_data = word_data;
        m_kia_data->m_data_db->struct_id = struct_id;
        m_kia_data->m_data_db->struct_id_desc = struct_id_desc;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}
uint16_t BokzM60::shtmi2(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Запрашиваем ШТМИ2!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 3;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "shtmi2";
        m_kia_data->m_data_db->struct_id_desc = "ШТМИ2";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    for (int i = 0; i <= 3; i++)
    {
        for (int j = 0; j<=7; j++)
        {
            printf("%04x  ", m_kia_data->m_data_mpi->m_data_word[i * 8 + j]);
        }
        printf("\n");
    }
    m_pio_bokz->decrypt_shtmi2(m_kia_data->m_data_mpi->m_data_word);
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        set_data_to_device_protocol(str_protocol);
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_shtmi2.shtmi2_list_name, m_kia_mko_struct->st_shtmi2.shtmi2_list_data));

        str_protocol.push_back("\n\n");
    }
    emit send_data_to_db_bokz(M60_SHTMI2, m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], *m_kia_mko_struct.get());
    save_to_specific_protocol(str_protocol, M60_SHTMI2, SET_WINDOW_INFO_DEVICE_PROTOCOL, SP_DO_DEV, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, M60_NONE, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::mshior(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Запрашиваем МШИОР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 24;
        m_kia_data->m_data_db->struct_id = "mshior";
        m_kia_data->m_data_db->struct_id_desc = "МШИОР";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    m_pio_bokz->decrypt_mshior(m_kia_data->m_data_mpi->m_data_word, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
    check_orientation();
    std::tie(m_kia_data->m_data_db->m_alpha, m_kia_data->m_data_db->m_delta, m_kia_data->m_data_db->m_azimuth) = math_alpha_delta_azimut(m_kia_mko_struct->st_mshior.Qo0, m_kia_mko_struct->st_mshior.Qo1, m_kia_mko_struct->st_mshior.Qo2, m_kia_mko_struct->st_mshior.Qo3);
    send_status_info();
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {

        set_data_to_device_protocol(str_protocol);
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_mshior.mshior_list_name, m_kia_mko_struct->st_mshior.mshior_list_data));
        str_protocol.push_back("\n\n");

        post_status_proc(m_kia_mko_struct->st_mshior.KC1, m_kia_mko_struct->st_mshior.KC2, str_protocol);

    }
    emit send_data_to_db_bokz(M60_MSHIOR, m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], *m_kia_mko_struct.get());
    save_to_specific_protocol(str_protocol, M60_MSHIOR, SET_WINDOW_INFO_DEVICE_PROTOCOL, SP_DO_DEV, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, M60_NONE, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::dtmi_or_dtmi_loc(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 4;// 60 - 4
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "dtmi" + m_kia_data->m_data_db->struct_id_dop;
        m_kia_data->m_data_db->struct_id_desc = "ДТМИ" + m_kia_data->m_data_db->struct_id_dop_desc;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    uint16_t count_dtmi_dtmi_loc = 0;
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Запрашиваем ") + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);
    uint16_t count_to_exchange = 9;
    if ((parametr & EP_NOFULLEXCHANGE) != 0)
        count_to_exchange = 1;
    while (count_dtmi_dtmi_loc < count_to_exchange)
    {
        m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
        for (int i = 0; i <= 3; i++)
        {
            for (int j = 0; j<=7; j++)
            {
                printf("%04x  ", m_kia_data->m_data_mpi->m_data_word[i * 8 + j]);
            }
            printf("\n");
        }
        getDataToDTMIOrDTMILoc(count_dtmi_dtmi_loc);
        ++count_dtmi_dtmi_loc;
    }
    QString str_protocol;
    if (m_kia_data->m_data_db->struct_id_dop == "loc")
    {
        if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        {
            m_pio_bokz->parse_dtmi_loc();
            set_data_to_device_protocol(str_protocol);
            str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name, m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data));
            str_protocol.push_back("\n\n");

        }
        emit send_data_to_db_bokz(M60_DTMI_LOC, m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], *m_kia_mko_struct.get());
        save_to_specific_protocol(str_protocol, M60_DTMI_LOC, SET_WINDOW_INFO_DEVICE_PROTOCOL, SP_DO_DEV, parametr);
        save_to_protocol(str_to_protocol, parametr);
        save_to_specific_protocol(str_protocol, M60_NONE, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    }
    else
    {
        if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        {
            m_pio_bokz->parse_dtmi(m_kia_data->m_data_bokz->m_type_orient);
            set_data_to_device_protocol(str_protocol);
            str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_dtmi.dtmi_list_name, m_kia_mko_struct->st_dtmi.dtmi_list_data));
            str_protocol.push_back("\n\n");

        }
        emit send_data_to_db_bokz(M60_DTMI, m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], *m_kia_mko_struct.get());
        save_to_specific_protocol(str_protocol, M60_DTMI, SET_WINDOW_INFO_DEVICE_PROTOCOL, SP_DO_DEV, parametr);
        save_to_protocol(str_to_protocol, parametr);
        save_to_specific_protocol(str_protocol, M60_NONE, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    }
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();

    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::mloc(uint16_t parametr)
{

}

uint16_t BokzM60::upn(uint16_t type_upn, QStringList value, uint16_t parametr)
{
    for(auto const& imap: m_func_upn)
    {
        if (type_upn == imap.first)
            m_func_upn[type_upn](value, parametr);
    }

    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::chpn(QStringList type_chpn, uint16_t parametr)
{
    for (auto el : type_chpn)
    {
        for(auto const& imap: m_map_chpn)
        {
            if (el.toUInt() == imap.first)
                m_map_chpn[el.toUInt()](parametr);
        }
    }
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::chkd(uint16_t parametr)
{

}


void BokzM60::getDataToDTMIOrDTMILoc(uint16_t& count_dtmi_or_dtmi_loc)
{
    if (m_kia_data->m_data_db->struct_id_dop == "loc")
        m_pio_bokz->decrypt_dtmi_loc(m_kia_data->m_data_mpi->m_data_word, count_dtmi_or_dtmi_loc);
    else
        m_pio_bokz->decrypt_dtmi(m_kia_data->m_data_mpi->m_data_word, count_dtmi_or_dtmi_loc);
}

void BokzM60::save_to_protocol(QString str_to_protocol, uint16_t parametr)
{
    if (m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info[m_num_bokz])
        str_to_protocol.clear();
    else
        str_to_protocol.push_back(m_kia_data->m_data_mpi->m_is_error + "\n");

    save_to_specific_protocol(str_to_protocol, M60_NONE, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);

    if (m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
        save_to_specific_protocol(str_to_protocol, M60_NONE, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);

    save_to_specific_protocol(str_to_protocol, M60_NONE, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    count_of_fails(parametr);

}

void BokzM60::save_to_specific_protocol(QString str_to_protocol, uint16_t num_mpi_command,
                                        uint16_t type_window, uint16_t type_protocol, uint16_t parametr)
{
    Kia_protocol_parametrs kia_protocol_parametrs;
    kia_protocol_parametrs.num_mpi_command = num_mpi_command;
    kia_protocol_parametrs.num_bokz = m_num_bokz;
    kia_protocol_parametrs.data_to_out = str_to_protocol;
    kia_protocol_parametrs.type_window = type_window;
    kia_protocol_parametrs.type_protocol = type_protocol;
    kia_protocol_parametrs.parametr = parametr;
    emit send_to_save_protocol(kia_protocol_parametrs);
}

//void BokzM60::continue_exchange()
//{
//    std::lock_guard lock(m_mtx);
//    m_count_exchange++;
//    m_cv.notify_all();
//}

template <typename T>
void BokzM60::calc_frame_param(std::vector<T> frame_buffer)
{
    m_kia_data->m_data_db->m_max = frame_buffer[0];
    m_kia_data->m_data_db->m_min = frame_buffer[0];
    for (uint32_t el = 0; el < frame_buffer.size(); el++)
    {
        if (frame_buffer[el] > m_kia_data->m_data_db->m_max)
        {
            m_kia_data->m_data_db->m_max = frame_buffer[el];
        }
        if (frame_buffer[el] < m_kia_data->m_data_db->m_min)
            m_kia_data->m_data_db->m_min = frame_buffer[el];
        m_kia_data->m_data_db->m_average = m_kia_data->m_data_db->m_average + frame_buffer[el];

    }
    m_kia_data->m_data_db->m_average = m_kia_data->m_data_db->m_average / frame_buffer.size();
    for (uint32_t el = 2; el < frame_buffer.size(); el++)
        m_kia_data->m_data_db->m_variance = m_kia_data->m_data_db->m_variance
                + pow(abs(frame_buffer[el] - (int32_t)m_kia_data->m_data_db->m_average), 2);
    m_kia_data->m_data_db->m_variance = sqrt(m_kia_data->m_data_db->m_variance / (frame_buffer.size()));
}

void BokzM60::count_of_fails(uint16_t parametr)
{
    QString str_error_counter;
    str_error_counter.push_back(helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + helpers::format_qstring("Счетчики ошибок", m_kia_settings->m_format_for_desc.shift_count_of_fail) + "\n");
    for (uint16_t num_counter = 0; num_counter < m_kia_data->m_data_bokz->m_count_fail_descr.size(); num_counter++)
    {
        str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_date_time)
                                    + helpers::format_qstring(m_kia_data->m_data_bokz->m_count_fail_descr[num_counter].first, m_kia_settings->m_format_for_desc.shift_count_of_fail)
                                    + QString::number(m_kia_data->m_data_bokz->m_count_fail[num_counter]) + "\n");
    }
    save_to_specific_protocol(str_error_counter, M60_NONE, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);
}

uint16_t BokzM60::smti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 1;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "smti";
        m_kia_data->m_data_db->struct_id_desc = "СМТИ";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем ")
            + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);

    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::vmti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 1;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "vmti";
        m_kia_data->m_data_db->struct_id_desc = "ВМТИ";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 0xffff); // define the range
        for (uint16_t num_word = 0; num_word < m_kia_data->m_data_mpi->m_word_data; num_word++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[num_word] = distr(gen);
        }
    };
    m_set_control_word();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Получаем ")
            + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);

    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::synchro(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД Синхро!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 17;
        m_kia_data->m_data_mpi->m_word_data = 4;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "synchro";
        m_kia_data->m_data_db->struct_id_desc = "СИНХРО";
        std::array <uint16_t, 2> ar_bshv = {0x0000, 0x0000};
        auto sec_mark = m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi] / m_kia_settings->m_freq_bokz;
        memcpy(&ar_bshv, &sec_mark, sizeof(ar_bshv));
        std::array <uint16_t, 2> ar_epZvKat = {0x0000, 0x0000};
        float fl_epZvKat = helpers::decodeDateTime();
        memcpy(&ar_epZvKat,&fl_epZvKat,sizeof(ar_epZvKat));
        m_kia_data->m_data_mpi->m_data_to_exc[0] = ar_bshv[1];
        m_kia_data->m_data_mpi->m_data_to_exc[1] = ar_bshv[0];
        m_kia_data->m_data_mpi->m_data_to_exc[2] = ar_epZvKat[1];
        m_kia_data->m_data_mpi->m_data_to_exc[3] = ar_epZvKat[0];
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::skor(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД СКОР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 21;
        m_kia_data->m_data_mpi->m_word_data = 6;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "skor";
        m_kia_data->m_data_db->struct_id_desc = "СКОР";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[i] = 0;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_no(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД НО!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "no";
        m_kia_data->m_data_db->struct_id_desc = "НО";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0004;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_to(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД ТО!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "to";
        m_kia_data->m_data_db->struct_id_desc = "ТО";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0008;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_full_exp(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Передаем УСД Полное Экспонирование!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "full_exp";
        m_kia_data->m_data_db->struct_id_desc = "Экспонирование";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0400;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();

    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_bin_exp(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Передаем УСД Бинарное Экспонирование!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "bin_exp";
        m_kia_data->m_data_db->struct_id_desc = "Бинарное Экспонирование";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x1000;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();

    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_loc(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД ЛОК!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "loc";
        m_kia_data->m_data_db->struct_id_desc = "ЛОК";
        m_kia_data->m_data_db->struct_id_dop = "loc";
        m_kia_data->m_data_db->struct_id_dop_desc = "ЛОК";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0040;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_otclp(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД ОТКЛР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "otclp";
        m_kia_data->m_data_db->struct_id_desc = "ОТКЛР";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0080;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_openkr(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД Открыть крышку!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "openkr";
        m_kia_data->m_data_db->struct_id_desc = "ОПЕНКР";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0001;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_zkr(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД Закрыть крышку!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "zkr";
        m_kia_data->m_data_db->struct_id_desc = "ЗКР";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0002;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_bshv(uint16_t parametr)
{
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_restart(uint16_t parametr)
{

}

uint16_t BokzM60::command_oo(uint16_t parametr)
{

}

uint16_t BokzM60::kvaor(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД КВАОР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 20;
        m_kia_data->m_data_mpi->m_word_data = 8;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "kvaor";
        m_kia_data->m_data_db->struct_id_desc = "КВАОР";
        m_kia_data->m_data_mpi->m_data_to_exc = m_kia_data->m_data_mpi->m_qa;
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::os(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД ОС!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_format = CTRL_C_A;
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_sub_address = 31;
        m_kia_data->m_data_mpi->m_word_data = 2;
        m_kia_data->m_data_db->struct_id = "os";
        m_kia_data->m_data_db->struct_id_desc = "ОС";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::vskou(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД ВСКОУ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_format = CTRL_C_AD;//CTRL_CD_A;
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_sub_address = 31;
        m_kia_data->m_data_mpi->m_word_data = 19;
        m_kia_data->m_data_db->struct_id = "vsk";
        m_kia_data->m_data_db->struct_id_desc = "ВСК";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::initial_state(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД Установить в исходное состояние!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_format = CTRL_C_A;
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_sub_address = 31;
        m_kia_data->m_data_mpi->m_word_data = 8;
        m_kia_data->m_data_db->struct_id = "initial_state";
        m_kia_data->m_data_db->struct_id_desc = "Начальное состояние";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::block_ou(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД Заблокировать передатчик!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_format = CTRL_C_A;
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_sub_address = 31;
        m_kia_data->m_data_mpi->m_word_data = 4;
        m_kia_data->m_data_db->struct_id = "block_ou";
        m_kia_data->m_data_db->struct_id_desc = "БЛОК ОУ";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::unblock_ou(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Передаем УСД Разблокировать передатчик!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_format = CTRL_C_A;
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_sub_address = 31;
        m_kia_data->m_data_mpi->m_word_data = 5;
        m_kia_data->m_data_db->struct_id = "unblock_ou";
        m_kia_data->m_data_db->struct_id_desc = "РАЗБЛОК ОУ";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::do_frames(uint16_t type_recieve, uint16_t type_frame, uint16_t parametr)
{
    if (type_frame < m_func_type_frames.size())
    {
        m_func_type_frames[type_frame](parametr);

        if (type_recieve < m_func_type_frame_recieve.size() && m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        {
            m_func_type_frame_recieve[type_recieve](type_frame, parametr);
            m_kia_data->m_data_db->frame_name = "frame_num_bokz_" + std::to_string(m_num_bokz) + "_" + std::to_string(m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
            emit send_data_to_db_for_frames(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
        }
    }
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::set_epsilon(float command, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Устанавливаем допуск распознавания");
    preset_before_exchange();
    m_set_control_word = [this, command]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT; //DATA_RT_BC
        m_kia_data->m_data_mpi->m_sub_address = 10;
        m_kia_data->m_data_mpi->m_word_data = 2;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "set_epsilon";
        m_kia_data->m_data_db->struct_id_desc = "Задать эпсилон";
        std::array <uint16_t, 2> ar_command = {0x0000, 0x0000};
        memcpy(&ar_command, &command, sizeof(ar_command));
        m_kia_data->m_data_mpi->m_data_to_exc[0] = ar_command[0];
        m_kia_data->m_data_mpi->m_data_to_exc[1] = ar_command[1];
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::get_epsilon(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Получаем эпсилон");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC; //DATA_RT_BC
        m_kia_data->m_data_mpi->m_sub_address = 10;
        m_kia_data->m_data_mpi->m_word_data = 2;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "get_epsilon";
        m_kia_data->m_data_db->struct_id_desc = "Получить эпсилон";
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    std::array <uint16_t, 2> ar_command;
    for (uint16_t ind = 0; ind < ar_command.size(); ++ind)
        ar_command[ind] = m_kia_data->m_data_mpi->m_data_word[ind + 2];
    float epsilon = 0;
    memcpy(&epsilon, &ar_command, sizeof(epsilon));
    auto data = QString::number(epsilon);
    send_data_to_command(IS_PARAM, TP_EPS, data);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::set_focus(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Устанавливаем Фокус и Координаты главной точки");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT; //DATA_RT_BC
        m_kia_data->m_data_mpi->m_sub_address = 27;
        m_kia_data->m_data_mpi->m_word_data = 6;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "set_focus";
        m_kia_data->m_data_db->struct_id_desc = "Задать фокус";
        for (uint16_t ind = 0; ind < m_kia_data->m_data_mpi->m_focus_data.size(); ++ind)
            memcpy(&m_kia_data->m_data_mpi->m_data_to_exc[2 * ind], &m_kia_data->m_data_mpi->m_focus_data[ind], sizeof(m_kia_data->m_data_mpi->m_focus_data[ind]));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::get_focus(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
            QString("Получаем Фокус и Координаты главной точки");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC; //DATA_RT_BC
        m_kia_data->m_data_mpi->m_sub_address = 27;
        m_kia_data->m_data_mpi->m_word_data = 6;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "get_focus";
        m_kia_data->m_data_db->struct_id_desc = "Получить фокус";
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    uint16_t focus_size_arr = 3;
    std::vector<std::array <uint16_t, 2>> ar_command(focus_size_arr);
    std::vector<float> data_for_focus (focus_size_arr);
    for (uint16_t ind_out = 0; ind_out < ar_command.size(); ++ind_out)
    {
        for (uint16_t ind_in = 0; ind_in < ar_command[ind_out].size(); ++ind_in)
            ar_command[ind_out][ind_in] = m_kia_data->m_data_mpi->m_data_word[2 + ind_out * 2 + ind_in];

        memcpy(&data_for_focus[ind_out], &ar_command[ind_out], sizeof(data_for_focus[ind_out]));
    }
    send_data_to_command(IS_PARAM, TP_FOC, QString::number(data_for_focus[FOCUS]));
    send_data_to_command(IS_PARAM, TP_X, QString::number(data_for_focus[CORD_X]));
    send_data_to_command(IS_PARAM, TP_Y, QString::number(data_for_focus[CORD_Y]));
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::set_texp(uint16_t command, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Устанавливаем Время экспонирования");
    preset_before_exchange();
    m_set_control_word = [this, command]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT; //DATA_RT_BC
        m_kia_data->m_data_mpi->m_sub_address = 9;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "set_texp";
        m_kia_data->m_data_db->struct_id_desc = "Задать Texp";
        m_kia_data->m_data_mpi->m_data_to_exc[0] = command;
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::get_texp(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
            + QString("Получаем Время экспонирования");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC; //DATA_RT_BC
        m_kia_data->m_data_mpi->m_sub_address = 9;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "get_texp";
        m_kia_data->m_data_db->struct_id_desc = "Получить Texp";
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    auto data = QString::number(m_kia_data->m_data_mpi->m_data_word[2]);
    send_data_to_command(IS_PARAM, TP_TEXP, data);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

void BokzM60::set_type_frame_functions()
{
    auto full_frame_func = [this](uint16_t parametr = EP_DOALL)
    {
        command_full_exp(parametr);
    };
    m_frame_resulution.push_back(512 * 512);
    m_func_type_frames.push_back(full_frame_func);

    auto bin_frame_func = [this](uint16_t parametr = EP_DOALL)
    {
        command_bin_exp(parametr);
    };
    m_frame_resulution.push_back(256 * 256);
    m_func_type_frames.push_back(bin_frame_func);
}

void BokzM60::set_type_frame_recieve()
{
    auto func_mko = [this](uint16_t type_frame, uint16_t parametr = EP_DOALL)
    {
        do_pause(1000);
        QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                + QString("Снимаем кадр через МКО!");
        m_kia_settings->m_flags_for_thread->m_mtx.lock();
        m_set_control_word = [this]()
        {
            m_kia_data->m_data_mpi->m_data_to_exc = {0};
            m_kia_data->m_data_mpi->m_direction = 1;
            m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
            m_kia_data->m_data_mpi->m_sub_address = 23;
            m_kia_data->m_data_mpi->m_word_data = 32;
            m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
            m_kia_data->m_data_db->struct_id = "full_exp_get";
            m_kia_data->m_data_db->struct_id_desc = "Снять кадр";
        };
        m_set_control_word();
        save_to_protocol(str_to_protocol, parametr);

        uint16_t count_pixel_in_one_arr = 64;
        std::vector<uint8_t> frame_buffer(m_frame_resulution[type_frame]);
        uint32_t num_command = 0;
        uint32_t pos = 0;
        while (num_command < m_frame_resulution[type_frame] / count_pixel_in_one_arr)
        {
            m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);

            if ( m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
            {
                memcpy(&frame_buffer[pos], &m_kia_data->m_data_mpi->m_data_word[2], sizeof(m_kia_data->m_data_mpi->m_data_word) - 4);
                pos = pos + count_pixel_in_one_arr;
                num_command++;
            }
            //  save_to_protocol(str_to_protocol, DO_FULL_FRAME, parametr);
        }
        m_kia_settings->m_flags_for_thread->m_mtx.unlock();
        Kia_frame_parametrs kia_frame_parametrs;
        kia_frame_parametrs.num_bokz = m_num_bokz;
        kia_frame_parametrs.bshv = m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi];
        kia_frame_parametrs.lvp_buf = frame_buffer.data();
        kia_frame_parametrs.buf_size = frame_buffer.size();
        emit save_to_frames_protocols(kia_frame_parametrs);
        calc_frame_param(frame_buffer);

    };
    m_func_type_frame_recieve.push_back(func_mko);

    auto func_ftdi_usb = [this](uint16_t type_frame, uint16_t parametr = EP_DOALL)
    {
        QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                + QString("Снимаем кадр через FTDI_USB!");
        save_to_protocol(str_to_protocol, parametr);

        m_kia_settings->m_flags_for_thread->m_mtx.lock();
        Kia_frame_parametrs kia_frame_parametrs;
        kia_frame_parametrs.resulution = m_frame_resulution[type_frame];
        m_kia_ftdi->read_frame(&kia_frame_parametrs);
        m_kia_settings->m_flags_for_thread->m_mtx.unlock();

        kia_frame_parametrs.num_bokz = m_num_bokz;
        kia_frame_parametrs.bshv = m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi];

        emit save_to_frames_protocols(kia_frame_parametrs);

        std::vector<uint16_t > read_buffer;
        read_buffer.resize(kia_frame_parametrs.resulution);
        memcpy(read_buffer.data(), kia_frame_parametrs.lvp_buf, kia_frame_parametrs.buf_size);
        calc_frame_param(read_buffer);


    };

    m_func_type_frame_recieve.push_back(func_ftdi_usb);
}

void BokzM60::create_count_of_exc_fail()
{
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Нарушение обмена", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Ненорма привязки ко времени", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Неисправность ОУ", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Ориентация не определена", 5700));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Абонент занят", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Ненорма кватерниона", 120));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Залипание информации", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Нет выхода в режим ожидания", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Неустойчивая работа НЕОР", 16));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Неустойчивая работа ПРЗ", 5));

    m_kia_data->m_data_bokz->m_count_fail.resize(m_kia_data->m_data_bokz->m_count_fail_descr.size());
}

void BokzM60::set_type_upn_func()
{
    auto func_texp = [this](QStringList value, uint16_t parametr)
    {
        return set_texp(value[0].toUInt(), parametr);
    };
    m_func_upn[TP_TEXP] = func_texp;

    auto func_foc = [this](QStringList value, uint16_t parametr)
    {
        m_kia_data->m_data_mpi->m_focus_data[FOCUS] = value[0].toFloat();
        return set_focus(parametr);
    };
    m_func_upn[TP_FOC] = func_foc;

    auto func_x = [this](QStringList value, uint16_t parametr)
    {
        m_kia_data->m_data_mpi->m_focus_data[CORD_X] = value[0].toFloat();
        return set_focus(parametr);
    };
    m_func_upn[TP_X] = func_x;

    auto func_y = [this](QStringList value, uint16_t parametr)
    {
        m_kia_data->m_data_mpi->m_focus_data[CORD_Y] = value[0].toFloat();
        return set_focus(parametr);
    };
    m_func_upn[TP_Y] = func_y;

    auto func_eps = [this](QStringList value, uint16_t parametr)
    {
        return set_epsilon(value[0].toFloat(), parametr);
    };
    m_func_upn[TP_EPS] = func_eps;
    auto func_qa = [this](QStringList value, uint16_t parametr)
    {
        array<double, constants::size_qa> qa;
        for (uint16_t qa_index = 0; qa_index < value.size(); ++qa_index)
            qa[qa_index] = value[qa_index].toDouble();

        memcpy(&m_kia_data->m_data_mpi->m_qa, &qa, sizeof(qa));
        return m_kia_data->m_data_mpi->m_status_exchange;
    };
    m_func_upn[TP_QA] = func_qa;
    auto func_w = [this](QStringList value, uint16_t parametr)
    {
        array<uint16_t, constants::size_w> w;
        for (uint16_t w_index = 0; w_index < value.size(); ++w_index)
            w[w_index] = value[w_index].toDouble();

        memcpy(&m_kia_data->m_data_mpi->m_w, &w, sizeof(w));
        return m_kia_data->m_data_mpi->m_status_exchange;
    };
    m_func_upn[TP_W] = func_w;
}

void BokzM60::set_type_chpn_func()
{
    auto func_texp = [this](uint16_t parametr)
    {
        return get_texp(parametr);
    };
    m_map_chpn[TP_TEXP] = func_texp;

    auto func_foc = [this](uint16_t parametr)
    {
        return get_focus(parametr);
    };
    m_map_chpn[TP_FOC] = func_foc;

    auto func_x = [this](uint16_t parametr)
    {
        return get_focus(parametr);
    };
    m_map_chpn[TP_X] = func_x;

    auto func_y = [this](uint16_t parametr)
    {
        return get_focus(parametr);
    };
    m_map_chpn[TP_Y] = func_y;

    auto func_eps = [this](uint16_t parametr)
    {
        return get_epsilon(parametr);
    };
    m_map_chpn[TP_EPS] = func_eps;
}

void BokzM60::send_status_info()
{
    QStringList data_status;
    data_status.push_back(QString::number(ST_ST1));
    data_status.push_back(QString::number(m_num_bokz));
    data_status.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior.KC1, 16), 4, '0') );
    emit send_to_client(SEND_STATUS_INFO, data_status);
    data_status.clear();
    data_status.push_back(QString::number(ST_ST2));
    data_status.push_back(QString::number(m_num_bokz));
    data_status.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior.KC2, 16), 4, '0') );
    emit send_to_client(SEND_STATUS_INFO, data_status);
}

void BokzM60::post_status_proc(uint16_t st1, uint16_t st2, QString& str_protocol)
{
    QString str_norma;
    if (round(m_kia_settings->m_data_for_db->m_norm_qaor) != 1)
        str_norma = " Не норма!";
    else
        str_norma = " Норма!";

    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers) + helpers::format_qstring("Норма кватерниона", m_kia_settings->m_format_for_desc.shift_description) + QString::number(m_kia_settings->m_data_for_db->m_norm_qaor, 'f', 4) + str_norma + "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Углы ориентации", m_kia_settings->m_format_for_desc.shift_description) + "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers) + helpers::format_qstring("Альфа", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_degreze(m_kia_data->m_data_db->m_alpha) + helpers::get_minutes(m_kia_data->m_data_db->m_alpha) + helpers::get_seconds(m_kia_data->m_data_db->m_alpha)
                           +  "(" + QString::number(m_kia_data->m_data_db->m_alpha, 'f', 4) + ")" + "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Дельта", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_degreze(m_kia_data->m_data_db->m_delta) + helpers::get_minutes(m_kia_data->m_data_db->m_delta) + helpers::get_seconds(m_kia_data->m_data_db->m_delta)
                           + "(" + QString::number(m_kia_data->m_data_db->m_delta, 'f', 4) + ")"+ "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers) + helpers::format_qstring("Азимут", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_degreze(m_kia_data->m_data_db->m_azimuth) + helpers::get_minutes(m_kia_data->m_data_db->m_azimuth) + helpers::get_seconds(m_kia_data->m_data_db->m_azimuth)
                           + "(" + QString::number(m_kia_data->m_data_db->m_azimuth, 'f', 4) + ")" + "\n\n");

    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Расшифровка Код состояния 1:", m_kia_settings->m_format_for_desc.shift_description) + "\n");
    str_protocol.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Состояние концевого датчика \"крышка закрыта\"", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_status_zkr(st1, 1) + "\n");
    str_protocol.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Состояние концевого датчика \"крышка открыта\"", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_status_zkr(st1, 2) + "\n");
    str_protocol.push_back(helpers::format_qstring("5-8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Счетчик ошибочных секундных меток", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_count_sec_fail_mark(st1, 4) + "\n");
    str_protocol.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Готовность к работе по результатам теста", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_dev_ready(st1, 10) + "\n");
    str_protocol.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Ориентация определена", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_status_orientation(st1, 11) + "\n");
    str_protocol.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Режим ориентации", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_mode_orientation(st1, 13) + "\n");
    str_protocol.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Режим ожидания", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_command_wait(st1, 14) + "\n");
    str_protocol.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Команда выполнена", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_command_complete(st1, 15) + "\n\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Расшифровка Код состояния 2:", m_kia_settings->m_format_for_desc.shift_description) + "\n");
    str_protocol.push_back(helpers::format_qstring("1-4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Код последнего полученного УСД", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_last_usd(st2, 0, {{1, "ОКР"}, {2, "ЗКР"}, {3, "НО"},
                                                            {4, "ТО"}, {5, "ЛОК"}, {6, "ОТКЛР"}}) + "\n\n");
    str_protocol.push_back(helpers::format_qstring("9-21", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Код ошибки", m_kia_settings->m_format_for_desc.shift_description)
                           + helpers::get_status_error_m60(st2, 8) + "\n\n");
}

void BokzM60::send_data_to_command(const uint16_t& type_data, const uint16_t &type_command, const QString& data)
{
    QStringList data_status;
    data_status.push_back(QString::number(m_num_bokz));
    data_status.push_back(QString::number(type_data));
    data_status.push_back(QString::number(type_command));
    data_status.push_back(data);
    emit send_to_client(SEND_COMMAND, data_status);
}

void BokzM60::send_mpi_data_to_db()
{
    m_kia_data->m_data_db->data = QString('\\') + QString('\\') + "x";
    for (unsigned int i = 0; i < m_kia_data->m_data_mpi->m_data_word.size(); i++)
    {
        m_kia_data->m_data_db->data = m_kia_data->m_data_db->data + QString("%1").arg(QString::number(m_kia_data->m_data_mpi->m_data_word[i], 16), 4, '0').toUpper();
    }
    emit send_data_to_db_for_mpi(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
}

void BokzM60::check_orientation()
{
    const uint16_t norm_qaor = 1;
    const uint16_t max_or_is_not_def = 100;
    m_kia_data->m_data_db->m_norm_qaor = sqrt(pow(m_kia_mko_struct->st_mshior.Qo0,2) + pow(m_kia_mko_struct->st_mshior.Qo1,2) + pow(m_kia_mko_struct->st_mshior.Qo2, 2)  + pow(m_kia_mko_struct->st_mshior.Qo3,2));
    if ((m_kia_data->m_data_mpi->m_data_word[2] & 0xf000) == 0xe000)//|| (m_kia_data->m_data_mpi->m_data_word[2] & 0xf000) == 0x4000
    {
        for (uint16_t qa_index = 0; qa_index < constants::packetSize; ++qa_index)
            m_kia_data->m_data_mpi->m_qa[qa_index] = m_kia_data->m_data_mpi->m_data_word[qa_index + 12];

        if ((m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi] - m_kia_mko_struct->st_mshior.T) != 1)
        {
            m_kia_data->m_data_bokz->m_count_fail[SVREM]++;
        }

        if (round(m_kia_data->m_data_db->m_norm_qaor) != norm_qaor)
        {
            m_kia_data->m_data_bokz->m_count_fail[CHNKV]++;
        }

        if (m_kia_data->m_data_mpi->m_data_word == m_kia_data->m_data_mpi->m_prev_data_word)
        {
            m_kia_data->m_data_bokz->m_count_fail[CHZLP]++;
        }
        m_kia_data->m_data_mpi->m_prev_data_word = m_kia_data->m_data_mpi->m_data_word;

    }
    else
    {
        m_kia_data->m_data_bokz->m_count_fail[CHNOR]++;
    }

    if (m_kia_data->m_data_bokz->m_count_fail[CHNOR] >= max_or_is_not_def && (m_kia_data->m_data_mpi->m_data_word[2] & 0xf000) != 0x4000)
    {
        m_kia_data->m_data_bokz->m_count_fail[CHNRO]++;
    }


}

void BokzM60::preset_before_exchange()
{
    m_kia_data->m_data_mpi->m_is_error = " - УСПЕХ!";
}

void BokzM60::do_pause(uint16_t interval)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
}

uint16_t BokzM60::start_exchage(uint16_t parametr)
{
    execute_exchange();
    if ((parametr & EP_NOPROTECTEDEXCHANGE) == 0)
    {
        if (m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
        {
            execute_exchange();
        }
        if (m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
        {
            m_kia_data->m_data_mpi->m_lpi = (m_kia_data->m_data_mpi->m_lpi + 1) % 2;
            m_kia_settings->m_flags_for_thread->m_mtx.unlock();
            m_kia_data->m_data_mpi->m_status_exchange = execute_protected_exchange(m_set_control_word);
        }
    }

    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        m_kia_data->m_data_mpi->m_is_error = " - УСПЕХ!";
    else
        m_kia_data->m_data_mpi->m_is_error = " - ОШИБКА!";

    return m_kia_data->m_data_mpi->m_status_exchange;
}



uint16_t BokzM60::execute_protected_exchange(std::function<void()> func_mpi_command)
{
    if (os((EP_NOPROTECTEDEXCHANGE)) == KiaS_SUCCESS)
    {
        if (vskou((EP_NOPROTECTEDEXCHANGE)) == KiaS_SUCCESS)
        {
            func_mpi_command();
            execute_exchange();
        }
        else
            m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
    }
    else
        m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
    return  m_kia_data->m_data_mpi->m_status_exchange;
}

void BokzM60::execute_exchange()
{
    emit do_exchange(m_kia_data.get());
    wait_for_event();
    m_kia_settings->m_data_for_db->m_exchange_counter++;
    auto data = parse_mko_protocols(m_kia_data,
                                    m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_num_bokz);
    emit send_to_save_protocol(data);
    send_mpi_data_to_db();
}



void BokzM60::set_data_to_device_protocol(QString& str_protocol)
{
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers + 1, '-')
                           + helpers::format_qstring(" " + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc)
                                                     + " ", m_kia_settings->m_format_for_desc.shift_description,'-') + '\n');
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("БШВ", m_kia_settings->m_format_for_desc.shift_description)
                           + QString::number(m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]) + '\n');
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                           + helpers::format_qstring("Время", m_kia_settings->m_format_for_desc.shift_description)
                           + QString::fromStdString(m_kia_data->m_data_db->m_datetime) + '\n');
}
