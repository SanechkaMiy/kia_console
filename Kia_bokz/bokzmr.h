#ifndef BOKZMR_H
#define BOKZMR_H
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
#include "kia_bkpik.h"
#include "kia_synch_timer.h"
#include "kia_biu.h"
#include "simpletimer.h"
#include "kia_ftdi.h"
#include "kia_bi.h"
#include "Kia_mko_struct.h"
#include "Kia_modules/kia_mpi.h"
#include "Kia_modules/kia_db.h"

class BokzMR : public Bokz
{
    Q_OBJECT
public:
    BokzMR(uint16_t num_bokz,
           std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
           std::vector<shared_ptr <Timer>> timer, std::vector<std::shared_ptr<Kia_synch_timer> > kia_synch_timer,
           std::vector<shared_ptr<Kia_bi>> kia_bi, shared_ptr <Kia_mpi> kia_mpi,
           shared_ptr<Kia_protocol> kia_protocol, shared_ptr<Kia_matrox> kia_matrox,
           std::shared_ptr<Kia_settings> kia_settings, shared_ptr<Kia_ftdi> kia_ftdi);
    ~BokzMR();
    void set_bokz_settings() override;

    uint16_t debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address, uint16_t word_data,
                               string struct_id, string struct_id_desc, uint16_t parametr = EP_DOALL) override;

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
signals:
    void send_to_client(quint16, QStringList) override;
private:
    void preset_before_exchange();

};

#endif // BOKZMR_H
