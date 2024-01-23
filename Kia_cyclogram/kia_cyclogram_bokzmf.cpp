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
    create_list_other_mpi_commands();
    create_list_cyclograms_for_ri();
    create_list_cyclograms_for_tp();
    create_list_command_for_oo();
    create_list_command_for_loc();
    create_list_chpn();
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_state_on(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_state_off(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_oo(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Начинаем циклограмму ОО!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    if (m_bokz[num_bokz]->command_otclp(parametr) == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                       * m_kia_settings->m_freq_bokz);
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_OO][CIO_OO] == KiaS_SUCCESS
                && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            sleep_for_pause(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[SCO_OO][CIO_OO]);
            if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do[SCO_OO][CIO_OO])(num_bokz, parametr) != KiaS_FAIL)
                start_regular_cyclogram(num_bokz);
        }

    }
    post_exchange(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);

    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму ОО!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_no(uint16_t &num_bokz, uint16_t parametr)
{
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
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму ЛОК!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    if (m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                       * m_kia_settings->m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            start_loc(num_bokz);
    }
    post_exchange(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Выполнили циклограмму ЛОК!") + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

void Kia_cyclogram_bokzmf::cyclogram_define_address(uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Начинаем циклограмму функционирования!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_tp; num_cyclogram++)
    {
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp[num_cyclogram] == KiaS_SUCCESS && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp[num_cyclogram])(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp[num_cyclogram], parametr) == KiaS_FAIL)
                break;
        }
    }
    post_exchange(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму функционирования!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation_oo(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Начинаем циклограмму функционирования ОО!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    if (m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                       * m_kia_settings->m_freq_bokz);
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_OO][CIO_OO] == KiaS_SUCCESS
                && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            sleep_for_pause(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[SCO_OO][CIO_OO]);
            if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do[SCO_OO][CIO_OO])(num_bokz, parametr) != KiaS_FAIL)
                start_regular_cyclogram(num_bokz, count_do_cyclogram, parametr);
        }

    }
    post_exchange(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму функционирования ОО!" ) + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation_no(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation_to(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_operation_loc(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму ЛОК!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    if(m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                       * m_kia_settings->m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            start_loc(num_bokz, parametr, count_do_cyclogram);
    }
    post_exchange(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Выполнили циклограмму ЛОК!") + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
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

        uint16_t counter_if_success_vmti_smti_check = 0;
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
                counter_if_success_vmti_smti_check++;

            std::cout  << "lpi " << m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi << " " << m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange << std::endl;
            if (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS
                    && counter_if_success_vmti_smti_check == constants::packetSize - 1)
            {
                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                 + QString("Для ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + " ВМТИ И СМТИ совпадают""\n", parametr);
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_SUCCESS;
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
            }
            else
            {
                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                 + QString("Для ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + " ВМТИ И СМТИ не совпадают""\n", parametr);
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
            }

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
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Начинаем циклограмму Технологический прогон!") + "\n", parametr);
    preset_before_exchange(num_bokz);
    uint16_t index_technical_run = 0;
    auto count_do_tp = m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_TP][SPC_COUNT];
    if (count_do_tp != 0)
        count_do_tp -= 1;
    while ((index_technical_run <= count_do_tp && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz]))
    {
        cyclogram_operation(num_bokz, parametr);
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_TP][SPC_COUNT] != 0)
            index_technical_run++;
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_TP][SPC_PERIOD]
                       * m_kia_settings->m_freq_bokz);
    }
    if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_off_power_for_tp)
        m_bokz[num_bokz]->m_kia_data->m_data_bi->m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    post_exchange(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму Технологический прогон!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::cyclogram_zkr(uint16_t &num_bokz, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzmf::cyclogram_full_frames(uint16_t &num_bokz, uint16_t parametr)
{

}

void Kia_cyclogram_bokzmf::set_cyclogram_settings()
{
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_localization = 2;
}

uint16_t Kia_cyclogram_bokzmf::start_loc(uint16_t &num_bokz, uint16_t parametr, uint16_t count_do_loc)
{
    uint16_t index_do_loc = 0;
    bool do_breake = false;
    while (index_do_loc <= count_do_loc && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] && m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_LOC].size(); num_cyclogram++)
        {
            if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_LOC][num_cyclogram] == KiaS_SUCCESS
                    && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            {
                sleep_for_pause(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[SCO_LOC][num_cyclogram]);
                if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do[SCO_LOC][num_cyclogram])(num_bokz, parametr) == KiaS_FAIL)
                {
                    do_breake = true;
                    break;
                }
            }
        }
        if (do_breake)
            break;

        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_localization
                       * m_kia_settings->m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] && m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
        {
            if(m_bokz[num_bokz]->mloc(parametr) == KiaS_SUCCESS)
            {
                if (count_do_loc != 0)
                    index_do_loc++;
            }
            else
                break;
        }
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzmf::start_regular_cyclogram(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{
    uint16_t index_do_cyclogram = 0;
    auto count_cyclogram = count_do_cyclogram;
    if (count_cyclogram != 0)
        count_cyclogram -= 1;
    while (index_do_cyclogram <= count_cyclogram && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            do_oo(num_bokz, parametr);

            for (uint16_t num_mpi_command = 0; num_mpi_command < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_mpi_command; ++num_mpi_command)
            {
                if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram[num_mpi_command] == KiaS_SUCCESS && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    if(get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command[num_mpi_command])(num_bokz, parametr) == KiaS_FAIL)
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
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_for_takt);
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

void Kia_cyclogram_bokzmf::do_oo(uint16_t &num_bokz, uint16_t parametr)
{
    auto start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    uint32_t sum_pause = 0;
    for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_OO].size() - 1; num_cyclogram++)
    {
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_OO][num_cyclogram + 1] == KiaS_SUCCESS
                && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            sleep_for_pause(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[SCO_OO][num_cyclogram + 1]);
            if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do[SCO_OO][num_cyclogram + 1])(num_bokz, parametr) == KiaS_FAIL)
                break;
            sum_pause = sum_pause + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[SCO_OO][num_cyclogram + 1];
        }
    }
    auto end = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    sleep_for_pause((m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_pre_do_mshior_in_oo + sum_pause) - (end - start));
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

