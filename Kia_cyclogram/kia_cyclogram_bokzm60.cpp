#include "kia_cyclogram_bokzm60.h"

Kia_cyclogram_bokzm60::Kia_cyclogram_bokzm60(std::shared_ptr<Kia_timers> kia_timers,
                                             std::vector<std::shared_ptr<Bokz>> bokz,
                                             std::shared_ptr<Kia_settings> kia_settings):
    m_kia_timers(kia_timers),
    m_bokz(bokz),
    m_kia_settings(kia_settings)
{
    m_kia_data_cyclogram.reset(new Kia_data_cyclogram());
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error.resize(m_kia_settings->m_count_bokz);

    set_cyclogram_settings();
    create_list_power_cyclograms();
    create_mpi_commands();
    create_list_other_mpi_commands();
    create_list_cyclograms_for_state_work();
    create_list_cyclograms_for_tp();
    create_list_cyclograms_for_ai();
    create_list_cyclograms_for_ri();
    create_list_command_for_no();
    create_list_command_for_to();
    create_list_command_for_loc();
    create_list_chpn();
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_state_on(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму участка включения!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_POWER]
                   * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        if(m_bokz[num_bokz]->shtmi1() == KiaS_SUCCESS)
        {
            QString is_ready = "";
            if ((static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_SHTMI1].data[m_bokz[num_bokz]->m_index_mpi_array[M60_SHTMI1]["post"]])) & 0x0f00) == 0x0400)
            {
                m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_SUCCESS;
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = "УСПЕХ!";
                is_ready = " готов";
                wait_for_bi_takt(num_bokz);
                if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    m_bokz[num_bokz]->synchro();
                }
            }
            else
            {
                is_ready = " не готов";
                m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";

            }
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                             + QString("Прибор на канале №") + QString::number(m_bokz[num_bokz]->m_data_bokz.m_num_used_channel + 1) + is_ready + "\n", parametr);
        }
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                         + QString("Выполнили циклограмму участка включения!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    }
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_state_off(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, QString(helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + "Начинаем циклограмму участка выключения!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    if (m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_OTCLR]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            if(m_bokz[num_bokz]->shtmi2() == KiaS_SUCCESS)
            {
                if(m_bokz[num_bokz]->dtmi_or_dtmi_loc() == KiaS_SUCCESS)
                {
                    start_loc(num_bokz, parametr, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_do_dtmi_in_state_off);
                    m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
                }
            }
        }
    }
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму участка выключения!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::do_restart(uint16_t num_bokz, uint16_t parametr)
{
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_oo(uint16_t &num_bokz, uint16_t parametr)
{
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_no(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму НО!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    start_no(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        start_regular_cyclogram(num_bokz);
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму НО!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_to(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму ТО!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    start_to(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        start_regular_cyclogram(num_bokz);
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму ТО!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_ai(uint16_t &num_bokz, uint16_t parametr)
{
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] = KiaS_SUCCESS;
    std::cout << m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_skip_fails_for_continue << std::endl;
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем автономные испытания!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    for (uint16_t num_cycl = 0; num_cycl < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_ai.size(); num_cycl++)
    {
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_ai[num_cycl] == KiaS_SUCCESS && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai[num_cycl])(num_bokz, parametr)
                    == KiaS_FAIL && m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_skip_fails_for_continue == 0)
                break;
        }
    }

    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили автономные испытания!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_loc(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Начинаем циклограмму ЛОК!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    if (m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_OTCLR]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            start_loc(num_bokz);
    }
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Выполнили циклограмму ЛОК!") + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

void Kia_cyclogram_bokzm60::cyclogram_define_address(uint16_t parametr)
{
    std::vector<std::array<int16_t, constants::max_avalable_address>> addr_ch;
    addr_ch.resize(m_kia_settings->m_count_bokz);
    std::array<int16_t, constants::max_avalable_address> buff_adr;
    std::fill(buff_adr.begin(), buff_adr.end(), -1);
    std::array<int16_t, constants::max_avalable_address> count_ch;
    std::fill(count_ch.begin(), count_ch.end(), 0);
    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_count_bokz; ++num_bokz)
    {
        if (m_bokz[num_bokz]->m_data_bokz.m_is_used_bokz == CS_IS_ON &&  m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
        {
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму определения адреса!") + "\n", parametr);
            preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
            m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, BI_MAIN_REZ_ON, parametr);
        }
    }
    wait_some_time_for_one_launch(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_POWER]
                                  * m_bokz[0]->m_data_bokz.m_freq_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_count_bokz; ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_data_bokz.m_is_used_bokz == CS_IS_ON &&  m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
            {
                for (uint16_t address = 0; address < constants::max_avalable_address; ++address)
                {
                    m_bokz[num_bokz]->m_mpi_data.m_address = address;
                    if (m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE) == KiaS_SUCCESS)
                    {
                        if (num_bokz == 0)
                            buff_adr[address] = address;
                        addr_ch[num_bokz][address] = address;
                    }
                }
                for (uint16_t address = 0; address < constants::max_avalable_address; ++address)
                {
                    if (addr_ch[num_bokz][address] == buff_adr[address])
                    {
                        count_ch[address]++;
                    }
                }
                for (uint16_t address = 0; address < constants::max_avalable_address; ++address)
                {
                    if (count_ch[address] != 0)
                    {
                        m_bokz[num_bokz]->m_mpi_data.m_address = address;
                    }
                }
                m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, BI_MAIN_REZ_ON, parametr);
                wait_some_time_for_one_launch(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_OFF_POWER]
                                              * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
            }
        }
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
        {
            for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_count_bokz; ++num_ch)
            {
                if (m_bokz[num_ch]->m_data_bokz.m_is_used_bokz == CS_IS_ON)
                {
                    m_bokz[num_ch]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_ch]->m_data_bokz.m_num_used_bi]->on_power_bi(num_ch, m_bokz[num_ch]->m_data_bokz.m_num_used_channel, BI_MAIN_REZ_ON, parametr);
                }
            }
            wait_some_time_for_one_launch(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_POWER]
                                          * m_bokz[0]->m_data_bokz.m_freq_bokz);
        }
    }
    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_count_bokz; ++num_bokz)
    {
        if (m_bokz[num_bokz]->m_data_bokz.m_is_used_bokz == CS_IS_ON)
        {
            if (m_bokz[num_bokz]->m_mpi_data.m_address != 0)
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
            else
            {
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
            }
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                             QString("Выполнили циклограмму определения адреса!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
        }
    }
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Начинаем циклограмму функционирования!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.size(); num_cyclogram++)
    {
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp[num_cyclogram] == KiaS_SUCCESS && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp[num_cyclogram])(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp[num_cyclogram], parametr) == KiaS_FAIL)
                break;
        }
    }
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму функционирования!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation_oo(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{

}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation_no(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Начинаем циклограмму функционирования НО!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    start_no(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        start_regular_cyclogram(num_bokz, count_do_cyclogram, parametr);
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму функционирования НО!" ) + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation_to(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{
    save_to_protocol(num_bokz, QString(helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                                       + "Начинаем циклограмму функционирования ТО!") + "\n", parametr);
    start_to(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        start_regular_cyclogram(num_bokz,count_do_cyclogram);
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму функционирования ТО!" ) + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation_loc(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму ЛОК!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    if(m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_OTCLR]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            start_loc(num_bokz, parametr, count_do_cyclogram);
    }
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Выполнили циклограмму ЛОК!") + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_1s_mark(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму теста секундной метки!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, 0, parametr);
    wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_OFF_POWER]
                   * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_1s_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, 0, parametr);
    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_POWER]
                   * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    if (m_bokz[num_bokz]->shtmi1() != KiaS_SUCCESS)
    {
        auto str_info_1s = helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                + QString("Тест секундной метки, получение ШТМИ 1 - ошибка!") + "\n";
        save_to_protocol(num_bokz, str_info_1s, parametr);
    }
    else if ((static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_SHTMI1].data[m_bokz[num_bokz]->m_index_mpi_array[M60_SHTMI1]["post"]])) & 0x0080) != KiaS_SUCCESS)
    {
        m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
        m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Тест секундной метки, проверка наличия метки канале - ошибка!") + "\n", parametr);
    }
    m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_OFF_POWER]
                   * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_1s_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, 2, parametr);
    m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_POWER]
                   * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    if (m_bokz[num_bokz]->shtmi1() != KiaS_SUCCESS)
    {
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Тест секундной метки, получение ШТМИ 1 - ошибка!") + "\n", parametr);
    }
    else if ((static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_SHTMI1].data[m_bokz[num_bokz]->m_index_mpi_array[M60_SHTMI1]["post"]])) & 0x0080) == KiaS_SUCCESS)
    {
        m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
        m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Тест секундной метки, проверка наличия метки на резервном канале - ошибка!") + "\n", parametr);
    }
    m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_OFF_POWER]
                   * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_1s_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, 0, parametr);
    m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_POWER]
                   * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    if (m_bokz[num_bokz]->shtmi1() != KiaS_SUCCESS)
    {
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Тест секундной метки, получение ШТМИ 1 - ошибка!") + "\n", parametr);
    }
    else if ((static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_SHTMI1].data[m_bokz[num_bokz]->m_index_mpi_array[M60_SHTMI1]["post"]])) & 0x0080) == KiaS_SUCCESS)
    {
        m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
        m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Тест секундной метки, проверка наличия метки канале - ошибка!") + "\n", parametr);
    }
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму теста секундной метки!" ) + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_check_address(uint16_t &num_bokz, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.lock();
    std::vector<std::pair<uint16_t, uint16_t>> status_work_lpi;
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму проверки адреса прибора!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    for (uint16_t ind_bokz = 0; ind_bokz < m_bokz.size(); ++ind_bokz)
    {
        if (ind_bokz != num_bokz &&  m_bokz[num_bokz]->m_data_bokz.m_is_powered == IS_POWERED)
        {
            m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, BI_MAIN_REZ_ON, parametr);

        }
    }
    uint16_t cur_address = m_bokz[num_bokz]->m_mpi_data.m_address;
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_mpi_data.m_lpi = check_lpi;
        for (uint16_t address = 0; address < constants::max_avalable_address; ++address)
        {
            m_bokz[num_bokz]->m_mpi_data.m_address = address;
            m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
            if ((cur_address != address) && (m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first == KiaS_SUCCESS))
            {

                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Обнаружен ответ на ЛПИ ")
                                 + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) +
                                 " по адресу " + QString::number(address) + ", адрес прибора "
                                 + QString::number(m_bokz[num_bokz]->m_mpi_data.m_address) + "\n", parametr);
            }
            else if((cur_address == address) && (m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first == KiaS_SUCCESS))
            {
                status_work_lpi.push_back(std::make_pair(KiaS_SUCCESS, m_bokz[num_bokz]->m_mpi_data.m_lpi));
                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                                 + QString("Адрес ") + QString::number(address) + " прибора подтвержден на линии "
                                 + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + "\n", parametr);
            }
            else if((cur_address == address) && (m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first != KiaS_SUCCESS))
            {
                status_work_lpi.push_back(std::make_pair(KiaS_FAIL, m_bokz[num_bokz]->m_mpi_data.m_lpi));
                save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                                 + QString("Линия ") + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + " не исправна"+ "\n", parametr);
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
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму проверки адреса прибора!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    m_bokz[num_bokz]->m_mpi_data.m_address = cur_address;

    for (uint16_t ind_bokz = 0; ind_bokz < m_bokz.size(); ++ind_bokz)
    {
        if (m_bokz[num_bokz]->m_data_bokz.m_is_used_bokz == CS_IS_ON && ind_bokz != num_bokz && m_bokz[num_bokz]->m_data_bokz.m_is_powered == IS_NOT_POWERED)
        {
            m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, BI_MAIN_REZ_ON, parametr);

        }
    }

    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.unlock();
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_test_mko(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму теста МКО!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_mpi_data.m_lpi = check_lpi;
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + "\n", parametr);
        m_bokz[num_bokz]->initial_state(EP_NOPROTECTEDEXCHANGE);
    }
    check_work_lpi(num_bokz, 0);
    m_bokz[num_bokz]->m_mpi_data.m_lpi = 1;
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + "\n", parametr);
    m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
    check_work_lpi(num_bokz, 1);
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_mpi_data.m_lpi = check_lpi;
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + "\n", parametr);
        m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
        m_bokz[num_bokz]->vskou(EP_NOPROTECTEDEXCHANGE);
    }
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_mpi_data.m_lpi = check_lpi;
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + "\n", parametr);
        uint16_t counter_if_success_vmti_smti_check = 0;

        m_bokz[num_bokz]->vmti(EP_NOPROTECTEDEXCHANGE);
        m_bokz[num_bokz]->smti(EP_NOPROTECTEDEXCHANGE);
        uint16_t count_if_true = 0;
        for (uint16_t num_word = 0; num_word < m_bokz[num_bokz]->m_mpi_data.m_word_data; num_word++)
        {
            if (m_bokz[num_bokz]->m_mpi_data.m_data_for_exchange[num_word] == m_bokz[num_bokz]->m_mpi_data.m_data_word[num_word + 2])
            {
                count_if_true++;
            }
        }
        if (count_if_true == m_bokz[num_bokz]->m_mpi_data.m_word_data)
            counter_if_success_vmti_smti_check++;

        if (m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first == KiaS_SUCCESS
                && counter_if_success_vmti_smti_check == 1)
        {
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                             + QString("Для ЛПИ ") + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + " ВМТИ И СМТИ совпадают""\n", parametr);
            m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_SUCCESS;
            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
        }
        else
        {
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                             + QString("Для ЛПИ ") + QString::number(m_bokz[num_bokz]->m_mpi_data.m_lpi) + " ВМТИ И СМТИ не совпадают""\n", parametr);
            m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        }
    }

    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму теста МКО!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_test_synchro(uint16_t &num_bokz, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.lock();
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму теста Синхро!") + "\n");
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    m_bokz[num_bokz]->mshior();
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Изменяю время привязки на ") + QString::number(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_shift_bshv) + "\n", parametr);
    *(m_bokz[num_bokz]->m_data_bokz.bshv[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]) = static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_MSHIOR].data[m_bokz[num_bokz]->m_index_mpi_array[M60_MSHIOR]["t"]])) + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_shift_bshv;
    wait_some_time(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    m_bokz[num_bokz]->synchro();
    wait_some_time(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    m_bokz[num_bokz]->mshior();
    if ((*(m_bokz[num_bokz]->m_data_bokz.bshv[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]) - static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_MSHIOR].data[m_bokz[num_bokz]->m_index_mpi_array[M60_MSHIOR]["t"]]))) == 1)
    {
        m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Норма привязки по времени выполняется и равняется 1!") + "\n", parametr);
    }
    else
    {
        m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
        m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Норма привязки по времени выполняется и не равняется 1!") + "\n", parametr);
    }
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму теста Синхро!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.unlock();
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_technical_run(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Начинаем циклограмму Технологический прогон!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
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
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    }
    if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_off_power_for_tp)
        m_bokz[num_bokz]->m_data_bokz.m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_num_used_channel, parametr);
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму Технологический прогон!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_zkr(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Начинаем циклограмму Закрытия и открытия крышки!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    uint16_t index_cyclogram_zkr = 0;
    auto count_do = m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_ZKR][SPC_COUNT];
    if (count_do != 0)
        count_do -= 1;
    while ((index_cyclogram_zkr <= count_do && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz]))
    {
        m_bokz[num_bokz]->command_openkr();
        wait_some_time(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        m_bokz[num_bokz]->shtmi2();
        if ((static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_SHTMI2].data[m_bokz[num_bokz]->m_index_mpi_array[M60_SHTMI2]["st1"]])) & 0x000f) == 0x0004)
        {

            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Крышка открыта - Успех!") + "\n", parametr);
        }
        else
        {
            m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Крышка закрыта - Ошибка!") + "\n", parametr);
        }
        m_bokz[num_bokz]->command_zkr();
        wait_some_time(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        m_bokz[num_bokz]->shtmi2();
        if ((static_cast<uint16_t>(std::get<Pio_bokz::DOUBLE_VALUE>(m_bokz[num_bokz]->m_kia_mko_struct->m_data[M60_SHTMI2].data[m_bokz[num_bokz]->m_index_mpi_array[M60_SHTMI2]["st1"]])) & 0x000f) == 0x0002)
        {

            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Крышка закрыта - Успех!") + "\n", parametr);
        }
        else
        {
            m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first = KiaS_FAIL;
            m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
            save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) + QString("Крышка открыта - Ошибка!") + "\n", parametr);
        }
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_ZKR][SPC_COUNT] != 0)
            index_cyclogram_zkr++;
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_ZKR][SPC_PERIOD]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    }
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму Закрытия и открытия крышки!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_full_frames(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Начинаем циклограмму получения кадров!") + "\n", parametr);
    preset_before_exchange(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    uint16_t index_cyclogram_zkr = 0;
    auto count_do = m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_CYCL_FRAMES][SPC_COUNT];
    if (count_do != 0)
        count_do -= 1;
    std::cout << "her " << m_kia_settings->m_frame_settings.m_type_frame_recieve << std::endl;
    while ((index_cyclogram_zkr <= count_do && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz]))
    {

        m_bokz[num_bokz]->do_frames(m_kia_settings->m_frame_settings.m_type_frame_recieve, m_kia_settings->m_frame_settings.m_type_frame, parametr);
        if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_CYCL_FRAMES][SPC_COUNT] != 0)
            index_cyclogram_zkr++;
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[PIL_CYCL_FRAMES][SPC_PERIOD]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
    }
    post_exchange(m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz]);
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time) +
                     QString("Выполнили циклограмму получения кадров!") + m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

