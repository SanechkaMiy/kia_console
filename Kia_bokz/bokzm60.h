#ifndef BOKZM60_H
#define BOKZM60_H
#include <QtCore>
#include <iostream>
#include "bokz.h"
#include <stdio.h>
#include <stdlib.h>
#include "mainStruct.h"
#include "kia_matrox.h"
#include "kia_synch_timer.h"
#include "simpletimer.h"
#include "kia_ftdi.h"
#include "Kia_mko_struct.h"
#include "Kia_pio/pio_bokzm60.h"


class BokzM60 : public Bokz
{
    Q_OBJECT
public:


    enum TYPE_CHPN
    {
        TP_TEXP = 0,
        TP_FOC = 1,
        TP_X = 2,
        TP_Y = 3,
        TP_EPS = 4,
        TP_MAT = 5,
        TP_QA = 6,
        TP_W = 7
    };
    enum TYPE_COUNT_OF_FAIL
    {
        CHNOB = 0,
        SVREM = 1,
        SSBOU = 2,
        CHNOR = 3,
        CHAB = 4,
        CHNKV = 5,
        CHZLP = 6,
        CHNRO = 7,
        CHNEOR = 8,
        CHPRZ = 9,
    };
    //using kia_info_p = shared_ptr <KiaInformationBot>;
    BokzM60(uint16_t num_bokz, shared_ptr <Kia_mpi> kia_mpi,
            std::shared_ptr<Kia_settings> kia_settings, shared_ptr<Kia_ftdi> kia_ftdi);
    ~BokzM60();
    void set_bokz_settings() override;

    uint16_t debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address, uint16_t word_data,
                               string struct_id, string struct_id_desc, uint16_t parametr = EP_DOALL) override;


    uint16_t shtmi1(uint16_t parametr = EP_DOALL) override;
    uint16_t shtmi2(uint16_t parametr = EP_DOALL) override;
    uint16_t mshior(uint16_t parametr = EP_DOALL) override;
    uint16_t dtmi_or_dtmi_loc(uint16_t parametr = EP_DOALL) override;
    uint16_t mloc(uint16_t parametr = EP_DOALL) override;
    uint16_t upn(uint16_t type_upn, QStringList value, uint16_t parametr = EP_DOALL) override;
    uint16_t chpn(QStringList type_chpn, uint16_t parametr = EP_DOALL) override;
    uint16_t chkd(uint16_t parametr = EP_DOALL) override;
    uint16_t smti(uint16_t parametr = EP_DOALL) override;
    uint16_t vmti(uint16_t parametr = EP_DOALL) override;
    uint16_t synchro(uint16_t parametr = EP_DOALL) override;
    uint16_t skor(uint16_t parametr = EP_DOALL) override;
    uint16_t command_no(uint16_t parametr = EP_DOALL) override;
    uint16_t command_to(uint16_t parametr = EP_DOALL) override;
    uint16_t command_full_exp(uint16_t parametr = EP_DOALL) override;
    uint16_t command_bin_exp(uint16_t parametr = EP_DOALL) override;
    uint16_t command_loc(uint16_t parametr = EP_DOALL) override;
    uint16_t command_otclp(uint16_t parametr = EP_DOALL) override;
    uint16_t command_openkr(uint16_t parametr = EP_DOALL) override;
    uint16_t command_zkr(uint16_t parametr = EP_DOALL) override;
    uint16_t command_bshv(uint16_t parametr = EP_DOALL) override;
    uint16_t command_restart(uint16_t parametr = EP_DOALL) override;
    uint16_t command_oo(uint16_t parametr = EP_DOALL) override;

    uint16_t kvaor(uint16_t parametr = EP_DOALL) override;
    uint16_t os(uint16_t parametr = EP_DOALL) override;
    uint16_t vskou(uint16_t parametr = EP_DOALL) override;
    uint16_t initial_state(uint16_t parametr = EP_DOALL) override;
    uint16_t block_ou( uint16_t parametr = EP_DOALL) override;
    uint16_t unblock_ou( uint16_t parametr = EP_DOALL) override;
    uint16_t do_frames(uint16_t type_recieve, uint16_t type_frame, uint16_t parametr = EP_DOALL) override;

    void save_to_specific_protocol(QString str_to_protocol, uint16_t num_mpi_command,
                                   uint16_t type_window, uint16_t type_protocol, uint16_t parametr) override;

private:
    uint16_t set_epsilon(float command, uint16_t parametr = EP_DOALL);
    uint16_t get_epsilon(uint16_t parametr = EP_DOALL);
    uint16_t set_focus(uint16_t parametr = EP_DOALL);
    uint16_t get_focus( uint16_t parametr = EP_DOALL);
    uint16_t set_texp(uint16_t command, uint16_t parametr = EP_DOALL);
    uint16_t get_texp( uint16_t parametr = EP_DOALL);

    void set_type_frame_functions();
    void set_type_frame_recieve();
    void create_count_of_exc_fail();
    void set_type_upn_func();
    void set_type_chpn_func();
    void do_pause(uint16_t interval);
    void check_orientation();
    void getDataToDTMIOrDTMILoc(uint16_t &count_dtmo_or_dtmo_loc);
    void send_status_info();
    void post_status_proc(uint16_t st1, uint16_t st2, QString &str_protocol);
    void send_data_to_command(const uint16_t &type_data, const uint16_t &type_command, const QString &data);
    void send_mpi_data_to_db();
    void preset_before_exchange();
    void save_to_protocol(QString str_to_protocol,  uint16_t parametr = EP_DOALL);
    template <typename T>
    void calc_frame_param(std::vector<T> frame_buffer);
    void count_of_fails(uint16_t parametr = EP_DOALL);
    uint16_t start_exchage(uint16_t parametr = EP_DOALL);
    uint16_t execute_protected_exchange(std::function<void()> func_mpi_command);
    void execute_exchange();
    std::function<void()> m_set_control_word;
    void set_data_to_device_protocol(QString &str_protocol);
    std::vector<shared_ptr<Kia_bi>> m_kia_bi;
    std::shared_ptr<Kia_mpi> m_kia_mpi;
    std::shared_ptr<Kia_settings> m_kia_settings;
    shared_ptr<Kia_ftdi> m_kia_ftdi;
    uint16_t m_count_dtmi_dtmi_loc;
    std::vector<uint8_t> m_commandR;

    std::vector<std::function<void(uint16_t parametr)>> m_func_type_frames;
    std::vector<std::function<void(uint16_t type_frame, uint16_t parametr)>> m_func_type_frame_recieve;
    std::vector<uint32_t> m_frame_resulution;

    std::map<uint16_t, std::function<uint16_t(QStringList value, uint16_t parametr)>> m_func_upn;
    std::map<uint16_t, std::function<uint16_t(uint16_t parametr)>> m_map_chpn;



};

#endif // BOKZM60_H
