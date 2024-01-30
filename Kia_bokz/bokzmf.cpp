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
    m_kia_data->m_data_bokz->m_type_orient = TO_NO;
    create_count_of_exc_fail();
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

    m_pio_bokz->decrypt_shtmi1(m_kia_data->m_data_mpi->m_data_word);
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        set_data_to_device_protocol(str_protocol);
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name, m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data));
        str_protocol.push_back("\n\n");
    }
    m_parser_db->sendDataIntoSHTMI1_MF(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shtmi1_mf);
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
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name, m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data));
        str_protocol.push_back("\n\n");
    }
    m_parser_db->sendDataIntoSHTMI2_MF(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_shtmi2_mf);
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
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_mshior_mf.mshior_list_name, m_kia_mko_struct->st_mshior_mf.mshior_list_data));

        str_protocol.push_back("\n\n");

        post_status_proc(m_kia_mko_struct->st_mshior_mf.KC1, m_kia_mko_struct->st_mshior_mf.KC2, str_protocol);

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
        m_pio_bokz->parse_dtmi(m_kia_data->m_data_bokz->m_type_orient);
        set_data_to_device_protocol(str_protocol);
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_dtmi_mf.dtmi_list_name, m_kia_mko_struct->st_dtmi_mf.dtmi_list_data));
        str_protocol.push_back("\n\n");

    }
    m_parser_db->sendDataIntoDTMI_MF(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_dtmi_mf);
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
        m_kia_data->m_data_db->struct_id = "mloc";
        m_kia_data->m_data_db->struct_id_desc = "МЛОК";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    uint16_t count_dtmi_dtmi_loc = 0;
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ") + QString::fromStdString(m_kia_data->m_data_db->struct_id);
    uint16_t count_to_exchange = 9;
    if ((parametr & EP_NOFULLEXCHANGE) != 0)
        count_to_exchange = 1;
    while (count_dtmi_dtmi_loc < count_to_exchange)
    {
        m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
        m_pio_bokz->decrypt_dtmi_loc(m_kia_data->m_data_mpi->m_data_word, count_dtmi_dtmi_loc);
        ++count_dtmi_dtmi_loc;
    }
    QString str_protocol;
    if (m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        m_pio_bokz->parse_dtmi_loc();
        set_data_to_device_protocol(str_protocol);
        str_protocol.push_back(set_data_from_mko_struct(m_kia_mko_struct->st_mloc_mf.mloc_list_name, m_kia_mko_struct->st_mloc_mf.mloc_list_data));
        str_protocol.push_back("\n\n");

    }
    m_parser_db->sendDataIntoMLOC_MF(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi], m_kia_mko_struct->st_mloc_mf);
    m_kia_protocol->save_and_out_to_dev_protocols(m_num_bokz, str_protocol, MF_MLOC, parametr);
    save_to_protocol(str_to_protocol, parametr);
    save_to_specific_protocol(str_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::upn(uint16_t type_upn, QStringList value, uint16_t parametr)
{
    m_func_upn[type_upn](value, parametr);
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::chpn(QStringList type_chpn, uint16_t parametr)
{
    command_chpn(parametr);
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

uint16_t Bokzmf::chkd(uint16_t parametr)
{
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 23;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "chkd";
        m_kia_data->m_data_db->struct_id_desc = "ЧКД";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ")
            + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);
    uint16_t count_of_chpn_arr = 2;
    for (uint16_t num_arr = 0; num_arr < count_of_chpn_arr; num_arr++)
    {
        m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
        m_pio_bokz->decrypt_chkd(m_kia_data->m_data_mpi->m_data_word, num_arr);
    }
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::smti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Передаем ")
            + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::vmti(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
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
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Получаем ")
            + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::synchro(uint16_t parametr)
{
    return m_kia_data->m_data_mpi->m_status_exchange;
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

uint16_t Bokzmf::command_bin_exp(uint16_t parametr)
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
        auto [sec_whole_part, milliseconds] = helpers::get_seconds_for_bshv();
                std::array <uint16_t, 2> second = {0x0000, 0x0000};
        memcpy(&second, &sec_whole_part, sizeof(second));
        m_kia_data->m_data_mpi->m_data_to_exc[0] = 0x002E;
        m_kia_data->m_data_mpi->m_data_to_exc[1] = second[1];
        m_kia_data->m_data_mpi->m_data_to_exc[2] = second[0];
        m_kia_data->m_data_mpi->m_data_to_exc[3] = milliseconds;
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
        m_kia_data->m_data_bokz->m_count_fail[Bokzmf::CHRES]++;
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

uint16_t Bokzmf::do_frames(uint16_t type_recieve, uint16_t type_frame, uint16_t parametr)
{

}

uint16_t Bokzmf::command_upn(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 0;
        m_kia_data->m_data_mpi->m_format = DATA_BC_RT;
        m_kia_data->m_data_mpi->m_sub_address = 22;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "upn";
        m_kia_data->m_data_db->struct_id_desc = "УПН";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
        for (uint16_t num_word = 0; num_word < m_kia_data->m_data_mpi->m_word_data; num_word++)
        {
            m_kia_data->m_data_mpi->m_data_to_exc[num_word] = m_kia_data->m_data_mpi->m_data_upn[num_word];
        }
    };
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Получаем ")
            + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);
    m_set_control_word();
    m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Bokzmf::command_chpn(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    preset_before_exchange();
    m_set_control_word = [this]()
    {
        m_kia_data->m_data_mpi->m_direction = 1;
        m_kia_data->m_data_mpi->m_format = DATA_RT_BC;
        m_kia_data->m_data_mpi->m_sub_address = 24;
        m_kia_data->m_data_mpi->m_word_data = 32;
        m_kia_data->m_data_db->struct_id = "chpn";
        m_kia_data->m_data_db->struct_id_desc = "ЧПН";
        m_kia_data->m_data_mpi->m_code_word = ((m_kia_data->m_data_mpi->m_address << 11) | (m_kia_data->m_data_mpi->m_direction << 10) | (m_kia_data->m_data_mpi->m_sub_address << 5) | (m_kia_data->m_data_mpi->m_word_data & 0x1F));
    };
    m_set_control_word();
    QString str_to_protocol = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ")
            + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc);
    uint16_t count_of_chpn_arr = 2;
    for (uint16_t num_arr = 0; num_arr < count_of_chpn_arr; num_arr++)
    {
        m_kia_data->m_data_mpi->m_status_exchange = start_exchage(parametr);
        m_pio_bokz->decrypt_chpn(m_kia_data->m_data_mpi->m_data_word, num_arr);

    }
    send_data_read_chpn();
    save_to_protocol(str_to_protocol, parametr);
    m_kia_settings->m_flags_for_thread->m_mtx.unlock();
    return m_kia_data->m_data_mpi->m_status_exchange;
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
    const uint16_t norm_qaor = 1;
    const uint16_t max_or_is_not_def = 100;
    m_kia_data->m_data_db->m_norm_qaor = sqrt(pow(m_kia_mko_struct->st_mshior.Qo0,2) + pow(m_kia_mko_struct->st_mshior.Qo1,2) + pow(m_kia_mko_struct->st_mshior.Qo2, 2)  + pow(m_kia_mko_struct->st_mshior.Qo3,2));
    if ((m_kia_data->m_data_mpi->m_data_word[2] & 0xf000) == 0xe000)
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
    if (m_kia_data->m_data_bokz->m_count_fail[CHNOR] >= max_or_is_not_def && (m_kia_data->m_data_mpi->m_data_word[2] & 0xf000) != 0x4000)
    {
        m_kia_data->m_data_bokz->m_count_fail[CHNRO]++;
    }
}

void Bokzmf::post_status_proc(uint16_t st1, uint16_t st2, QString &str_protocol)
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
    str_protocol.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Результат калибровки", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 1, "1 - требуется запрос ЧКД", "0 - запрос ЧКД не требуется") + "\n");

    str_protocol.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Питание ФПУ", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 2, "1 - подано", "0 - снято") + "\n");

    str_protocol.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Признак наличия КС \"БШВ\" на входе", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 3, "1 - есть", "0 - нет") + "\n");

    str_protocol.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Признак наличия КС \"СКОР\" на входе", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 3, "1 - есть", "0 - нет") + "\n");

    str_protocol.push_back(helpers::format_qstring("5-8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Счетчик ошибочных Синхропосылок КС \"БШВ\"", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_count_sec_fail_mark(st1, 5) + "\n");

    str_protocol.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Скорость определена", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 9, "1 - скорость определена", "0 - скорость не определена") + "\n");

    str_protocol.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Готовность к работе по результатам теста", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 10, "1 - ОУ ЭО ЗД к работе готов",
                                                 "0 - ОУ ЭО ЗД не готов к работе") + "\n");

    str_protocol.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Ориентация определена", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 11, "1 - ориентация определена",
                                                 "0 - ориентация отсутствует") + "\n");

    str_protocol.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Признак перехода в \"Слежение\"", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 12, "1 - переход выполнен",
                                                 "0 - переход не выполнен") + "\n");

    str_protocol.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Режим ориентации", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 13, "1 - ОУ ЭО ЗД находится в режиме ОО",
                                                 "0 - ОУ ЭО ЗД не находится в режиме ОО") + "\n");

    str_protocol.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Режим ожидания", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 14, "1 - выполнение команды завершено",
                                                 "0 - команда выполняется") + "\n");

    str_protocol.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Команда выполнена", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status(st1, 15, "1 - выполнение команды завершено успешно",
                                                 "0 - выполнение команды завершено неуспешно") + "\n");

    str_protocol.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Расшифровка Код состояния 2:", m_kia_settings->m_format_for_desc->shift_description) + "\n");
    str_protocol.push_back(helpers::format_qstring("1-4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Код последнего полученного УСД", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_last_usd(st2, 0, {{0x0003, "ОО"}, {0x0005, "ЛОК"}, {0x000e, "РСТ"}, {0x000f, "ОТКЛР"}}) + "\n");
    str_protocol.push_back(helpers::format_qstring("5-20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Код текущего состояния прибора", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status_dev(st2, 0) + "\n");
    str_protocol.push_back(helpers::format_qstring("21-38", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + helpers::format_qstring("Код ошибки", m_kia_settings->m_format_for_desc->shift_description)
                           + helpers::get_status_error_mf(st2, 8) + "\n");
}

void Bokzmf::count_of_fails(uint16_t parametr)
{
    QString str_error_counter;
    str_error_counter.push_back(helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + helpers::format_qstring("Счетчики ошибок", m_kia_settings->m_format_for_desc->shift_count_of_fail) + "\n");
    for (uint16_t num_counter = 0; num_counter < m_kia_data->m_data_bokz->m_count_fail_descr.size(); num_counter++)
    {
        str_error_counter.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_date_time)
                                    + helpers::format_qstring(m_kia_data->m_data_bokz->m_count_fail_descr[num_counter].first, m_kia_settings->m_format_for_desc->shift_count_of_fail)
                                    + QString::number(m_kia_data->m_data_bokz->m_count_fail[num_counter]) + "\n");
    }
    m_kia_protocol->preset_before_save_and_out(m_num_bokz, str_error_counter, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);
}

