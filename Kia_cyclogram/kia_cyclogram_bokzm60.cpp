#include "kia_cyclogram_bokzm60.h"

Kia_cyclogram_bokzm60::Kia_cyclogram_bokzm60(std::vector<shared_ptr<Timer>> timer,
                                             std::vector<shared_ptr<Kia_synch_timer>> kia_synch_timer,
                                             std::vector<std::shared_ptr<Bokz>> bokz, std::vector<shared_ptr<Kia_bi>> kia_bi,
                                             shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings):
    m_timer(timer),
    m_kia_synch_timer(kia_synch_timer),
    m_bokz(bokz),
    m_kia_bi(kia_bi),
    m_kia_protocol(kia_protocol),
    m_kia_settings(kia_settings)
{

}

uint16_t Kia_cyclogram_bokzm60::cyclogram_state_on(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму участка включения!") + "\n", parametr);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_on_power_is_stable
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        m_bokz[num_bokz]->shtmi1();
        if ((m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_data_word[6] & 0x0f00) == 0x0400)
        {

            m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = "УСПЕХ!";
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                             + QString("Прибор на канале №") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel + 1) + " готов!" + "\n", parametr);
            wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
            if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            {
                m_bokz[num_bokz]->synchro();
            }
        }
        else
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
            m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                             + QString("Прибор на канале №") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel + 1) + " не готов!" + "\n", parametr);
        }
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                         + QString("Выполнили циклограмму участка включения!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_state_off(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, QString(format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + "Начинаем циклограмму участка выключения!") + "\n", parametr);
    m_bokz[num_bokz]->command_otclp();
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        m_bokz[num_bokz]->shtmi2();
        m_bokz[num_bokz]->dtmi_or_dtmi_loc();
        start_loc(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_count_do_dtmi_in_state_off);
        m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);

    }
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму участка выключения!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_no(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму НО!") + "\n", parametr);
    start_no(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        start_regular_cyclogram(num_bokz);
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму НО!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_to(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму ТО!") + "\n", parametr);
    start_to(num_bokz);
    start_regular_cyclogram(num_bokz);
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму ТО!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_offline_tests(uint16_t &num_bokz, uint16_t parametr)
{
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] = KiaS_SUCCESS;
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем автономные испытания!") + "\n", parametr);
    cyclogram_state_on(num_bokz, parametr);
    cyclogram_check_address(num_bokz, parametr);
    cyclogram_test_mko(num_bokz, parametr);
    cyclogram_1s_mark(num_bokz, parametr);
    cyclogram_operation_no(num_bokz, parametr);
    cyclogram_operation_to(num_bokz, parametr);
    cyclogram_test_synchro(num_bokz, parametr);
    cyclogram_state_off(num_bokz, parametr);
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили автономные испытания!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_loc(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму ЛОК!") + "\n", parametr);
    m_bokz[num_bokz]->command_otclp();
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        start_loc(num_bokz);
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Выполнили циклограмму ЛОК!") + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

void Kia_cyclogram_bokzm60::cyclogram_define_address(uint16_t parametr)
{
    std::vector<std::array<int16_t, constants::max_avalable_address>> addr_ch;
    addr_ch.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    std::array<int16_t, constants::max_avalable_address> buff_adr;
    std::fill(buff_adr.begin(), buff_adr.end(), -1);
    std::array<int16_t, constants::max_avalable_address> count_ch;
    std::fill(count_ch.begin(), count_ch.end(), 0);
    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_data_for_bokz->m_count_bokz; ++num_bokz)
    {
        if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON &&  m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
        {
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму определения адреса!") + "\n", parametr);
            m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, BI_MAIN_REZ_ON, parametr);
        }
    }
    wait_some_time_for_one_launch(m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_on_power_is_stable
                                  * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_data_for_bokz->m_count_bokz; ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON &&  m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
            {
                for (uint16_t address = 0; address < constants::max_avalable_address; ++address)
                {
                    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address = address;
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
                        m_kia_settings->m_data_for_bokz->m_address_defined[count_ch[address] - 1] = address;
                    }
                }
                m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, BI_MAIN_REZ_ON, parametr);
                wait_some_time_for_one_launch(m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_off_power_is_stable
                                              * m_kia_settings->m_data_for_bokz->m_freq_bokz);
            }
        }
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
        {
            for (uint16_t num_ch = 0; num_ch < m_kia_settings->m_data_for_bokz->m_count_bokz; ++num_ch)
            {
                if (m_bokz[num_ch]->m_is_used_bokz == CS_IS_ON)
                {
                    m_kia_bi[m_bokz[num_ch]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_ch, m_bokz[num_ch]->m_kia_data->m_data_mpi->m_num_used_channel, BI_MAIN_REZ_ON, parametr);
                }
            }
            wait_some_time_for_one_launch(m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_on_power_is_stable
                                          * m_kia_settings->m_data_for_bokz->m_freq_bokz);
        }
    }
    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_data_for_bokz->m_count_bokz; ++num_bokz)
    {
        if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
        {
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                             QString("Выполнили циклограмму определения адреса!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
        }
    }
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму функционирования!") + "\n", parametr);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        cyclogram_operation_no(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        cyclogram_operation_to(num_bokz);
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму функционирования!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation_no(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму функционирования НО!") + "\n", parametr);
    start_no(num_bokz);
    start_regular_cyclogram(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_count_cyclogram_operation_no);
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму функционирования НО!" ) + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_operation_to(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, QString(format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + "Начинаем циклограмму функционирования ТО!") + "\n", parametr);
    start_to(num_bokz);
    start_regular_cyclogram(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_count_cyclogram_operation_to);
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму функционирования ТО!" ) + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_1s_mark(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму теста секундной метки!") + "\n", parametr);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_off_power_is_stable
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_1s_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, 0, parametr);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_on_power_is_stable
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_bokz[num_bokz]->shtmi1() != KiaS_SUCCESS)
    {
        auto str_info_1s = format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                + QString("Тест секундной метки, получение ШТМИ 1 - ошибка!") + "\n";
        if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_SYSTEM] == KiaS_SUCCESS)
            m_kia_protocol->preset_before_save_and_out(num_bokz, str_info_1s, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);
        if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] == KiaS_SUCCESS)
            m_kia_protocol->preset_before_save_and_out(num_bokz, str_info_1s, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
    }
    else if ((m_bokz[num_bokz]->m_kia_mko_struct->st_shtmi1.POST & 0x0080) != KiaS_SUCCESS)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Тест секундной метки, проверка наличия метки канале - ошибка!") + "\n", parametr);
    }
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_off_power_is_stable
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_1s_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, 2, parametr);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_on_power_is_stable
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_bokz[num_bokz]->shtmi1() != KiaS_SUCCESS)
    {
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Тест секундной метки, получение ШТМИ 1 - ошибка!") + "\n", parametr);
    }
    else if ((m_bokz[num_bokz]->m_kia_mko_struct->st_shtmi1.POST & 0x0080) == KiaS_SUCCESS)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Тест секундной метки, проверка наличия метки на резервном канале - ошибка!") + "\n", parametr);
    }
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_off_power_is_stable
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_1s_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, 0, parametr);
    m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel, parametr);
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_on_power_is_stable
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_bokz[num_bokz]->shtmi1() != KiaS_SUCCESS)
    {
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Тест секундной метки, получение ШТМИ 1 - ошибка!") + "\n", parametr);
    }
    else if ((m_bokz[num_bokz]->m_kia_mko_struct->st_shtmi1.POST & 0x0080) == KiaS_SUCCESS)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Тест секундной метки, проверка наличия метки канале - ошибка!") + "\n", parametr);
    }
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму теста секундной метки!" ) + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_check_address(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму проверки адреса прибора!") + "\n", parametr);
    m_bokz[num_bokz]->preset_before_exchange();
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
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
                m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
                save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Обнаружен ответ на ЛПИ ")
                                 + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) +
                                 " по адресу " + QString::number(address) + ", адрес прибора "
                                 + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address) + "\n", parametr);
            }
            else if((cur_address == address) && (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS))
            {

                m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = "УСПЕХ!";
                save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                                 + QString("Адрес ") + QString::number(address) + " прибора подтвержден на линии "
                                 + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
            }
        }
    }
    if (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_SUCCESS;
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = "УСПЕХ!";
    }
    else
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
    }
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму проверки адреса прибора!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address = cur_address;
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_test_mko(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму теста МКО!") + "\n", parametr);
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = check_lpi;
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
        m_bokz[num_bokz]->initial_state(EP_NOPROTECTEDEXCHANGE);
    }
    check_work_lpi(num_bokz, 0);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = 1;
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
    m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
    check_work_lpi(num_bokz, 1);
    for (uint16_t check_lpi = 0; check_lpi < constants::m_count_lpi; ++check_lpi)
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = check_lpi;
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                         + QString("Выбор ЛПИ ") + QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi) + "\n", parametr);
        m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
        m_bokz[num_bokz]->vskou(EP_NOPROTECTEDEXCHANGE);
    }

    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму теста МКО!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_test_synchro(uint16_t &num_bokz, uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.lock();
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму теста Синхро!") + "\n");
    m_bokz[num_bokz]->mshior();
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Изменяю время привязки на ") + QString::number(m_kia_settings->m_wait_and_param_for_cyclogram->m_shift_bshv) + "\n", parametr);
    m_kia_settings->m_data_for_db->bshv[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi] = m_bokz[num_bokz]->m_kia_mko_struct->st_mshior.T + m_kia_settings->m_wait_and_param_for_cyclogram->m_shift_bshv;
    wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
    m_bokz[num_bokz]->synchro();
    wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
    m_bokz[num_bokz]->mshior();
    if ((m_kia_settings->m_data_for_db->bshv[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi] - m_bokz[num_bokz]->m_kia_mko_struct->st_mshior.T) == 1)
    {

        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Норма привязки по времени выполняется и равняется 1!") + "\n", parametr);
    }
    else
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
        m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
        save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Норма привязки по времени выполняется и не равняется 1!") + "\n", parametr);
    }
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму теста Синхро!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    m_kia_settings->m_flags_for_thread->m_mtx_cyclogram.unlock();
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_technical_run(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму Технический прогон!") + "\n", parametr);
    m_bokz[num_bokz]->preset_before_exchange();
    uint16_t index_technical_run = 0;
    //uint16_t bi_1s = 1;
    std::cout << m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_tech_run[SPC_PERIOD] << std::endl;
    while ((index_technical_run <= m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_tech_run[SPC_COUNT] && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz]))
    {
        cyclogram_operation(num_bokz, parametr);
        if (m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_tech_run[SPC_COUNT] != 0)
            index_technical_run++;
        wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_tech_run[SPC_PERIOD]
                       * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    }
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму Технический прогон!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_zkr(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Начинаем циклограмму Закрытия и открытия крышки!") + "\n", parametr);
    uint16_t index_cyclogram_zkr = 0;
    while ((index_cyclogram_zkr <= m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_zkr[SPC_COUNT] && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz]))
    {
        m_bokz[num_bokz]->command_openkr();
        wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
        m_bokz[num_bokz]->shtmi2();
        if ((m_bokz[num_bokz]->m_kia_mko_struct->st_shtmi2.KC1 & 0x000f) == 0x0004)
        {

            m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Крышка открыта - Успех!") + "\n", parametr);
        }
        else
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
            m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Крышка закрыта - Ошибка!") + "\n", parametr);
        }
        m_bokz[num_bokz]->command_zkr();
        wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
        m_bokz[num_bokz]->shtmi2();
        if ((m_bokz[num_bokz]->m_kia_mko_struct->st_shtmi2.KC1 & 0x000f) == 0x0002)
        {

            m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - УСПЕХ!";
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Крышка закрыта - Успех!") + "\n", parametr);
        }
        else
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
            m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
            save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + QString("Крышка открыта - Ошибка!") + "\n", parametr);
        }
        if (m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_zkr[SPC_COUNT] != 0)
            index_cyclogram_zkr++;
        wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_zkr[SPC_PERIOD]
                       * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    }
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму Закрытия и открытия крышки!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::cyclogram_full_frames(uint16_t &num_bokz, uint16_t parametr)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Начинаем циклограмму получения кадров!") + "\n", parametr);
    uint16_t index_cyclogram_zkr = 0;
    std::cout << m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_full_frames[SPC_COUNT] << std::endl;
    std::cout << m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_full_frames[SPC_PERIOD] << std::endl;
    while ((index_cyclogram_zkr <= m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_full_frames[SPC_COUNT] && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz]))
    {
        //m_kia_matrox->matrox_grab_frame();
        if (m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_full_frames[SPC_COUNT] != 0)
            index_cyclogram_zkr++;
        wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_param_for_cycl_full_frames[SPC_PERIOD]
                       * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    }
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) +
                     QString("Выполнили циклограмму получения кадров!") + m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] + "\n", parametr);
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::start_no(uint16_t &num_bokz)
{
    m_bokz[num_bokz]->command_otclp();
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    wait_for_bi_takt(num_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->synchro();
        wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->skor();
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->command_no();
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::start_to(uint16_t &num_bokz)
{
    m_bokz[num_bokz]->command_otclp();
    wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_otclp
                   * m_kia_settings->m_data_for_bokz->m_freq_bokz);
    wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->synchro();
        wait_some_time(num_bokz, m_kia_settings->m_data_for_bokz->m_freq_bokz);
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->skor();
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->kvaor();
        m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = m_bokz[num_bokz]->command_to();
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::start_loc(uint16_t &num_bokz, uint16_t count_do_loc)
{
    uint16_t index_do_loc = 0;
    while (index_do_loc <= count_do_loc && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        m_bokz[num_bokz]->command_loc();
        wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_start_dtmi_loc
                       * m_kia_settings->m_data_for_bokz->m_freq_bokz);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            m_bokz[num_bokz]->dtmi_or_dtmi_loc();
            if (count_do_loc != 0)
                index_do_loc++;
        }
    }
    return m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange;
}