void Kia_cyclogram_bokzm60::set_cyclogram_settings()
{
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_FOR_TAKT] = 1;
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_POWER] = 120;
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_OTCLR] = 2;
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_LOC] = 10;
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_AFTER_OFF_POWER] = 2;
}

uint16_t Kia_cyclogram_bokzm60::start_no(uint16_t &num_bokz, uint16_t parametr)
{
    if (m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_OTCLR]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        wait_for_bi_takt(num_bokz);

        for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_NO].size(); num_cyclogram++)
        {
            if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_NO][num_cyclogram] == KiaS_SUCCESS
                    && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            {
                sleep_for_pause(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[SCO_NO][num_cyclogram]);
                if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do[SCO_NO][num_cyclogram])(num_bokz, parametr) == KiaS_FAIL)
                    break;
            }
        }
    }
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::start_to(uint16_t &num_bokz, uint16_t parametr)
{
    if (m_bokz[num_bokz]->command_otclp() == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_OTCLR]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        wait_for_bi_takt(num_bokz);
        for (uint16_t num_cyclogram = 0; num_cyclogram < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_TO].size(); num_cyclogram++)
        {
            if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[SCO_TO][num_cyclogram] == KiaS_SUCCESS
                    && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            {
                sleep_for_pause(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[SCO_TO][num_cyclogram]);
                if (std::get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do[SCO_TO][num_cyclogram])(num_bokz, parametr) == KiaS_FAIL)
                    break;
            }
        }

    }
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::start_loc(uint16_t &num_bokz, uint16_t parametr, uint16_t count_do_loc)
{
    uint16_t index_do_loc = 0;
    bool do_breake = false;
    auto count_cyclogram = count_do_loc;
    if (count_cyclogram != 0)
        count_cyclogram -= 1;
    while (index_do_loc <= count_do_loc && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] && m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first == KiaS_SUCCESS)
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

        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_LOC]
                       * m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] && m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first == KiaS_SUCCESS)
        {
            if(m_bokz[num_bokz]->dtmi_or_dtmi_loc(parametr) == KiaS_SUCCESS)
            {
                if (count_do_loc != 0)
                    index_do_loc++;
            }
            else
                break;
        }
    }
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

