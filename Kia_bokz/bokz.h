#ifndef BOKZ_H
#define BOKZ_H
#include <QObject>
#include <iostream>
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include "Kia_pio/pio_bokz.h"
#include "Kia_modules/kia_help_functions.h"
#include "math.h"
class Bokz : public QObject
{
    Q_OBJECT
public:
    Bokz();
    virtual void set_bokz_settings() = 0;

    virtual uint16_t debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address, uint16_t word_data,
                                       string struct_id, string struct_id_desc, uint16_t parametr = EP_DOALL) = 0;

    virtual uint16_t shtmi1(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t shtmi2(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t mshior(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t dtmi_or_dtmi_loc(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t smti(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t vmti(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t synchro(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t skor(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_no(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_to(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_full_exp(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_loc(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_otclp(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_openkr(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_zkr(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t kvaor(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t os(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t vskou(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t initial_state(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t block_ou(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t unblock_ou(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t do_frames( uint16_t parametr = EP_DOALL) = 0;

    virtual uint16_t set_epsilon(float command, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t get_epsilon(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t set_focus(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t get_focus(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t set_texp(uint16_t command, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t get_texp(uint16_t parametr = EP_DOALL) = 0;

    virtual void preset_before_exchange() = 0;

    std::tuple<double, double, double> math_alpha_delta_azimut(double Qo0, double Qo1, double Qo2, double Qo3);
    double atan2m(double y, double x);
    double asinm(double x);

    std::shared_ptr<Kia_data> m_kia_data;
    std::shared_ptr<Kia_mko_struct> m_kia_mko_struct;
    std::shared_ptr<Pio_bokz> m_pio_bokz;
    uint16_t m_is_used_bokz = CS_IS_OFF;
    uint16_t m_num_bokz;
    virtual ~Bokz(){    cout<<"destructor bokz"<<endl;};
protected:
signals:
    virtual void send_to_client(quint16, QStringList) = 0 ;
};

#endif // BOKZ_H
