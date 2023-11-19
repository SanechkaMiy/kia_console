#ifndef WORKWITHSTRUCT_H
#define WORKWITHSTRUCT_H
#include <QtCore>
#include <QFile>
#include "Kia_mko_struct.h"
#include <QString>
#include <iostream>
#include "mainStruct.h"
#include <stdio.h>
#include <cstdlib>
#include <array>
#include <math.h>
#include "simpletimer.h"
#include "mainStruct.h"
#define _USE_MATH_DEFINES

class WorkWithStruct: public QObject
{
    Q_OBJECT
public:
    WorkWithStruct(std::shared_ptr<Kia_settings> kia_settings);
    void workWithDTMILoc(array<uint16_t, constants::packetSize> dataWord, uint16_t count, DTMILoc& dtmi_loc, DTMILoc_1 &dtmi_loc_1,
                         DTMILoc_2 &dtmi_2, DTMILoc_3 &dtmi_loc_3, DTMILoc_4 &dtmi_loc_4,
                         DTMILoc_5 &dtmi_loc_5, DTMILoc_6 &dtmi_loc_6, DTMILoc_7 &dtmi_loc_7, DTMILoc_8 &dtmi_loc_8, DTMILoc_9 &dtmi_9);
    void workWithDTMI(array<uint16_t, constants::packetSize> dataWord, uint16_t count, DTMI& dtmi, DTMI_1 &dtmi_1,
                      DTMI_2 &dtmi_2, DTMI_3 &dtmi_3,DTMI_4 &dtmi_4,DTMI_5 &dtmi_5,
                      DTMI_6 &dtmi_6, DTMI_7 &dtmi_7,DTMI_8 &dtmi_8, DTMI_9 &dtmi_9);
    void workWithSHTMI1(array<uint16_t, constants::packetSize> dataWord, SHTMI1 &shtmi1);
    void workWithSHTMI2(array<uint16_t, constants::packetSize> dataWord, SHTMI2 &shtmi2, int countSize);
    void workWithMSHIOR(array<uint16_t, constants::packetSize> dataWord, MSHIOR &mshior);
    void workWithTransferDTMILoc(DTMILocRaw_2_3_4_5_6_7_8 &dtmi_loc_raw_2_3_4_5_6_7_8);
    void workWithTransferDTMIRaw_2_3_4(DTMIRaw_2_3_4 &dtmiRaw_2_3_4);
    void workWithTransferDTMIRaw_6_7(DTMIRaw_6_7 &dtmiRaw_6_7);
    float uint32_to_float(uint32_t value);
    std::string currentDateTime();
    uint32_t current_hours();
    float decodeDateTime();
    template < typename T >
    T swapHex(T value);
    QString format(const QString& str, const int16_t &shift, const char &fillchar = ' ');
signals:
    void send_to_client(quint16, QStringList);
private:
    std::shared_ptr<Kia_settings> m_kia_settings;
};

#endif // WORKWITHSTRUCT_H
