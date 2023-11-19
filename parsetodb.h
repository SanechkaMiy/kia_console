#ifndef PARSETODB_H
#define PARSETODB_H
#include <QObject>
#include <QWidget>
#include <QtGlobal>
#include <QtCore>
#include "mainStruct.h"
#include "workwithstruct.h"
#include "Kia_modules/kia_db.h"
class ParseToDB : public QObject
{
    Q_OBJECT
public:
    ParseToDB(std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
              std::shared_ptr<Kia_data> kia_data,
              std::shared_ptr<Kia_settings> kia_settings);
    ~ParseToDB();
    void sendDataIntoMSHIOR(uint16_t& num_bokz, uint32_t& bshv, MSHIOR &st_mshior);
    void sendDataIntoSHTMI1(uint16_t& num_bokz, uint32_t& bshv, SHTMI1 &st_shtmi1);
    void sendDataIntoSHTMI2(uint16_t& num_bokz, uint32_t& bshv, SHTMI2 &st_shmti2);
    void sendDataIntoMPI(uint16_t& num_bokz, uint32_t &bshv);
    void sendDataIntoDTMILOC(uint16_t& num_bokz, uint32_t& bshv, DTMILoc_1 &dtmiLoc_1, DTMILoc_2 &dtmiLoc_2, DTMILoc_3 &dtmiLoc_3,
                             DTMILoc_4 &dtmiLoc_4, DTMILoc_5 &dtmiLoc_5, DTMILoc_6 &dtmiLoc_6,
                             DTMILoc_7 &dtmiLoc_7, DTMILoc_8 &dtmiLoc_8, DTMILoc_9 &dtmiLoc_9);
    void sendDataIntoDTMI(uint16_t& num_bokz, uint32_t &bshv, DTMI_1& dtmi_1, DTMI_2& dtmi_2, DTMI_3 &dtmi_3, DTMI_4 &dtmi_4,
                          DTMI_5 &dtmi_5, DTMI_6 &dtmi_6, DTMI_7 &dtmi_7, DTMI_8 &dtmi_8,
                          DTMI_9 &dtmi_9);

    void send_to_bkpik(uint16_t& num_bi);
    void send_to_bi(uint16_t& num_bi);
    string parse_td();
    string parse_kc_kp(uint16_t n);
    template<typename arr>
    void parse_data_bi(std::string& str, arr data);
    void send_to_frames(uint16_t& num_bokz, uint32_t &bshv);
private:
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_db;
    std::shared_ptr<Kia_data> m_kia_data;
    std::shared_ptr<Kia_settings> m_kia_settings;
};

#endif // PARSETODB_H
