#ifndef PARSETODB_H
#define PARSETODB_H
#include <QObject>
#include <QWidget>
#include <QtGlobal>
#include <QtCore>
#include <string.h>
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
    void sendDataIntoDTMILOC_M60(uint16_t& num_bokz, int32_t &bshv, DTMILoc &dtmiLoc);
    void sendDataIntoDTMI_M60(uint16_t& num_bokz, int32_t &bshv, DTMI& dtmi);


    void sendDataIntoMSHIOR_MF(uint16_t& num_bokz, int32_t& bshv, MSHIOR_MF &st_mshior);
    void sendDataIntoSHTMI1_MF(uint16_t& num_bokz, int32_t& bshv, SHTMI1_MF &st_shtmi1);
    void sendDataIntoSHTMI2_MF(uint16_t& num_bokz, int32_t &bshv, SHTMI2_MF &st_shtmi2);
    void sendDataIntoMLOC_MF(uint16_t& num_bokz, int32_t &bshv, MLoc_MF &mloc_mf);
    void sendDataIntoDTMI_MF(uint16_t& num_bokz, int32_t &bshv, DTMI_MF& dtmi);

    template<typename T>
    std::string convert_array_to_json_string(T data);

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
