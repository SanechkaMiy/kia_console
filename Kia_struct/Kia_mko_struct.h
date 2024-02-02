#ifndef KIA_MKO_STRUCT_H
#define KIA_MKO_STRUCT_H
#include <iostream>
#include <QMetaType>
#include <QStringList>
using namespace std;
#pragma pack(push, 1)
struct SHTMI1
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    float Foc = 0;
    uint32_t Xo = 0;
    uint32_t Yo = 0;
    uint16_t Texp = 0;
    uint16_t Mt = 0;
    uint16_t St = 0;
    uint16_t Ndef = 0;
    uint16_t rezerv1 = 0;
    uint16_t rezerv2 = 0;
    uint16_t rezerv3 = 0;
    uint16_t rezerv4 = 0;
    uint16_t rezerv5 = 0;
    uint16_t rezerv6 = 0;
    uint16_t rezerv7 = 0;
    uint16_t rezerv8 = 0;
    uint16_t rezerv9 = 0;
    uint16_t rezerv10 = 0;
    uint16_t rezerv11 = 0;
    uint16_t XCF = 0;
    uint16_t Years = 0;
    uint16_t Month= 0;
    uint16_t Days = 0;
    uint16_t Ver1 = 0;
    uint16_t Ver2 = 0;
    uint16_t Ver3 = 0;

    QStringList shtmi1_list_name;
    std::vector<std::tuple<QString, double, double, double>> shtmi1_list_data;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHTMI1raw
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    uint32_t Foc = 0;
    uint32_t Xo = 0;
    uint32_t Yo = 0;
    uint16_t Texp = 0;
    uint16_t Mt = 0;
    uint16_t St = 0;
    uint16_t Ndef = 0;
    uint16_t rezerv1 = 0;
    uint16_t rezerv2 = 0;
    uint16_t rezerv3 = 0;
    uint16_t rezerv4 = 0;
    uint16_t rezerv5 = 0;
    uint16_t rezerv6 = 0;
    uint16_t rezerv7 = 0;
    uint16_t rezerv8 = 0;
    uint16_t rezerv9 = 0;
    uint16_t rezerv10 = 0;
    uint16_t rezerv11 = 0;
    uint16_t XCF = 0;
    uint16_t Date = 0;
    uint16_t Ver = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHTMI1_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    float Foc = 0;
    float Xo = 0;
    float Yo = 0;
    uint16_t Texp = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    uint16_t rezerv1 = 0;
    uint16_t rezerv2 = 0;
    uint16_t cntUPN = 0;
    int16_t Tcmv = 0;
    uint16_t ConfCS = 0;
    uint16_t desc = 0;
    uint16_t ogConstCrc = 0;
    uint16_t CatCS0 = 0;
    uint16_t CatCS1 = 0;
    uint16_t ConstCS0 = 0;
    uint16_t ConstCS1 = 0;
    uint16_t ProgCS0 = 0;
    uint16_t ProgCS1 = 0;
    uint16_t Ver1 = 0;
    uint16_t Ver2 = 0;
    uint16_t Ver3 = 0;
    uint16_t cs = 0;

    QStringList shtmi1_list_name;
    std::vector<std::tuple<QString, double, double, double>> shtmi1_list_data;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHTMI1raw_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    uint32_t Foc = 0;
    uint32_t Xo = 0;
    uint32_t Yo = 0;
    uint16_t Texp = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    uint16_t rezerv1 = 0;
    uint16_t rezerv2 = 0;
    uint16_t cntUPN = 0;
    uint16_t Tcmv = 0;
    uint16_t ConfCS = 0;
    uint16_t desc = 0;
    uint16_t ogConstCrc = 0;
    uint16_t CatCS0 = 0;
    uint16_t CatCS1 = 0;
    uint16_t ConstCS0 = 0;
    uint16_t ConstCS1 = 0;
    uint16_t ProgCS0 = 0;
    uint16_t ProgCS1 = 0;
    uint16_t Ver = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHTMI2
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    uint16_t Texp = 0;
    uint16_t Nusd = 0;
    uint16_t Nno = 0;
    uint16_t Nnosl = 0;
    uint16_t Nto = 0;
    uint16_t Ntosl = 0;
    uint32_t Nsl = 0;
    std::array<uint16_t, 16> eCount;

    QStringList shtmi2_list_name;
    std::vector<std::tuple<QString, double, double, double>> shtmi2_list_data;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHTMI2raw
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    uint16_t Texp = 0;
    uint16_t Nusd = 0;
    uint16_t Nno = 0;
    uint16_t Nnosl = 0;
    uint16_t Nto = 0;
    uint16_t Ntosl = 0;
    uint32_t Nsl = 0;
    uint16_t eCount[16] = {0};
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHTMI2raw_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    uint16_t Texp = 0;
    uint16_t Nusd = 0;
    uint16_t Nno = 0;
    uint16_t Nnosl = 0;
    uint16_t Nto = 0;
    uint16_t Ntosl = 0;
    uint32_t Nsl = 0;
    uint16_t eCount1 = 0;
    uint16_t eCount2 = 0;
    uint16_t eCount3 = 0;
    uint16_t eCount4 = 0;
    uint16_t eCount5 = 0;
    uint16_t eCount6 = 0;
    uint16_t eCount7 = 0;
    uint16_t eCount8 = 0;
    uint16_t eCount9 = 0;
    uint16_t eCount10 = 0;
    uint8_t eCount11 = 0;
    uint8_t eCount12 = 0;
    uint8_t eCount13 = 0;
    uint8_t eCount14 = 0;
    uint8_t eCount15 = 0;
    uint8_t eCount16 = 0;
    uint16_t eCount17 = 0;
    uint8_t eCount18 = 0;
    uint8_t eCount19 = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct SHTMI2_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    uint16_t Texp = 0;
    uint16_t Nusd = 0;
    uint16_t Nno = 0;
    uint16_t Nnosl = 0;
    uint16_t Nto = 0;
    uint16_t Ntosl = 0;
    uint32_t Nsl = 0;
    uint16_t eCount1 = 0;
    uint16_t eCount2 = 0;
    uint16_t eCount3 = 0;
    uint16_t eCount4 = 0;
    uint16_t eCount5 = 0;
    uint16_t eCount6 = 0;
    uint16_t eCount7 = 0;
    uint16_t eCount8 = 0;
    uint16_t eCount9 = 0;
    uint16_t eCount10 = 0;
    uint8_t eCount11 = 0;
    uint8_t eCount12 = 0;
    uint8_t eCount13 = 0;
    uint8_t eCount14 = 0;
    uint8_t eCount15 = 0;
    uint8_t eCount16 = 0;
    uint16_t eCount17 = 0;
    uint8_t eCount18 = 0;
    uint8_t eCount19 = 0;
    uint16_t cs = 0;
    QStringList shtmi2_list_name;
    std::vector<std::tuple<QString, double, double, double>> shtmi2_list_data;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MSHIOR
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint32_t T = 0;
    double OZx = 0;
    double OZy = 0;
    double OZz = 0;
    float Qo0 = 0;
    float Qo1 = 0;
    float Qo2 = 0;
    float Qo3 = 0;
    double wox = 0;
    double woy = 0;
    double woz = 0;
    uint16_t rezerv25 = 0;
    uint16_t rezerv26 = 0;
    uint16_t rezerv27 = 0;
    uint16_t rezerv28 = 0;
    uint16_t rezerv29 = 0;
    uint16_t rezerv30 = 0;
    uint16_t rezerv31 = 0;
    uint16_t rezerv32 = 0;

    QStringList mshior_list_name;
    std::vector<std::tuple<QString, double, double, double>> mshior_list_data;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MSHIORRaw
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint32_t T = 0;
    int32_t OZx = 0;
    int32_t OZy = 0;
    int32_t OZz = 0;
    uint32_t Qo0 = 0;
    uint32_t Qo1 = 0;
    uint32_t Qo2 = 0;
    uint32_t Qo3 = 0;
    int32_t wox = 0;
    int32_t woy = 0;
    int32_t woz = 0;
    uint16_t rezerv25;
    uint16_t rezerv26;
    uint16_t rezerv27;
    uint16_t rezerv28;
    uint16_t rezerv29;
    uint16_t rezerv30;
    uint16_t rezerv31;
    uint16_t rezerv32;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MSHIORRaw_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint32_t Qo0 = 0;
    uint32_t Qo1 = 0;
    uint32_t Qo2 = 0;
    uint32_t Qo3 = 0;
    int32_t wox = 0;
    int32_t woy = 0;
    int32_t woz = 0;
    uint16_t Tcmv = 0;
    uint8_t NumFrag = 0;
    uint8_t NumLoc_0 = 0;
    uint8_t NumDet = 0;
    uint8_t LightMv5 = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    uint16_t ThMax;
    uint16_t m_cur;
    uint16_t P;
    uint16_t dpf_state;
    uint8_t dpf_total;
    uint8_t dpf_hotpixels;
    uint8_t dpf_updated;
    uint8_t dpf_rejected;
    uint8_t dpf_threshold;
    uint8_t dpf_applied;
    uint16_t ser_num;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MSHIOR_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    float Qo0 = 0;
    float Qo1 = 0;
    float Qo2 = 0;
    float Qo3 = 0;
    float wox = 0;
    float woy = 0;
    float woz = 0;
    uint16_t Tcmv = 0;
    uint8_t NumFrag = 0;
    uint8_t NumLoc_0 = 0;
    uint8_t NumDet = 0;
    uint8_t LightMv5 = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    uint16_t ThMax;
    uint16_t m_cur;
    uint16_t P;
    uint16_t dpf_state;
    uint8_t dpf_total;
    uint8_t dpf_hotpixels;
    uint8_t dpf_updated;
    uint8_t dpf_rejected;
    uint8_t dpf_threshold;
    uint8_t dpf_applied;
    uint16_t ser_num;

    QStringList mshior_list_name;
    std::vector<std::tuple<QString, double, double, double>> mshior_list_data;
};
#pragma pack(pop)


