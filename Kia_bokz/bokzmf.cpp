#include "bokzmf.h"

Bokzmf::Bokzmf(uint16_t num_bokz, std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
               shared_ptr<Kia_mpi> kia_mpi,
               std::shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_db(kia_db)
  , m_kia_mpi(kia_mpi)
  , m_kia_protocol(kia_protocol)
  , m_kia_settings(kia_settings)
{
    m_num_bokz = num_bokz;
    set_bokz_settings();
}

void Bokzmf::set_bokz_settings()
{
    m_kia_data.reset(new Kia_data());
    m_kia_mko_struct.reset(new Kia_mko_struct());
    m_pio_bokz.reset(new Pio_bokzmf(m_kia_mko_struct, m_kia_settings));
    m_kia_db[TYPE_RAW]->add_device_to_experiment(m_kia_settings->m_data_for_db->m_type_bokz[m_kia_settings->m_type_bokz], m_num_bokz);
    m_parser_db.reset(new ParseToDB(m_kia_db, m_kia_data, m_kia_settings));
}

uint16_t Bokzmf::debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address, uint16_t word_data,
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

Bokzmf::~Bokzmf()
{

}

uint16_t Bokzmf::shtmi1(uint16_t parametr)
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
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");
    }
    //m_parser_db->sendDataIntoSHTMI1(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shtmi1);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, MF_SHTMI1, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::shtmi2(uint16_t parametr)
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
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");
    }
    //m_parser_db->sendDataIntoSHTMI2(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shtmi2);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, MF_SHTMI2, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::mshior(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем МШИОР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 16;
        m_kia_data->m_data_mpi->m_word_data = 32;
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
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_mshior_mf.mshior_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_mshior_mf.mshior_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_mshior_mf.mshior_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_mshior_mf.mshior_list_data[num_list] + "\n");
        }

        str_protocol.push_back("\n\n");

        post_status_proc(str_protocol);

    }
    m_parser_db->sendDataIntoMSHIOR_MF(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_mshior_mf);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, MF_MSHIOR, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::dtmi_or_dtmi_loc(uint16_t parametr)
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
    m_kia_data->m_data_db->struct_id = "dtmi";
    m_kia_data->m_data_db->struct_id_desc = "ДТМИ";
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ") + QString::fromStdString(m_kia_data->m_data_db->struct_id);
    uint16_t count_to_exchange = 12;
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
        m_pio_bokz->decrypt_dtmi(m_kia_data->m_data_mpi->m_data_word, count_dtmi_dtmi_loc);
        ++count_dtmi_dtmi_loc;
    }
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        set_data_to_device_protocol(str_protocol);
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_dtmi_mf.dtmi_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_dtmi_mf.dtmi_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_dtmi_mf.dtmi_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");

    }
    //    m_parser_db->sendDataIntoDTMILOC(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->dtmiLoc_1, m_kia_mko_struct->dtmiLoc_2, m_kia_mko_struct->dtmiLoc_3, m_kia_mko_struct->dtmiLoc_4,
    //            m_kia_mko_struct->dtmiLoc_5, m_kia_mko_struct->dtmiLoc_6, m_kia_mko_struct->dtmiLoc_7, m_kia_mko_struct->dtmiLoc_8,
    //            m_kia_mko_struct->dtmiLoc_9);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, MF_DTMI, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::mloc(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 5;// 60 - 4
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    uint16_t count_dtmi_dtmi_loc = 0;
    m_kia_data->m_data_db->struct_id = "mloc";
    m_kia_data->m_data_db->struct_id_desc = "МЛОК";
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
        m_pio_bokz->decrypt_dtmi_loc(m_kia_data->m_data_mpi->m_data_word, count_dtmi_dtmi_loc);
        ++count_dtmi_dtmi_loc;
    }
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        set_data_to_device_protocol(str_protocol);
        for (uint16_t num_list = 0; num_list < m_kia_mko_struct->st_mloc_mf.mloc_list_name.size(); ++num_list)
        {
            uint16_t do_shift_left = 0;
            if (m_kia_mko_struct->st_mloc_mf.mloc_list_data[num_list][0] == '-')
                do_shift_left = 1;
            str_protocol.push_back(helpers::format_qstring(m_kia_mko_struct->st_mloc_mf.mloc_list_name[num_list],
                                                           m_kia_settings->m_format_for_desc->shift_description
                                                           + m_kia_settings->m_format_for_desc->shift_for_numbers + do_shift_left)
                                   + m_kia_mko_struct->st_mloc_mf.mloc_list_data[num_list] + "\n");
        }
        str_protocol.push_back("\n\n");

    }
    //    m_parser_db->sendDataIntoDTMILOC(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->dtmiLoc_1, m_kia_mko_struct->dtmiLoc_2, m_kia_mko_struct->dtmiLoc_3, m_kia_mko_struct->dtmiLoc_4,
    //            m_kia_mko_struct->dtmiLoc_5, m_kia_mko_struct->dtmiLoc_6, m_kia_mko_struct->dtmiLoc_7, m_kia_mko_struct->dtmiLoc_8,
    //            m_kia_mko_struct->dtmiLoc_9);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, MF_MLOC, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::smti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем СМТИ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 30;
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

