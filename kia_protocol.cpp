#include "kia_protocol.h"

Kia_protocol::Kia_protocol(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{
    std::fill(m_kia_settings->m_data_to_protocols->m_is_protocol_used.begin(), m_kia_settings->m_data_to_protocols->m_is_protocol_used.end(), KiaS_SUCCESS);
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] = KiaS_FAIL;
}

Kia_protocol::~Kia_protocol()
{
    std::cout <<"Destrcutor kia_protocol" << std::endl;
}

void Kia_protocol::create_dir_for_protocols()
{
    m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol = KiaS_SUCCESS;
    m_kia_settings->m_data_to_protocols->m_start_create_dir_for_protocols = helpers::current_hours();

    QString name_dir = "exp_" + QString::fromStdString(helpers::currentDateTime());
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
        for (uint16_t count_bokz = 0; count_bokz < m_kia_settings->m_count_bokz + 1; ++count_bokz)
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
    //create_dir_for_sql_protocols();
    create_dir_for_frame_protocols();
}

void Kia_protocol::create_dir_for_sql_protocols()
{
    m_kia_settings->m_data_to_protocols->m_is_sql_protocol_used = KiaS_SUCCESS;
    QDir dir_sql("/home/alexander/Project/kia_console/sql_protocols/");
    QString full_path_and_name_sql = "/home/alexander/Project/kia_console/sql_protocols/sql_protocol_" + QString::fromStdString(helpers::currentDateTime()) + ".txt";
    m_kia_settings->m_data_to_protocols->m_file_for_sql_protocol = new QFile(full_path_and_name_sql);
    m_kia_settings->m_data_to_protocols->m_file_for_sql_protocol->open(QIODevice::Append | QIODevice::Text);

}

void Kia_protocol::create_dir_for_frame_protocols()
{
    m_kia_settings->m_data_to_protocols->m_is_frames_protocol_used = KiaS_SUCCESS;
    QString name_dir = "exp_" + QString::fromStdString(helpers::currentDateTime());
    QDir dir_frames("/home/alexander/Project/kia_console/frames/");

    m_full_path = "/home/alexander/Project/kia_console/frames/" + name_dir;
        dir_frames.mkdir(m_full_path);
    //m_kia_settings->m_data_to_protocols->m_file_for_frames_protocol = new QFile(m_full_path);
    //m_kia_settings->m_data_to_protocols->m_file_for_frames_protocol->open(QIODevice::Append | QIODevice::Text);
}

void Kia_protocol::close_dir_for_protocols()
{
    for (uint16_t type_protocol = 0; type_protocol < constants::protocol_count; ++type_protocol)
    {
        for (uint16_t count_bokz = 0; count_bokz < m_kia_settings->m_count_bokz + 1; ++count_bokz)
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




void Kia_protocol::save_to_protocols(uint16_t &num_bokz, const QString & data_to_out, const uint16_t &type_protocol)
{
    uint16_t common_protocol = 0;
    if (m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol == KiaS_SUCCESS)
    {
        if (m_kia_settings->m_data_to_protocols->m_is_protocol_used[type_protocol] == KiaS_SUCCESS)
        {
            if (!m_kia_settings->m_data_to_protocols->m_save_binary)
            {
                QTextStream stream(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][num_bokz + 1]);
                stream << data_to_out;
                QTextStream stream_common(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][common_protocol]);
                stream_common << data_to_out;
            }
            else
            {
                QDataStream stream(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][num_bokz + 1]);
                stream << data_to_out;
                QDataStream stream_common(m_kia_settings->m_data_to_protocols->m_file_for_protocol[type_protocol][common_protocol]);
                stream_common << data_to_out;
            }
        }
    }
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

void Kia_protocol::save_to_frames_protocols(uint16_t &num_bokz, int32_t& bshv, void* lvp_buf, uint32_t buf_size)
{    
    reset_protocol();
    if (m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol == KiaS_SUCCESS)
    {
        //auto full_path = m_full_path + "/frame_num_bokz_" + QString::number(num_bokz) + "_" + QString::number(bshv) + ".mtx";
        //FILE* file = fopen(full_path.toStdString().c_str(), "wb");
        std::cout << sizeof(lvp_buf) << " " << buf_size << std::endl;
        QString full_path_and_name = m_full_path + "/frame_num_bokz_" + QString::number(num_bokz) + "_" + QString::number(bshv) + ".mtx";
        if (m_kia_settings->m_data_to_protocols->m_is_frames_protocol_used == KiaS_SUCCESS)
        {
            //fwrite(lvp_buf, buf_size, 1, file);
            auto file_frame_protocol  = new QFile(full_path_and_name);
            file_frame_protocol->open(QIODevice::Append | QIODevice::Text);
            QDataStream stream_common(file_frame_protocol);
            stream_common.writeBytes(static_cast<char*>(lvp_buf), buf_size);
            file_frame_protocol->close();
            //stream_common << lvp_buf;
        }
        //fclose(file);
    }

}

void Kia_protocol::preset_before_save_and_out(uint16_t& num_bokz, QString data_to_out, uint16_t type_window, uint16_t type_protocol, uint16_t parametr)
{
    reset_protocol();
    if (!data_to_out.isEmpty())
    {
        QStringList list_protocol;
        list_protocol.push_back(QString::number(num_bokz));
        list_protocol.push_back(data_to_out);
        emit send_to_client(type_window, list_protocol);
        save_to_protocols(num_bokz, data_to_out, type_protocol);
    }
}

void Kia_protocol::reset_protocol()
{
    if (m_kia_settings->m_data_to_protocols->m_start_create_dir_for_protocols  != helpers::current_hours())
    {
        m_kia_settings->m_data_to_protocols->m_stop_do_save_protocol = KiaS_FAIL;
        reset_dir_for_protocols();
    }
}

void Kia_protocol::save_and_out_to_dev_protocols(uint16_t &num_bokz, const QString &data_to_out, const uint16_t &num_mpi_command, uint16_t parametr)
{
    QStringList list_dev_protocol;
    list_dev_protocol.push_back(QString::number(num_mpi_command));
    list_dev_protocol.push_back(QString::number(num_bokz));
    list_dev_protocol.push_back(data_to_out);


    emit send_to_client(SET_WINDOW_INFO_DEVICE_PROTOCOL, list_dev_protocol);


    save_to_protocols(num_bokz, data_to_out, SP_DO_DEV);

}

void Kia_protocol::save_and_out_to_mko_protocols(uint16_t &num_bokz, const QString &data_to_out, uint16_t parametr)
{
    QStringList list_mko_protocol;
    list_mko_protocol.push_back(QString::number(num_bokz));
    list_mko_protocol.push_back(data_to_out);
    emit send_to_client(SET_WINDOW_INFO_MPI, list_mko_protocol);
    save_to_protocols(num_bokz, data_to_out, SP_DO_MKO);
}

void Kia_protocol::reset_dir_for_protocols()
{
    close_dir_for_protocols();
    create_dir_for_protocols();
}
