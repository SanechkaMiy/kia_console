#ifndef BOKZ_H
#define BOKZ_H
#include <QObject>
#include <iostream>
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include "Kia_pio/pio_bokz.h"
#include "Kia_modules/kia_help_functions.h"
#include "Kia_modules/kia_mpi.h"
class Bokz : public QObject
{
    Q_OBJECT
public:
    Bokz();
    enum TYPE_FRAME
    {
        FULL_FRAME = 0,
        BIN_FRAME = 1
    };
    enum TYPE_FRAME_RECIEVE
    {
        MKO = 0,
        FTDI_USB = 1,
        MATROX_CAM_LINK = 2
    };

    virtual void set_bokz_settings() = 0;

    virtual uint16_t debugging_command(uint16_t direction, uint16_t format, uint16_t sub_address, uint16_t word_data,
                                       string struct_id, string struct_id_desc, uint16_t parametr = EP_DOALL) = 0;

    virtual uint16_t shtmi1(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t shtmi2(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t mshior(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t dtmi_or_dtmi_loc(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t mloc(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t upn(uint16_t type_upn, QStringList value, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t chpn(QStringList type_chpn, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t chkd(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t smti(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t vmti(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t synchro(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t skor(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_no(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_to(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_full_exp(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_bin_exp(uint16_t parametr = EP_DOALL) = 0;
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
    virtual uint16_t do_frames(uint16_t type_recieve, uint16_t type_frame, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_bshv(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_restart(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t command_oo(uint16_t parametr = EP_DOALL) = 0;

    virtual void save_to_specific_protocol(QString str_to_protocol, uint16_t num_mpi_command,
                                           uint16_t type_window, uint16_t type_protocol, uint16_t parametr) = 0;

    void continue_exchange();
    void wait_for_event();

    std::tuple<double, double, double> math_alpha_delta_azimut(double Qo0, double Qo1, double Qo2, double Qo3);
    double atan2m(double y, double x);
    double asinm(double x);


    Kia_protocol_parametrs parse_mko_protocols(std::shared_ptr<Kia_data> kia_data,
                                               int32_t bshv, uint16_t num_bokz);

    QString set_data_from_mko_struct(QStringList list_name, std::vector<std::tuple<QString, double, double, double>> list_data);
    std::shared_ptr<Kia_data> m_kia_data;
    std::shared_ptr<Kia_mko_struct> m_kia_mko_struct;
    std::shared_ptr<Pio_bokz> m_pio_bokz;
    uint16_t m_is_used_bokz = CS_IS_OFF;
    uint16_t m_num_bokz;

    std::condition_variable m_cv;
    uint32_t m_count_exchange = 0;
    virtual ~Bokz(){    cout<<"destructor bokz"<<endl;};
signals:
    void send_to_client(quint16, QStringList);

    void send_to_save_protocol(Kia_protocol_parametrs);
    void save_to_frames_protocols(const Kia_frame_parametrs&);

    void send_data_to_db_bokz(qint16, quint16, qint32, Kia_mko_struct);
    void send_data_to_db_for_frames(quint16, qint32);
    void send_data_to_db_for_mpi(quint16, qint32);

    void do_exchange(Kia_data*);

private:
    std::mutex m_mtx;
};

#endif // BOKZ_H
