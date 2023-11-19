#ifndef WORKWITHDB_H
#define WORKWITHDB_H
#include <iostream>
#include <QObject>
#include "kia_protocol.h"
#include <pqxx/pqxx>
#include <map>
#include <functional>
#include <stack>
#include "simpletimer.h"
#include <mutex>
#include <future>
#include <queue>
#include <mainStruct.h>
class WorkWithDB : public QObject
{
    Q_OBJECT
public:
    WorkWithDB(uint16_t max_cons, shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings);
    ~WorkWithDB();
    uint16_t connect_to_db();
    void start_experiment();
    void add_device_to_experiment(string type_dev, uint16_t &num_dev);
    void insert_data_to_bi(uint16_t ind, string data_to_bd);
    void insertDataIntoBOKZ(uint16_t ind, string data_to_bd, string prepare_name);
    void prepareRequest(shared_ptr<pqxx::connection> conn);
    void stopCommit();
    void stop_check_internet_connections();
    void send_status_connection_to_db();
    string getMacAddress();
    uint16_t close_connect();
public slots:
    void reconnect_to_db();
signals:
    void send_to_client(quint16, QStringList);
    void do_reconnect();
private:
    void check_internet_connections();
    uint16_t m_max_cons = 0;
    bool m_is_connected_to_db = true;
    shared_ptr<Kia_protocol> m_kia_protocol;
    std::shared_ptr<Kia_settings> m_kia_settings;
    vector<shared_ptr<pqxx::connection> > m_conn;
    vector<shared_ptr<pqxx::work> > m_work;
    void do_commit_bi();
    void doCommitBOKZ();
    string m_db_data;
    //    string m_dbname = "kiauniversal";
    //    string m_user = "postgres";
    //    string m_password = "88005553535";
    //    string m_hostaddr = "193.232.17.12";
    //    string m_port = "5435";
    string m_dbname = "kia_bokzm60";
    string m_user = "postgres";
    string m_password = "88005553535";
    string m_hostaddr = "127.0.0.1";
    string m_port = "5432";
    string m_prepare_name;
    bool m_con_internet = false;
    uint16_t m_count = 0;
    std::queue<std::string> m_data_raw_bi;
    std::queue<std::string> m_data_telemetry_bi;
    std::queue<std::string> m_queryQueueMPIBOKZ;
    std::queue<std::string> m_queryQueueDescBOKZ;
    Flags_for_thread m_flags_for_thread;
    pqxx::result m_MacAdress;
    uint16_t m_interval_check_con;
    std::map<std::string, QString> m_map_for_save_sql;
};

#endif // WORKWITHDB_H
