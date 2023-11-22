#ifndef BOKZM60_H
#define BOKZM60_H
#include <QtCore>
#include <iostream>
#include "bokz.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "mainStruct.h"
#include "parsetodb.h"
#include "kia_protocol.h"
#include "kia_matrox.h"
#include "workwithstruct.h"
#include "kia_bkpik.h"
#include "kia_synch_timer.h"
#include "kia_biu.h"
#include "simpletimer.h"
#include "kia_ftdi.h"
#include "kia_bi.h"
#include "Kia_mko_struct.h"
#include "Kia_modules/kia_mpi.h"
#include "Kia_modules/kia_db.h"
#include "Kia_modules/kia_help_functions.h"
class BokzM60 : public Bokz
{
    Q_OBJECT
public:
    //using kia_info_p = shared_ptr <KiaInformationBot>;
    BokzM60(uint16_t num_bokz, shared_ptr<WorkWithStruct> wws,
            std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
            std::vector<shared_ptr <Timer>> timer, std::vector<std::shared_ptr<Kia_synch_timer> > kia_synch_timer,
            std::vector<shared_ptr<Kia_bi>> kia_bi, shared_ptr <Kia_mpi> kia_mpi,
            shared_ptr<Kia_protocol> kia_protocol, shared_ptr<Kia_matrox> kia_matrox,
            std::shared_ptr<Kia_settings> kia_settings, shared_ptr<Kia_ftdi> kia_ftdi);
    ~BokzM60();
    void set_bokz_settings() override;
    uint16_t shtmi1(uint16_t parametr = EP_DOALL) override;
    uint16_t shtmi2(uint16_t parametr = EP_DOALL) override;
    uint16_t mshior(uint16_t parametr = EP_DOALL) override;
    uint16_t dtmi_or_dtmi_loc(uint16_t parametr = EP_DOALL) override;
    uint16_t smti(uint16_t parametr = EP_DOALL) override;
    uint16_t vmti(uint16_t parametr = EP_DOALL) override;
    uint16_t synchro(uint16_t parametr = EP_DOALL) override;
    uint16_t skor(uint16_t parametr = EP_DOALL) override;
    uint16_t command_no(uint16_t parametr = EP_DOALL) override;
    uint16_t command_to(uint16_t parametr = EP_DOALL) override;
    uint16_t command_full_exp(uint16_t parametr = EP_DOALL) override;
    uint16_t command_loc(uint16_t parametr = EP_DOALL) override;
    uint16_t command_otclp(uint16_t parametr = EP_DOALL) override;
    uint16_t command_openkr(uint16_t parametr = EP_DOALL) override;
    uint16_t command_zkr(uint16_t parametr = EP_DOALL) override;
    uint16_t kvaor(uint16_t parametr = EP_DOALL) override;
    uint16_t os(uint16_t parametr = EP_DOALL) override;
    uint16_t vskou(uint16_t parametr = EP_DOALL) override;
    uint16_t initial_state(uint16_t parametr = EP_DOALL) override;
    uint16_t block_ou( uint16_t parametr = EP_DOALL) override;
    uint16_t unblock_ou( uint16_t parametr = EP_DOALL) override;
    uint16_t do_frames( uint16_t parametr = EP_DOALL) override;
    uint16_t set_epsilon(float command, uint16_t parametr = EP_DOALL) override;
    uint16_t get_epsilon(uint16_t parametr = EP_DOALL) override;
    uint16_t set_focus(uint16_t parametr = EP_DOALL) override;
    uint16_t get_focus( uint16_t parametr = EP_DOALL) override;
    uint16_t set_texp(uint16_t command, uint16_t parametr = EP_DOALL) override;
    uint16_t get_texp( uint16_t parametr = EP_DOALL) override;
    void preset_before_exchange() override;
signals:
    void send_to_client(quint16, QStringList) override;

private:
    void check_orientation();
    void getDataToDTMIOrDTMILoc();
    void send_status_info();
    void post_status_proc(QString &str_protocol);
    void send_data_to_command(const uint16_t &type_data, const uint16_t &type_command, const QString &data);
    void send_mpi_data_to_db();
    void save_to_protocol(QString str_to_protocol,  uint16_t parametr = EP_DOALL);
    uint16_t start_exchage(uint16_t parametr = EP_DOALL);
    uint16_t execute_protected_exchange(std::function<void()> func_mpi_command);
    std::function<void()> m_set_control_word;
    void set_data_to_device_protocol(QString &str_protocol);
    shared_ptr<WorkWithStruct> m_wws;
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_db;
    shared_ptr <ParseToDB> m_parser_db;
    std::vector<shared_ptr<Timer>> m_timer;
    std::vector<shared_ptr<Kia_synch_timer>> m_kia_synch_timer;
    std::vector<shared_ptr<Kia_bi>> m_kia_bi;
    shared_ptr<Kia_mpi> m_kia_mpi;
    shared_ptr<Kia_protocol> m_kia_protocol;
    shared_ptr<Kia_matrox> m_kia_matrox;
    std::shared_ptr<Kia_settings> m_kia_settings;
    shared_ptr<Kia_ftdi> m_kia_ftdi;
    uint16_t m_count_dtmi_dtmi_loc;
    std::vector<uint8_t> m_commandR;
};

#endif // BOKZM60_H