const uint16_t size_dtmi1 = 9;
#pragma pack(push, 1)
struct DTMI_1
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t Texp = 0;
    uint16_t NumLoc = 0;
    uint16_t NumObj = 0;
    uint16_t NumFrag = 0;
    uint16_t Epsilon = 0;
    float deltaT = 0;
    std::array<float, size_dtmi1> loc;
};
#pragma pack(pop)
const uint16_t size_dtmi2 = 15;
#pragma pack(push, 1)
struct DTMI_2
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, size_dtmi2> loc;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_3
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, size_dtmi2> loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_4
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, size_dtmi2> loc;
};
#pragma pack(pop)
const uint16_t size_dtmi5 = 10;
#pragma pack(push, 1)
struct DTMI_5
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, size_dtmi5> loc;
    float Wo_x = 0;
    float Wo_y = 0;
    float Wo_z = 0;
    float XYc_0_0 = 0;
    float XYc_0_1 = 0;

};
#pragma pack(pop)
const uint16_t size_dtmi6_xyc = 15;
#pragma pack(push, 1)
struct DTMI_6
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, size_dtmi6_xyc> XYc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_7
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, size_dtmi6_xyc> XYc;
};
#pragma pack(pop)

const uint16_t size_dtmi8_thfrag = 16;
const uint16_t size_dtmi8_objfrag = 14;
#pragma pack(push, 1)
struct DTMI_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<uint16_t, size_dtmi8_thfrag> ThFrag;
    std::array<uint16_t, size_dtmi8_objfrag> ObjFrag;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_9
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint16_t ObjFrag_14 = 0;
    uint16_t ObjFrag_15 = 0;
    uint32_t TOlg = 0;
    float QOlg_0 = 0;
    float QOlg_1 = 0;
    float QOlg_2 = 0;
    float QOlg_3 = 0;
    float Epoch = 0;
    uint16_t NumL_0 = 0;
    uint16_t NumL_1 = 0;
    uint16_t maxH = 0;
    uint16_t dxmaxH = 0;
    uint16_t dymaxH = 0;
    uint16_t rezerv_22_32[11];

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI
{
    DTMI_1 dtmi_1;
    DTMI_2 dtmi_2;
    DTMI_3 dtmi_3;
    DTMI_4 dtmi_4;
    DTMI_5 dtmi_5;
    DTMI_6 dtmi_6;
    DTMI_7 dtmi_7;
    DTMI_8 dtmi_8;
    DTMI_9 dtmi_9;
    QStringList dtmi_list_name;
    std::vector<std::tuple<QString, double, double, double>> dtmi_list_data;
    std::vector<std::pair<uint16_t, uint16_t>> dtmi_cc1;
    std::vector<std::pair<uint16_t, uint16_t>> dtmi_cc2;
    std::vector<std::tuple<float, float, float>> loc_x;
    std::vector<std::tuple<float, float, float>> loc_y;
    std::vector<std::tuple<float, float, float>> loc_b;
    std::vector<std::tuple<float, float, float>> loc_c;
    std::vector<std::tuple<uint16_t, float, float>> XY_x;
    std::vector<std::tuple<uint16_t, float, float>> XY_y;
    std::vector<std::tuple<uint16_t, float, float>> ObjFrag;
    std::vector<std::tuple<uint16_t, float, float>> ThFrag;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct DTMIRaw_1
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t Texp = 0;
    uint16_t NumLoc = 0;
    uint16_t NumObj = 0;
    uint16_t NumFrag = 0;
    uint16_t Epsilon = 0;
    uint32_t deltaT = 0;
    std::array<uint32_t, size_dtmi1> loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_2_3_4
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<uint32_t, size_dtmi2> loc;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_5
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<uint32_t, size_dtmi5> loc;
    uint32_t Wo_x = 0;
    uint32_t Wo_y = 0;
    uint32_t Wo_z = 0;
    uint32_t XYc_0_0 = 0;
    uint32_t XYc_0_1 = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_6_7
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<uint32_t, size_dtmi6_xyc> XYc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<uint16_t, size_dtmi8_thfrag> ThFrag;
    std::array<uint16_t, size_dtmi8_objfrag> ObjFrag;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_9
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint16_t ObjFrag_14 = 0;
    uint16_t ObjFrag_15 = 0;
    uint32_t TOlg = 0;
    uint32_t QOlg_0 = 0;
    uint32_t QOlg_1 = 0;
    uint32_t QOlg_2 = 0;
    uint32_t QOlg_3 = 0;
    uint32_t Epoch = 0;
    uint16_t NumL_0 = 0;
    uint16_t NumL_1 = 0;
    uint16_t maxH = 0;
    uint16_t dxmaxH = 0;
    uint16_t dymaxH = 0;
    uint16_t rezerv_22_32[11];

};
#pragma pack(pop)
const uint16_t size_qlst_dtmi = 4;
#pragma pack(push, 1)
struct DTMIRaw_1_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    int16_t Tcmv = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    uint16_t Texp = 0;
    uint16_t PixCount_NumLoc = 0;
    uint8_t NumStore = 0;
    uint8_t NumDet = 0;
    uint8_t NumProgFrag = 0;
    uint8_t NumFrag = 0;
    uint32_t Tlast = 0;
    uint16_t Tmslast = 0;
    std::array<uint32_t, size_qlst_dtmi> Qlst;
    uint16_t rezerv = 0;
    uint8_t HistDef_0 = 0;
    uint8_t HistDef_1 = 0;
    uint8_t HistDef_2 = 0;
    uint8_t HistDef_3 = 0;
    uint8_t HistDef_4 = 0;
    uint8_t HistDef_5 = 0;
    uint8_t HistDef_6 = 0;
    uint8_t HistDef_7 = 0;
    uint16_t cs = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_2_3_4_5_6_7_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t RsLoc_0_x = 0;
    uint32_t RsLoc_0_y = 0;
    uint32_t RsLoc_0_b = 0;
    uint32_t RsLoc_1_x = 0;
    uint32_t RsLoc_1_y = 0;
    uint32_t RsLoc_1_b = 0;
    uint32_t RsLoc_2_x = 0;
    uint32_t RsLoc_2_y = 0;
    uint32_t RsLoc_2_b = 0;
    uint32_t RsLoc_3_x = 0;
    uint32_t RsLoc_3_y = 0;
    uint32_t RsLoc_3_b = 0;
    uint32_t RsLoc_4_x = 0;
    uint32_t RsLoc_4_y = 0;
    uint32_t RsLoc_4_b = 0;
    uint16_t cs = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_8_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t RsLoc_T0_0_S = 0;
    uint16_t RsLoc_T0_1_S = 0;
    uint16_t RsLoc_T0_2_S = 0;
    uint16_t RsLoc_T0_3_S = 0;
    uint16_t RsLoc_T0_4_S = 0;
    uint16_t RsLoc_T0_5_S = 0;
    uint16_t RsLoc_T0_6_S = 0;
    uint16_t RsLoc_T0_7_S = 0;
    uint16_t RsLoc_T0_8_S = 0;
    uint16_t RsLoc_T0_9_S = 0;
    uint16_t RsLoc_T0_10_S = 0;
    uint16_t RsLoc_T0_11_S = 0;
    uint16_t RsLoc_T0_12_S = 0;
    uint16_t RsLoc_T0_13_S = 0;
    uint16_t RsLoc_T0_14_S = 0;
    uint16_t RsLoc_T1_0_S = 0;
    uint16_t RsLoc_T1_1_S = 0;
    uint16_t RsLoc_T1_2_S = 0;
    uint16_t RsLoc_T1_3_S = 0;
    uint16_t RsLoc_T1_4_S = 0;
    uint16_t RsLoc_T1_5_S = 0;
    uint16_t RsLoc_T1_6_S = 0;
    uint16_t RsLoc_T1_7_S = 0;
    uint16_t RsLoc_T1_8_S = 0;
    uint16_t RsLoc_T1_9_S = 0;
    uint16_t RsLoc_T1_10_S = 0;
    uint16_t RsLoc_T1_11_S = 0;
    uint16_t RsLoc_T1_12_S = 0;
    uint16_t RsLoc_T1_13_S = 0;
    uint16_t RsLoc_T1_14_S = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_9_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t XYc_0_0 = 0;
    uint16_t XYc_0_1 = 0;
    uint16_t XYc_1_0 = 0;
    uint16_t XYc_1_1 = 0;
    uint16_t XYc_2_0 = 0;
    uint16_t XYc_2_1 = 0;
    uint16_t XYc_3_0 = 0;
    uint16_t XYc_3_1 = 0;
    uint16_t XYc_4_0 = 0;
    uint16_t XYc_4_1 = 0;
    uint16_t XYc_5_0 = 0;
    uint16_t XYc_5_1 = 0;
    uint16_t XYc_6_0 = 0;
    uint16_t XYc_6_1 = 0;
    uint16_t XYc_7_0 = 0;
    uint16_t XYc_7_1 = 0;
    uint16_t XYc_8_0 = 0;
    uint16_t XYc_8_1 = 0;
    uint16_t XYc_9_0 = 0;
    uint16_t XYc_9_1 = 0;
    uint16_t XYc_10_0 = 0;
    uint16_t XYc_10_1 = 0;
    uint16_t XYc_11_0 = 0;
    uint16_t XYc_11_1 = 0;
    uint16_t XYc_12_0 = 0;
    uint16_t XYc_12_1 = 0;
    uint16_t XYc_13_0 = 0;
    uint16_t XYc_13_1 = 0;
    uint16_t XYc_14_0 = 0;
    uint16_t XYc_14_1 = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_10_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t Mean_0_0 = 0;
    uint16_t Mean_0_1 = 0;
    uint16_t Mean_1_0 = 0;
    uint16_t Mean_1_1 = 0;
    uint16_t Mean_2_0 = 0;
    uint16_t Mean_2_1 = 0;
    uint16_t Mean_3_0 = 0;
    uint16_t Mean_3_1 = 0;
    uint16_t Mean_4_0 = 0;
    uint16_t Mean_4_1 = 0;
    uint16_t Mean_5_0 = 0;
    uint16_t Mean_5_1 = 0;
    uint16_t Mean_6_0 = 0;
    uint16_t Mean_6_1 = 0;
    uint16_t Mean_7_0 = 0;
    uint16_t Mean_7_1 = 0;
    uint16_t Mean_8_0 = 0;
    uint16_t Mean_8_1 = 0;
    uint16_t Mean_9_0 = 0;
    uint16_t Mean_9_1 = 0;
    uint16_t Mean_10_0 = 0;
    uint16_t Mean_10_1 = 0;
    uint16_t Mean_11_0 = 0;
    uint16_t Mean_11_1 = 0;
    uint16_t Mean_12_0 = 0;
    uint16_t Mean_12_1 = 0;
    uint16_t Mean_13_0 = 0;
    uint16_t Mean_13_1 = 0;
    uint16_t Mean_14_0 = 0;
    uint16_t Mean_14_1 = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_11_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t ThFrag_0 = 0;
    uint16_t ThFrag_1 = 0;
    uint16_t ThFrag_2 = 0;
    uint16_t ThFrag_3 = 0;
    uint16_t ThFrag_4 = 0;
    uint16_t ThFrag_5 = 0;
    uint16_t ThFrag_6 = 0;
    uint16_t ThFrag_7 = 0;
    uint16_t ThFrag_8 = 0;
    uint16_t ThFrag_9 = 0;
    uint16_t ThFrag_10 = 0;
    uint16_t ThFrag_11 = 0;
    uint16_t ThFrag_12 = 0;
    uint16_t ThFrag_13 = 0;
    uint16_t ThFrag_14 = 0;
    uint16_t ObjFrag_0_1_2_3 = 0;
    uint16_t ObjFrag_4_5_6_7 = 0;
    uint16_t ObjFrag_8_9_10_11 = 0;
    uint16_t ObjFrag_12_13_14_15 = 0;
    uint16_t MultXY_0_1_2_3 = 0;
    uint16_t MultXY_4_5_6_7 = 0;
    uint16_t MultXY_8_9_10_11 = 0;
    uint16_t MultXY_12_13_14_Xh = 0;
    uint16_t ZipXY_0_0_0_1_1_0_1_1 = 0;
    uint16_t ZipXY_2_0_2_1_3_0_3_1 = 0;
    uint16_t ZipXY_4_0_4_1_5_0_5_1 = 0;
    uint16_t ZipXY_6_0_6_0_7_0_7_1 = 0;
    uint16_t ZipXY_8_0_8_0_9_0_9_1 = 0;
    uint16_t ZipXY_10_0_10_0_11_0_11_1 = 0;
    uint16_t ZipXY_12_0_12_0_13_0_13_1 = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_12_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t Vx = 0;
    uint16_t Vy = 0;
    uint16_t Vz = 0;
    uint16_t Wx = 0;
    uint16_t Wy = 0;
    uint16_t Wz = 0;
    uint16_t rezerv_8 = 0;
    uint16_t rezerv_9 = 0;
    uint16_t rezerv_10 = 0;
    uint16_t rezerv_11 = 0;
    uint16_t rezerv_12 = 0;
    uint16_t rezerv_13 = 0;
    uint16_t rezerv_14 = 0;
    uint16_t rezerv_15 = 0;
    uint32_t Epoch = 0;
    uint8_t NumL_0 = 0;
    uint8_t NumL_1 = 0;
    uint16_t maxH = 0;
    uint8_t dxmaxH = 0;
    uint8_t dymaxH = 0;
    uint8_t NumSec = 0;
    uint8_t Epsilon = 0;
    uint16_t deltaT = 0;
    uint16_t m_cur = 0;
    uint8_t HistPix_0 = 0;
    uint8_t HistPix_1 = 0;
    uint8_t HistPix_2 = 0;
    uint8_t HistPix_3 = 0;
    uint8_t HistPix_4 = 0;
    uint8_t HistPix_5 = 0;
    uint8_t HistPix_6 = 0;
    uint8_t HistPix_7 = 0;
    uint8_t HistPix_8 = 0;
    uint8_t HistPix_9 = 0;
    uint8_t HistPix_10 = 0;
    uint8_t HistPix_11 = 0;
    uint8_t HistPix_12 = 0;
    uint8_t HistPix_13 = 1;
    uint8_t HistPix_14 = 1;
    uint8_t HistPix_15 = 1;
    uint8_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
