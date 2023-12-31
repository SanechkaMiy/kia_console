#include "bokzm60.h"
BokzM60::BokzM60(uint16_t num_bokz, std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
                 shared_ptr <Kia_mpi> kia_mpi, shared_ptr<Kia_protocol> kia_protocol,
                 std::shared_ptr<Kia_settings> kia_settings, shared_ptr<Kia_ftdi> kia_ftdi) :
    m_kia_db(kia_db)
  , m_kia_mpi(kia_mpi)
  , m_kia_protocol(kia_protocol)
  , m_kia_settings(kia_settings)
  , m_kia_ftdi(kia_ftdi)
{
    m_num_bokz = num_bokz;
    set_bokz_settings();
}

BokzM60::~BokzM60()
{
    cout<<"destructor bokzm60"<<endl;
}

void BokzM60::set_bokz_settings()
{
    m_kia_data.reset(new Kia_data());
    m_kia_mko_struct.reset(new Kia_mko_struct());
    m_pio_bokz.reset(new Pio_bokzm60(m_kia_mko_struct, m_kia_settings));

    m_kia_db[TYPE_RAW]->add_device_to_experiment(m_kia_settings->m_data_for_db->m_type_bokz[m_kia_settings->m_type_bokz], m_num_bokz);
    m_parser_db.reset(new ParseToDB(m_kia_db, m_kia_data, m_kia_settings));
}


uint16_t BokzM60::shtmi1(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ШТМИ1!");
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
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_shtmi1.shtmi1_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_shtmi1.shtmi1_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_shtmi1.shtmi1_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_shtmi1.shtmi1_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");
    }
    m_parser_db->sendDataIntoSHTMI1_M60(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shtmi1);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_M60_SHTMI1, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address,  uint16_t word_data,
                                    string struct_id, string struct_id_desc, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ") + QString::fromStdString(struct_id_desc) + "!";
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ШТМИ2!");
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
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_shtmi2.shtmi2_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_shtmi2.shtmi2_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_shtmi2.shtmi2_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_shtmi2.shtmi2_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");
    }
    m_parser_db->sendDataIntoSHTMI2_M60(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shtmi2);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_M60_SHTMI2, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::mshior(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем МШИОР!");
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
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_mshior.mshior_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_mshior.mshior_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_mshior.mshior_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_mshior.mshior_list_data[num_list] + "\n");
        }

        str_protocol.push_back("\n\n");

        post_status_proc(str_protocol);

    }
    m_parser_db->sendDataIntoMSHIOR_M60(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_mshior);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_M60_MSHIOR, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
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
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    uint16_t count_dtmi_dtmi_loc = 0;
    m_kia_data->m_data_db->struct_id = "dtmi" + m_kia_data->m_data_db->struct_id_dop;
    m_kia_data->m_data_db->struct_id_desc = "ДТМИ" + m_kia_data->m_data_db->struct_id_dop_desc;
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ") + QString::fromStdString(m_kia_data->m_data_db->struct_id);
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
            set_data_to_device_protocol(str_protocol);
            for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.size(); ++num_list)
            {
                uint16_t do_shift_left = 0;
                if (m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data[num_list][0] == '-')
                    do_shift_left = 1;
                str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name[num_list],
                                                               m_kia_settings->m_format_for_desc->shift_description
                                                               + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                       + m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data[num_list] + "\n");
            }
            str_protocol.push_back("\n\n");

        }
        m_parser_db->sendDataIntoDTMILOC_M60(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->dtmiLoc_1, m_kia_mko_struct->dtmiLoc_2, m_kia_mko_struct->dtmiLoc_3, m_kia_mko_struct->dtmiLoc_4,
                m_kia_mko_struct->dtmiLoc_5, m_kia_mko_struct->dtmiLoc_6, m_kia_mko_struct->dtmiLoc_7, m_kia_mko_struct->dtmiLoc_8,
                m_kia_mko_struct->dtmiLoc_9);
        m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_M60_DTMI_LOC, parametr);
        save_to_protocol(str_to_protocol, parametr);
        save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    }
    else
    {
        if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        {
            set_data_to_device_protocol(str_protocol);
            for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_dtmi.dtmi_list_name.size(); ++num_list)
            {
                uint16_t do_shift_left = 0;
                if (m_kia_mko_struct->st_dtmi.dtmi_list_data[num_list][0] == '-')
                    do_shift_left = 1;
                str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_dtmi.dtmi_list_name[num_list],
                                                               m_kia_settings->m_format_for_desc->shift_description
                                                               + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                       + m_kia_mko_struct->st_dtmi.dtmi_list_data[num_list] + "\n");
            }
            str_protocol.push_back("\n\n");

        }
        m_parser_db->sendDataIntoDTMI_M60(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->dtmi_1, m_kia_mko_struct->dtmi_2, m_kia_mko_struct->dtmi_3, m_kia_mko_struct->dtmi_4,
                m_kia_mko_struct->dtmi_5, m_kia_mko_struct->dtmi_6, m_kia_mko_struct->dtmi_7, m_kia_mko_struct->dtmi_8,
                m_kia_mko_struct->dtmi_9);
        m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_M60_DTMI, parametr);
        save_to_protocol(str_to_protocol, parametr);
        save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    }
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();

    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::mloc(uint16_t parametr)
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

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_SYSTEM] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] == KiaS_SUCCESS)
        if (m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
            m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);

    count_of_fails(parametr);

}