void Bokzmf::send_data_read_chpn()
{
    m_kia_data->m_data_bokz->m_chpn_data.push_back(std::make_tuple(IS_PARAM, TP_TEXP, QStringList(QString::number(m_kia_mko_struct->st_chpn_mf.chpn_1_mf.Texp))));
    m_kia_data->m_data_bokz->m_chpn_data.push_back(std::make_tuple(IS_PARAM, TP_FOC, QStringList(QString::number(m_kia_mko_struct->st_chpn_mf.chpn_1_mf.Foc))));
    m_kia_data->m_data_bokz->m_chpn_data.push_back(std::make_tuple(IS_PARAM, TP_X, QStringList(QString::number(m_kia_mko_struct->st_chpn_mf.chpn_1_mf.XG))));
    m_kia_data->m_data_bokz->m_chpn_data.push_back(std::make_tuple(IS_PARAM, TP_Y, QStringList(QString::number(m_kia_mko_struct->st_chpn_mf.chpn_1_mf.YG))));
    m_kia_data->m_data_bokz->m_chpn_data.push_back(std::make_tuple(IS_PARAM, TP_EPS, QStringList(QString::number(m_kia_mko_struct->st_chpn_mf.chpn_1_mf.Epsilon))));
    QStringList matrix;
    for (auto el : m_kia_mko_struct->st_chpn_mf.chpn_1_mf.m_pr)
        matrix.push_back(QString::number(el));
    m_kia_data->m_data_bokz->m_chpn_data.push_back(std::make_tuple(IS_PARAM, TP_MAT, matrix));

    for (auto el : m_kia_data->m_data_bokz->m_chpn_data)
    {
        QStringList data;
        data.push_back(QString::number(m_num_bokz));
        data.push_back(QString::number(std::get<0>(el)));
        data.push_back(QString::number(std::get<1>(el)));
        for (auto el : std::get<2>(el))
            data.push_back(el);
        emit send_to_client(SEND_COMMAND, data);
    }
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
    m_kia_data->m_data_mpi->m_status_exchange = m_kia_mpi->execute_exchange(m_kia_data);
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

std::pair<bool, QString> Bokzmf::check_post(uint16_t post)
{
    uint16_t max_count_digit = 16;
    QStringList descr_post = {"Номер банка загрузки", "Признак холодного рестарта",
                              "Тест внешнего ОЗУ", "Целостнотсь программы банк 0",
                              "Целостнотсь программы банк 1", "Целостнотсь калибровачных констант банк 0",
                              "Целостнотсь калибровачных констант банк 1", "Целостность каталога",
                              "Рез1", "Рез2", "Рез3", "Рез4", "Тест видеотракта",
                              "Тест внутреннего ОЗУ", "Переключение загрузочных банков", "Рез5"};
    QString str_fail;
    bool post_is_good = true;
    for (uint16_t num_digit = 0; num_digit < max_count_digit; num_digit++)
    {
        if (num_digit >= 8 && num_digit <= 11)
            continue;
        if ((post & (0x0001 << num_digit)) != 1)
        {
            str_fail.push_back(str_fail[num_digit] + " не норма" + "\n");
            post_is_good = false;
        }

    }
    return {post_is_good, str_fail};
}

void Bokzmf::create_count_of_exc_fail()
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
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Неправильная выдача УПН", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Неправильная выдача КП", 5));
    m_kia_data->m_data_bokz->m_count_fail_descr.push_back(std::make_pair("Количество рестартов", 5));
    m_kia_data->m_data_bokz->m_count_fail.resize(m_kia_data->m_data_bokz->m_count_fail_descr.size());
}