const uint16_t size_histdef_dtmi = 8;
struct DTMI_1_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t POST = 0;
    int16_t Tcmv = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    uint16_t Texp = 0;
    uint16_t PixCount_NumLoc = 0;
    uint8_t NumStore = 0;
    uint8_t NumDet = 0;
    uint8_t NumProgFrag = 0;
    uint8_t NumFrag = 0;
    uint32_t Tlast = 0;
    uint16_t Tmslast = 0;
    std::array<float, size_qlst_dtmi> Qlst;
    uint16_t rezerv = 0;
    std::array<uint8_t, size_histdef_dtmi> HistDef;
    uint16_t cs = 0;

};
#pragma pack(pop)

const uint16_t size_loc_dtmi = 15;
#pragma pack(push, 1)
struct DTMI_2_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<float, size_loc_dtmi> rs_loc_0_dtmi2;
    uint16_t cs = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_3_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<float, size_loc_dtmi> rs_loc_0_dtmi3;
    uint16_t cs = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_4_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<float, size_loc_dtmi> rs_loc_0_dtmi4;
    uint16_t cs = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_5_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<float, size_loc_dtmi> rs_loc_1_dtmi5;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_6_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<float, size_loc_dtmi> rs_loc_1_dtmi6;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_7_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<float, size_loc_dtmi> rs_loc_1_dtmi7;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_8_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<uint16_t, size_loc_dtmi> rs_loc_s_0_dtmi8;
    std::array<uint16_t, size_loc_dtmi> rs_loc_s_1_dtmi8;
    uint16_t cs = 0;
};
#pragma pack(pop)

