#include "kia_db.h"

Kia_db::Kia_db(uint32_t interval_to_send) :
    m_interval_to_send(interval_to_send)

{
    m_db_data = "dbname = " + m_dbname + " user = " + m_user + " password = " + m_password + " hostaddr = " + m_hostaddr + " port = " + m_port;
}

std::string Kia_db::get_mac_address()
{
    auto mac_adress = m_work->exec_prepared("prepare_get_mac_address");
    m_work->commit();
    return mac_adress[0][0].c_str();
}

void Kia_db::set_type_bokz_and_type_bi(uint16_t type_bokz, uint16_t type_bi)
{
    m_type_bokz = type_bokz;
    m_type_bi = type_bi;
}

void Kia_db::send_status_connection_to_db()
{
    QStringList status_connection;
    status_connection.push_back(QString::number(m_is_con_to_db));
    emit send_to_client(CONNECT_TO_DB, status_connection);
}

void Kia_db::close_connect()
{
    if (m_is_con_to_db == CS_IS_ON)
    {
        std::lock_guard lock(m_mtx);
        m_pipeline->complete();
        m_work->commit();
        m_conn->close();
    }

}

Kia_db::~Kia_db()
{
    std::cout << "destr db" << std::endl;
}
void Kia_db::start_experiment(const std::string& extype_id, const std::string& description,
                              const std::string& experiment_id, const std::string& true_host)
{
    std::lock_guard lock(m_mtx);
    m_work->exec_prepared("prepare_begin_experiment", extype_id, description, experiment_id, true_host);
}

void Kia_db::add_device_to_experiment(const std::string &type_dev, uint16_t &num_dev,
                                      const std::string& experiment_id, const std::string& true_host)
{
    std::lock_guard lock(m_mtx);
    m_work->exec_prepared("prepare_add_device_to_experiment", type_dev, num_dev, experiment_id, true_host);
    m_work->commit();
}

void Kia_db::end_experiment(const std::string& experiment_id, const std::string& true_host)
{
    std::lock_guard lock(m_mtx);
    m_work->exec_prepared("prepare_end_experiment", experiment_id, true_host);
}

void Kia_db::start_commit()
{
    m_stop_commit_thread  = std::async([this]
    {
        m_stop_commit = true;
        while(m_stop_commit)
        {
            wait_for_event();
            if (m_data.front() == "end")
                break;
            //std::lock_guard lock(m_mtx);

            //m_work->exec(m_data.front());
            //            m_pipeline->retain();
            m_pipeline->insert(m_data.front());
            if (m_count_to_send == m_interval_to_send)
            {

                m_pipeline->complete();
                //m_pipeline->retrieve();
                //m_work->exec_prepared(m_name_prepare, m_data.front());
                m_work->commit();
                m_count_to_send = 0;
            }
            if(m_interval_to_send != 0)
                m_count_to_send++;
            m_data.pop();
        }
    });
}

void Kia_db::insert_data(std::string data_to_db, std::string prepare_name)
{
    if (m_is_con_to_db == CS_IS_ON)
    {
        m_curr_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        if (m_prev_time != 0)
        {
            auto delta = m_curr_time - m_prev_time;
            m_interval_to_send = round(delta / 1000.0);
        }
        m_prev_time = m_curr_time;
        m_data.push(m_prepare_sql[prepare_name].arg(QString::fromStdString(data_to_db)).toStdString());
        m_cv.notify_all();
        //m_prepare_sql[prepare_name].arg(QString::fromStdString(data_to_db)).toStdString()
        //std::lock_guard lock(m_mtx);
        //        m_name_prepare = prepare_name;
        //        m_data.push(data_to_db);
        //        m_cv.notify_all();

        //        if (m_count_to_send == 2)
        //        {
        //            m_data.push(m_buffer_data);
        //            m_cv.notify_all();
        //            m_count_to_send = 0;
        //            m_buffer_data.clear();
        //        }
        //        else
        //        {
        //            m_buffer_data = m_buffer_data + m_prepare_sql[prepare_name].arg(QString::fromStdString(data_to_db)).toStdString();
        //            m_count_to_send++;
        //        }
    }
}

void Kia_db::wait_for_event()
{
    std::mutex m;
    std::unique_lock lk(m);
    m_cv.wait(lk, [this]
    {
        return !m_data.empty();
    });
}