uint16_t Kia_cyclogram_bokzm60::start_regular_cyclogram(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr)
{
    uint16_t index_do_cyclogram = 0;
    auto count_cyclogram = count_do_cyclogram;
    if (count_cyclogram != 0)
        count_cyclogram -= 1;
    while (index_do_cyclogram <= count_cyclogram && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz]
           && m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first == KiaS_SUCCESS)
    {
        wait_some_time(num_bokz, m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_wait_time_for_cyclogram[WAIT_FOR_TAKT]);

        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            for (uint16_t num_mpi_command = 0; num_mpi_command < m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram.size(); ++num_mpi_command)
            {
                if (m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram[num_mpi_command] == KiaS_SUCCESS && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    if(get<CYCL_FUNC>(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command[num_mpi_command])(num_bokz, parametr) == KiaS_FAIL)
                        break;
                }
            }
            if (m_bokz[num_bokz]->m_kia_data->m_data_bokz->m_type_orient == Bokz::TO_WAIT
                    || m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first == KiaS_FAIL)
            {
                m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
                break;
            }
            if (count_do_cyclogram != 0)
            {
                if (m_bokz[num_bokz]->m_kia_data->m_data_bokz->m_type_orient == Bokz::TO_TO)
                    index_do_cyclogram++;
            }
        }
    }
    return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
}

