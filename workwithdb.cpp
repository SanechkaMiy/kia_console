#include "workwithdb.h"


WorkWithDB::WorkWithDB(uint16_t max_cons, shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings) :
    m_max_cons(max_cons)
  , m_kia_protocol(kia_protocol)
  , m_kia_settings(kia_settings)
{
    m_db_data = "dbname = " + m_dbname + " user = " + m_user + " password = " + m_password + " hostaddr = " + m_hostaddr + " port = " + m_port;
    connect(this, SIGNAL(do_reconnect()), this, SLOT(reconnect_to_db()));
    connect_to_db();
    //check_internet_connections();
}



WorkWithDB::~WorkWithDB()
{
    cout<<"destructor WorkWithDB"<<endl;
}

uint16_t WorkWithDB::connect_to_db()
{
    m_is_connected_to_db = false;
    try
    {
        m_kia_settings->m_is_con_to_internet = CS_IS_ON;
        m_kia_settings->m_is_con_to_db = CS_IS_ON;
        for (uint32_t i = 0; i < m_max_cons; i++)
        {
            shared_ptr<pqxx::connection> con(new pqxx::connection(m_db_data));
            shared_ptr<pqxx::work> work(new pqxx::work(*con));
            m_conn.push_back(shared_ptr < pqxx::connection > (con));
            m_work.push_back(shared_ptr <pqxx::work> (work));
            prepareRequest(m_conn[i]);
        }
        m_kia_settings->m_data_for_db->true_host = getMacAddress();
        m_kia_settings->m_data_for_db->m_extype_id = "stand";
        m_kia_settings->m_data_for_db->m_description = "Тестовое испытание";
        start_experiment();
        do_commit_bi();
        doCommitBOKZ();
    }
    catch(std::exception const &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "cannot to connect to db" << std::endl;
        m_kia_settings->m_is_con_to_db = CS_IS_OFF;
        return m_kia_settings->m_is_con_to_db;
    }
    return m_kia_settings->m_is_con_to_db;
}
void WorkWithDB::prepareRequest(shared_ptr<pqxx::connection> conn)
{
    conn->prepare("prepare_get_mac_address", "SELECT public.mac_address()");
    conn->prepare("prepare_begin_experiment", "SELECT public.begin_experiment($1, $2, $3, $4);");
    conn->prepare("prepare_add_device_to_experiment", "SELECT add_device_to_experiment($1, $2, 'original', $3, $4);");
    conn->prepare("prepare_end_experiment", "SELECT public.end_experiment($1, $2);");
    conn->prepare("prepare_insert_telemetry", "CALL " + m_kia_settings->m_data_for_db->m_type_bi[m_kia_settings->m_type_bi] + ".insert_into_telemetry($1::json);");
    conn->prepare("prepare_insert_raw", "CALL " + m_kia_settings->m_data_for_db->m_type_bi[m_kia_settings->m_type_bi] + ".insert_into_raw($1::json);");
    conn->prepare("prepare_insert_into_mpi", "CALL bokzm60.insert_into_mpi($1::json)");
    conn->prepare("prepare_insert_into_mshior","CALL bokzm60.insert_into_mshior($1::json)");
    conn->prepare("prepare_insert_into_shtmi1","CALL bokzm60.insert_into_shtmi1($1::json)");
    conn->prepare("prepare_insert_into_shtmi2","CALL bokzm60.insert_into_shtmi2($1::json)");
    conn->prepare("prepare_insert_into_dtmiloc", "CALL bokzm60.insert_into_dtmiloc($1::json)");
    conn->prepare("prepare_insert_into_dtmi", "CALL bokzm60.insert_into_dtmi($1::json)");
    conn->prepare("prepare_insert_into_frames", "CALL bokzm60.insert_into_frames($1::json)");

    m_map_for_save_sql["prepare_insert_into_mshior"] = "CALL bokzm60.insert_into_mshior('%1'::json);\n";
    m_map_for_save_sql["prepare_insert_into_shtmi1"] = "CALL bokzm60.insert_into_shtmi1('%1'::json);\n";
    m_map_for_save_sql["prepare_insert_into_shtmi2"] = "CALL bokzm60.insert_into_shtmi2('%1'::json);\n";
    m_map_for_save_sql["prepare_insert_into_dtmiloc"] = "CALL bokzm60.insert_into_dtmiloc('%1'::json);\n";
    m_map_for_save_sql["prepare_insert_into_dtmi"] = "CALL bokzm60.insert_into_dtmi('%1'::json);\n";
    m_map_for_save_sql["prepare_insert_into_frames"] = "CALL bokzm60.insert_into_frames('%1'::json);\n";
}

string WorkWithDB::getMacAddress()
{
    auto mac_adress = m_work[0]->exec_prepared("prepare_get_mac_address");
    m_work[0]->commit();
    return mac_adress[0][0].c_str();
}

