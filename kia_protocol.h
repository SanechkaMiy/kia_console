#ifndef KIA_PROTOCOL_H
#define KIA_PROTOCOL_H
#include <QtCore>
#include <future>
#include <QFile>
#include <queue>
#include "mainStruct.h"
#include "Kia_modules/kia_help_functions.h"
class Kia_protocol: public QObject
{
    Q_OBJECT
public:
    Kia_protocol(std::shared_ptr<Kia_settings> kia_settings);
    ~Kia_protocol();
    void create_dir_for_protocols();
    void create_dir_for_sql_protocols();
    void create_dir_for_frame_protocols();
    void close_dir_for_protocols();
    void close_dir_for_sql_protocols();
    void close_dir_for_frame_protocols();
    void save_to_protocols(uint16_t &num_bokz, const QString & data_to_out, const uint16_t &type_protocol);
    void save_to_sql_protocols(const QString &data_to_out);
    void save_and_out_to_dev_protocols(uint16_t &num_bokz, const QString & data_to_out, const uint16_t &num_mpi_command, uint16_t parametr = EP_DOALL);
    void save_and_out_to_mko_protocols(uint16_t &num_bokz, const QString & data_to_out, uint16_t parametr = EP_DOALL);

    void preset_before_save_and_out(uint16_t& num_bokz, QString data_to_out, uint16_t type_window, uint16_t type_protocol, uint16_t parametr = EP_DOALL);

    void reset_dir_for_protocols();

public slots:
    void preset_before_save_and_out(Kia_protocol_parametrs kia_protocol_parametrs);
    void save_to_frames_protocols(const Kia_frame_parametrs &kia_frame_parametrs);
signals:
    void send_to_client(quint16, QStringList);
private:
    QString m_full_path;
    void start_check_time();
    void reset_protocol();
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::future<void> m_check_time;
    std::atomic_bool m_stop_check_timer{false};
    std::array<std::vector<QFile*>, constants::protocol_count> m_file_for_protocol;
    QFile* m_file_for_sql_protocol;
    uint32_t m_start_create_dir_for_protocols = 0;
    uint16_t m_stop_do_save_protocol = KiaS_SUCCESS;
};

#endif // KIA_PROTOCOL_H