void Kia_cyclogram_bokzm60::wait_some_time(uint16_t &num_bokz, const uint16_t &wait_s)
{
    for (uint16_t sec = 0; sec < wait_s; ++sec)
    {
        if (!m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            break;
        m_kia_timers->m_kia_synch_timer[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]
                ->wait_for_event(m_kia_timers->m_timer[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]);
    }
}

void Kia_cyclogram_bokzm60::wait_for_bi_takt(uint16_t &num_bokz)
{
    while (*(m_bokz[num_bokz]->m_data_bokz.bshv[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]) % m_bokz[num_bokz]->m_data_bokz.m_freq_bokz != 0)
    {
        m_kia_timers->m_kia_synch_timer[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]
                ->wait_for_event(m_kia_timers->m_timer[m_bokz[num_bokz]->m_data_bokz.m_num_used_bi]);
    }
}

void Kia_cyclogram_bokzm60::wait_some_time_for_one_launch(const uint16_t &wait_s)
{
    auto timer_interval = m_kia_timers->m_timer[0]->get_timer_interval();
    for (uint16_t sec = 0; sec < wait_s; ++sec)
    {
        if (!m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
            break;
        this_thread::sleep_for(std::chrono::milliseconds(timer_interval));
    }
}

void Kia_cyclogram_bokzm60::check_work_lpi(uint16_t &num_bokz, const uint16_t &lpi)
{
    save_to_protocol(num_bokz, helpers::format_qstring(QString::fromStdString(helpers::currentDateTime()), m_kia_settings->m_format_for_desc.shift_date_time)
                     + QString("Выбор ЛПИ ") + QString::number(lpi) + "\n");
    m_bokz[num_bokz]->m_mpi_data.m_lpi = lpi;
    m_bokz[num_bokz]->block_ou(EP_NOPROTECTEDEXCHANGE);
    m_bokz[num_bokz]->m_mpi_data.m_lpi = abs(lpi - 1);
    m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
    m_bokz[num_bokz]->m_mpi_data.m_lpi = lpi;
    m_bokz[num_bokz]->unblock_ou(EP_NOPROTECTEDEXCHANGE);
}

void Kia_cyclogram_bokzm60::save_to_protocol(uint16_t &num_bokz, QString str_to_protocol, uint16_t parametr)
{

    m_bokz[num_bokz]->save_to_specific_protocol(str_to_protocol, M60_NONE, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);

    if (m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first != KiaS_SUCCESS)
        m_bokz[num_bokz]->save_to_specific_protocol(str_to_protocol, M60_NONE, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);

    m_bokz[num_bokz]->save_to_specific_protocol(str_to_protocol, M60_NONE, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
}

void Kia_cyclogram_bokzm60::create_list_power_cyclograms()
{
    auto cycl_state_on = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_state_on(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_power.push_back(std::make_tuple(cycl_state_on, "Участок включения", CYCLOGRAM_STATE_ON));
    auto cycl_state_off = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_state_off(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_power.push_back(std::make_tuple(cycl_state_off, "Участок выключения", CYCLOGRAM_STATE_OFF));

}

void Kia_cyclogram_bokzm60::create_mpi_commands()
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

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command.size());
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram.end(), KiaS_FAIL);
}

void Kia_cyclogram_bokzm60::create_list_other_mpi_commands()
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

    auto fu_synchro = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->synchro(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_synchro, "Команда СИНХРО", SYNCHRO));

    auto fu_skor = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->skor(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_skor, "Команда СКОР", SKOR));

    auto fu_no = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_no(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_no, "Команда НО", COMMAND_NO));

    auto fu_to = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_to(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_to, "Команда ТО", COMMAND_TO));

    auto fu_loc = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_loc(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_loc, "Команда ЛОК", COMMAND_LOC));

    auto fu_otkl_p = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_otclp(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_otkl_p, "Команда ОТКЛ Р", COMMAND_OTCLP));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(separator, "separator", VMTI));

    auto fu_os = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->os(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_os, "Команда ОС", COMMAND_OS));

    auto fu_vskou = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->vskou(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_vskou, "Команда ВСКОУ", COMMAND_VSKOU));

    auto fu_otkr = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_openkr(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_otkr, "Команда ОТКР", COMMAND_OTKR));

    auto fu_zkr = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_zkr(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_zkr, "Команда ЗКР", COMMAND_ZKR));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(separator, "separator", VMTI));

    auto fu_full_exp = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_full_exp(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_full_exp, "Полная экспозиция", COMMAND_FULL_EXP));

    auto fu_bin_exp = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_bin_exp(parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(fu_bin_exp, "Бинированная экспозиция", COMMAND_BIN_EXP));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command.push_back(std::make_tuple(separator, "separator", VMTI));
}

