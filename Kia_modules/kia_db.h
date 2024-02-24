#ifndef KIA_DB_H
#define KIA_DB_H
#include <queue>
#include <QObject>
#include <pqxx/pqxx>
#include <iostream>
#include "Kia_enums.h"
#include "simpletimer.h"
#include <mutex>
#include <future>
#include <math.h>
class Kia_db : public QObject
{
    Q_OBJECT
public:
    Kia_db(uint32_t interval_to_send = 0);
    uint16_t connect_to_db();
    ~Kia_db();
    std::string get_mac_address();
    void set_type_bokz_and_type_bi(uint16_t type_bokz, uint16_t type_bi);
    void send_status_connection_to_db();
    void close_connect();
    void start_experiment(const std::string& extype_id, const std::string& description,
                          const std::string& experiment_id, const std::string& true_host);
    void add_device_to_experiment(const std::string& type_dev, uint16_t &num_dev,
                                  const std::string &experiment_id, const std::string &true_host);
    void end_experiment(const std::string& experiment_id, const std::string& true_host);
    void start_commit();
    void insert_data(std::string data_to_db, std::string prepare_name);
    void stop_commit();

    std::string get_type_bokz_string(uint16_t type_bokz)
    {
        return m_type_bokz_list[type_bokz];
    }

    std::string get_type_bi_string(uint16_t type_bi)
    {
        return m_type_bi_list[type_bi];
    }
    void set_interval_to_send(uint32_t interval = 0)
    {
        m_interval_to_send = interval;
    }
signals:
    void send_to_client(quint16, QStringList);
private:
    void wait_for_event();
    std::mutex m_mtx;
    void prepare_request(std::shared_ptr<pqxx::connection> conn);
    std::shared_ptr<pqxx::connection> m_conn;
    std::shared_ptr<pqxx::work> m_work;
    std::shared_ptr<pqxx::pipeline> m_pipeline;
    std::future<void> m_stop_commit_thread;
    std::atomic_bool m_stop_commit{false};
    std::string m_db_data;
    //    std::string m_dbname = "kiauniversal";
    //    std::string m_user = "postgres";
    //    std::string m_password = "88005553535";
    //    std::string m_hostaddr = "193.232.17.12";
    //    std::string m_port = "5435";
    std::string m_dbname = "kia_bokzm60";
    std::string m_user = "postgres";
    std::string m_password = "88005553535";
    std::string m_hostaddr = "127.0.0.1";
    std::string m_port = "5432";
    std::queue<std::string> m_data;
    std::string m_buffer_data;
    std::map<std::string, QString> m_prepare_sql;
    uint32_t m_count_to_send = 0;
    uint32_t m_interval_to_send = 0;
    std::string m_name_prepare_raw;
    std::string m_name_prepare;
    std::condition_variable m_cv;
    uint16_t m_is_con_to_db;
    int64_t m_curr_time = 0;
    int64_t m_prev_time = 0;
    std::vector<std::string> m_type_bokz_list = {"bokzm60", "bokzmf"};
    std::vector<std::string> m_type_bi_list = {"bkpik", "biu"};
    uint16_t m_type_bokz;
    uint16_t m_type_bi;
};

#endif // KIA_DB_H