uint16_t Kia_cyclogram_bokzm60::start_regular_cyclogram(uint16_t &num_bokz, uint16_t count_do_cyclogram)
{
    uint16_t index_do_cyclogram = 0;
    while (index_do_cyclogram <= count_do_cyclogram && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
    {
        wait_some_time(num_bokz, m_kia_settings->m_wait_and_param_for_cyclogram->m_wait_for_takt);

        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
        {
            for (uint16_t num_mpi_command = 0; num_mpi_command < constants::max_mpi_command; ++num_mpi_command)
            {
                if (m_kia_settings->m_data_for_bokz->m_do_mpi_command_in_cyclogram[num_mpi_command] == KiaS_SUCCESS && m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_mpi_command[num_mpi_command](EP_DOALL);
                }
            }
            if ((m_bokz[num_bokz]->m_kia_mko_struct->st_mshior.KC1 & 0xf000) == 0x4000)
            {
                m_kia_settings->m_wait_and_param_for_cyclogram->m_is_error[num_bokz] = " - ОШИБКА!";
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

void Kia_cyclogram_bokzm60::wait_some_time(uint16_t &num_bokz, const uint16_t &wait_s)
{
    for (uint16_t sec = 0; sec < wait_s; ++sec)
    {
        if (!m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
            break;
        m_kia_synch_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]
                ->wait_for_event(m_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]);
    }
}

void Kia_cyclogram_bokzm60::wait_for_bi_takt(uint16_t &num_bokz)
{
    while (m_kia_settings->m_data_for_db->bshv[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi] % m_kia_settings->m_data_for_bokz->m_freq_bokz != 0)
    {
        m_kia_synch_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]
                ->wait_for_event(m_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]);
    }
}

void Kia_cyclogram_bokzm60::wait_some_time_for_one_launch(const uint16_t &wait_s)
{
    for (uint16_t sec = 0; sec < wait_s; ++sec)
    {
        if (!m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
            break;
        this_thread::sleep_for(std::chrono::milliseconds(m_kia_settings->m_timer_interval));
    }
}

void Kia_cyclogram_bokzm60::check_work_lpi(uint16_t &num_bokz, const uint16_t &lpi)
{
    save_to_protocol(num_bokz, format(QString::fromStdString(currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time)
                     + QString("Выбор ЛПИ ") + QString::number(lpi) + "\n");
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = lpi;
    m_bokz[num_bokz]->block_ou(EP_NOPROTECTEDEXCHANGE);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = abs(lpi - 1);
    m_bokz[num_bokz]->os(EP_NOPROTECTEDEXCHANGE);
    m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = lpi;
    m_bokz[num_bokz]->unblock_ou(EP_NOPROTECTEDEXCHANGE);
}

void Kia_cyclogram_bokzm60::save_to_protocol(uint16_t &num_bokz, QString str_to_protocol, uint16_t parametr)
{
    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_SYSTEM] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(num_bokz, str_to_protocol, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] == KiaS_SUCCESS)
        if (m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange != KiaS_SUCCESS)
            m_kia_protocol->preset_before_save_and_out(num_bokz, str_to_protocol, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] == KiaS_SUCCESS)
        m_kia_protocol->preset_before_save_and_out(num_bokz, str_to_protocol, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
}
