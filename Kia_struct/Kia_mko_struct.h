#ifndef KIA_MKO_STRUCT_H
#define KIA_MKO_STRUCT_H
#include <iostream>
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
    QStringList shtmi1_list_data;
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
    QStringList shtmi2_list_data;
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
    QStringList mshior_list_data;
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
struct DTMI
{
    QStringList dtmi_list_name;
    QStringList dtmi_list_data;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc
{
    QStringList dtmi_loc_list_name;
    QStringList dtmi_loc_list_data;
};
#pragma pack(pop)


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
    float Loc_0_0 = 0;
    float Loc_0_1 = 0;
    float Loc_0_2 = 0;
    float Loc_0_3 = 0;
    float Loc_1_0 = 0;
    float Loc_1_1 = 0;
    float Loc_1_2 = 0;
    float Loc_1_3 = 0;
    float Loc_2_0 = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_2
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 2_1
    float Loc_5_6 = 0;// 2_2
    float Loc_7_8 = 0;// 2_3
    float Loc_9_10 = 0;// 3_0
    float Loc_11_12 = 0;// 3_1
    float Loc_13_14 = 0;// 3_2
    float Loc_15_16 = 0;// 3_3
    float Loc_17_18 = 0;// 4_0
    float Loc_19_20 = 0;// 4_1
    float Loc_21_22 = 0;// 4_2
    float Loc_23_24 = 0;// 4_3
    float Loc_25_26 = 0;// 5_0
    float Loc_27_28 = 0;// 5_1
    float Loc_29_30 = 0;// 5_2
    float Loc_31_32 = 0;// 5_3

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_3
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 6_0
    float Loc_5_6 = 0;// 6_1
    float Loc_7_8 = 0;// 6_2
    float Loc_9_10 = 0;// 6_3
    float Loc_11_12 = 0;// 7_0
    float Loc_13_14 = 0;// 7_1
    float Loc_15_16 = 0;// 7_2
    float Loc_17_18 = 0;// 7_3
    float Loc_19_20 = 0;// 8_0
    float Loc_21_22 = 0;// 8_1
    float Loc_23_24 = 0;// 8_2
    float Loc_25_26 = 0;// 8_3
    float Loc_27_28 = 0;// 9_0
    float Loc_29_30 = 0;// 9_1
    float Loc_31_32 = 0;// 9_2
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_4
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 9_3
    float Loc_5_6 = 0;// 10_0
    float Loc_7_8 = 0;// 10_1
    float Loc_9_10 = 0;// 10_2
    float Loc_11_12 = 0;// 10_3
    float Loc_13_14 = 0;// 11_0
    float Loc_15_16 = 0;// 11_1
    float Loc_17_18 = 0;// 11_2
    float Loc_19_20 = 0;// 11_3
    float Loc_21_22 = 0;// 12_0
    float Loc_23_24 = 0;// 12_1
    float Loc_25_26 = 0;// 12_2
    float Loc_27_28 = 0;// 12_3
    float Loc_29_30 = 0;// 13_0
    float Loc_31_32 = 0;// 13_1
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_5
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 13_2
    float Loc_5_6 = 0;// 13_3
    float Loc_7_8 = 0;// 14_0
    float Loc_9_10 = 0;// 14_1
    float Loc_11_12 = 0;// 14_2
    float Loc_13_14 = 0;// 14_3
    float Loc_15_16 = 0;// 15_0
    float Loc_17_18 = 0;// 15_1
    float Loc_19_20 = 0;// 15_2
    float Loc_21_22 = 0;// 15_3
    float Wo_x = 0;
    float Wo_y = 0;
    float Wo_z = 0;
    float XYc_0_0 = 0;
    float XYc_0_1 = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_6
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float XYc_3_4 = 0; // 1_0
    float XYc_5_6 = 0;// 1_1
    float XYc_7_8 = 0;// 2_0
    float XYc_9_10 = 0;// 2_1
    float XYc_11_12 = 0;// 3_0
    float XYc_13_14 = 0;// 3_1
    float XYc_15_16 = 0;// 4_0
    float XYc_17_18 = 0;// 4_1
    float XYc_19_20 = 0;// 5_0
    float XYc_21_22 = 0;// 5_1
    float XYc_23_24 = 0;// 6_0
    float XYc_25_26 = 0;// 6_1
    float XYc_27_28 = 0;// 7_0
    float XYc_29_30 = 0;// 7_1
    float XYc_31_32 = 0;// 8_0
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_7
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float XYc_3_4 = 0; // 1_0
    float XYc_5_6 = 0;// 1_1
    float XYc_7_8 = 0;// 2_0
    float XYc_9_10 = 0;// 2_1
    float XYc_11_12 = 0;// 3_0
    float XYc_13_14 = 0;// 3_1
    float XYc_15_16 = 0;// 4_0
    float XYc_17_18 = 0;// 4_1
    float XYc_19_20 = 0;// 5_0
    float XYc_21_22 = 0;// 5_1
    float XYc_23_24 = 0;// 6_0
    float XYc_25_26 = 0;// 6_1
    float XYc_27_28 = 0;// 7_0
    float XYc_29_30 = 0;// 7_1
    float XYc_31_32 = 0;// 8_0
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMI_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint16_t TheFrag_0 = 0; // 1_0
    uint16_t TheFrag_1 = 0;// 1_1
    uint16_t TheFrag_2 = 0;// 2_0
    uint16_t TheFrag_3 = 0;// 2_1
    uint16_t TheFrag_4 = 0;// 3_0
    uint16_t TheFrag_5 = 0;// 3_1
    uint16_t TheFrag_6 = 0;// 4_0
    uint16_t TheFrag_7 = 0;// 4_1
    uint16_t TheFrag_8 = 0;// 5_0
    uint16_t TheFrag_9 = 0;// 5_1
    uint16_t TheFrag_10 = 0;// 6_0
    uint16_t TheFrag_11 = 0;// 6_1
    uint16_t TheFrag_12 = 0;// 7_0
    uint16_t TheFrag_13 = 0;// 7_1
    uint16_t TheFrag_14 = 0;// 8_0
    uint16_t TheFrag_15 = 0;// 8_0
    uint16_t ObjFrag_0 = 0;
    uint16_t ObjFrag_1 = 0;
    uint16_t ObjFrag_2 = 0;
    uint16_t ObjFrag_3 = 0;
    uint16_t ObjFrag_4 = 0;
    uint16_t ObjFrag_5 = 0;
    uint16_t ObjFrag_6 = 0;
    uint16_t ObjFrag_7 = 0;
    uint16_t ObjFrag_8 = 0;
    uint16_t ObjFrag_9 = 0;
    uint16_t ObjFrag_10 = 0;
    uint16_t ObjFrag_11 = 0;
    uint16_t ObjFrag_12 = 0;
    uint16_t ObjFrag_13 = 0;
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
    uint32_t Loc_0_0 = 0;
    uint32_t Loc_0_1 = 0;
    uint32_t Loc_0_2 = 0;
    uint32_t Loc_0_3 = 0;
    uint32_t Loc_1_0 = 0;
    uint32_t Loc_1_1 = 0;
    uint32_t Loc_1_2 = 0;
    uint32_t Loc_1_3 = 0;
    uint32_t Loc_2_0 = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_2_3_4
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t Loc_3_4 = 0;
    uint32_t Loc_5_6 = 0;
    uint32_t Loc_7_8 = 0;
    uint32_t Loc_9_10 = 0;
    uint32_t Loc_11_12 = 0;
    uint32_t Loc_13_14 = 0;
    uint32_t Loc_15_16 = 0;
    uint32_t Loc_17_18 = 0;
    uint32_t Loc_19_20 = 0;
    uint32_t Loc_21_22 = 0;
    uint32_t Loc_23_24 = 0;
    uint32_t Loc_25_26 = 0;
    uint32_t Loc_27_28 = 0;
    uint32_t Loc_29_30 = 0;
    uint32_t Loc_31_32 = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_5
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t Loc_3_4 = 0;
    uint32_t Loc_5_6 = 0;
    uint32_t Loc_7_8 = 0;
    uint32_t Loc_9_10 = 0;
    uint32_t Loc_11_12 = 0;
    uint32_t Loc_13_14 = 0;
    uint32_t Loc_15_16 = 0;
    uint32_t Loc_17_18 = 0;
    uint32_t Loc_19_20 = 0;
    uint32_t Loc_21_22 = 0;
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
    uint32_t XYc_3_4 = 0; // 1_0
    uint32_t XYc_5_6 = 0;// 1_1
    uint32_t XYc_7_8 = 0;// 2_0
    uint32_t XYc_9_10 = 0;// 2_1
    uint32_t XYc_11_12 = 0;// 3_0
    uint32_t XYc_13_14 = 0;// 3_1
    uint32_t XYc_15_16 = 0;// 4_0
    uint32_t XYc_17_18 = 0;// 4_1
    uint32_t XYc_19_20 = 0;// 5_0
    uint32_t XYc_21_22 = 0;// 5_1
    uint32_t XYc_23_24 = 0;// 6_0
    uint32_t XYc_25_26 = 0;// 6_1
    uint32_t XYc_27_28 = 0;// 7_0
    uint32_t XYc_29_30 = 0;// 7_1
    uint32_t XYc_31_32 = 0;// 8_0
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMIRaw_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint16_t TheFrag_0 = 0; // 1_0
    uint16_t TheFrag_1 = 0;// 1_1
    uint16_t TheFrag_2 = 0;// 2_0
    uint16_t TheFrag_3 = 0;// 2_1
    uint16_t TheFrag_4 = 0;// 3_0
    uint16_t TheFrag_5 = 0;// 3_1
    uint16_t TheFrag_6 = 0;// 4_0
    uint16_t TheFrag_7 = 0;// 4_1
    uint16_t TheFrag_8 = 0;// 5_0
    uint16_t TheFrag_9 = 0;// 5_1
    uint16_t TheFrag_10 = 0;// 6_0
    uint16_t TheFrag_11 = 0;// 6_1
    uint16_t TheFrag_12 = 0;// 7_0
    uint16_t TheFrag_13 = 0;// 7_1
    uint16_t TheFrag_14 = 0;// 8_0
    uint16_t TheFrag_15 = 0;// 8_0
    uint16_t ObjFrag_0 = 0;
    uint16_t ObjFrag_1 = 0;
    uint16_t ObjFrag_2 = 0;
    uint16_t ObjFrag_3 = 0;
    uint16_t ObjFrag_4 = 0;
    uint16_t ObjFrag_5 = 0;
    uint16_t ObjFrag_6 = 0;
    uint16_t ObjFrag_7 = 0;
    uint16_t ObjFrag_8 = 0;
    uint16_t ObjFrag_9 = 0;
    uint16_t ObjFrag_10 = 0;
    uint16_t ObjFrag_11 = 0;
    uint16_t ObjFrag_12 = 0;
    uint16_t ObjFrag_13 = 0;
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
    float Loc_0_0 = 0;
    float Loc_0_1 = 0;
    float Loc_0_2 = 0;
    float Loc_0_3 = 0;
    float Loc_1_0 = 0;
    float Loc_1_1 = 0;
    float Loc_1_2 = 0;
    float Loc_1_3 = 0;
    float Loc_2_0 = 0;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct DTMILoc_2
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 2_1
    float Loc_5_6 = 0;// 2_2
    float Loc_7_8 = 0;// 2_3
    float Loc_9_10 = 0;// 3_0
    float Loc_11_12 = 0;// 3_1
    float Loc_13_14 = 0;// 3_2
    float Loc_15_16 = 0;// 3_3
    float Loc_17_18 = 0;// 4_0
    float Loc_19_20 = 0;// 4_1
    float Loc_21_22 = 0;// 4_2
    float Loc_23_24 = 0;// 4_3
    float Loc_25_26 = 0;// 5_0
    float Loc_27_28 = 0;// 5_1
    float Loc_29_30 = 0;// 5_2
    float Loc_31_32 = 0;// 5_3
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_3
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 6_0
    float Loc_5_6 = 0;// 6_1
    float Loc_7_8 = 0;// 6_2
    float Loc_9_10 = 0;// 6_3
    float Loc_11_12 = 0;// 7_0
    float Loc_13_14 = 0;// 7_1
    float Loc_15_16 = 0;// 7_2
    float Loc_17_18 = 0;// 7_3
    float Loc_19_20 = 0;// 8_0
    float Loc_21_22 = 0;// 8_1
    float Loc_23_24 = 0;// 8_2
    float Loc_25_26 = 0;// 8_3
    float Loc_27_28 = 0;// 9_0
    float Loc_29_30 = 0;// 9_1
    float Loc_31_32 = 0;// 9_2
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_4
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 9_3
    float Loc_5_6 = 0;// 10_0
    float Loc_7_8 = 0;// 10_1
    float Loc_9_10 = 0;// 10_2
    float Loc_11_12 = 0;// 10_3
    float Loc_13_14 = 0;// 11_0
    float Loc_15_16 = 0;// 11_1
    float Loc_17_18 = 0;// 11_2
    float Loc_19_20 = 0;// 11_3
    float Loc_21_22 = 0;// 12_0
    float Loc_23_24 = 0;// 12_1
    float Loc_25_26 = 0;// 12_2
    float Loc_27_28 = 0;// 12_3
    float Loc_29_30 = 0;// 13_0
    float Loc_31_32 = 0;// 13_1
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_5
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 13_2
    float Loc_5_6 = 0;// 13_3
    float Loc_7_8 = 0;// 14_0
    float Loc_9_10 = 0;// 14_1
    float Loc_11_12 = 0;// 14_2
    float Loc_13_14 = 0;// 14_3
    float Loc_15_16 = 0;// 15_0
    float Loc_17_18 = 0;// 15_1
    float Loc_19_20 = 0;// 15_2
    float Loc_21_22 = 0;// 15_3
    float Loc_23_24 = 0;// 16_0
    float Loc_25_26 = 0;// 16_1
    float Loc_27_28 = 0;// 16_2
    float Loc_29_30 = 0;// 16_3
    float Loc_31_32 = 0;// 17_0
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_6
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 17_1
    float Loc_5_6 = 0;// 17_2
    float Loc_7_8 = 0;// 17_3
    float Loc_9_10 = 0;// 18_0
    float Loc_11_12 = 0;// 18_1
    float Loc_13_14 = 0;// 18_2
    float Loc_15_16 = 0;// 18_3
    float Loc_17_18 = 0;// 19_0
    float Loc_19_20 = 0;// 19_1
    float Loc_21_22 = 0;// 19_2
    float Loc_23_24 = 0;// 19_3
    float Loc_25_26 = 0;// 20_0
    float Loc_27_28 = 0;// 20_1
    float Loc_29_30 = 0;// 20_2
    float Loc_31_32 = 0;// 20_3
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_7
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 21_0
    float Loc_5_6 = 0;// 21_1
    float Loc_7_8 = 0;// 21_2
    float Loc_9_10 = 0;// 21_3
    float Loc_11_12 = 0;// 22_0
    float Loc_13_14 = 0;// 22_1
    float Loc_15_16 = 0;// 22_2
    float Loc_17_18 = 0;// 22_3
    float Loc_19_20 = 0;// 23_0
    float Loc_21_22 = 0;// 23_1
    float Loc_23_24 = 0;// 23_2
    float Loc_25_26 = 0;// 23_3
    float Loc_27_28 = 0;// 24_0
    float Loc_29_30 = 0;// 24_1
    float Loc_31_32 = 0;// 24_2
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILoc_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 24_3
    float Loc_5_6 = 0;// 25_0
    float Loc_7_8 = 0;// 25_1
    float Loc_9_10 = 0;// 25_2
    float Loc_11_12 = 0;// 25_3
    float Loc_13_14 = 0;// 26_0
    float Loc_15_16 = 0;// 26_1
    float Loc_17_18 = 0;// 26_2
    float Loc_19_20 = 0;// 26_3
    float Loc_21_22 = 0;// 27_0
    float Loc_23_24 = 0;// 27_1
    float Loc_25_26 = 0;// 27_2
    float Loc_27_28 = 0;// 27_3
    float Loc_29_30 = 0;// 28_0
    float Loc_31_32 = 0;// 28_1
};
#pragma pack(pop)
#pragma pack(push, 1)
struct DTMILoc_9
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    float Loc_3_4 = 0;// 28_2
    float Loc_5_6 = 0;// 28_3
    float Loc_7_8 = 0;// 29_0
    float Loc_9_10 = 0;// 29_1
    float Loc_11_12 = 0;// 29_2
    float Loc_13_14 = 0;// 29_3
    float Loc_15_16 = 0;// 30_0
    float Loc_17_18 = 0;// 30_1
    float Loc_19_20 = 0;// 30_2
    float Loc_21_22 = 0;// 30_3
    float Loc_23_24 = 0;// 31_0
    float Loc_25_26 = 0;// 31_1
    float Loc_27_28 = 0;// 31_2
    float Loc_29_30 = 0;// 31_3
    uint32_t rezerv = 0;
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
    uint32_t Loc_0_0 = 0;
    uint32_t Loc_0_1 = 0;
    uint32_t Loc_0_2 = 0;
    uint32_t Loc_0_3 = 0;
    uint32_t Loc_1_0 = 0;
    uint32_t Loc_1_1 = 0;
    uint32_t Loc_1_2 = 0;
    uint32_t Loc_1_3 = 0;
    uint32_t Loc_2_0 = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_2_3_4_5_6_7_8
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t Loc_3_4 = 0;
    uint32_t Loc_5_6 = 0;
    uint32_t Loc_7_8 = 0;
    uint32_t Loc_9_10 = 0;
    uint32_t Loc_11_12 = 0;
    uint32_t Loc_13_14 = 0;
    uint32_t Loc_15_16 = 0;
    uint32_t Loc_17_18 = 0;
    uint32_t Loc_19_20 = 0;
    uint32_t Loc_21_22 = 0;
    uint32_t Loc_23_24 = 0;
    uint32_t Loc_25_26 = 0;
    uint32_t Loc_27_28 = 0;
    uint32_t Loc_29_30 = 0;
    uint32_t Loc_31_32 = 0;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_9
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t Loc_3_4 = 0;
    uint32_t Loc_5_6 = 0;
    uint32_t Loc_7_8 = 0;
    uint32_t Loc_9_10 = 0;
    uint32_t Loc_11_12 = 0;
    uint32_t Loc_13_14 = 0;
    uint32_t Loc_15_16 = 0;
    uint32_t Loc_17_18 = 0;
    uint32_t Loc_19_20 = 0;
    uint32_t Loc_21_22 = 0;
    uint32_t Loc_23_24 = 0;
    uint32_t Loc_25_26 = 0;
    uint32_t Loc_27_28 = 0;
    uint32_t Loc_29_30 = 0;
    uint32_t rezerv = 0;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DTMILocRaw_9_m60
{
    uint16_t CW = 0;
    uint16_t AW = 0;
    uint16_t CC1 = 0;
    uint16_t CC2 = 0;
    uint32_t Loc_3_4 = 0;
    uint32_t Loc_5_6 = 0;
    uint32_t Loc_7_8 = 0;
    uint32_t Loc_9_10 = 0;
    uint32_t Loc_11_12 = 0;
    uint32_t Loc_13_14 = 0;
    uint32_t Loc_15_16 = 0;
    uint32_t Loc_17_18 = 0;
    uint32_t Loc_19_20 = 0;
    uint32_t Loc_21_22 = 0;
    uint32_t Loc_23_24 = 0;
    uint32_t Loc_25_26 = 0;
    uint32_t Loc_27_28 = 0;
    uint32_t Loc_29_30 = 0;
    uint32_t rezerv = 0;
};
#pragma pack(pop)

