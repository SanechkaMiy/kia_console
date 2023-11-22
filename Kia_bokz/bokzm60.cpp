#include "bokzm60.h"

BokzM60::BokzM60(uint16_t num_bokz, shared_ptr<WorkWithStruct> wws, std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
                 std::vector<shared_ptr<Timer> > timer, std::vector<std::shared_ptr<Kia_synch_timer>> kia_synch_timer, std::vector<shared_ptr<Kia_bi> > kia_bi,
                 shared_ptr <Kia_mpi> kia_mpi, shared_ptr<Kia_protocol> kia_protocol,
                 shared_ptr<Kia_matrox> kia_matrox, std::shared_ptr<Kia_settings> kia_settings, shared_ptr<Kia_ftdi> kia_ftdi) :
    m_wws(wws)
  , m_kia_db(kia_db)
  , m_timer(timer)
  , m_kia_synch_timer(kia_synch_timer)
  , m_kia_bi(kia_bi)
  , m_kia_mpi(kia_mpi)
  , m_kia_protocol(kia_protocol)
  , m_kia_matrox(kia_matrox)
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
    m_kia_data->m_data_mpi->m_mpi_command[NMC_SHTMI1] = [this](uint16_t parametr = EP_DOALL)
    {
        shtmi1(parametr);
    };
    m_kia_data->m_data_mpi->m_mpi_command[NMC_SHTMI2] = [this](uint16_t parametr = EP_DOALL)
    {
        shtmi2(parametr);
    };
    m_kia_data->m_data_mpi->m_mpi_command[NMC_MSHIOR] = [this](uint16_t parametr = EP_DOALL)
    {
        mshior(parametr);
    };
    m_kia_data->m_data_mpi->m_mpi_command[NMC_DTMI] = [this](uint16_t parametr = EP_DOALL)
    {
        dtmi_or_dtmi_loc(parametr);
    };
    m_kia_data->m_data_mpi->m_mpi_command[NMC_DTMI_LOC] = [this](uint16_t parametr = EP_DOALL)
    {
        command_loc(parametr);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[m_num_bokz])
            dtmi_or_dtmi_loc(parametr);
    };
    m_kia_db[TYPE_RAW]->add_device_to_experiment(m_kia_settings->m_data_for_db->m_type_bokz[m_kia_settings->m_type_bokz], m_num_bokz);
    m_parser_db.reset(new ParseToDB(m_kia_db, m_kia_data, m_kia_settings));
}