void WorkWithDB::reconnect_to_db()
{
    std::cout << "connect" << std::endl;
    connect_to_db();
}

void WorkWithDB::send_status_connection_to_db()
{
    QStringList status_connection;
    status_connection.push_back(QString::number(m_kia_settings->m_is_con_to_db));
    emit send_to_client(CONNECT_TO_DB, status_connection);
}

uint16_t WorkWithDB::close_connect()
{
    if (m_kia_settings->m_is_con_to_internet == CS_IS_ON)
    {
        if (m_kia_settings->m_is_con_to_db == CS_IS_ON)
        {
            m_work[0]->exec_prepared("prepare_end_experiment", m_kia_settings->m_data_for_db->experiment_id, m_kia_settings->m_data_for_db->true_host);
            m_kia_protocol->save_to_sql_protocols(QString("SELECT public.end_experiment('%1', '%2');\n").arg(QString::fromStdString(m_kia_settings->m_data_for_db->experiment_id))
                                                  .arg(QString::fromStdString(m_kia_settings->m_data_for_db->true_host)));
            for (uint16_t i; i < m_conn.size(); i++)
            {
                m_work[i]->commit();
                m_conn[i]->close();
            }
            m_conn.clear();
            m_work.clear();
        }
        else
        {
            for (uint16_t i; i < m_conn.size(); i++)
            {
                m_conn[i]->close();
            }
            m_work.clear();
        }
        return CS_IS_ON;
    }
    else
        return CS_IS_OFF;
}

void WorkWithDB::check_internet_connections()
{

    m_kia_settings->m_flags_for_thread->m_stop_check_internet_con_thread = std::async([this]
    {
        m_kia_settings->m_flags_for_thread->m_stop_check_internet_con = true;
        m_interval_check_con = 100;
        while(m_kia_settings->m_flags_for_thread->m_stop_check_internet_con)
        {

            FILE *output;
            output = popen("/sbin/route -n | grep -c '^0\\.0\\.0\\.0'","r");
            unsigned int i;
            fscanf(output,"%u",&i);
            if(i == 1)
            {
                m_kia_settings->m_is_con_to_internet = CS_IS_ON;
                if (m_is_connected_to_db)
                    emit do_reconnect();
                //cerr<<"There is internet connection\n";
            }
            else if(i == 0)
            {
                stopCommit();
                m_kia_settings->m_is_con_to_db = CS_IS_OFF;
                close_connect();
                m_kia_settings->m_is_con_to_internet = CS_IS_OFF;
                //cerr<<"There is no internet connection\n";
            }
            pclose(output);
            this_thread::sleep_for(std::chrono::milliseconds(m_interval_check_con));
        }
    });
}


//void WorkWithDB::stopCommit()
//{

//    if (m_kia_settings->m_is_con_to_db == CS_IS_ON)
//    {
//        std::cout << "stop commit!" << std::endl;
//        if (m_flags_for_thread.m_stopDoCommitBOKZ)
//        {
//            while ((!m_queryQueueMPIBOKZ.empty()) && (!m_queryQueueDescBOKZ.empty()))
//            {
//                std::cout << "mpi "<<m_queryQueueMPIBOKZ.size() << std::endl;
//                std::cout << "desc " << m_queryQueueDescBOKZ.size() << std::endl;
//            }
//            m_flags_for_thread.m_stopDoCommitBOKZ = false;
//            m_flags_for_thread.m_futStopDoCommitBOKZ.get();
//            std::cout << "stop_commit bokz" << std::endl;
//        }
//        if (m_flags_for_thread.m_stop_do_commit_bi)
//        {
//            while ((!m_data_raw_bi.empty()) && (!m_data_telemetry_bi.empty()))
//            {
//                std::cout <<"raw bkpik " << m_data_raw_bi.size() << std::endl;
//                std::cout << "des bkpik " << m_data_telemetry_bi.size() << std::endl;

//            }
//            m_flags_for_thread.m_stop_do_commit_bi = false;
//            m_flags_for_thread.m_stop_do_commit_bi_thread.get();
//            std::cout << "stop_commit bkpik" << std::endl;
//        }

//    }
//}

void WorkWithDB::stop_check_internet_connections()
{
    if (m_kia_settings->m_flags_for_thread->m_stop_check_internet_con)
    {
        m_kia_settings->m_flags_for_thread->m_stop_check_internet_con = false;
        m_kia_settings->m_flags_for_thread->m_stop_check_internet_con_thread.get();
    }
}

