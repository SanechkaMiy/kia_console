#include "bokzmf.h"

Bokzmf::Bokzmf(uint16_t num_bokz, std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
               std::vector<shared_ptr<Timer> > timer, std::vector<std::shared_ptr<Kia_synch_timer> >
               kia_synch_timer, shared_ptr<Kia_mpi> kia_mpi,
               std::shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_db(kia_db)
  , m_timer(timer)
  , m_kia_synch_timer(kia_synch_timer)
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

uint16_t Bokzmf::debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address, uint16_t word_data,
                                   string struct_id, string struct_id_desc, uint16_t parametr)
{

}

Bokzmf::~Bokzmf()
{

}

uint16_t Bokzmf::shtmi1(uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx.lock();
    QString str_to_protocol = format_qstring(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Запрашиваем ШТМИ1!");
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
            str_protocol.push_back(format_qstring(m_kia_mko_struct->st_shtmi1.shtmi1_list_name[num_list],
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

uint16_t Bokzmf::shtmi2(uint16_t parametr)
{

}

uint16_t Bokzmf::mshior(uint16_t parametr)
{

}

uint16_t Bokzmf::dtmi_or_dtmi_loc(uint16_t parametr)
{

}

uint16_t Bokzmf::smti(uint16_t parametr)
{

}

uint16_t Bokzmf::vmti(uint16_t parametr)
{

}

uint16_t Bokzmf::synchro(uint16_t parametr)
{

}

uint16_t Bokzmf::skor(uint16_t parametr)
{

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

}

uint16_t Bokzmf::command_otclp(uint16_t parametr)
{

}

uint16_t Bokzmf::command_openkr(uint16_t parametr)
{

}

uint16_t Bokzmf::command_zkr(uint16_t parametr)
{

}

uint16_t Bokzmf::kvaor(uint16_t parametr)
{

}

uint16_t Bokzmf::os(uint16_t parametr)
{

}

uint16_t Bokzmf::vskou(uint16_t parametr)
{

}

uint16_t Bokzmf::initial_state(uint16_t parametr)
{

}

uint16_t Bokzmf::block_ou(uint16_t parametr)
{

}

uint16_t Bokzmf::unblock_ou(uint16_t parametr)
{

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
    m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[m_num_bokz] = " - УСПЕХ!";
}

uint16_t Bokzmf::start_exchage(uint16_t parametr)
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

uint16_t Bokzmf::execute_protected_exchange(std::function<void ()> func_mpi_command)
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

void Bokzmf::send_mpi_data_to_db()
{
    m_kia_data->m_data_db->data = QString('\\') + QString('\\') + "x";
    for (unsigned int i = 0; i < m_kia_data->m_data_mpi->m_data_word.size(); i++)
    {
        m_kia_data->m_data_db->data = m_kia_data->m_data_db->data + QString("%1").arg(QString::number(m_kia_data->m_data_mpi->m_data_word[i], 16), 4, '0').toUpper();
    }
    //m_parser_db->sendDataIntoMPI(m_num_bokz, m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]);
}

void Bokzmf::save_to_protocol(QString str_to_protocol, uint16_t parametr)
{

}

void Bokzmf::set_data_to_device_protocol(QString &str_protocol)
{
    str_protocol.push_back(format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers + 1, '-')
                           + format_qstring(" " + QString::fromStdString(m_kia_data->m_data_db->struct_id_desc) + " ", m_kia_settings->m_format_for_desc->shift_description,'-') + '\n');
    str_protocol.push_back(format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + format_qstring("БШВ", m_kia_settings->m_format_for_desc->shift_description) + QString::number(m_kia_settings->m_data_for_db->bshv[m_kia_data->m_data_bi->m_num_used_bi]) + '\n');
    str_protocol.push_back(format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                           + format_qstring("Время", m_kia_settings->m_format_for_desc->shift_description) + QString::fromStdString(m_kia_data->m_data_db->m_datetime) + '\n');
}