void BokzM60::save_to_specific_protocol(QString str_to_protocol, uint16_t type_window, uint16_t type_protocol, uint16_t parametr)
{
    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[type_protocol] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, type_window, type_protocol, parametr);

}

void BokzM60::calc_frame_param(std::array<uint8_t, frame_size> frame_buffer)
{
    m_kia_data->m_data_db->m_max = frame_buffer[0];
    m_kia_data->m_data_db->m_min = frame_buffer[0];
    for (uint32_t el = 0; el < frame_size; el++)
    {
        if (frame_buffer[el] > m_kia_data->m_data_db->m_max)
        {
            m_kia_data->m_data_db->m_max = frame_buffer[el];
        }
        if (frame_buffer[el] < m_kia_data->m_data_db->m_min)
            m_kia_data->m_data_db->m_min = frame_buffer[el];
        m_kia_data->m_data_db->m_average = m_kia_data->m_data_db->m_average + frame_buffer[el];

    }
    m_kia_data->m_data_db->m_average = m_kia_data->m_data_db->m_average / frame_size;
    for (uint32_t el = 2; el < frame_size; el++)
        m_kia_data->m_data_db->m_variance = m_kia_data->m_data_db->m_variance
                + pow(abs(frame_buffer[el] - (int32_t)m_kia_data->m_data_db->m_average), 2);
    m_kia_data->m_data_db->m_variance = sqrt(m_kia_data->m_data_db->m_variance / (frame_size));
}

void BokzM60::count_of_fails(uint16_t parametr)
{
    QString str_error_counter;
    str_error_counter.push_back(helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + helpers::format_qstring("Счетчики ошибок", m_kia_settings->m_format_for_desc->shift_count_of_fail) + "\n");
    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
                                + helpers::format_qstring("Счетчик нарушения обмена", m_kia_settings->m_format_for_desc->shift_count_of_fail)
                                + QString::number(m_kia_data->m_data_bokz->m_count_of_exc_fail) + "\n");
    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
                                + helpers::format_qstring("Счетчик ненормы привязки ко времени", m_kia_settings->m_format_for_desc->shift_count_of_fail)
                                + QString::number(m_kia_data->m_data_bokz->m_count_of_time_bind_fail) + "\n");
    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
                                + helpers::format_qstring("Ориентация не определена", m_kia_settings->m_format_for_desc->shift_count_of_fail)
                                + QString::number(m_kia_data->m_data_bokz->m_count_of_no_is_not_def_fail) + "\n");
    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
                                + helpers::format_qstring("Ненорма кватерниона", m_kia_settings->m_format_for_desc->shift_count_of_fail)
                                + QString::number(m_kia_data->m_data_bokz->m_count_of_kvaor_is_not_corr_fail) + "\n");
    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
                                + helpers::format_qstring("Нет выхода в режим ожидания", m_kia_settings->m_format_for_desc->shift_count_of_fail)
                                + QString::number(m_kia_data->m_data_bokz->m_count_of_time_out_fail) + "\n");
    m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_error_counter, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);
}