struct Kia_mko_struct
{
    SHTMI1 st_shtmi1;
    SHTMI2 st_shtmi2;
    MSHIOR st_mshior;
    DTMI st_dtmi;
    DTMILoc st_dtmi_loc;
    DTMI_1 dtmi_1;
    DTMI_2 dtmi_2;
    DTMI_3 dtmi_3;
    DTMI_4 dtmi_4;
    DTMI_5 dtmi_5;
    DTMI_6 dtmi_6;
    DTMI_7 dtmi_7;
    DTMI_8 dtmi_8;
    DTMI_9 dtmi_9;
    DTMILoc_1 dtmiLoc_1;
    DTMILoc_2 dtmiLoc_2;
    DTMILoc_3 dtmiLoc_3;
    DTMILoc_4 dtmiLoc_4;
    DTMILoc_5 dtmiLoc_5;
    DTMILoc_6 dtmiLoc_6;
    DTMILoc_7 dtmiLoc_7;
    DTMILoc_8 dtmiLoc_8;
    DTMILoc_9 dtmiLoc_9;
    DTMILocRaw_9_m60 dtmiLoc_9_m60;
};

struct Kia_mko_struct_bokzm60 : public Kia_mko_struct
{

};

struct Kia_mko_struct_bokzmr : public Kia_mko_struct
{

};
#endif // KIA_MKO_STRUCT_H
