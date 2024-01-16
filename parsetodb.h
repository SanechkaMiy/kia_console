#ifndef PARSETODB_H
#define PARSETODB_H
#include <QObject>
#include <QWidget>
#include <QtGlobal>
#include <QtCore>
#include "mainStruct.h"
#include "Kia_modules/kia_db.h"
#include "Kia_pio/pio_bokz.h"
class ParseToDB : public QObject
{
    Q_OBJECT
public:
    ParseToDB(std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db,
              std::shared_ptr<Kia_data> kia_data,
              std::shared_ptr<Kia_settings> kia_settings);
    ~ParseToDB();
    void sendDataIntoMPI(uint16_t& num_bokz, int32_t &bshv);

    void sendDataIntoMSHIOR_M60(uint16_t& num_bokz, int32_t& bshv, MSHIOR &st_mshior);
    void sendDataIntoSHTMI1_M60(uint16_t& num_bokz, int32_t& bshv, SHTMI1 &st_shtmi1);
    void sendDataIntoSHTMI2_M60(uint16_t& num_bokz, int32_t &bshv, SHTMI2 &st_shmti2);
    void sendDataIntoDTMILOC_M60(uint16_t& num_bokz, int32_t &bshv, DTMILoc_1 &dtmiLoc_1, DTMILoc_2 &dtmiLoc_2, DTMILoc_3 &dtmiLoc_3,
                                 DTMILoc_4 &dtmiLoc_4, DTMILoc_5 &dtmiLoc_5, DTMILoc_6 &dtmiLoc_6,
                                 DTMILoc_7 &dtmiLoc_7, DTMILoc_8 &dtmiLoc_8, DTMILoc_9 &dtmiLoc_9);
    void sendDataIntoDTMI_M60(uint16_t& num_bokz, int32_t &bshv, DTMI_1& dtmi_1, DTMI_2& dtmi_2, DTMI_3 &dtmi_3, DTMI_4 &dtmi_4,
                              DTMI_5 &dtmi_5, DTMI_6 &dtmi_6, DTMI_7 &dtmi_7, DTMI_8 &dtmi_8,
                              DTMI_9 &dtmi_9);


    void sendDataIntoMSHIOR_MF(uint16_t& num_bokz, int32_t& bshv, MSHIOR_MF &st_mshior);
    void sendDataIntoSHTMI1_MF(uint16_t& num_bokz, int32_t& bshv, SHTMI1_MF &st_shtmi1);
    void sendDataIntoSHTMI2_MF(uint16_t& num_bokz, int32_t &bshv, SHTMI2_MF &st_shtmi2);
    void sendDataIntoMLOC_MF(uint16_t& num_bokz, int32_t &bshv, MLoc_1_MF &dtmiLoc_1, MLoc_2_MF &dtmiLoc_2, MLoc_3_MF &dtmiLoc_3,
                                 MLoc_4_MF &dtmiLoc_4, MLoc_5_MF &dtmiLoc_5, MLoc_6_MF &dtmiLoc_6,
                                 MLoc_7_MF &dtmiLoc_7, MLoc_8_MF &dtmiLoc_8, MLoc_9_MF &dtmiLoc_9);
    void sendDataIntoDTMI_MF(uint16_t& num_bokz, int32_t &bshv, DTMI_1_MF& dtmi_1, DTMI_2_MF& dtmi_2, DTMI_3_MF &dtmi_3, DTMI_4_MF &dtmi_4,
                              DTMI_5_MF &dtmi_5, DTMI_6_MF &dtmi_6, DTMI_7_MF &dtmi_7, DTMI_8_MF &dtmi_8,
                              DTMI_9_MF &dtmi_9, DTMI_10_MF &dtmi_10, DTMI_11_MF &dtmi_11, DTMI_12_MF &dtmi_12);

    void send_to_bkpik(uint16_t& num_bi);
    void send_to_bi(uint16_t& num_bi);
    string parse_td();
    string parse_kc_kp(uint16_t n);
    template<typename arr>
    void parse_data_bi(std::string& str, arr data);
    void send_to_frames(uint16_t& num_bokz, int32_t &bshv);
private:
    std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> m_kia_db;
    std::shared_ptr<Kia_data> m_kia_data;
    std::shared_ptr<Kia_settings> m_kia_settings;
};

#endif // PARSETODB_H
