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
    void shtmi1(uint16_t parametr = EP_DOALL);
    void shtmi2(uint16_t parametr = EP_DOALL);
    void mshior(uint16_t parametr = EP_DOALL);
    void os(uint16_t parametr = EP_DOALL);
    void synchro(uint16_t parametr = EP_DOALL);
    void skor(uint16_t parametr = EP_DOALL);
    void smti(uint16_t parametr = EP_DOALL);
    void vmti(uint16_t parametr = EP_DOALL);
    void command_no(uint16_t parametr = EP_DOALL);
    void command_to(uint16_t parametr = EP_DOALL);
    void command_loc(uint16_t parametr = EP_DOALL);
    void command_otclp(uint16_t parametr = EP_DOALL);
    void command_bshv(uint16_t parametr = EP_DOALL);
    void command_restart(uint16_t parametr = EP_DOALL);
    void command_oo(uint16_t parametr = EP_DOALL);
    void command_zkr(uint16_t parametr = EP_DOALL);
    void command_full_exp(uint16_t parametr = EP_DOALL);
    void kvaor(uint16_t parametr = EP_DOALL);
    void vskou(uint16_t parametr = EP_DOALL);
    void dtmi_or_dtmi_loc(uint16_t parametr = EP_DOALL);
    void mloc(uint16_t parametr = EP_DOALL);
    void set_epsilon(uint16_t parametr = EP_DOALL);
    void get_epsilon(uint16_t parametr = EP_DOALL);
    void set_focus(uint16_t parametr = EP_DOALL);
    void get_focus(uint16_t parametr = EP_DOALL);
    void set_texp(uint16_t parametr = EP_DOALL);
    void get_texp(uint16_t parametr = EP_DOALL);

    void do_frames(uint16_t type_frame, uint16_t parametr = EP_DOALL);

    void cyclogram_state_on(uint16_t parametr = EP_DOALL);
    void cyclogram_state_off(uint16_t parametr = EP_DOALL);
    void cyclogram_oo(uint16_t parametr = EP_DOALL);
    void cyclogram_no(uint16_t parametr = EP_DOALL);
    void cyclogram_to(uint16_t parametr = EP_DOALL);
    void cyclogram_ai(uint16_t parametr = EP_DOALL);
    void cyclogram_loc(uint16_t parametr = EP_DOALL);
    void cyclogram_define_address(uint16_t parametr = EP_DOALL);
    void cyclogram_operation(uint16_t parametr = EP_DOALL);
    void cyclogram_1s_mark(uint16_t parametr = EP_DOALL);
    void cyclogram_test_mko(uint16_t parametr = EP_DOALL);
    void cyclogram_test_synchro(uint16_t parametr = EP_DOALL);
    void cyclogram_technical_run(uint16_t parametr = EP_DOALL);
    void cyclogram_zkr(uint16_t parametr = EP_DOALL);
    void cyclogram_full_frames(uint16_t parametr = EP_DOALL);
    void cyclogram_check_address(uint16_t parametr = EP_DOALL);

    void delete_all_threads();
    void set_stop();
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
    void kia_init();
    void start_kia_gui();
    void set_kia_settings();
    void close_db_connection();
    bool check_used_bokz(uint16_t type_command, std::function<void(uint16_t, uint16_t)> start_exchange, uint16_t parametr = EP_DOALL);
    void send_kia_initial_settings();
    void send_mpi_list_command();
    void send_mpi_list_other_command();
    void send_cyclogams_list();
    void send_cyclogams_ai_list();
    void send_cyclogams_ri_list();
    void send_cyclograms_do();
    void kia_profile_load();
    void send_type_bi_to_table_settings();
    void send_info_about_connection();
    QProcess *m_process;
    bool m_is_con_to_db;
    bool m_is_con_to_tg;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::shared_ptr<Kia_load_initial_settings> m_kia_load_initial_settings;
    std::shared_ptr<Kia_db> m_kia_db;
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_bi_db;
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_bokz_db;
    std::shared_ptr<Kia_mpi> m_kia_mpi;
    shared_ptr<Kia_matrox> m_kia_matrox;
    shared_ptr<Kia_protocol> m_kia_protocol;
    std::shared_ptr<Kia_timers> m_kia_timers;
    shared_ptr<ParseToDB> m_parseToDB;
    shared_ptr<Kia_ftdi> m_kia_ftdi;
    std::vector<std::shared_ptr<Bokz>> m_bokz;
    std::shared_ptr<Kia_cyclogram> m_kia_cyclogram;
    quint16 m_nNextBlockSize = 0;
    QTcpServer* m_ptcpServer;
    QTcpSocket* m_pClientSocket;
    uint16_t m_type_frame_recieve = Bokz::MKO;
};

#endif // WORKWITHMAIN_H
