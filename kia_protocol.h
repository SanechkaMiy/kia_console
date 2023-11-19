#ifndef KIA_PROTOCOL_H
#define KIA_PROTOCOL_H
#include <QtCore>
#include <future>
#include <QFile>
#include <workwithstruct.h>
#include <queue>
#include "mainStruct.h"
class Kia_protocol: public QObject
{
    Q_OBJECT
public:
    Kia_protocol(shared_ptr<WorkWithStruct> wws, std::shared_ptr<Kia_settings> kia_settings);
    ~Kia_protocol();
    void create_dir_for_protocols();
    void create_dir_for_sql_protocols();
    void create_dir_for_frame_protocols();
    void close_dir_for_protocols();
    void close_dir_for_sql_protocols();
    void close_dir_for_frame_protocols();
    void save_to_protocols(uint16_t &num_bokz, const uint16_t &type_protocol);
    void save_to_sql_protocols(const QString &data_to_out);
    void save_to_frames_protocols(uint16_t& num_bokz, uint32_t &bshv, void *lvp_buf, uint32_t buf_size);
    void save_and_out_to_system_error_ai_protocols(uint16_t &num_bokz, const QString &data_to_out, uint16_t parametr = EP_DOALL);
    void save_and_out_to_dev_mko_protocols(uint16_t &num_bokz, const uint16_t &num_mpi_command, uint16_t parametr = EP_DOALL);
    void reset_dir_for_protocols();
    void count_of_fails(uint16_t &num_bokz, uint16_t parametr = EP_DOALL);
signals:
    void send_to_client(quint16, QStringList);
private:
    QString m_full_path;
    void preset_before_save_and_out(uint16_t& num_bokz, const QString &data_to_out, uint16_t type_window, uint16_t type_protocol, uint16_t parametr = EP_DOALL);
    void start_check_time();
    void reset_protocol();
    shared_ptr<WorkWithStruct> m_wws;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::future<void> m_check_time;
    std::atomic_bool m_stop_check_timer{false};
};

#endif // KIA_PROTOCOL_H