void Kia_cyclogram_bokzmf::create_list_other_mpi_commands()
{
    auto fu_smti = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->smti(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_smti, "СМТИ", SMTI));

    auto fu_vmti = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->vmti(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_vmti, "ВМТИ", VMTI));

    auto separator = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->smti(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(separator, "separator", VMTI));
}

void Kia_cyclogram_bokzmf::create_list_command_for_oo()
{
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>> command_cycl;

    auto comm_oo = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_oo(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_oo, "УСД ОО", CYCLOGRAM_TECH_RUN));

    auto comm_bshv = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_bshv(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_bshv, "БШВ", CYCLOGRAM_TECH_RUN));

    auto comm_skor = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->skor(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_skor, "УСД СКОР", CYCLOGRAM_ZKR));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do.push_back(command_cycl);
    std::vector<uint16_t> do_cyclogram(command_cycl.size());
    std::fill(do_cyclogram.begin(),
              do_cyclogram.end(), KiaS_SUCCESS);
    std::vector<uint64_t> sleep_to_command_cyclogram(command_cycl.size());
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do.push_back(do_cyclogram);
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram.push_back(sleep_to_command_cyclogram);
}

void Kia_cyclogram_bokzmf::create_list_command_for_loc()
{
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>> command_cycl;
    auto comm_loc = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_loc(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_loc, "УСД ЛОК", CYCLOGRAM_TECH_RUN));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do.push_back(command_cycl);
    std::vector<uint16_t> do_cyclogram(command_cycl.size());
    std::fill(do_cyclogram.begin(),
              do_cyclogram.end(), KiaS_SUCCESS);
    std::vector<uint64_t> sleep_to_command_cyclogram(command_cycl.size());
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do.push_back(do_cyclogram);
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram.push_back(sleep_to_command_cyclogram);
}

void Kia_cyclogram_bokzmf::create_list_cyclograms_for_tp()
{
    auto cycl_oo = [this](uint16_t num_bokz, uint16_t cound_do_cyclogram, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_operation_oo(num_bokz, cound_do_cyclogram, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.push_back(std::make_tuple(cycl_oo, "Определение ориентация (ОО)", CYCLOGRAM_OO));

    auto cycl_loc = [this](uint16_t num_bokz, uint16_t cound_do_cyclogram, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_operation_loc(num_bokz, cound_do_cyclogram, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.push_back(std::make_tuple(cycl_loc, "Локализация (ЛОК)", CYCLOGRAM_LOC));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_tp = m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.size();
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_tp);
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_tp);
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.end(), 10);
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.end(), KiaS_FAIL);
}

void Kia_cyclogram_bokzmf::create_list_chpn()
{
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Время экспонирования", "texp", IS_PARAM, Bokzmf::TP_TEXP));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Фокус", "focus", IS_PARAM, Bokzmf::TP_FOC));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Координата X", "cord_x", IS_PARAM, Bokzmf::TP_X));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Координата Y", "cord_y", IS_PARAM, Bokzmf::TP_Y));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Допуск распознавания", "epsilon", IS_PARAM, Bokzmf::TP_EPS));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Матрица ПСК", "mat_psk", IS_TABLE, Bokzmf::TP_MAT));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Кватернион ориентации", "qo", IS_TABLE, Bokzmf::TP_QA));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Угловая скорость", "w0", IS_TABLE, Bokzmf::TP_W));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Коэффициенты дисторсии", "kd", IS_TABLE, Bokzmf::TP_KD));
}

void Kia_cyclogram_bokzmf::create_list_cyclograms_for_ri()
{
    auto cycl_technical_run = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_technical_run(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri.push_back(std::make_tuple(cycl_technical_run, "Технологический прогон", CYCLOGRAM_TECH_RUN));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_ri = m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri.size();

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_max_cyclogram_ri);

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
