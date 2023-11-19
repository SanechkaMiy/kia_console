#include "kia_protocol.h"

Kia_protocol::Kia_protocol(shared_ptr<WorkWithStruct> wws, std::shared_ptr<Kia_settings> kia_settings) :
    m_wws(wws)
  , m_kia_settings(kia_settings)
{

}

Kia_protocol::~Kia_protocol()
{
    std::cout <<"Destrcutor kia_protocol" << std::endl;
}

void Kia_protocol::create_dir_for_protocols()
{
    m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol = KiaS_SUCCESS;
    m_kia_settings->m_data_to_protocols->m_start_create_dir_for_protocols = m_wws->current_hours();
    for (uint16_t type_protocol = 0; type_protocol < constants::protocol_count; ++type_protocol)
    {
        m_kia_settings->m_data_to_protocols->m_protocols[type_protocol].resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    }
    m_kia_settings->m_data_to_protocols->m_count_of_exc_fail.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    m_kia_settings->m_data_to_protocols->m_count_of_time_bind_fail.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    m_kia_settings->m_data_to_protocols->m_count_of_no_is_not_def_fail.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    m_kia_settings->m_data_to_protocols->m_count_of_time_out_fail.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    m_kia_settings->m_data_to_protocols->m_count_of_kvaor_is_not_corr_fail.resize(m_kia_settings->m_data_for_bokz->m_count_bokz);
    std::fill(m_kia_settings->m_data_to_protocols->m_is_protocol_used.begin(), m_kia_settings->m_data_to_protocols->m_is_protocol_used.end(), KiaS_SUCCESS);
    QString name_dir = "exp_" + QString::fromStdString(m_wws->currentDateTime());
    QDir dir("/home/alexander/Project/kia_console/protocols/");
    dir.mkdir(name_dir);
    QString full_path_and_name;
    QStringList path_to_protocol = {"/home/alexander/Project/kia_console/protocols/" + name_dir + "/protocol_MKO_",
                                    "/home/alexander/Project/kia_console/protocols/" + name_dir + "/protocol_Device_",
                                    "/home/alexander/Project/kia_console/protocols/" + name_dir + "/protocol_System_",
                                    "/home/alexander/Project/kia_console/protocols/" + name_dir + "/protocol_AI_",
                                    "/home/alexander/Project/kia_console/protocols/" + name_dir + "/protocol_Error_"};
    QString name_protocol;
    for (uint16_t type_protocol = 0; type_protocol < constants::protocol_count; ++type_protocol)
    {
        for (uint16_t count_bokz = 0; count_bokz < m_kia_settings->m_data_for_bokz->m_count_bokz + 1; ++count_bokz)
        {
            if (count_bokz == 0)
                name_protocol = "common";
            else
                name_protocol = QString::number(count_bokz);
            full_path_and_name = path_to_protocol[type_protocol] + " " + name_protocol + ".txt";
            m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol].push_back(new QFile(full_path_and_name));
            m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][count_bokz]->open(QIODevice::Append | QIODevice::Text);
        }
    }
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] = KiaS_FAIL;
    //create_dir_for_sql_protocols();
    create_dir_for_frame_protocols();
}

void Kia_protocol::create_dir_for_sql_protocols()
{
    m_kia_settings->m_data_to_protocols->m_is_sql_protocol_used = KiaS_SUCCESS;
    QDir dir_sql("/home/alexander/Project/kia_console/sql_protocols/");
    QString full_path_and_name_sql = "/home/alexander/Project/kia_console/sql_protocols/sql_protocol_" + QString::fromStdString(m_wws->currentDateTime()) + ".txt";
    m_kia_settings->m_data_to_protocols->m_file_for_sql_protocol = new QFile(full_path_and_name_sql);
    m_kia_settings->m_data_to_protocols->m_file_for_sql_protocol->open(QIODevice::Append | QIODevice::Text);

}

void Kia_protocol::create_dir_for_frame_protocols()
{
    m_kia_settings->m_data_to_protocols->m_is_frames_protocol_used = KiaS_SUCCESS;
    QString name_dir = "exp_" + QString::fromStdString(m_wws->currentDateTime());
    QDir dir_frames("/home/alexander/Project/kia_console/frames/");
    dir_frames.mkdir(name_dir);
    m_full_path = "/home/alexander/Project/kia_console/frames/" + name_dir;
    m_kia_settings->m_data_to_protocols->m_file_for_frames_protocol = new QFile(m_full_path);
    m_kia_settings->m_data_to_protocols->m_file_for_frames_protocol->open(QIODevice::Append | QIODevice::Text);
}

