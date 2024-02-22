#ifndef WORKWITHMAIN_H
#define WORKWITHMAIN_H
#include <QWidget>
#include <QtGlobal>
#include <QVector>
#include <QtCore>
#include "timer.h"
#include "kia_synch_timer.h"
#include "parsetodb.h"
#include "kia_bkpik.h"
#include "kia_protocol.h"
#include "kia_matrox.h"
#include "mainStruct.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QFile>
#include <functional>
#include "kia_bi.h"
#include "kia_biu.h"
#include "kia_bkpik.h"
#include "kia_ftdi.h"
#include "bokz.h"
#include "bokzm60.h"
#include "bokzmf.h"
#include "kia_load_initial_settings.h"
#include "Kia_modules/kia_mpi.h"
#include "Kia_modules/kia_port.h"
#include "kia_cyclogram.h"
#include "kia_cyclogram_bokzm60.h"
#include "kia_cyclogram_bokzmf.h"
#include "Kia_modules/kia_db.h"
class WorkWithMain : public QObject
{
    Q_OBJECT

public:
    WorkWithMain(int nPort);
    ~WorkWithMain();

    void delete_all_threads();
signals:
    void send_to_client(quint16, QStringList);
public slots:
    void slot_send_to_client(quint16 num, QStringList data_for_client);
private slots:
    void delete_connection();
    void slot_read_client();
    void send_data_from_mpi_current_lpi_to_table_settings();
    virtual void new_connection_slot();
private:
    void start_tcp_server(uint16_t nPort);
    void create_func_to_read();
    void kia_init();
    void init_db();
    void init_bi();
    void init_bokz();
    void start_kia_gui();
    void set_kia_settings();
    void close_db_connection();
    bool check_used_bokz(uint16_t type_command, std::function<void(uint16_t, uint16_t)> start_exchange, uint16_t parametr = EP_DOALL);
    void send_bi_telemetry_list();
    void send_kia_initial_settings();
    void send_cyclogram_power_list();
    void send_mpi_list_command();
    void send_mpi_list_other_command();

    void send_pn_list_command();

    void send_cyclogams_list();
    void send_cyclogams_ai_list();
    void send_cyclogams_ri_list();
    void send_cyclograms_do();
    void send_cyclograms_power_do();

    void send_type_frame();
    void send_type_frame_recieve();

    void kia_profile_load();
    void send_type_bi_to_table_settings();
    void send_info_about_connection();
    QProcess *m_process;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Kia_load_initial_settings> m_kia_load_initial_settings;
    std::shared_ptr<Kia_db> m_kia_db;
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_bi_db;
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_bokz_db;
    std::shared_ptr<Kia_mpi> m_kia_mpi;
    shared_ptr<Kia_matrox> m_kia_matrox;
    shared_ptr<Kia_protocol> m_kia_protocol;
    std::shared_ptr<Kia_timers> m_kia_timers;
    std::vector<std::shared_ptr<ParseToDB>> m_parse_db_bi;
    std::vector<std::shared_ptr<ParseToDB>> m_parse_db_bokz;
    shared_ptr<Kia_ftdi> m_kia_ftdi;
    std::vector<std::shared_ptr<Bokz>> m_bokz;
    std::shared_ptr<Kia_cyclogram> m_kia_cyclogram;
    quint16 m_nNextBlockSize = 0;
    QTcpServer* m_ptcpServer;
    QTcpSocket* m_pClientSocket;
    std::map<uint16_t, std::function<void(QStringList)>> m_func_to_read;

};

#endif // WORKWITHMAIN_H