uint16_t BokzM60::smti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем СМТИ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 1;
        m_kia_data->m_data_db->struct_id = "smti";
        m_kia_data->m_data_db->struct_id_desc = "СМТИ";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::vmti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Получаем ВМТИ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 1;
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
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::synchro(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД СКОР!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД НО!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ТО!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
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
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        m_kia_ftdi->read_frame();
        m_kia_protocol->save_to_frames_protocols(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_ftdi->get_frame_buf(), m_kia_ftdi->get_buf_size());
    }
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();

    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::command_loc(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ЛОК!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ОТКЛР!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Открыть крышку!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Закрыть крышку!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД КВАОР!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ОС!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ВСКОУ!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Установить в исходное состояние!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Заблокировать передатчик!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Разблокировать передатчик!");
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

uint16_t BokzM60::do_frames(uint16_t parametr)
{
    //    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    //    m_kia_matrox->matrox_grab_frame(m_kia_data);

    //    m_kia_protocol->save_to_frames_protocols(m_kia_matrox->get_frame_buf(), m_kia_matrox->get_buf_size());

    //    m_parser_db->send_to_frames(num_bokz);
    //    m_kia_settings->m_flags_for_thread->m_mtx.unlock();

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

    do_pause(1000);

    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                + QString("Снимаем кадр!");
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
        std::array<uint8_t, frame_size> frame_buffer;
        uint32_t num_command = 0;
        uint32_t pos = 0;
        while (num_command < frame_size / count_pixel_in_one_arr)
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
        m_kia_protocol->save_to_frames_protocols(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], frame_buffer.data(), frame_buffer.size());
        calc_frame_param(frame_buffer);
        m_kia_data->m_data_db->frame_name = "frame_num_bokz_" + std::to_string(m_num_bokz) + "_" + std::to_string(m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
        m_parser_db->send_to_frames(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
        m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    }
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::set_epsilon(float command, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    send_data_to_command(IS_PARAM, TP_FOCUS, QString::number(data_for_focus[FOCUS]));
    send_data_to_command(IS_PARAM, TP_CORD_X, QString::number(data_for_focus[CORD_X]));
    send_data_to_command(IS_PARAM, TP_CORD_Y, QString::number(data_for_focus[CORD_Y]));
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::set_texp(uint16_t command, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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

void BokzM60::post_status_proc(QString& str_protocol)
{
    QString str_norma;
    if (round(m_kia_settings->m_data_for_db->m_norm_qaor) != 1)
        str_norma = " Не норма!";
    else
        str_norma = " Норма!";

    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers) + helpers::format_qstring("Норма кватерниона", m_kia_settings->m_format_for_desc->shift_description) + QString::number(m_kia_settings->m_data_for_db->m_norm_qaor, 'f', 4) + str_norma + "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Углы ориентации", m_kia_settings->m_format_for_desc->shift_description) + "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers) + helpers::format_qstring("Альфа", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_degreze(m_kia_data->m_data_db->m_alpha) + helpers::get_minutes(m_kia_data->m_data_db->m_alpha) + helpers::get_seconds(m_kia_data->m_data_db->m_alpha)
                           +  "(" + QString::number(m_kia_data->m_data_db->m_alpha, 'f', 4) + ")" + "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Дельта", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_degreze(m_kia_data->m_data_db->m_delta) + helpers::get_minutes(m_kia_data->m_data_db->m_delta) + helpers::get_seconds(m_kia_data->m_data_db->m_delta)
                           + "(" + QString::number(m_kia_data->m_data_db->m_delta, 'f', 4) + ")"+ "\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers) + helpers::format_qstring("Азимут", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_degreze(m_kia_data->m_data_db->m_azimuth) + helpers::get_minutes(m_kia_data->m_data_db->m_azimuth) + helpers::get_seconds(m_kia_data->m_data_db->m_azimuth)
                           + "(" + QString::number(m_kia_data->m_data_db->m_azimuth, 'f', 4) + ")" + "\n\n");

    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Расшифровка Код состояния 1:", m_kia_settings->m_format_for_desc->shift_description) + "\n");
    str_protocol.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Состояние концевого датчика \"крышка закрыта\"", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status_zkr(m_kia_mko_struct->st_mshior.KC1, 1) + "\n");
    str_protocol.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Состояние концевого датчика \"крышка открыта\"", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status_zkr(m_kia_mko_struct->st_mshior.KC1, 2) + "\n");
    str_protocol.push_back(helpers::format_qstring("5-8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Счетчик ошибочных секундных меток", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_count_sec_fail_mark(m_kia_mko_struct->st_mshior.KC1, 4) + "\n");
    str_protocol.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Готовность к работе по результатам теста", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_dev_ready(m_kia_mko_struct->st_mshior.KC1, 10) + "\n");
    str_protocol.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Ориентация определена", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status_orientation(m_kia_mko_struct->st_mshior.KC1, 11) + "\n");
    str_protocol.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Режим ориентации", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_mode_orientation(m_kia_mko_struct->st_mshior.KC1, 13) + "\n");
    str_protocol.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Режим ожидания", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_command_wait(m_kia_mko_struct->st_mshior.KC1, 14) + "\n");
    str_protocol.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Команда выполнена", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_command_complete(m_kia_mko_struct->st_mshior.KC1, 15) + "\n\n");
    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Расшифровка Код состояния 2:", m_kia_settings->m_format_for_desc->shift_description) + "\n");
    str_protocol.push_back(helpers::format_qstring("1-4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Код последнего полученного УСД", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_last_usd(m_kia_mko_struct->st_mshior.KC2, 0) + "\n\n");
    str_protocol.push_back(helpers::format_qstring("9-21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Код ошибки", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status_error(m_kia_mko_struct->st_mshior.KC2, 8) + "\n\n");
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
    m_parser_db->sendDataIntoMPI(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
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
    }
    else
    {
        m_kia_data->m_data_bokz->m_count_of_no_is_not_def_fail++;
    }
    if (round(m_kia_data->m_data_db->m_norm_qaor) != norm_qaor)
    {
        m_kia_data->m_data_bokz->m_count_of_kvaor_is_not_corr_fail++;
    }
    if (m_kia_data->m_data_bokz->m_count_of_no_is_not_def_fail >= max_or_is_not_def && (m_kia_data->m_data_mpi->m_data_word[2] & 0xf000) != 0x4000)
    {
        m_kia_data->m_data_bokz->m_count_of_time_out_fail++;
    }
    if ((m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi] - m_kia_mko_struct->st_mshior.T) != 1)
    {
        m_kia_data->m_data_bokz->m_count_of_time_bind_fail++;
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
    m_kia_data->m_data_mpi->m_status_exchange = m_kia_mpi->execute_exchange(m_kia_data, m_num_bokz);
    parse_mko_protocols(m_kia_protocol, m_kia_data,
                        m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_num_bokz);
    send_mpi_data_to_db();
}

void BokzM60::set_data_to_device_protocol(QString& str_protocol)
{
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers + 1, '-')
                           + helpers::format_qstring(" " + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc)
                                                     + " ", m_kia_settings->m_format_for_desc->shift_description,'-') + '\n');
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("БШВ", m_kia_settings->m_format_for_desc->shift_description)
                           + QString::number(m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]) + '\n');
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Время", m_kia_settings->m_format_for_desc->shift_description)
                           + QString::fromStdString(m_kia_data->m_data_db->m_datetime) + '\n');
}