uint16_t Bokzmf::vmti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Получаем ВМТИ!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 30;
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

uint16_t Bokzmf::synchro(uint16_t parametr)
{

}

uint16_t Bokzmf::skor(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД СКОР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 17;
        m_kia_data->m_data_mpi->m_word_data = 6;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "skor";
        m_kia_data->m_data_db->struct_id_desc = "СКОР";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
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

uint16_t Bokzmf::command_no(uint16_t parametr)
{

}

uint16_t Bokzmf::command_to(uint16_t parametr)
{

}

uint16_t Bokzmf::command_full_exp(uint16_t parametr)
{

}

uint16_t Bokzmf::command_loc(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ЛОК!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 6;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "loc";
        m_kia_data->m_data_db->struct_id_desc = "ЛОК";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0005;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::command_otclp(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ОТКЛР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 6;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "otclp";
        m_kia_data->m_data_db->struct_id_desc = "ОТКЛР";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x000F;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::command_openkr(uint16_t parametr)
{

}

uint16_t Bokzmf::command_zkr(uint16_t parametr)
{

}

uint16_t Bokzmf::command_bshv(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД Синхро!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT_BRCST;
        m_kia_data->m_data_mpi->m_sub_address = 29;
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

uint16_t Bokzmf::command_restart(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ОТКЛР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 17;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "rst";
        m_kia_data->m_data_db->struct_id_desc = "РСТ";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x000E;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::command_oo(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем УСД ОТКЛР!");
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_data_to_exc = {0};
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 17;
        m_kia_data->m_data_mpi->m_word_data = 1;
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        m_kia_data->m_data_db->struct_id = "oo";
        m_kia_data->m_data_db->struct_id_desc = "ОО";
        for (uint32_t i = 0; i < m_kia_data->m_data_mpi->m_word_data; i++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x0003;
        }
    };
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::kvaor(uint16_t parametr)
{

}

uint16_t Bokzmf::os(uint16_t parametr)
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

uint16_t Bokzmf::vskou(uint16_t parametr)
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

uint16_t Bokzmf::initial_state(uint16_t parametr)
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

uint16_t Bokzmf::block_ou(uint16_t parametr)
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

uint16_t Bokzmf::unblock_ou(uint16_t parametr)
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

uint16_t Bokzmf::do_frames(uint16_t parametr)
{

}

uint16_t Bokzmf::set_epsilon(float command, uint16_t parametr)
{

}

uint16_t Bokzmf::get_epsilon(uint16_t parametr)
{

}

uint16_t Bokzmf::set_focus(uint16_t parametr)
{

}

uint16_t Bokzmf::get_focus(uint16_t parametr)
{

}

uint16_t Bokzmf::set_texp(uint16_t command, uint16_t parametr)
{

}

uint16_t Bokzmf::get_texp(uint16_t parametr)
{

}

void Bokzmf::preset_before_exchange()
{
    m_kia_data->m_data_mpi->m_is_error = " - УСПЕХ!";
}

void Bokzmf::send_status_info()
{
    QStringList data_status;
    data_status.push_back(QString::number(ST_ST1));
    data_status.push_back(QString::number(m_num_bokz));
    data_status.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior_mf.KC1, 16), 4, '0') );
    emit send_to_client(SEND_STATUS_INFO, data_status);
    data_status.clear();
    data_status.push_back(QString::number(ST_ST2));
    data_status.push_back(QString::number(m_num_bokz));
    data_status.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior_mf.KC2, 16), 4, '0') );
    emit send_to_client(SEND_STATUS_INFO, data_status);
}