uint16_t BokzM60::shtmi1(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ШТМИ1!");
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
    m_wws->workWithSHTMI1(m_kia_data->m_data_mpi->m_data_word, m_kia_mko_struct->st_shtmi1);
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        set_data_to_device_protocol(str_protocol);
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_shtmi1.shtmi1_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_shtmi1.shtmi1_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(m_wws->format(m_kia_mko_struct->st_shtmi1.shtmi1_list_name[num_list],
                                                 m_kia_settings->m_format_for_desc->shift_description
                                                 + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_shtmi1.shtmi1_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");
    }
    m_parser_db->sendDataIntoSHTMI1(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shtmi1);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_SHTMI1, parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::shtmi2(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ШТМИ2!");
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
    int countSize = 16;
    m_wws->workWithSHTMI2(m_kia_data->m_data_mpi->m_data_word, m_kia_mko_struct->st_shmti2, countSize);
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        set_data_to_device_protocol(str_protocol);
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_shmti2.shtmi2_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_shmti2.shtmi2_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(m_wws->format(m_kia_mko_struct->st_shmti2.shtmi2_list_name[num_list],
                                                 m_kia_settings->m_format_for_desc->shift_description
                                                 + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_shmti2.shtmi2_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");
    }
    m_parser_db->sendDataIntoSHTMI2(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shmti2);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_SHTMI2, parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::mshior(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем МШИОР!");
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
    m_wws->workWithMSHIOR(m_kia_data->m_data_mpi->m_data_word, m_kia_mko_struct->st_mshior);
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
            str_protocol.push_back(m_wws->format(m_kia_mko_struct->st_mshior.mshior_list_name[num_list],
                                                 m_kia_settings->m_format_for_desc->shift_description
                                                 + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_mshior.mshior_list_data[num_list] + "\n");
        }

        str_protocol.push_back("\n\n");

        post_status_proc(str_protocol);

    }
    m_parser_db->sendDataIntoMSHIOR(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_mshior);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_MSHIOR, parametr);
    save_to_protocol(str_to_protocol, parametr);
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
    m_count_dtmi_dtmi_loc = 0;
    uint16_t no_full_exchange = 0;
    m_kia_data->m_data_db->struct_id = "dtmi" + m_kia_data->m_data_db->struct_id_dop;
    m_kia_data->m_data_db->struct_id_desc = "ДТМИ" + m_kia_data->m_data_db->struct_id_dop_desc;
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ") + QString::fromStdString(m_kia_data->m_data_db->struct_id);
    if ((parametr & EP_NOFULLEXCHANGE) != 0)
        no_full_exchange = constants::m_countArrayDTMILoc - 1;
    while (m_count_dtmi_dtmi_loc < constants::m_countArrayDTMILoc - no_full_exchange)
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
        getDataToDTMIOrDTMILoc();
        ++m_count_dtmi_dtmi_loc;
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
                str_protocol.push_back(m_wws->format(m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name[num_list],
                                                     m_kia_settings->m_format_for_desc->shift_description
                                                     + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                       + m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data[num_list] + "\n");
            }
            str_protocol.push_back("\n\n");

        }
        m_parser_db->sendDataIntoDTMILOC(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->dtmiLoc_1, m_kia_mko_struct->dtmiLoc_2, m_kia_mko_struct->dtmiLoc_3, m_kia_mko_struct->dtmiLoc_4,
                m_kia_mko_struct->dtmiLoc_5, m_kia_mko_struct->dtmiLoc_6, m_kia_mko_struct->dtmiLoc_7, m_kia_mko_struct->dtmiLoc_8,
                m_kia_mko_struct->dtmiLoc_9);
        m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_DTMI_LOC, parametr);
        save_to_protocol(str_to_protocol, parametr);
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
                str_protocol.push_back(m_wws->format(m_kia_mko_struct->st_dtmi.dtmi_list_name[num_list],
                                                     m_kia_settings->m_format_for_desc->shift_description
                                                     + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                       + m_kia_mko_struct->st_dtmi.dtmi_list_data[num_list] + "\n");
            }
            str_protocol.push_back("\n\n");

        }
        m_parser_db->sendDataIntoDTMI(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->dtmi_1, m_kia_mko_struct->dtmi_2, m_kia_mko_struct->dtmi_3, m_kia_mko_struct->dtmi_4,
                m_kia_mko_struct->dtmi_5, m_kia_mko_struct->dtmi_6, m_kia_mko_struct->dtmi_7, m_kia_mko_struct->dtmi_8,
                m_kia_mko_struct->dtmi_9);
        m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, NMC_DTMI, parametr);
        save_to_protocol(str_to_protocol, parametr);
    }
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();

    return m_kia_data->m_data_mpi->m_status_exchange;
}

void BokzM60::getDataToDTMIOrDTMILoc()
{
    if (m_kia_data->m_data_db->struct_id_dop == "loc")
        m_wws->workWithDTMILoc(m_kia_data->m_data_mpi->m_data_word, m_count_dtmi_dtmi_loc, m_kia_mko_struct->st_dtmi_loc, m_kia_mko_struct->dtmiLoc_1, m_kia_mko_struct->dtmiLoc_2, m_kia_mko_struct->dtmiLoc_3, m_kia_mko_struct->dtmiLoc_4,
                               m_kia_mko_struct->dtmiLoc_5, m_kia_mko_struct->dtmiLoc_6, m_kia_mko_struct->dtmiLoc_7, m_kia_mko_struct->dtmiLoc_8, m_kia_mko_struct->dtmiLoc_9);
    else
        m_wws->workWithDTMI(m_kia_data->m_data_mpi->m_data_word, m_count_dtmi_dtmi_loc, m_kia_mko_struct->st_dtmi, m_kia_mko_struct->dtmi_1, m_kia_mko_struct->dtmi_2, m_kia_mko_struct->dtmi_3, m_kia_mko_struct->dtmi_4,
                            m_kia_mko_struct->dtmi_5, m_kia_mko_struct->dtmi_6, m_kia_mko_struct->dtmi_7, m_kia_mko_struct->dtmi_8, m_kia_mko_struct->dtmi_9);
}

void BokzM60::save_to_protocol(QString str_to_protocol, uint16_t parametr)
{
    if (m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info[m_num_bokz])
        str_to_protocol.clear();
    else
        str_to_protocol.push_back(m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[m_num_bokz] + "\n");

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_SYSTEM] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] == KiaS_SUCCESS)
        if (m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
            m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);

    m_kia_protocol->count_of_fails(m_num_bokz, parametr);


}