//void WorkWithDB::do_commit_bi()
//{
//        m_flags_for_thread.m_stop_do_commit_bi_thread = std::async([this]
//        {
//            m_flags_for_thread.m_stop_do_commit_bi = true;
//            while(m_flags_for_thread.m_stop_do_commit_bi)
//            {
//                if (!m_data_raw_bi.empty())
//                {
//                    m_work[1]->exec_prepared("prepare_insert_raw", m_data_raw_bi.front());
//                    m_kia_protocol->save_to_sql_protocols(QString(QString::fromStdString(m_kia_settings->m_data_for_db->m_type_bi[m_kia_settings->m_type_bi])
//                                                          + ".insert_into_raw('%1'::json);\n").arg(QString::fromStdString(m_data_raw_bi.front())));
//                    m_work[1]->commit();
//                    m_data_raw_bi.pop();
//                }
//                if (!m_data_telemetry_bi.empty())
//                {
//                    m_work[1]->exec_prepared("prepare_insert_telemetry", m_data_telemetry_bi.front());
//                    m_kia_protocol->save_to_sql_protocols(QString(QString::fromStdString(m_kia_settings->m_data_for_db->m_type_bi[m_kia_settings->m_type_bi]) +
//                                                          ".insert_into_telemetry('%1'::json;\n").arg(QString::fromStdString(m_data_telemetry_bi.front())));
//                    m_work[1]->commit();
//                    m_data_telemetry_bi.pop();
//                }
//            }
//        });
//}
//void WorkWithDB::doCommitBOKZ()
//{
//    m_flags_for_thread.m_futStopDoCommitBOKZ = std::async([this]
//    {
//        m_flags_for_thread.m_stopDoCommitBOKZ = true;
//        while(m_flags_for_thread.m_stopDoCommitBOKZ)
//        {
//            if (!m_queryQueueMPIBOKZ.empty())
//            {
//                m_work[2]->exec_prepared("prepare_insert_into_mpi", m_queryQueueMPIBOKZ.front());
//                m_kia_protocol->save_to_sql_protocols(QString("CALL bokzm60.insert_into_mpi('%1'::json);\n").arg(QString::fromStdString(m_queryQueueMPIBOKZ.front())));
//                m_work[2]->commit();
//                m_queryQueueMPIBOKZ.pop();
//            }
//            if (!m_queryQueueDescBOKZ.empty())
//            {
//                m_work[2]->exec_prepared(m_prepare_name, m_queryQueueDescBOKZ.front());
//                m_kia_protocol->save_to_sql_protocols(m_map_for_save_sql[m_prepare_name].arg(QString::fromStdString(m_queryQueueDescBOKZ.front())));
//                m_work[2]->commit();
//                m_queryQueueDescBOKZ.pop();
//            }
//        }
//    });
//}

void WorkWithDB::start_experiment()
{
    m_work[0]->exec_prepared("prepare_begin_experiment", m_kia_settings->m_data_for_db->m_extype_id, m_kia_settings->m_data_for_db->m_description, m_kia_settings->m_data_for_db->experiment_id, m_kia_settings->m_data_for_db->true_host);
    m_kia_protocol->save_to_sql_protocols(QString("SELECT public.begin_experiment('%1', '%2', '%3', '%4');\n").arg(QString::fromStdString(m_kia_settings->m_data_for_db->m_extype_id)).arg(QString::fromStdString(m_kia_settings->m_data_for_db->m_description))
                                          .arg(QString::fromStdString(m_kia_settings->m_data_for_db->experiment_id)).arg(QString::fromStdString(m_kia_settings->m_data_for_db->true_host)));
}

void WorkWithDB::add_device_to_experiment(string type_dev, uint16_t &num_dev)
{
    m_work[0]->exec_prepared("prepare_add_device_to_experiment", type_dev, num_dev, m_kia_settings->m_data_for_db->experiment_id, m_kia_settings->m_data_for_db->true_host);
    m_kia_protocol->save_to_sql_protocols(QString("SELECT add_device_to_experiment('%1', %2, 'original', '%3', '%4');\n").arg(QString::fromStdString(type_dev)).arg(QString::number(num_dev))
                                          .arg(QString::fromStdString(m_kia_settings->m_data_for_db->experiment_id)).arg(QString::fromStdString(m_kia_settings->m_data_for_db->true_host)));
    m_work[0]->commit();
}


void WorkWithDB::insert_data_to_bi(uint16_t ind, string data_to_bd)
{
    if (m_kia_settings->m_is_con_to_db == CS_IS_ON)
    {
        switch(ind)
        {
        case 0:
            m_data_raw_bi.push(data_to_bd);
            break;
        case 1:
            m_data_telemetry_bi.push(data_to_bd);
            break;
        }
    }
}

void WorkWithDB::insertDataIntoBOKZ(uint16_t ind, string data_to_bd, string prepare_name)
{
    if (m_kia_settings->m_is_con_to_db == CS_IS_ON)
    {
        switch(ind)
        {
        case 0:
            m_queryQueueMPIBOKZ.push(data_to_bd);
            break;
        case 1:
            m_prepare_name = prepare_name;
            m_queryQueueDescBOKZ.push(data_to_bd);
            break;
        }
    }
}