void Bokzmf::check_orientation()
{

}

void Bokzmf::post_status_proc(QString &str_protocol)
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
}

void Bokzmf::count_of_fails(uint16_t parametr)
{
    QString str_error_counter;
    str_error_counter.push_back(helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + helpers::format_qstring("Счетчики ошибок", m_kia_settings->m_format_for_desc->shift_count_of_fail) + "\n");
    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
                                + helpers::format_qstring("Счетчик нарушения обмена", m_kia_settings->m_format_for_desc->shift_count_of_fail)
                                + QString::number(m_kia_data->m_data_bokz->m_count_of_exc_fail) + "\n");
    //    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
    //                                + helpers::format_qstring("Счетчик ненормы привязки ко времени", m_kia_settings->m_format_for_desc->shift_count_of_fail)
    //                                + QString::number(m_kia_data->m_data_bokz->m_count_of_time_bind_fail) + "\n");
    //    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
    //                                + helpers::format_qstring("Ориентация не определена", m_kia_settings->m_format_for_desc->shift_count_of_fail)
    //                                + QString::number(m_kia_data->m_data_bokz->m_count_of_no_is_not_def_fail) + "\n");
    //    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
    //                                + helpers::format_qstring("Ненорма кватерниона", m_kia_settings->m_format_for_desc->shift_count_of_fail)
    //                                + QString::number(m_kia_data->m_data_bokz->m_count_of_kvaor_is_not_corr_fail) + "\n");
    //    str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
    //                                + helpers::format_qstring("Нет выхода в режим ожидания", m_kia_settings->m_format_for_desc->shift_count_of_fail)
    //                                + QString::number(m_kia_data->m_data_bokz->m_count_of_time_out_fail) + "\n");
    m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_error_counter, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);
}

uint16_t Bokzmf::start_exchage(uint16_t parametr)
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

void Bokzmf::execute_exchange()
{
    m_kia_data->m_data_mpi->m_status_exchange = m_kia_mpi->execute_exchange(m_kia_data, m_num_bokz);
    parse_mko_protocols(m_kia_protocol, m_kia_data,
                        m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_num_bokz);
    send_mpi_data_to_db();
}

uint16_t Bokzmf::execute_protected_exchange(std::function<void ()> func_mpi_command)
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

void Bokzmf::send_mpi_data_to_db()
{
    m_kia_data->m_data_db->data = QString('\\') + QString('\\') + "x";
    for (unsigned int i = 0; i < m_kia_data->m_data_mpi->m_data_word.size(); i++)
    {
        m_kia_data->m_data_db->data = m_kia_data->m_data_db->data + QString("%1").arg(QString::number(m_kia_data->m_data_mpi->m_data_word[i], 16), 4, '0').toUpper();
    }
    m_parser_db->sendDataIntoMPI(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
}

void Bokzmf::save_to_protocol(QString str_to_protocol, uint16_t parametr)
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

void Bokzmf::save_to_specific_protocol(QString str_to_protocol, uint16_t type_window, uint16_t type_protocol, uint16_t parametr)
{
    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[type_protocol] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_to_protocol, type_window, type_protocol, parametr);
}

void Bokzmf::set_data_to_device_protocol(QString &str_protocol)
{
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers + 1, '-')
                           + helpers::format_qstring(" " + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc) + " ", m_kia_settings->m_format_for_desc->shift_description,'-') + '\n');
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("БШВ", m_kia_settings->m_format_for_desc->shift_description) + QString::number(m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]) + '\n');
    str_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Время", m_kia_settings->m_format_for_desc->shift_description) + QString::fromStdString(m_kia_data->m_data_db->m_datetime) + '\n');
}