const uint16_t size_xyc_dtmi = 30;
#pragma pack(push, 1)
struct DTMI_9_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<uint16_t, size_xyc_dtmi> Xyc;
    uint16_t cs = 0;
};
#pragma pack(pop)

const uint16_t size_mean_dtmi = 30;

#pragma pack(push, 1)
struct DTMI_10_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<uint16_t, size_mean_dtmi> Mean;
    uint16_t cs = 0;
};
#pragma pack(pop)

const uint16_t size_thfrag_dtmi = 15;
const uint16_t size_objfrag_dtmi = 4;
const uint16_t size_multxy_dtmi = 4;
const uint16_t size_zipxy_dtmi = 7;
#pragma pack(push, 1)
struct DTMI_11_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    std::array<uint16_t, size_thfrag_dtmi> ThFrag;
    std::array<uint16_t, size_objfrag_dtmi> ObjFrag;
    std::array<uint16_t, size_multxy_dtmi> MultXY;
    std::array<uint16_t, size_zipxy_dtmi> ZipXY;
    uint16_t cs = 0;
};
#pragma pack(pop)
const uint16_t size_hist_pix = 15;
#pragma pack(push, 1)
struct DTMI_12_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t Vx = 0;
    uint16_t Vy = 0;
    uint16_t Vz = 0;
    uint16_t Wx = 0;
    uint16_t Wy = 0;
    uint16_t Wz = 0;
    uint16_t rezerv_8 = 0;
    uint16_t rezerv_9 = 0;
    uint16_t rezerv_10 = 0;
    uint16_t rezerv_11 = 0;
    uint16_t rezerv_12 = 0;
    uint16_t rezerv_13 = 0;
    uint16_t rezerv_14 = 0;
    uint16_t rezerv_15 = 0;
    float Epoch = 0;
    uint8_t NumL_0 = 0;
    uint8_t NumL_1 = 0;
    uint16_t maxH = 0;
    uint8_t dxmaxH = 0;
    uint8_t dymaxH = 0;
    uint8_t NumSec = 0;
    uint8_t Epsilon = 0;
    uint16_t deltaT = 0;
    uint16_t m_cur = 0;
    std::array<uint8_t, size_hist_pix> HistPix;
    uint8_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_MF
{
    QStringList dtmi_list_name;
    std::vector<std::tuple<QString, double, double, double>> dtmi_list_data;
    std::vector<std::pair<uint16_t, uint16_t>> nAr;
    std::vector<uint16_t> calc_cs;
    std::vector<std::pair<uint16_t, uint16_t>> cs;
    std::vector<std::tuple<float, double, double>> qlst;
    std::vector<std::tuple<uint8_t, double, double>> HistDef;
    std::vector<std::tuple<float, double, double>> rsLoc_0_x;
    std::vector<std::tuple<float, double, double>> rsLoc_0_y;
    std::vector<std::tuple<float, double, double>> rsLoc_0_b;
    std::vector<std::tuple<uint16_t, double, double>> rsLoc_0_s;

    std::vector<std::tuple<float, double, double>> rsLoc_1_x;
    std::vector<std::tuple<float, double, double>> rsLoc_1_y;
    std::vector<std::tuple<float, double, double>> rsLoc_1_b;
    std::vector<std::tuple<uint16_t, double, double>> rsLoc_1_s;

    std::vector<std::tuple<uint16_t, double, double>> XYc_x;
    std::vector<std::tuple<uint16_t, double, double>> XYc_y;
    std::vector<std::tuple<uint16_t, double, double>> MeanFrag;
    std::vector<std::tuple<uint16_t, double, double>> SigmaFrag;
    std::vector<std::tuple<uint16_t, double, double>> ThFrag;
    std::vector<std::tuple<uint16_t, double, double>> ObjFrag;
    std::vector<std::tuple<uint16_t, double, double>> MultXY;
    std::vector<std::tuple<uint16_t, double, double>> ZipXY_X;
    std::vector<std::tuple<uint16_t, double, double>> ZipXY_Y;
    std::vector<std::tuple<uint16_t, double, double>> HistPix;

    DTMI_1_MF dtmi_1_mf;
    DTMI_2_MF dtmi_2_mf;
    DTMI_3_MF dtmi_3_mf;
    DTMI_4_MF dtmi_4_mf;
    DTMI_5_MF dtmi_5_mf;
    DTMI_6_MF dtmi_6_mf;
    DTMI_7_MF dtmi_7_mf;
    DTMI_8_MF dtmi_8_mf;
    DTMI_9_MF dtmi_9_mf;
    DTMI_10_MF dtmi_10_mf;
    DTMI_11_MF dtmi_11_mf;
    DTMI_12_MF dtmi_12_mf;
};
#pragma pack(pop)