uint16_t BokzM60::smti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем СМТИ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_word_data = 32;
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Получаем ВМТИ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_mpi->m_sub_address = 1;
        m_kia_data->m_data_db->struct_id = "vmti";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
        memcpy(&ar_bshv, &m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], sizeof(ar_bshv));
        std::array <uint16_t, 2> ar_epZvKat = {0x0000, 0x0000};
        float fl_epZvKat = m_wws->decodeDateTime();
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД СКОР!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД НО!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ТО!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ЛОК!");
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
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ОТКЛР!");
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
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Открыть крышку!");
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
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Закрыть крышку!");
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
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_sub_address; i++)
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

uint16_t BokzM60::kvaor(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД КВАОР!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ОС!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ВСКОУ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_format = CTRL_C_A;//CTRL_CD_A;
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_sub_address = 31;
        m_kia_data->m_data_mpi->m_word_data = 19;
        m_kia_data->m_data_db->struct_id = "vskou";
        m_kia_data->m_data_db->struct_id_desc = "ВСКОУ";
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Установить в исходное состояние!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Заблокировать передатчик!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Разблокировать передатчик!");
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

    m_kia_synch_timer[m_kia_data->m_data_bi->m_num_used_bi]->wait_for_event(m_timer[m_kia_data->m_data_bi->m_num_used_bi]);

    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
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
        std::array<uint8_t, constants::frame_size> frame_buffer;
        uint32_t num_command = 0;
        uint32_t pos = 0;
        while (num_command < constants::frame_size / count_pixel_in_one_arr)
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
        m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    }
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::set_epsilon(float command, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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
    QString str_to_protocol = m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
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

    str_protocol.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers) + m_wws->format("Норма кватерниона", m_kia_settings->m_format_for_desc->shift_description) + QString::number(m_kia_settings->m_data_for_db->m_norm_qaor, 'f', 4) + str_norma + "\n");
    str_protocol.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Углы ориентации", m_kia_settings->m_format_for_desc->shift_description) + "\n");
    str_protocol.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers) + m_wws->format("Альфа", m_kia_settings->m_format_for_desc->shift_description)
                           + get_degreze(m_kia_data->m_data_db->m_alpha) + get_minutes(m_kia_data->m_data_db->m_alpha) + get_seconds(m_kia_data->m_data_db->m_alpha)
                           +  "(" + QString::number(m_kia_data->m_data_db->m_alpha, 'f', 4) + ")" + "\n");
    str_protocol.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Дельта", m_kia_settings->m_format_for_desc->shift_description)
                           + get_degreze(m_kia_data->m_data_db->m_delta) + get_minutes(m_kia_data->m_data_db->m_delta) + get_seconds(m_kia_data->m_data_db->m_delta)
                           + "(" + QString::number(m_kia_data->m_data_db->m_delta, 'f', 4) + ")"+ "\n");
    str_protocol.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers) + m_wws->format("Азимут", m_kia_settings->m_format_for_desc->shift_description)
                           + get_degreze(m_kia_data->m_data_db->m_azimuth) + get_minutes(m_kia_data->m_data_db->m_azimuth) + get_seconds(m_kia_data->m_data_db->m_azimuth)
                           + "(" + QString::number(m_kia_data->m_data_db->m_azimuth, 'f', 4) + ")" + "\n\n");

    str_protocol.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Расшифровка Код состояния 1:", m_kia_settings->m_format_for_desc->shift_description) + "\n");
    str_protocol.push_back(m_wws->format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Состояние концевого датчика \"крышка закрыта\"", m_kia_settings->m_format_for_desc->shift_description)
                           + get_status_zkr(m_kia_mko_struct->st_mshior.KC1, 1) + "\n");
    str_protocol.push_back(m_wws->format("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Состояние концевого датчика \"крышка открыта\"", m_kia_settings->m_format_for_desc->shift_description)
                           + get_status_zkr(m_kia_mko_struct->st_mshior.KC1, 2) + "\n");
    str_protocol.push_back(m_wws->format("5,6,7,8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Счетчик ошибочных секундных меток", m_kia_settings->m_format_for_desc->shift_description)
                           + get_count_sec_fail_mark(m_kia_mko_struct->st_mshior.KC1, 4) + "\n");
    str_protocol.push_back(m_wws->format("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Готовность к работе по результатам теста", m_kia_settings->m_format_for_desc->shift_description)
                           + get_dev_ready(m_kia_mko_struct->st_mshior.KC1, 10) + "\n");
    str_protocol.push_back(m_wws->format("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Ориентация определена", m_kia_settings->m_format_for_desc->shift_description)
                           + get_status_orientation(m_kia_mko_struct->st_mshior.KC1, 11) + "\n");
    str_protocol.push_back(m_wws->format("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Ориентация определена", m_kia_settings->m_format_for_desc->shift_description)
                           + get_status_orientation(m_kia_mko_struct->st_mshior.KC1, 11) + "\n");
    str_protocol.push_back(m_wws->format("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Режим ориентации", m_kia_settings->m_format_for_desc->shift_description)
                           + get_mode_orientation(m_kia_mko_struct->st_mshior.KC1, 13) + "\n");
    str_protocol.push_back(m_wws->format("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Режим ожидания", m_kia_settings->m_format_for_desc->shift_description)
                           + get_command_wait(m_kia_mko_struct->st_mshior.KC1, 14) + "\n");
    str_protocol.push_back(m_wws->format("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Команда выполнена", m_kia_settings->m_format_for_desc->shift_description)
                           + get_command_complete(m_kia_mko_struct->st_mshior.KC1, 15) + "\n\n");
    str_protocol.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Расшифровка Код состояния 2:", m_kia_settings->m_format_for_desc->shift_description) + "\n");
    str_protocol.push_back(m_wws->format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Код последнего полученного УСД", m_kia_settings->m_format_for_desc->shift_description)
                           + get_last_usd(m_kia_mko_struct->st_mshior.KC2, 0) + "\n\n");
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
        m_kia_settings->m_data_to_protocols->m_count_of_no_is_not_def_fail[m_num_bokz]++;
    }
    if (round(m_kia_data->m_data_db->m_norm_qaor) != norm_qaor)
    {
        m_kia_settings->m_data_to_protocols->m_count_of_kvaor_is_not_corr_fail[m_num_bokz]++;
    }
    if (m_kia_settings->m_data_to_protocols->m_count_of_no_is_not_def_fail[m_num_bokz] >= max_or_is_not_def && (m_kia_data->m_data_mpi->m_data_word[2] & 0xf000) != 0x4000)
    {
        m_kia_settings->m_data_to_protocols->m_count_of_time_out_fail[m_num_bokz]++;
    }
    if ((m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi] - m_kia_mko_struct->st_mshior.T) != 1)
    {
        m_kia_settings->m_data_to_protocols->m_count_of_time_bind_fail[m_num_bokz]++;
    }
}