void Kia_protocol::close_dir_for_protocols()
{
    for (uint16_t type_protocol = 0; type_protocol < constants::protocol_count; ++type_protocol)
    {
        for (uint16_t count_bokz = 0; count_bokz < m_kia_settings->m_data_for_bokz->m_count_bokz + 1; ++count_bokz)
        {
            m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][count_bokz]->close();
        }
        m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol].clear();
    }
    //close_dir_for_sql_protocols();
    close_dir_for_frame_protocols();
}

void Kia_protocol::close_dir_for_sql_protocols()
{
    m_kia_settings->m_data_to_protocols->m_file_for_sql_protocol->close();
}

void Kia_protocol::close_dir_for_frame_protocols()
{
    m_kia_settings->m_data_to_protocols->m_file_for_frames_protocol->close();
}


void Kia_protocol::save_to_protocols(uint16_t &num_bokz, const uint16_t &type_protocol)
{
    uint16_t common_protocol = 0;
    if (m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol == KiaS_SUCCESS)
    {
        if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[type_protocol] == KiaS_SUCCESS)
        {
            if (!m_kia_settings->m_data_to_protocols->m_save_binary)
            {
                QTextStream stream(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][num_bokz + 1]);
                stream << m_kia_settings->m_data_to_protocols->m_protocols[type_protocol][num_bokz];
                QTextStream stream_common(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][common_protocol]);
                stream_common << m_kia_settings->m_data_to_protocols->m_protocols[type_protocol][num_bokz];
            }
            else
            {
                QDataStream stream(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][num_bokz + 1]);
                stream << m_kia_settings->m_data_to_protocols->m_protocols[type_protocol][num_bokz];
                QDataStream stream_common(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][common_protocol]);
                stream_common << m_kia_settings->m_data_to_protocols->m_protocols[type_protocol][num_bokz];
            }
        }
    }
    m_kia_settings->m_data_to_protocols->m_protocols[type_protocol][num_bokz].clear();
}

void Kia_protocol::save_to_sql_protocols(const QString &data_to_out)
{
    if (m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol == KiaS_SUCCESS)
    {
        if (m_kia_settings->m_data_to_protocols->m_is_sql_protocol_used == KiaS_SUCCESS)
        {
            QTextStream stream(m_kia_settings->m_data_to_protocols->m_file_for_sql_protocol);
            stream << data_to_out;
        }
    }
}

void Kia_protocol::save_to_frames_protocols(uint16_t &num_bokz, uint32_t& bshv, void* lvp_buf, uint32_t buf_size)
{    
    reset_protocol();
    if (m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol == KiaS_SUCCESS)
    {
        auto full_path = m_full_path + "/frame_num_bokz_" + QString::number(num_bokz) + "_" + QString::number(bshv) + ".mtx";
        FILE* file = fopen(full_path.toStdString().c_str(), "wb");
        if (m_kia_settings->m_data_to_protocols->m_is_frames_protocol_used == KiaS_SUCCESS)
        {
            fwrite(lvp_buf, buf_size, 1, file);
        }
        fclose(file);
    }

}

void Kia_protocol::save_and_out_to_system_error_ai_protocols(uint16_t &num_bokz, const QString &data_to_out, uint16_t parametr)
{
    reset_protocol();
    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_SYSTEM] == KiaS_SUCCESS)
    {
        preset_before_save_and_out(num_bokz, data_to_out, SET_INFO_TO_WINDOW_INFO, SP_DO_SYSTEM, parametr);
    }

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_ERROR] == KiaS_SUCCESS)
    {
        if ((m_kia_settings->m_wait_and_param_for_cyclogram->m_is_cyclogram_is_succesful != KiaS_SUCCESS))
        {
            preset_before_save_and_out(num_bokz, data_to_out, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);
        }
    }

    if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] == KiaS_SUCCESS)
    {
        if ((m_kia_settings->m_wait_and_param_for_cyclogram->m_is_cyclogram_is_succesful != KiaS_SUCCESS))
        {
            preset_before_save_and_out(num_bokz, data_to_out, SET_INFO_TO_AI_WINDOW, SP_DO_AI, parametr);
        }
    }

}

