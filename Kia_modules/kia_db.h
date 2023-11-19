#ifndef KIA_DB_H
#define KIA_DB_H
#include <queue>
#include <QObject>
#include <pqxx/pqxx>
#include <mainStruct.h>
#include "simpletimer.h"
class Kia_db : public QObject
{
    Q_OBJECT
public:
    Kia_db(std::shared_ptr<Kia_settings> kia_settings);
    ~Kia_db();
    string get_mac_address();
    void send_status_connection_to_db();
    void close_connect();
    void start_experiment();
    void add_device_to_experiment(const string& type_dev, uint16_t &num_dev);
    void end_experiment();
    void start_commit();
    void insert_data(string data_to_db, string prepare_name);
    void stop_commit();
signals:
    void send_to_client(quint16, QStringList);
private:
    void wait_for_event();
    std::mutex m_mtx;
    uint16_t connect_to_db();
    void prepare_request(std::shared_ptr<pqxx::connection> conn);
    std::shared_ptr<pqxx::connection> m_conn;
    std::shared_ptr<pqxx::work> m_work;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::future<void> m_stop_commit_thread;
    std::atomic_bool m_stop_commit{false};
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
    std::map<std::string, QString> m_map_for_save_sql;
    std::queue<std::string> m_data;
    std::string m_name_prepare_raw;
    std::string m_name_prepare;
    std::condition_variable m_cv;
};

#endif // KIA_DB_H
