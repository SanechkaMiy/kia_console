#include "kia_cyclogram_bokzmf.h"

Kia_cyclogram_bokzmf::Kia_cyclogram_bokzmf(std::shared_ptr<Kia_timers> kia_timers, std::vector<std::shared_ptr<Bokz> > bokz,
                                           shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings):
    m_kia_timers(kia_timers),
    m_bokz(bokz),
    m_kia_protocol(kia_protocol),
    m_kia_settings(kia_settings)
{
    m_kia_data_cyclogram.reset(new Kia_data_cyclogram());
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error.resize(m_kia_settings->m_count_bokz);
    create_mpi_commands();
    create_list_cyclograms_for_tp();
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_state_on(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_state_off(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_oo(uint16_t &num_bokz, uint16_t parametr)
{
    if (m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                       * m_kia_settings->m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] && m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        {
            if(m_bokz[num_bokz]->command_oo() == KiaS_SUCCESS)
            {
                wait_some_time(num_bokz, m_kia_settings->m_freq_bokz);
                if(m_bokz[num_bokz]->command_bshv() == KiaS_SUCCESS)
                {
                    m_bokz[num_bokz]->command_no();
                }
            }
        }
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_no(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму НО!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    //start_no(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        start_regular_cyclogram(num_bokz);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму НО!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_to(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_ai(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_loc(uint16_t &num_bokz, uint16_t parametr)
{

}

void Kia_cyclogram_bokzmf::cyclogram_define_address(uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation_no(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation_to(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation_loc(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_1s_mark(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_check_address(uint16_t &num_bokz, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.lock();
    std::vector<std::pair<uint16_t, uint16_t>> status_work_lpi;
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму проверки адреса прибора!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    uint16_t cur_address = m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address;
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = check_lpi;
        for (uint16_t address = 0; address < constants::max_avalable_address; ++address)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address = address;
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
            if ((cur_address != address) && (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS))
            {

                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Обнаружен ответ на ЛПИ ")
                                 + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) +
                                 " по адресу " + QString::number(address) + ", адрес прибора "
                                 + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address) + "\n", parametr);
            }
            else if((cur_address == address) && (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS))
            {
                status_work_lpi.push_back(std::make_pair(KiaS_SUCCESS, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi));
                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                 + QString("Адрес ") + QString::number(address) + " прибора подтвержден на линии "
                                 + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
            }
            else if((cur_address == address) && (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS))
            {
                status_work_lpi.push_back(std::make_pair(KiaS_FAIL, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi));
                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                 + QString("Линия ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + " не исправна"+ "\n", parametr);
            }
        }
    }
    for (auto el : status_work_lpi)
    {
        if (el.first == KiaS_SUCCESS)
            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
        else
            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
    }
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму проверки адреса прибора!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address = cur_address;

    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.unlock();
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_test_mko(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму теста МКО!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = check_lpi;
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
        m_bokz[num_bokz]->initial_state(EP_NOPROTECTEDEXCHANGE);
    }
    check_work_lpi(num_bokz, 0);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = 1;
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
    m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
    check_work_lpi(num_bokz, 1);
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = check_lpi;
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
        m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
        m_bokz[num_bokz]->vskou(EP_NOPROTECTEDEXCHANGE);
    }

    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = check_lpi;
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);

        for (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_word_data = 1; m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_word_data < constants::packetSize - 1; m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_word_data++)
        {
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                             + QString("Выбор количества СД ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_word_data) + "\n", parametr);
            m_bokz[num_bokz]->vmti(EP_NOPROTECTEDEXCHANGE);
            m_bokz[num_bokz]->smti(EP_NOPROTECTEDEXCHANGE);
            uint16_t count_if_true = 0;
            for (uint16_t num_word = 0; num_word < m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_word_data; num_word++)
            {
                if (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_data_to_exc[num_word] == m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_data_word[num_word + 2])
                {
                    count_if_true++;
                }
            }
            if (count_if_true == m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_word_data)
                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                 + QString("Для количества СД ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_word_data) + " ВМТИ И СМТИ совпадают""\n", parametr);

        }
    }

    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму теста МКО!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_test_synchro(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_technical_run(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_zkr(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_full_frames(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::start_regular_cyclogram(uint16_t &num_bokz, uint16_t count_do_cyclogram)
{
    uint16_t index_do_cyclogram = 0;
    auto count_cyclogram = count_do_cyclogram;
    if (count_cyclogram != 0)
        count_cyclogram -= 1;
    while (index_do_cyclogram <= count_cyclogram && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_for_takt);

        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            for (uint16_t num_mpi_command = 0; num_mpi_command < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_mpi_command; ++num_mpi_command)
            {
                if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram[num_mpi_command] == KiaS_SUCCESS && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    if(get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command[num_mpi_command])(num_bokz, EP_DOALL) == KiaS_FAIL)
                        break;
                }
            }
            if (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_FAIL)
            {
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
                break;
            }
            if ((m_bokz[num_bokz]->m_kia_mko_struct->st_mshior.KC1 & 0xf000) == 0x4000)
            {
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
                break;
            }
            if (count_do_cyclogram != 0)
            {
                if ((m_bokz[num_bokz]->m_kia_mko_struct->st_mshior.KC1 & 0xf000) == 0xe000)
                    index_do_cyclogram++;
            }
        }
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

void Kia_cyclogram_bokzmf::wait_some_time(uint16_t &num_bokz, const uint16_t &wait_s)
{
    for (uint16_t sec = 0; sec < wait_s; ++sec)
    {
        if (!m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            break;
        m_kia_timers->m_kia_synch_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]
                ->wait_for_event(m_kia_timers->m_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]);
    }
}

void Kia_cyclogram_bokzmf::wait_for_bi_takt(uint16_t &num_bokz)
{
    while (m_kia_settings->m_data_for_db->bshv[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi] % m_kia_settings->m_freq_bokz != 0)
    {
        m_kia_timers->m_kia_synch_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]
                ->wait_for_event(m_kia_timers->m_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]);
    }
}

void Kia_cyclogram_bokzmf::wait_some_time_for_one_launch(const uint16_t &wait_s)
{
    for (uint16_t sec = 0; sec < wait_s; ++sec)
    {
        if (!m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
            break;
        this_thread::sleep_for(std::chrono::milliseconds(m_kia_settings->m_timer_interval));
    }
}

void Kia_cyclogram_bokzmf::save_to_protocol(uint16_t &num_bokz, QString str_to_protocol, uint16_t parametr)
{
    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_SYSTEM] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(num_bokz, str_to_protocol, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] == KiaS_SUCCESS)
        if (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
            m_kia_protocol->preset_before_save_and_out(num_bokz, str_to_protocol, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(num_bokz, str_to_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
}

void Kia_cyclogram_bokzmf::preset_before_exchange(uint16_t num_bokz)
{
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
}

void Kia_cyclogram_bokzmf::create_mpi_commands()
{
    auto fu_shtmi1 = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->shtmi1(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command.push_back(std::make_tuple(fu_shtmi1, "ШТМИ1", SHTMI_1));
    auto fu_shtmi2 = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->shtmi2(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command.push_back(std::make_tuple(fu_shtmi2, "ШТМИ2", SHTMI_2));
    auto fu_mshior = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->mshior(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command.push_back(std::make_tuple(fu_mshior, "МШИОР", MSHI_OR));
    auto dtmi = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->dtmi_or_dtmi_loc(EP_NOFULLEXCHANGE);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command.push_back(std::make_tuple(dtmi, "ДТМИ", DTMI_ONE));
    auto mloc = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->mloc(EP_NOFULLEXCHANGE);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command.push_back(std::make_tuple(mloc, "МЛОК", MLOCK_ONE));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_mpi_command = m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command.size();
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_mpi_command);
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram.end(), KiaS_FAIL);
}

void Kia_cyclogram_bokzmf::create_list_cyclograms_for_tp()
{
    auto cycl_no = [this](uint16_t num_bokz, uint16_t cound_do_cyclogram, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_operation_no(num_bokz, cound_do_cyclogram, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.push_back(std::make_tuple(cycl_no, "Начальная ориентация (НО)", CYCLOGRAM_NO));
    auto cycl_to = [this](uint16_t num_bokz, uint16_t cound_do_cyclogram, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_operation_to(num_bokz, cound_do_cyclogram, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.push_back(std::make_tuple(cycl_to, "Текущая ориентация (ТО)", CYCLOGRAM_TO));
    auto cycl_loc = [this](uint16_t num_bokz, uint16_t cound_do_cyclogram, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_operation_loc(num_bokz, cound_do_cyclogram, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.push_back(std::make_tuple(cycl_loc, "Локализация (ЛОК)", CYCLOGRAM_LOC));

    for (uint16_t num_cycl = 0; num_cycl < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.size(); num_cycl++)
        m_index_for_cyclograms[std::get<CYCL_TYPE_TO_SEND>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp[num_cycl])] = num_cycl;

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_tp = m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.size();
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_tp);
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_tp);
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.end(), 10);
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.end(), KiaS_FAIL);
}

void Kia_cyclogram_bokzmf::check_work_lpi(uint16_t &num_bokz, const uint16_t &lpi)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Выбор ЛПИ ") + QString::number(lpi) + "\n");
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = lpi;
    m_bokz[num_bokz]->block_ou(EP_NOPROTECTEDEXCHANGE);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = abs(lpi - 1);
    m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = lpi;
    m_bokz[num_bokz]->unblock_ou(EP_NOPROTECTEDEXCHANGE);
}