void Kia_protocol::preset_before_save_and_out(uint16_t& num_bokz, const QString &data_to_out, uint16_t type_window, uint16_t type_protocol, uint16_t parametr)
{
    if (!data_to_out.isEmpty())
    {
        m_kia_settings->m_data_to_protocols->m_protocols[type_protocol][num_bokz].push_back(data_to_out);
        QStringList list_protocol;
        list_protocol.push_back(QString::number(num_bokz));
        list_protocol.push_back(m_kia_settings->m_data_to_protocols->m_protocols[type_protocol][num_bokz]);
        emit send_to_client(type_window, list_protocol);
        save_to_protocols(num_bokz, type_protocol);
    }
}

void Kia_protocol::reset_protocol()
{
    if (m_kia_settings->m_data_to_protocols->m_start_create_dir_for_protocols  != m_wws->current_hours())
    {
        m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol = KiaS_FAIL;
        reset_dir_for_protocols();
    }
}

void Kia_protocol::save_and_out_to_dev_mko_protocols(uint16_t &num_bokz, const uint16_t &num_mpi_command, uint16_t parametr)
{
    QStringList list_mko_protocol;
    list_mko_protocol.push_back(QString::number(num_bokz));
    list_mko_protocol.push_back(m_kia_settings->m_data_to_protocols->m_protocols[SP_DO_MKO][num_bokz]);


    QStringList list_dev_protocol;
    list_dev_protocol.push_back(QString::number(num_mpi_command));
    list_dev_protocol.push_back(QString::number(num_bokz));
    list_dev_protocol.push_back(m_kia_settings->m_data_to_protocols->m_protocols[SP_DO_DEV][num_bokz]);

    emit send_to_client(SET_WINDOW_INFO_MPI, list_mko_protocol);
    emit send_to_client(SET_WINDOW_INFO_DEVICE_PROTOCOL, list_dev_protocol);

    save_to_protocols(num_bokz, SP_DO_MKO);
    save_to_protocols(num_bokz, SP_DO_DEV);

}

void Kia_protocol::reset_dir_for_protocols()
{
    close_dir_for_protocols();
    create_dir_for_protocols();
}



void Kia_protocol::count_of_fails(uint16_t &num_bokz, uint16_t parametr)
{

    QString str_error_counter;
    str_error_counter.push_back(m_wws->format(QString::fromStdString(m_wws->currentDateTime()), m_kia_settings->m_format_for_desc->shift_date_time) + m_wws->format("Счетчики ошибок", m_kia_settings->m_format_for_desc->shift_count_of_fail) + "\n");
    str_error_counter.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_date_time) + m_wws->format("Счетчик нарушения обмена", m_kia_settings->m_format_for_desc->shift_count_of_fail) + QString::number(m_kia_settings->m_data_to_protocols->m_count_of_exc_fail[num_bokz]) + "\n");
    str_error_counter.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_date_time) + m_wws->format("Счетчик ненормы привязки ко времени", m_kia_settings->m_format_for_desc->shift_count_of_fail) + QString::number(m_kia_settings->m_data_to_protocols->m_count_of_time_bind_fail[num_bokz]) + "\n");
    str_error_counter.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_date_time) + m_wws->format("Ориентация не определена", m_kia_settings->m_format_for_desc->shift_count_of_fail) + QString::number(m_kia_settings->m_data_to_protocols->m_count_of_no_is_not_def_fail[num_bokz]) + "\n");
    str_error_counter.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_date_time) + m_wws->format("Ненорма кватерниона", m_kia_settings->m_format_for_desc->shift_count_of_fail) + QString::number(m_kia_settings->m_data_to_protocols->m_count_of_kvaor_is_not_corr_fail[num_bokz]) + "\n");
    str_error_counter.push_back(m_wws->format(" ", m_kia_settings->m_format_for_desc->shift_date_time) + m_wws->format("Нет выхода в режим ожидания", m_kia_settings->m_format_for_desc->shift_count_of_fail) + QString::number(m_kia_settings->m_data_to_protocols->m_count_of_time_out_fail[num_bokz]) + "\n");
    preset_before_save_and_out(num_bokz, str_error_counter, SET_INFO_TO_ERROR_WINDOW, SP_DO_ERROR, parametr);
}