void Kia_cyclogram_bokzm60::create_list_cyclograms_for_state_work()
{
    auto cycl_no = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_no(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_state_work.push_back(std::make_tuple(cycl_no, "Начальная ориентация (НО)", CYCLOGRAM_NO));
    auto cycl_to = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_to(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_state_work.push_back(std::make_tuple(cycl_to, "Текущая ориентация (ТО)", CYCLOGRAM_TO));
    auto cycl_loc = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_loc(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_state_work.push_back(std::make_tuple(cycl_loc, "Локализация (ЛОК)", CYCLOGRAM_LOC));
}

void Kia_cyclogram_bokzm60::create_list_cyclograms_for_tp()
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

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.size());
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp.size());
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp.end(), 10);
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp.end(), KiaS_FAIL);
}

void Kia_cyclogram_bokzm60::create_list_cyclograms_for_ai()
{
    auto cycl_state_on = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_state_on(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.push_back(std::make_tuple(cycl_state_on, "Тест участка включения", CYCLOGRAM_STATE_ON));

    auto cycl_check_address = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_check_address(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.push_back(std::make_tuple(cycl_check_address, "Тест проверки адресов", CYCLOGRAM_TEST_ADRESS));

    auto cycl_test_mko = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_test_mko(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.push_back(std::make_tuple(cycl_test_mko, "Тест МПИ", CYCLOGRAM_TEST_MKO));

    auto cycl_1s_mark = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_1s_mark(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.push_back(std::make_tuple(cycl_1s_mark, "Тест 1с метки", CYCLOGRAM_1S_MARK));

    auto cycl_operation = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_operation(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.push_back(std::make_tuple(cycl_operation, "Тест функционирования", CYCLOGRAM_OPERATION));

    auto cycl_synchro = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_test_synchro(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.push_back(std::make_tuple(cycl_synchro, "Тест Синхро", CYCLOGRAM_SYNCHRO));

    auto cycl_state_off = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_state_off(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.push_back(std::make_tuple(cycl_state_off, "Тест участка выключения", CYCLOGRAM_STATE_OFF));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_ai.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai.size());
    std::fill(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_ai.begin(),
              m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_ai.end(), KiaS_FAIL);
}

void Kia_cyclogram_bokzm60::create_list_cyclograms_for_ri()
{
    auto cycl_technical_run = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_technical_run(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri.push_back(std::make_tuple(cycl_technical_run, "Технологический прогон", CYCLOGRAM_TECH_RUN));

    auto cycl_zkr = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_zkr(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri.push_back(std::make_tuple(cycl_zkr, "Испытание крышки", CYCLOGRAM_ZKR));

    auto cycl_full_frames = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return cyclogram_full_frames(num_bokz, parametr);
    };
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri.push_back(std::make_tuple(cycl_full_frames, "Получение темновых кадров", CYCL_FULL_FRAMES));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot.resize(m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri.size());

}

void Kia_cyclogram_bokzm60::create_list_command_for_no()
{
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>> command_cycl;
    auto comm_synchro = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        m_bokz[num_bokz]->synchro(parametr);
        wait_some_time(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
    };
    command_cycl.push_back(std::make_tuple(comm_synchro, "УСД СИНХРО", CYCLOGRAM_TECH_RUN));

    auto comm_skor = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->skor(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_skor, "УСД СКОР", CYCLOGRAM_ZKR));

    auto comm_no = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_no(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_no, "УСД НО", CYCL_FULL_FRAMES));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do.push_back(command_cycl);
    std::vector<uint16_t> do_cyclogram(command_cycl.size());
    std::fill(do_cyclogram.begin(),
              do_cyclogram.end(), KiaS_SUCCESS);
    std::vector<uint64_t> sleep_to_command_cyclogram(command_cycl.size());
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do.push_back(do_cyclogram);
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram.push_back(sleep_to_command_cyclogram);

}

void Kia_cyclogram_bokzm60::create_list_command_for_to()
{
    std::vector<std::tuple<std::function<uint16_t(uint16_t num_bokz, uint16_t parametr)>, QString, uint16_t>> command_cycl;
    auto comm_synchro = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        m_bokz[num_bokz]->synchro(parametr);
        wait_some_time(num_bokz, m_bokz[num_bokz]->m_data_bokz.m_freq_bokz);
        return m_bokz[num_bokz]->m_mpi_data.m_status_exchange.first;
    };

    command_cycl.push_back(std::make_tuple(comm_synchro, "УСД СИНХРО", CYCLOGRAM_TECH_RUN));

    auto comm_skor = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->skor(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_skor, "УСД СКОР", CYCLOGRAM_ZKR));

    auto comm_kvaor = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->kvaor(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_kvaor, "УСД КВАОР", CYCL_FULL_FRAMES));

    auto comm_to = [this](uint16_t num_bokz, uint16_t parametr = EP_DOALL)
    {
        return m_bokz[num_bokz]->command_to(parametr);
    };
    command_cycl.push_back(std::make_tuple(comm_to, "УСД ТО", CYCL_FULL_FRAMES));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do.push_back(command_cycl);
    std::vector<uint16_t> do_cyclogram(command_cycl.size());
    std::fill(do_cyclogram.begin(),
              do_cyclogram.end(), KiaS_SUCCESS);
    std::vector<uint64_t> sleep_to_command_cyclogram(command_cycl.size());
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do.push_back(do_cyclogram);
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram.push_back(sleep_to_command_cyclogram);
}

void Kia_cyclogram_bokzm60::create_list_command_for_loc()
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

void Kia_cyclogram_bokzm60::create_list_chpn()
{
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Время экспонирования", "texp", IS_PARAM, BokzM60::TP_TEXP));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Фокус", "focus", IS_PARAM, BokzM60::TP_FOC));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Координата X", "cord_x", IS_PARAM, BokzM60::TP_X));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Координата Y", "cord_y", IS_PARAM, BokzM60::TP_Y));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Допуск распознавания", "epsilon", IS_PARAM, BokzM60::TP_EPS));

    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Матрица ПСК", "mat_psk", IS_TABLE, BokzM60::TP_MAT));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Кватернион ориентации", "qo", IS_TABLE, BokzM60::TP_QA));
    m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn.push_back(std::make_tuple("Угловая скорость", "wo", IS_TABLE, BokzM60::TP_W));
}