void Kia_db::stop_commit()
{
    std::cout << "start_commit " << std::endl;
    if (m_is_con_to_db == CS_IS_ON)
    {
        if (m_stop_commit)
        {
            while (!m_data.empty())
            {
                std::cout << m_data.front() << std::endl;
                std::cout << "data " << m_data.size() << std::endl;
            }
            m_data.push("end");
            m_cv.notify_all();
            std::cout << "stop commit!" << std::endl;
            m_stop_commit = false;
            //m_stop_commit_thread.get();
            std::cout << "stop_commit" << std::endl;
        }
    }
}

uint16_t Kia_db::connect_to_db()
{
    try
    {
        m_is_con_to_db = CS_IS_ON;
        m_conn.reset(new pqxx::connection(m_db_data));
        m_work.reset(new pqxx::work(*m_conn));
        prepare_request(m_conn);
        m_pipeline.reset(new pqxx::pipeline(*m_work));
        m_pipeline->complete();
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "cannot to connect to db" << std::endl;
        m_is_con_to_db = CS_IS_OFF;
        return m_is_con_to_db;
    }
    return m_is_con_to_db;
}

void Kia_db::prepare_request(std::shared_ptr<pqxx::connection> conn)
{
    conn->prepare("prepare_get_mac_address", "SELECT public.mac_address()");
    conn->prepare("prepare_begin_experiment", "SELECT public.begin_experiment($1, $2, $3, $4);");
    conn->prepare("prepare_add_device_to_experiment", "SELECT add_device_to_experiment($1, $2, 'original', $3, $4);");
    conn->prepare("prepare_end_experiment", "SELECT public.end_experiment($1, $2);");

    conn->prepare("prepare_insert_telemetry", "CALL " + m_type_bi_list[m_type_bi] + ".insert_into_telemetry($1::json);");
    conn->prepare("prepare_insert_raw", "CALL " + m_type_bi_list[m_type_bi] + ".insert_into_raw($1::json);");
    conn->prepare("prepare_insert_into_mpi", "CALL " + m_type_bokz_list[m_type_bokz] + ".insert_into_mpi($1::json)");
    conn->prepare("prepare_insert_into_shtmi1", "CALL " + m_type_bokz_list[m_type_bokz] + ".insert_into_shtmi1($1::json)");
    conn->prepare("prepare_insert_into_mshior", "CALL " + m_type_bokz_list[m_type_bokz] + ".insert_into_mshior($1::json)");
    conn->prepare("prepare_insert_into_shtmi2", "CALL " + m_type_bokz_list[m_type_bokz] + ".insert_into_shtmi2($1::json)");

    m_prepare_sql["prepare_insert_telemetry"] = "CALL " + QString::fromStdString(m_type_bi_list[m_type_bi]) + ".insert_into_telemetry('%1'::json);";
    m_prepare_sql["prepare_insert_raw"] = "CALL " + QString::fromStdString(m_type_bi_list[m_type_bi]) + ".insert_into_raw('%1'::json);";

    m_prepare_sql["prepare_insert_into_mpi"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_mpi('%1'::json);\n";
    m_prepare_sql["prepare_insert_into_mshior"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_mshior('%1'::json);\n";
    m_prepare_sql["prepare_insert_into_shtmi1"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_shtmi1('%1'::json);\n";
    m_prepare_sql["prepare_insert_into_shtmi2"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_shtmi2('%1'::json);\n";
    m_prepare_sql["prepare_insert_into_dtmi"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_dtmi('%1'::json);\n";

    switch(m_type_bokz)
    {
    case TYPE_BOKZ_BOKZM60:
        conn->prepare("prepare_insert_into_dtmiloc", "CALL " + m_type_bokz_list[m_type_bokz] + ".insert_into_dtmiloc($1::json)");
        conn->prepare("prepare_insert_into_dtmi", "CALL " + m_type_bokz_list[m_type_bokz] + ".insert_into_dtmi($1::json)");
        conn->prepare("prepare_insert_into_frames", "CALL " + m_type_bokz_list[m_type_bokz] + ".insert_into_frames($1::json)");
        m_prepare_sql["prepare_insert_into_dtmiloc"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_dtmiloc('%1'::json);\n";
        m_prepare_sql["prepare_insert_into_frames"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_frames('%1'::json);\n";
        break;
    case TYPE_BOKZ_BOKZMF:
        m_prepare_sql["prepare_insert_into_mloc"] = "CALL " + QString::fromStdString(m_type_bokz_list[m_type_bokz]) + ".insert_into_mloc('%1'::json);\n";
        break;
    }
}