const uint16_t count_dtmiloc_1 = 9;
#pragma pack(push, 1)
struct DTMILoc_1
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t Texp = 0;
    uint16_t NumLoc = 0;
    uint16_t NumObj = 0;
    uint32_t Mean = 0;
    uint32_t Sigma = 0;
    std::array<float, count_dtmiloc_1> Loc;
};
#pragma pack(pop)

const uint16_t count_dtmiloc_2 = 15;
#pragma pack(push, 1)
struct DTMILoc_2
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_3
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_4
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_5
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_6
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_7
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
};
#pragma pack(pop)

const uint16_t count_dtmiloc_9 = 14;
#pragma pack(push, 1)
struct DTMILoc_9
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<float, count_dtmiloc_2> Loc;
    uint32_t rezerv = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc
{
    DTMILoc_1 dtmiLoc_1;
    DTMILoc_2 dtmiLoc_2;
    DTMILoc_3 dtmiLoc_3;
    DTMILoc_4 dtmiLoc_4;
    DTMILoc_5 dtmiLoc_5;
    DTMILoc_6 dtmiLoc_6;
    DTMILoc_7 dtmiLoc_7;
    DTMILoc_8 dtmiLoc_8;
    DTMILoc_9 dtmiLoc_9;
    QStringList dtmi_loc_list_name;
    std::vector<std::pair<uint16_t, uint16_t>> dtmi_cc1;
    std::vector<std::pair<uint16_t, uint16_t>> dtmi_cc2;
    std::vector<std::tuple<float, float, float>> loc_x;
    std::vector<std::tuple<float, float, float>> loc_y;
    std::vector<std::tuple<float, float, float>> loc_b;
    std::vector<std::tuple<float, float, float>> loc_c;
    std::vector<std::tuple<QString, double, double, double>> dtmi_loc_list_data;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_1
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t T = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t Texp = 0;
    uint16_t NumLoc = 0;
    uint16_t NumObj = 0;
    uint32_t Mean = 0;
    uint32_t Sigma = 0;
    std::array<uint32_t, count_dtmiloc_1> Loc;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_2_3_4_5_6_7_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<uint32_t, count_dtmiloc_2> Loc;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_9
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    std::array<uint32_t, count_dtmiloc_9> Loc;
    uint32_t rezerv = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_1_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t Texp = 0;
    uint16_t NumLoc = 0;
    uint16_t NumObj = 0;
    uint16_t PixCount = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    uint32_t Loc_0_X = 0;
    uint32_t Loc_0_Y = 0;
    uint32_t Loc_0_B = 0;
    uint16_t Loc_0_S = 0;
    uint32_t Loc_1_X = 0;
    uint32_t Loc_1_Y = 0;
    uint32_t Loc_1_B = 0;
    uint16_t Loc_1_S = 0;
    uint32_t Loc_2_X = 0;
    uint32_t Loc_2_Y = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_2_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t Loc_2_B = 0;
    uint16_t Loc_2_S = 0;
    uint32_t Loc_3_X = 0;
    uint32_t Loc_3_Y = 0;
    uint32_t Loc_3_B = 0;
    uint16_t Loc_3_S = 0;
    uint32_t Loc_4_X = 0;
    uint32_t Loc_4_Y = 0;
    uint32_t Loc_4_B = 0;
    uint16_t Loc_4_S = 0;
    uint32_t Loc_5_X = 0;
    uint32_t Loc_5_Y = 0;
    uint32_t Loc_5_B = 0;
    uint32_t Loc_5_S = 0;
    uint32_t Loc_6_X = 0;
    uint32_t Loc_6_Y = 0;
    uint32_t Loc_6_B = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_3_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t Loc_6_S = 0;
    uint32_t Loc_7_X = 0;
    uint32_t Loc_7_Y = 0;
    uint32_t Loc_7_B = 0;
    uint16_t Loc_7_S = 0;
    uint32_t Loc_8_X = 0;
    uint32_t Loc_8_Y = 0;
    uint32_t Loc_8_B = 0;
    uint16_t Loc_8_S = 0;
    uint32_t Loc_9_X = 0;
    uint32_t Loc_9_Y = 0;
    uint32_t Loc_9_B = 0;
    uint16_t Loc_9_S = 0;
    uint32_t Loc_10_X = 0;
    uint32_t Loc_10_Y = 0;
    uint32_t Loc_10_B = 0;
    uint16_t Loc_10_S = 0;
    uint16_t rezerv = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_4_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t Loc_11_X = 0;
    uint32_t Loc_11_Y = 0;
    uint32_t Loc_11_B = 0;
    uint16_t Loc_11_S = 0;
    uint32_t Loc_12_X = 0;
    uint32_t Loc_12_Y = 0;
    uint32_t Loc_12_B = 0;
    uint16_t Loc_12_S = 0;
    uint32_t Loc_13_X = 0;
    uint32_t Loc_13_Y = 0;
    uint32_t Loc_13_B = 0;
    uint16_t Loc_13_S = 0;
    uint32_t Loc_14_X = 0;
    uint32_t Loc_14_Y = 0;
    uint32_t Loc_14_B = 0;
    uint16_t Loc_14_S = 0;
    uint32_t Loc_15_X = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_5_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t Loc_15_Y = 0;
    uint32_t Loc_15_B = 0;
    uint16_t Loc_15_S = 0;
    uint32_t Loc_16_X = 0;
    uint32_t Loc_16_Y = 0;
    uint32_t Loc_16_B = 0;
    uint16_t Loc_16_S = 0;
    uint32_t Loc_17_X = 0;
    uint32_t Loc_17_Y = 0;
    uint32_t Loc_17_B = 0;
    uint16_t Loc_17_S = 0;
    uint32_t Loc_18_X = 0;
    uint32_t Loc_18_Y = 0;
    uint32_t Loc_18_B = 0;
    uint16_t Loc_18_S = 0;
    uint32_t Loc_19_X = 0;
    uint32_t Loc_19_Y = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_6_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t Loc_19_B = 0;
    uint16_t Loc_19_S = 0;
    uint32_t Loc_20_X = 0;
    uint32_t Loc_20_Y = 0;
    uint32_t Loc_20_B = 0;
    uint16_t Loc_20_S = 0;
    uint32_t Loc_21_X = 0;
    uint32_t Loc_21_Y = 0;
    uint32_t Loc_21_B = 0;
    uint16_t Loc_21_S = 0;
    uint32_t Loc_22_X = 0;
    uint32_t Loc_22_Y = 0;
    uint32_t Loc_22_B = 0;
    uint16_t Loc_22_S = 0;
    uint32_t Loc_23_X = 0;
    uint32_t Loc_23_Y = 0;
    uint32_t Loc_23_B = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_7_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t Loc_23_S = 0;
    uint32_t Loc_24_X = 0;
    uint32_t Loc_24_Y = 0;
    uint32_t Loc_24_B = 0;
    uint16_t Loc_24_S = 0;
    uint32_t Loc_25_X = 0;
    uint32_t Loc_25_Y = 0;
    uint32_t Loc_25_B = 0;
    uint16_t Loc_25_S = 0;
    uint32_t Loc_26_X = 0;
    uint32_t Loc_26_Y = 0;
    uint32_t Loc_26_B = 0;
    uint16_t Loc_26_S = 0;
    uint32_t Loc_27_X = 0;
    uint32_t Loc_27_Y = 0;
    uint32_t Loc_27_B = 0;
    uint16_t Loc_27_S = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_8_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t Loc_28_X = 0;
    uint32_t Loc_28_Y = 0;
    uint32_t Loc_28_B = 0;
    uint16_t Loc_28_S = 0;
    uint32_t Loc_29_X = 0;
    uint32_t Loc_29_Y = 0;
    uint32_t Loc_29_B = 0;
    uint16_t Loc_29_S = 0;
    uint32_t Loc_30_X = 0;
    uint32_t Loc_30_Y = 0;
    uint32_t Loc_30_B = 0;
    uint16_t Loc_30_S = 0;
    uint32_t Loc_31_X = 0;
    uint32_t Loc_31_Y = 0;
    uint32_t Loc_31_B = 0;
    uint16_t Loc_31_S = 0;
    uint32_t Loc_32_X = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_9_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t Loc_32_Y = 0;
    uint32_t Loc_32_B = 0;
    uint16_t Loc_32_S = 0;
    uint32_t Loc_33_X = 0;
    uint32_t Loc_33_Y = 0;
    uint32_t Loc_33_B = 0;
    uint16_t Loc_33_S = 0;
    uint32_t Loc_34_X = 0;
    uint32_t Loc_34_Y = 0;
    uint32_t Loc_34_B = 0;
    uint16_t Loc_34_S = 0;
    uint32_t Loc_35_X = 0;
    uint32_t Loc_35_Y = 0;
    uint32_t Loc_35_B = 0;
    uint16_t Loc_35_S = 0;
    uint16_t nPixNs = 0;
    uint16_t nPixGrNs = 0;
    uint16_t Th = 0;
    uint16_t Tcmv = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_1_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint32_t T = 0;
    uint16_t Tms = 0;
    uint16_t KC1 = 0;
    uint16_t KC2 = 0;
    uint16_t SerNum = 0;
    uint16_t Texp = 0;
    uint16_t NumLoc = 0;
    uint16_t NumObj = 0;
    uint16_t PixCount = 0;
    uint16_t Mean = 0;
    uint16_t Sigma = 0;
    float Loc_0_X = 0;
    float Loc_0_Y = 0;
    float Loc_0_B = 0;
    uint16_t Loc_0_S = 0;
    float Loc_1_X = 0;
    float Loc_1_Y = 0;
    float Loc_1_B = 0;
    uint16_t Loc_1_S = 0;
    float Loc_2_X = 0;
    float Loc_2_Y = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_2_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    float Loc_2_B = 0;
    uint16_t Loc_2_S = 0;
    float Loc_3_X = 0;
    float Loc_3_Y = 0;
    float Loc_3_B = 0;
    uint16_t Loc_3_S = 0;
    float Loc_4_X = 0;
    float Loc_4_Y = 0;
    float Loc_4_B = 0;
    uint16_t Loc_4_S = 0;
    float Loc_5_X = 0;
    float Loc_5_Y = 0;
    float Loc_5_B = 0;
    uint16_t Loc_5_S = 0;
    float Loc_6_X = 0;
    float Loc_6_Y = 0;
    float Loc_6_B = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_3_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t Loc_6_S = 0;
    float Loc_7_X = 0;
    float Loc_7_Y = 0;
    float Loc_7_B = 0;
    uint16_t Loc_7_S = 0;
    float Loc_8_X = 0;
    float Loc_8_Y = 0;
    float Loc_8_B = 0;
    uint16_t Loc_8_S = 0;
    float Loc_9_X = 0;
    float Loc_9_Y = 0;
    float Loc_9_B = 0;
    uint16_t Loc_9_S = 0;
    float Loc_10_X = 0;
    float Loc_10_Y = 0;
    float Loc_10_B = 0;
    uint16_t Loc_10_S = 0;
    uint16_t rezerv = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_4_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    float Loc_11_X = 0;
    float Loc_11_Y = 0;
    float Loc_11_B = 0;
    uint16_t Loc_11_S = 0;
    float Loc_12_X = 0;
    float Loc_12_Y = 0;
    float Loc_12_B = 0;
    uint16_t Loc_12_S = 0;
    float Loc_13_X = 0;
    float Loc_13_Y = 0;
    float Loc_13_B = 0;
    uint16_t Loc_13_S = 0;
    float Loc_14_X = 0;
    float Loc_14_Y = 0;
    float Loc_14_B = 0;
    uint16_t Loc_14_S = 0;
    float Loc_15_X = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_5_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    float Loc_15_Y = 0;
    float Loc_15_B = 0;
    uint16_t Loc_15_S = 0;
    float Loc_16_X = 0;
    float Loc_16_Y = 0;
    float Loc_16_B = 0;
    uint16_t Loc_16_S = 0;
    float Loc_17_X = 0;
    float Loc_17_Y = 0;
    float Loc_17_B = 0;
    uint16_t Loc_17_S = 0;
    float Loc_18_X = 0;
    float Loc_18_Y = 0;
    float Loc_18_B = 0;
    uint16_t Loc_18_S = 0;
    float Loc_19_X = 0;
    float Loc_19_Y = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_6_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    float Loc_19_B = 0;
    uint16_t Loc_19_S = 0;
    float Loc_20_X = 0;
    float Loc_20_Y = 0;
    float Loc_20_B = 0;
    uint16_t Loc_20_S = 0;
    float Loc_21_X = 0;
    float Loc_21_Y = 0;
    float Loc_21_B = 0;
    uint16_t Loc_21_S = 0;
    float Loc_22_X = 0;
    float Loc_22_Y = 0;
    float Loc_22_B = 0;
    uint16_t Loc_22_S = 0;
    float Loc_23_X = 0;
    float Loc_23_Y = 0;
    float Loc_23_B = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_7_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    uint16_t Loc_23_S = 0;
    float Loc_24_X = 0;
    float Loc_24_Y = 0;
    float Loc_24_B = 0;
    uint16_t Loc_24_S = 0;
    float Loc_25_X = 0;
    float Loc_25_Y = 0;
    float Loc_25_B = 0;
    uint16_t Loc_25_S = 0;
    float Loc_26_X = 0;
    float Loc_26_Y = 0;
    float Loc_26_B = 0;
    uint16_t Loc_26_S = 0;
    float Loc_27_X = 0;
    float Loc_27_Y = 0;
    float Loc_27_B = 0;
    uint16_t Loc_27_S = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_8_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    float Loc_28_X = 0;
    float Loc_28_Y = 0;
    float Loc_28_B = 0;
    uint16_t Loc_28_S = 0;
    float Loc_29_X = 0;
    float Loc_29_Y = 0;
    float Loc_29_B = 0;
    uint16_t Loc_29_S = 0;
    float Loc_30_X = 0;
    float Loc_30_Y = 0;
    float Loc_30_B = 0;
    uint16_t Loc_30_S = 0;
    float Loc_31_X = 0;
    float Loc_31_Y = 0;
    float Loc_31_B = 0;
    uint16_t Loc_31_S = 0;
    float Loc_32_X = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_9_MF
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t nAr = 0;
    float Loc_32_Y = 0;
    float Loc_32_B = 0;
    uint16_t Loc_32_S = 0;
    float Loc_33_X = 0;
    float Loc_33_Y = 0;
    float Loc_33_B = 0;
    uint16_t Loc_33_S = 0;
    float Loc_34_X = 0;
    float Loc_34_Y = 0;
    float Loc_34_B = 0;
    uint16_t Loc_34_S = 0;
    float Loc_35_X = 0;
    float Loc_35_Y = 0;
    float Loc_35_B = 0;
    uint16_t Loc_35_S = 0;
    uint16_t nPixNs = 0;
    uint16_t nPixGrNs = 0;
    uint16_t Th = 0;
    uint16_t Tcmv = 0;
    uint16_t cs = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MLoc_MF
{
    QStringList mloc_list_name;
    std::vector<std::tuple<QString, double, double, double>> mloc_list_data;
    std::vector<uint16_t> calc_cs;
    MLoc_1_MF mLoc_1_mf;
    MLoc_2_MF mLoc_2_mf;
    MLoc_3_MF mLoc_3_mf;
    MLoc_4_MF mLoc_4_mf;
    MLoc_5_MF mLoc_5_mf;
    MLoc_6_MF mLoc_6_mf;
    MLoc_7_MF mLoc_7_mf;
    MLoc_8_MF mLoc_8_mf;
    MLoc_9_MF mLoc_9_mf;
    std::vector<std::pair<uint16_t, uint16_t>> nAr;
    std::vector<std::pair<uint16_t, uint16_t>> cs;
    std::vector<std::tuple<float, float, float>> loc_x;
    std::vector<std::tuple<float, float, float>> loc_y;
    std::vector<std::tuple<float, float, float>> loc_b;
    std::vector<std::tuple<uint16_t, float, float>> loc_c;
};
#pragma pack(pop)

const uint16_t count_chpn_matrix = 9;
#pragma pack(push, 1)
struct CHPN_1_MF_raw
{
    uint16_t nAr;
    uint16_t Texp;
    uint32_t Foc;
    uint32_t XG;
    uint32_t YG;
    uint32_t Epsilon;
    std::array<uint32_t, count_chpn_matrix> m_pr;
    uint16_t rezerv1;
    uint16_t rezerv2;
    uint16_t rezerv3;
};
#pragma pack(pop)
const uint16_t count_chpn_rezerv = 8;
#pragma pack(push, 1)
struct CHPN_2_MF_raw
{
    uint16_t nAr;
    uint32_t extBrightThres;
    uint32_t extOmegaLocalThres;
    uint16_t extMinPixelCount;
    uint16_t extMaxPixelCount;
    uint16_t MaxExp;
    uint16_t MinExp;
    uint32_t KSigmaNO;
    uint32_t KSigmaSL;
    uint16_t StarNO;
    uint16_t StarSrcSSL;
    uint16_t Noise;
    uint16_t radius;
    uint16_t fragNormalSizeY;
    uint16_t stepNormalY;
    uint16_t fragStatSizeY;
    uint16_t stepStatY;
    uint16_t x0;
    uint16_t y0;
    std::array<uint16_t, count_chpn_rezerv> rezerv;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct CHPN_1_MF
{
    uint16_t nAr;
    uint16_t Texp;
    float Foc;
    float XG;
    float YG;
    float Epsilon;
    uint16_t rezerv1;
    std::array<float, count_chpn_matrix> m_pr;
    uint16_t rezerv2;
    uint16_t rezerv3;
    uint16_t rezerv4;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CHPN_2_MF
{
    uint16_t nAr;
    float extBrightThres;
    float extOmegaLocalThres;
    uint16_t extMinPixelCount;
    uint16_t extMaxPixelCount;
    uint16_t MaxExp;
    uint16_t MinExp;
    float KSigmaNO;
    float KSigmaSL;
    uint16_t StarNO;
    uint16_t StarSrcSSL;
    uint16_t Noise;
    uint16_t radius;
    uint16_t fragNormalSizeY;
    uint16_t stepNormalY;
    uint16_t fragStatSizeY;
    uint16_t stepStatY;
    uint16_t x0;
    uint16_t y0;
    std::array<uint16_t, count_chpn_rezerv> rezerv;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CHPN_MF
{
    QStringList chpn_list_name;
    QStringList chpn_list_data;
    CHPN_1_MF chpn_1_mf;
    CHPN_2_MF chpn_2_mf;
};
#pragma pack(pop)

const uint16_t count_chkd = 14;
#pragma pack(push, 1)
struct CHKD_1_MF_raw
{
    uint16_t nAr;
    std::array<uint32_t, count_chkd> KofDX;
    uint16_t procCover;
    uint16_t procFieldCalibr;
    uint16_t cs;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CHKD_2_MF_raw
{
    uint16_t nAr;
    std::array<uint32_t, count_chkd> KofDY;
    uint16_t rezerv1;
    uint16_t rezerve2;
    uint16_t cs;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct CHKD_1_MF
{
    uint16_t nAr;
    std::array<float, count_chkd> KofDX;
    uint16_t procCover;
    uint16_t procFieldCalibr;
    uint16_t cs;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CHKD_2_MF
{
    uint16_t nAr;
    std::array<float, count_chkd> KofDY;
    uint16_t rezerv1;
    uint16_t rezerve2;
    uint16_t cs;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CHKD_MF
{
    QStringList chkd_list_name;
    QStringList chkd_list_data;
    CHKD_1_MF chkd_1_mf;
    CHKD_2_MF chkd_2_mf;
};
#pragma pack(pop)

struct Kia_mko_struct
{
    SHTMI1 st_shtmi1;
    SHTMI2 st_shtmi2;
    MSHIOR st_mshior;
    DTMI st_dtmi;
    DTMILoc st_dtmi_loc;

    SHTMI1_MF st_shtmi1_mf;
    SHTMI2_MF st_shtmi2_mf;
    MSHIOR_MF st_mshior_mf;
    DTMI_MF st_dtmi_mf;
    MLoc_MF st_mloc_mf;
    CHPN_MF st_chpn_mf;
    CHKD_MF st_chkd_mf;
}; Q_DECLARE_METATYPE(Kia_mko_struct)

Q_DECLARE_METATYPE(uint16_t)
#endif // KIA_MKO_STRUCT_H