void Bokzmf::set_type_upn_func()
{
    auto func_kd = [this](QStringList value, uint16_t parametr)
    {
        std::array<array<float, kd_size>, 2> kd;
        for (uint16_t ind = 0; ind < value.size() / 2; ind++)
        {
            kd[0][ind] = value[ind].toFloat();
            kd[1][ind] = value[ind + kd_size].toFloat();
        }
        memcpy(&m_kia_data->m_data_mpi->m_data_upn[1], &(kd[0]), sizeof(kd[0]));
        command_upn(parametr);

        memcpy(&m_kia_data->m_data_mpi->m_data_upn[1], &(kd[1]), sizeof(kd[1]));
        command_upn(parametr);
        return m_kia_data->m_data_mpi->m_status_exchange;
    };
    m_func_upn.push_back(func_kd);

    auto func_qa = [this](QStringList value, uint16_t parametr)
    {
        array<float, constants::size_qa> qa;
        for (uint16_t qa_index = 0; qa_index < value.size(); ++qa_index)
            qa[qa_index] = value[qa_index].toFloat();

        memcpy(&m_kia_data->m_data_mpi->m_qa, &qa, sizeof(qa));
        return m_kia_data->m_data_mpi->m_status_exchange;
    };
    m_func_upn.push_back(func_qa);

    auto func_w = [this](QStringList value, uint16_t parametr)
    {
        array<float, constants::size_w> w;
        for (uint16_t w_index = 0; w_index < value.size(); ++w_index)
            w[w_index] = value[w_index].toFloat();

        memcpy(&m_kia_data->m_data_mpi->m_w, &w, sizeof(w));
        return m_kia_data->m_data_mpi->m_status_exchange;
    };
    m_func_upn.push_back(func_w);
}

void Bokzmf::set_type_chpn_func()
{
    auto func_chkd = [this](uint16_t parametr)
    {
        return chkd(parametr);
    };
    m_map_chpn[TP_KD] = func_chkd;
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