void BokzM60::preset_before_exchange()
{
    m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[m_num_bokz] = " - ОШИБКА!";
}

uint16_t BokzM60::start_exchage(uint16_t parametr)
{
    m_kia_data->m_data_mpi->m_status_exchange = m_kia_mpi->execute_exchange(m_kia_data, m_num_bokz);
    send_mpi_data_to_db();
    if ((parametr & EP_NOPROTECTEDEXCHANGE) == 0)
    {
        if (m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
        {
            std::cout << "try one " << std::endl;
            m_kia_data->m_data_mpi->m_status_exchange = m_kia_mpi->execute_exchange(m_kia_data, m_num_bokz);
            send_mpi_data_to_db();
        }
        if (m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
        {
            cout << "LPI B is not worked! - " << m_kia_data->m_data_mpi->m_lpi << endl;
            m_kia_data->m_data_mpi->m_lpi = (m_kia_data->m_data_mpi->m_lpi + 1) % 2;
            m_kia_settings->m_flags_for_thread->m_mtx.unlock();
            m_kia_data->m_data_mpi->m_status_exchange = execute_protected_exchange(m_set_control_word);
        }
    }

    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[m_num_bokz] = " - УСПЕХ!";
    else
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[m_num_bokz] = " - ОШИБКА!";
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t BokzM60::execute_protected_exchange(std::function<void()> func_mpi_command)
{
    if (os((EP_NOPROTECTEDEXCHANGE)) == KiaS_SUCCESS)
    {
        if (vskou((EP_NOPROTECTEDEXCHANGE)) == KiaS_SUCCESS)
        {
            func_mpi_command();
            m_kia_data->m_data_mpi->m_status_exchange = m_kia_mpi->execute_exchange(m_kia_data, m_num_bokz);
            send_mpi_data_to_db();
        }
        else
            m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
    }
    else
        m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
    return  m_kia_data->m_data_mpi->m_status_exchange;
}

void BokzM60::set_data_to_device_protocol(QString& str_protocol)
{
    str_protocol.push_back(m_wws->format("", m_kia_settings->m_format_for_desc->shift_for_numbers + 1, '-')
                           + m_wws->format(" " + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc) + " ", m_kia_settings->m_format_for_desc->shift_description,'-') + '\n');
    str_protocol.push_back(m_wws->format("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("БШВ", m_kia_settings->m_format_for_desc->shift_description) + QString::number(m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]) + '\n');
    str_protocol.push_back(m_wws->format("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + m_wws->format("Время", m_kia_settings->m_format_for_desc->shift_description) + QString::fromStdString(m_kia_data->m_data_db->m_datetime) + '\n');
}
