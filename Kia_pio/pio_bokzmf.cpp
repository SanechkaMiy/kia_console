#include "pio_bokzmf.h"

Pio_bokzmf::Pio_bokzmf(std::shared_ptr<Kia_mko_struct> kia_mko_struct,
                       std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_mko_struct(kia_mko_struct),
    m_kia_settings(kia_settings)
{

}

void Pio_bokzmf::decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{
    m_kia_mko_struct->st_mloc_mf.mloc_list_name.clear();
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.clear();
    DTMILocRaw_1_MF dtmi_raw_1;
    DTMILocRaw_2_MF dtmi_raw_2;
    DTMILocRaw_3_MF dtmi_raw_3;
    DTMILocRaw_4_MF dtmi_raw_4;
    DTMILocRaw_5_MF dtmi_raw_5;
    DTMILocRaw_6_MF dtmi_raw_6;
    DTMILocRaw_7_MF dtmi_raw_7;
    DTMILocRaw_8_MF dtmi_raw_8;
    DTMILocRaw_9_MF dtmi_raw_9;
    switch (count)
    {
    case 0:
        memcpy(&dtmi_raw_1,&dataWord,sizeof(dtmi_raw_1));
        dtmi_raw_1.T = swapHex(dtmi_raw_1.T);
        dtmi_raw_1.Loc_0_X = swapHex(dtmi_raw_1.Loc_0_X);
        dtmi_raw_1.Loc_0_Y = swapHex(dtmi_raw_1.Loc_0_Y);
        dtmi_raw_1.Loc_0_B = swapHex(dtmi_raw_1.Loc_0_B);
        dtmi_raw_1.Loc_0_S = swapHex(dtmi_raw_1.Loc_0_S);
        dtmi_raw_1.Loc_1_X = swapHex(dtmi_raw_1.Loc_1_X);
        dtmi_raw_1.Loc_1_Y = swapHex(dtmi_raw_1.Loc_1_Y);
        dtmi_raw_1.Loc_1_B = swapHex(dtmi_raw_1.Loc_1_B);
        dtmi_raw_1.Loc_1_S = swapHex(dtmi_raw_1.Loc_1_S);
        dtmi_raw_1.Loc_2_X = swapHex(dtmi_raw_1.Loc_2_X);
        dtmi_raw_1.Loc_2_Y = swapHex(dtmi_raw_1.Loc_2_Y);
        memcpy(&m_kia_mko_struct->mLoc_1_mf, &dtmi_raw_1, sizeof(m_kia_mko_struct->mLoc_1_mf));
        break;
    case 1:
        memcpy(&dtmi_raw_2, &dataWord, sizeof(dtmi_raw_2));
        dtmi_raw_2.Loc_2_B = swapHex(dtmi_raw_2.Loc_2_B);
        dtmi_raw_2.Loc_2_S = swapHex(dtmi_raw_2.Loc_2_S);
        dtmi_raw_2.Loc_3_X = swapHex(dtmi_raw_2.Loc_3_X);
        dtmi_raw_2.Loc_3_Y = swapHex(dtmi_raw_2.Loc_3_Y);
        dtmi_raw_2.Loc_3_B = swapHex(dtmi_raw_2.Loc_3_B);
        dtmi_raw_2.Loc_3_S = swapHex(dtmi_raw_2.Loc_3_S);
        dtmi_raw_2.Loc_4_X = swapHex(dtmi_raw_2.Loc_4_X);
        dtmi_raw_2.Loc_4_Y = swapHex(dtmi_raw_2.Loc_4_Y);
        dtmi_raw_2.Loc_4_B = swapHex(dtmi_raw_2.Loc_4_B);
        dtmi_raw_2.Loc_4_S = swapHex(dtmi_raw_2.Loc_4_S);
        dtmi_raw_2.Loc_5_X = swapHex(dtmi_raw_2.Loc_5_X);
        dtmi_raw_2.Loc_5_Y = swapHex(dtmi_raw_2.Loc_5_Y);
        dtmi_raw_2.Loc_5_B = swapHex(dtmi_raw_2.Loc_5_B);
        dtmi_raw_2.Loc_5_S = swapHex(dtmi_raw_2.Loc_5_S);
        dtmi_raw_2.Loc_6_X = swapHex(dtmi_raw_2.Loc_6_X);
        dtmi_raw_2.Loc_6_Y = swapHex(dtmi_raw_2.Loc_6_Y);
        dtmi_raw_2.Loc_6_B = swapHex(dtmi_raw_2.Loc_6_B);
        memcpy(&m_kia_mko_struct->mLoc_2_mf, &dtmi_raw_2, sizeof(m_kia_mko_struct->mLoc_2_mf));
        break;
    case 2:
        memcpy(&dtmi_raw_3,&dataWord,sizeof(dtmi_raw_3));
        dtmi_raw_3.Loc_6_S = swapHex(dtmi_raw_3.Loc_6_S);
        dtmi_raw_3.Loc_7_X = swapHex(dtmi_raw_3.Loc_7_X);
        dtmi_raw_3.Loc_7_Y = swapHex(dtmi_raw_3.Loc_7_Y);
        dtmi_raw_3.Loc_7_B = swapHex(dtmi_raw_3.Loc_7_B);
        dtmi_raw_3.Loc_7_S = swapHex(dtmi_raw_3.Loc_7_S);
        dtmi_raw_3.Loc_8_X = swapHex(dtmi_raw_3.Loc_8_X);
        dtmi_raw_3.Loc_8_Y = swapHex(dtmi_raw_3.Loc_8_Y);
        dtmi_raw_3.Loc_8_B = swapHex(dtmi_raw_3.Loc_8_B);
        dtmi_raw_3.Loc_8_S = swapHex(dtmi_raw_3.Loc_8_S);
        dtmi_raw_3.Loc_9_X = swapHex(dtmi_raw_3.Loc_9_X);
        dtmi_raw_3.Loc_9_Y = swapHex(dtmi_raw_3.Loc_9_Y);
        dtmi_raw_3.Loc_9_B = swapHex(dtmi_raw_3.Loc_9_B);
        dtmi_raw_3.Loc_9_S = swapHex(dtmi_raw_3.Loc_9_S);
        dtmi_raw_3.Loc_10_X = swapHex(dtmi_raw_3.Loc_10_X);
        dtmi_raw_3.Loc_10_Y = swapHex(dtmi_raw_3.Loc_10_Y);
        dtmi_raw_3.Loc_10_B = swapHex(dtmi_raw_3.Loc_10_B);
        dtmi_raw_3.Loc_10_S = swapHex(dtmi_raw_3.Loc_10_S);
        memcpy(&m_kia_mko_struct->mLoc_3_mf, &dtmi_raw_3, sizeof(m_kia_mko_struct->mLoc_3_mf));
        break;
    case 3:
        memcpy(&dtmi_raw_4,&dataWord,sizeof(dtmi_raw_4));
        dtmi_raw_4.Loc_11_X = swapHex(dtmi_raw_4.Loc_11_X);
        dtmi_raw_4.Loc_11_Y = swapHex(dtmi_raw_4.Loc_11_Y);
        dtmi_raw_4.Loc_11_B = swapHex(dtmi_raw_4.Loc_11_B);
        dtmi_raw_4.Loc_11_S = swapHex(dtmi_raw_4.Loc_11_S);
        dtmi_raw_4.Loc_12_X = swapHex(dtmi_raw_4.Loc_12_X);
        dtmi_raw_4.Loc_12_Y = swapHex(dtmi_raw_4.Loc_12_Y);
        dtmi_raw_4.Loc_12_B = swapHex(dtmi_raw_4.Loc_12_B);
        dtmi_raw_4.Loc_12_S = swapHex(dtmi_raw_4.Loc_12_S);
        dtmi_raw_4.Loc_13_X = swapHex(dtmi_raw_4.Loc_13_X);
        dtmi_raw_4.Loc_13_Y = swapHex(dtmi_raw_4.Loc_13_Y);
        dtmi_raw_4.Loc_13_B = swapHex(dtmi_raw_4.Loc_13_B);
        dtmi_raw_4.Loc_13_S = swapHex(dtmi_raw_4.Loc_13_S);
        dtmi_raw_4.Loc_14_X = swapHex(dtmi_raw_4.Loc_14_X);
        dtmi_raw_4.Loc_14_Y = swapHex(dtmi_raw_4.Loc_14_Y);
        dtmi_raw_4.Loc_14_B = swapHex(dtmi_raw_4.Loc_14_B);
        dtmi_raw_4.Loc_14_S = swapHex(dtmi_raw_4.Loc_14_S);
        dtmi_raw_4.Loc_15_X = swapHex(dtmi_raw_4.Loc_15_X);
        memcpy(&m_kia_mko_struct->mLoc_4_mf, &dtmi_raw_4, sizeof(m_kia_mko_struct->mLoc_4_mf));
        break;
    case 4:
        memcpy(&dtmi_raw_5,&dataWord,sizeof(dtmi_raw_5));
        dtmi_raw_5.Loc_15_Y = swapHex(dtmi_raw_5.Loc_15_Y);
        dtmi_raw_5.Loc_15_B = swapHex(dtmi_raw_5.Loc_15_B);
        dtmi_raw_5.Loc_15_S = swapHex(dtmi_raw_5.Loc_15_S);
        dtmi_raw_5.Loc_16_X = swapHex(dtmi_raw_5.Loc_16_X);
        dtmi_raw_5.Loc_16_Y = swapHex(dtmi_raw_5.Loc_16_Y);
        dtmi_raw_5.Loc_16_B = swapHex(dtmi_raw_5.Loc_16_B);
        dtmi_raw_5.Loc_16_S = swapHex(dtmi_raw_5.Loc_16_S);
        dtmi_raw_5.Loc_17_X = swapHex(dtmi_raw_5.Loc_17_X);
        dtmi_raw_5.Loc_17_Y = swapHex(dtmi_raw_5.Loc_17_Y);
        dtmi_raw_5.Loc_17_B = swapHex(dtmi_raw_5.Loc_17_B);
        dtmi_raw_5.Loc_17_S = swapHex(dtmi_raw_5.Loc_17_S);
        dtmi_raw_5.Loc_18_X = swapHex(dtmi_raw_5.Loc_18_X);
        dtmi_raw_5.Loc_18_Y = swapHex(dtmi_raw_5.Loc_18_Y);
        dtmi_raw_5.Loc_18_B = swapHex(dtmi_raw_5.Loc_18_B);
        dtmi_raw_5.Loc_18_S = swapHex(dtmi_raw_5.Loc_18_S);
        dtmi_raw_5.Loc_19_X = swapHex(dtmi_raw_5.Loc_19_X);
        dtmi_raw_5.Loc_19_Y = swapHex(dtmi_raw_5.Loc_19_Y);
        memcpy(&m_kia_mko_struct->mLoc_5_mf, &dtmi_raw_5, sizeof(m_kia_mko_struct->mLoc_5_mf));
        break;
    case 5:
        memcpy(&dtmi_raw_6,&dataWord,sizeof(dtmi_raw_6));
        dtmi_raw_6.Loc_19_B = swapHex(dtmi_raw_6.Loc_19_B);
        dtmi_raw_6.Loc_19_S = swapHex(dtmi_raw_6.Loc_19_S);
        dtmi_raw_6.Loc_20_X = swapHex(dtmi_raw_6.Loc_20_X);
        dtmi_raw_6.Loc_20_Y = swapHex(dtmi_raw_6.Loc_20_Y);
        dtmi_raw_6.Loc_20_B = swapHex(dtmi_raw_6.Loc_20_B);
        dtmi_raw_6.Loc_20_S = swapHex(dtmi_raw_6.Loc_20_S);
        dtmi_raw_6.Loc_21_X = swapHex(dtmi_raw_6.Loc_21_X);
        dtmi_raw_6.Loc_21_Y = swapHex(dtmi_raw_6.Loc_21_Y);
        dtmi_raw_6.Loc_21_B = swapHex(dtmi_raw_6.Loc_21_B);
        dtmi_raw_6.Loc_21_S = swapHex(dtmi_raw_6.Loc_21_S);
        dtmi_raw_6.Loc_22_X = swapHex(dtmi_raw_6.Loc_22_X);
        dtmi_raw_6.Loc_22_Y = swapHex(dtmi_raw_6.Loc_22_Y);
        dtmi_raw_6.Loc_22_B = swapHex(dtmi_raw_6.Loc_22_B);
        dtmi_raw_6.Loc_22_S = swapHex(dtmi_raw_6.Loc_22_S);
        dtmi_raw_6.Loc_23_X = swapHex(dtmi_raw_6.Loc_23_X);
        dtmi_raw_6.Loc_23_Y = swapHex(dtmi_raw_6.Loc_22_Y);
        dtmi_raw_6.Loc_23_B = swapHex(dtmi_raw_6.Loc_23_B);
        memcpy(&m_kia_mko_struct->mLoc_6_mf, &dtmi_raw_6, sizeof(m_kia_mko_struct->mLoc_6_mf));
        break;
    case 6:
        memcpy(&dtmi_raw_7,&dataWord,sizeof(dtmi_raw_7));
        dtmi_raw_7.Loc_23_S = swapHex(dtmi_raw_7.Loc_23_S);
        dtmi_raw_7.Loc_24_X = swapHex(dtmi_raw_7.Loc_24_X);
        dtmi_raw_7.Loc_24_Y = swapHex(dtmi_raw_7.Loc_24_Y);
        dtmi_raw_7.Loc_24_B = swapHex(dtmi_raw_7.Loc_24_B);
        dtmi_raw_7.Loc_24_S = swapHex(dtmi_raw_7.Loc_24_S);
        dtmi_raw_7.Loc_25_X = swapHex(dtmi_raw_7.Loc_25_X);
        dtmi_raw_7.Loc_25_Y = swapHex(dtmi_raw_7.Loc_25_Y);
        dtmi_raw_7.Loc_25_B = swapHex(dtmi_raw_7.Loc_25_B);
        dtmi_raw_7.Loc_25_S = swapHex(dtmi_raw_7.Loc_25_S);
        dtmi_raw_7.Loc_26_X = swapHex(dtmi_raw_7.Loc_26_X);
        dtmi_raw_7.Loc_26_Y = swapHex(dtmi_raw_7.Loc_26_Y);
        dtmi_raw_7.Loc_26_B = swapHex(dtmi_raw_7.Loc_26_B);
        dtmi_raw_7.Loc_26_S = swapHex(dtmi_raw_7.Loc_26_S);
        dtmi_raw_7.Loc_27_X = swapHex(dtmi_raw_7.Loc_27_X);
        dtmi_raw_7.Loc_27_Y = swapHex(dtmi_raw_7.Loc_27_Y);
        dtmi_raw_7.Loc_27_B = swapHex(dtmi_raw_7.Loc_27_B);
        dtmi_raw_7.Loc_27_S = swapHex(dtmi_raw_7.Loc_27_S);
        memcpy(&m_kia_mko_struct->mLoc_7_mf,&dtmi_raw_7, sizeof(m_kia_mko_struct->mLoc_7_mf));
        break;
    case 7:
        memcpy(&dtmi_raw_8,&dataWord,sizeof(dtmi_raw_8));
        dtmi_raw_8.Loc_28_X = swapHex(dtmi_raw_8.Loc_28_X);
        dtmi_raw_8.Loc_28_Y = swapHex(dtmi_raw_8.Loc_28_Y);
        dtmi_raw_8.Loc_28_B = swapHex(dtmi_raw_8.Loc_28_B);
        dtmi_raw_8.Loc_28_S = swapHex(dtmi_raw_8.Loc_28_S);
        dtmi_raw_8.Loc_29_X = swapHex(dtmi_raw_8.Loc_29_X);
        dtmi_raw_8.Loc_29_Y = swapHex(dtmi_raw_8.Loc_29_Y);
        dtmi_raw_8.Loc_29_B = swapHex(dtmi_raw_8.Loc_29_B);
        dtmi_raw_8.Loc_29_S = swapHex(dtmi_raw_8.Loc_29_S);
        dtmi_raw_8.Loc_30_X = swapHex(dtmi_raw_8.Loc_30_X);
        dtmi_raw_8.Loc_30_Y = swapHex(dtmi_raw_8.Loc_30_Y);
        dtmi_raw_8.Loc_30_B = swapHex(dtmi_raw_8.Loc_30_B);
        dtmi_raw_8.Loc_30_S = swapHex(dtmi_raw_8.Loc_30_S);
        dtmi_raw_8.Loc_31_X = swapHex(dtmi_raw_8.Loc_31_X);
        dtmi_raw_8.Loc_31_Y = swapHex(dtmi_raw_8.Loc_31_Y);
        dtmi_raw_8.Loc_31_B = swapHex(dtmi_raw_8.Loc_31_B);
        dtmi_raw_8.Loc_31_S = swapHex(dtmi_raw_8.Loc_31_S);
        dtmi_raw_8.Loc_32_X = swapHex(dtmi_raw_8.Loc_32_X);
        memcpy(&m_kia_mko_struct->mLoc_8_mf, &dtmi_raw_8, sizeof(m_kia_mko_struct->mLoc_8_mf));
        break;
    case 8:
        memcpy(&dtmi_raw_9, &dataWord, sizeof(dtmi_raw_9));
        dtmi_raw_9.Loc_32_Y = swapHex(dtmi_raw_9.Loc_32_Y);
        dtmi_raw_9.Loc_32_B = swapHex(dtmi_raw_9.Loc_32_B);
        dtmi_raw_9.Loc_32_S = swapHex(dtmi_raw_9.Loc_32_S);
        dtmi_raw_9.Loc_33_X = swapHex(dtmi_raw_9.Loc_33_X);
        dtmi_raw_9.Loc_33_Y = swapHex(dtmi_raw_9.Loc_33_Y);
        dtmi_raw_9.Loc_33_B = swapHex(dtmi_raw_9.Loc_33_B);
        dtmi_raw_9.Loc_33_S = swapHex(dtmi_raw_9.Loc_33_S);
        dtmi_raw_9.Loc_34_X = swapHex(dtmi_raw_9.Loc_34_X);
        dtmi_raw_9.Loc_34_Y = swapHex(dtmi_raw_9.Loc_34_Y);
        dtmi_raw_9.Loc_34_B = swapHex(dtmi_raw_9.Loc_34_B);
        dtmi_raw_9.Loc_34_S = swapHex(dtmi_raw_9.Loc_34_S);
        dtmi_raw_9.Loc_35_X = swapHex(dtmi_raw_9.Loc_35_X);
        dtmi_raw_9.Loc_35_Y = swapHex(dtmi_raw_9.Loc_35_Y);
        dtmi_raw_9.Loc_35_B = swapHex(dtmi_raw_9.Loc_35_B);
        dtmi_raw_9.Loc_35_S = swapHex(dtmi_raw_9.Loc_35_S);
        memcpy(&m_kia_mko_struct->mLoc_9_mf, &dtmi_raw_9, sizeof(m_kia_mko_struct->mLoc_9_mf));
        break;
    }

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Номер подмассива");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.nAr, 16), 4, '0'));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Контрольная сумма");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.cs, 16), 4, '0'));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.T));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.Tms));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Заводской номер");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.SerNum));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время экспонирования");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.Texp));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Количество локализованных объектов");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.NumLoc));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.NumObj));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Число пикселей на кадре");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.PixCount));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Среднее сигнала");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.Mean));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "СКО сигнала");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_1_mf.Sigma));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                                          + helpers::format_qstring("X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("B", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("S", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back("");

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.Loc_0_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.Loc_0_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.Loc_0_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.Loc_0_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.Loc_2_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_1_mf.Loc_2_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_2_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_2_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_3_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_4_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_4_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_4_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_4_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_5_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_5_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_5_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_5_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_6_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_6_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_2_mf.Loc_6_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_6_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_7_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_7_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_7_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_7_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_8_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_8_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_8_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_8_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_9_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_9_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_9_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_9_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_10_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_10_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_10_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_3_mf.Loc_10_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_11_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_11_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_11_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_11_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_12_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_12_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_12_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_12_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_13_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_13_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_13_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_13_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_14_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_14_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_14_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_14_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_4_mf.Loc_15_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_15_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_15_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_15_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_16_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_16_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_16_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_16_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_17_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_17_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_17_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_17_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_18_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_18_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_18_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_18_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_19_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_5_mf.Loc_19_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_19_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_19_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_20_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_20_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_20_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_20_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_21_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_21_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_21_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_21_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_22_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_22_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_22_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_22_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_23_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_23_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_6_mf.Loc_23_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_23_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_24_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_24_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_24_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_24_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_25_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_25_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_25_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_25_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("27", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_26_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_26_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_26_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_26_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_27_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_27_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_27_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_7_mf.Loc_27_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("29", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_28_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_28_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_28_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_28_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_29_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_29_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_29_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_29_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_30_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_30_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_30_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_30_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_31_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_31_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_31_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_31_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("33", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_8_mf.Loc_32_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_32_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_32_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_32_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("34", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_33_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_33_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_33_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_33_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("35", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_34_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_34_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_34_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_34_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("36", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_35_X, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_35_Y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_35_B, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->mLoc_9_mf.Loc_35_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Число пикселей для расчета порога");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_9_mf.nPixNs));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("29", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Число пикселей выше порога шума");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_9_mf.nPixGrNs));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Порог");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_9_mf.Th));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Температура КМОП матрицы");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(QString::number(m_kia_mko_struct->mLoc_9_mf.Tcmv));
}

void Pio_bokzmf::decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.clear();
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.clear();
    DTMIRaw_1_MF dtmiRaw_1;
    DTMIRaw_2_3_4_5_6_7_MF dtmiRaw_2_3_4_5_6_7;
    DTMIRaw_8_MF dtmiRaw_8;
    DTMIRaw_9_MF dtmiRaw_9;
    DTMIRaw_10_MF dtmiRaw_10;
    DTMIRaw_11_MF dtmiRaw_11;
    DTMIRaw_12_MF dtmiRaw_12;
    switch (count)
    {
    case 0:
        memcpy(&dtmiRaw_1,&dataWord,sizeof(dtmiRaw_1));
        dtmiRaw_1.T = swapHex(dtmiRaw_1.T);
        dtmiRaw_1.Tlast = swapHex(dtmiRaw_1.Tlast);
        memcpy(&m_kia_mko_struct->dtmi_1_mf, &dtmiRaw_1, sizeof(m_kia_mko_struct->dtmi_1_mf));
        m_kia_mko_struct->dtmi_1_mf.Qlst_0 = helpers::uint32_to_float(swapHex(dtmiRaw_1.Qlst_0));
        m_kia_mko_struct->dtmi_1_mf.Qlst_1 = helpers::uint32_to_float(swapHex(dtmiRaw_1.Qlst_1));
        m_kia_mko_struct->dtmi_1_mf.Qlst_2 = helpers::uint32_to_float(swapHex(dtmiRaw_1.Qlst_2));
        m_kia_mko_struct->dtmi_1_mf.Qlst_3 = helpers::uint32_to_float(swapHex(dtmiRaw_1.Qlst_3));
        break;
    case 1:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->dtmi_2_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->dtmi_2_mf));
        break;
    case 2:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->dtmi_3_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->dtmi_3_mf));
        break;
    case 3:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->dtmi_4_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->dtmi_4_mf));
        break;
    case 4:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->dtmi_5_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->dtmi_5_mf));
        break;
    case 5:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->dtmi_6_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->dtmi_6_mf));
        break;
    case 6:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->dtmi_7_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->dtmi_7));
        break;
    case 7:
        memcpy(&dtmiRaw_8, &dataWord, sizeof(dtmiRaw_8));
        memcpy(&m_kia_mko_struct->dtmi_8_mf, &dtmiRaw_8, sizeof(m_kia_mko_struct->dtmi_8_mf));
        break;
    case 8:
        memcpy(&dtmiRaw_9,&dataWord,sizeof(dtmiRaw_9));
        memcpy(&m_kia_mko_struct->dtmi_9_mf, &dtmiRaw_9, sizeof(m_kia_mko_struct->dtmi_9_mf));
        break;
    case 9:
        memcpy(&dtmiRaw_10,&dataWord,sizeof(dtmiRaw_10));
        memcpy(&m_kia_mko_struct->dtmi_10_mf, &dtmiRaw_10, sizeof(m_kia_mko_struct->dtmi_10_mf));
        break;
        break;
    case 10:
        memcpy(&dtmiRaw_11,&dataWord, sizeof(dtmiRaw_11));
        memcpy(&m_kia_mko_struct->dtmi_11_mf, &dtmiRaw_11, sizeof(m_kia_mko_struct->dtmi_11_mf));
        break;
    case 11:
        memcpy(&dtmiRaw_12,&dataWord,sizeof(dtmiRaw_12));
        dtmiRaw_12.Epoch = swapHex(dtmiRaw_12.Epoch);
        memcpy(&m_kia_mko_struct->dtmi_12_mf, &dtmiRaw_12, sizeof(m_kia_mko_struct->dtmi_12_mf));
        break;
    }

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Номер подмассива");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.nAr, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_12_mf.nAr, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Контрольная сумма");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.cs, 16), 4, '0') +
                                                          " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_12_mf.cs, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.T));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Tms));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1_mf.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1_mf.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Заводской номер");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.SerNum));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Слово внутреннего теста");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.POST));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Температура КМОП-матрицы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Tcmv));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Среднее сигнала");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Mean));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "СКО сигнала");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Tcmv));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время экспонирования");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Texp));

    QString dtmi_1_wd_num_13 = "Число пикселей выше порог в НО/ТО";
    dtmi_1_wd_num_13 = "Число локализованных объектов в слежении";
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + dtmi_1_wd_num_13);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.PixCount_NumLoc));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("14[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.NumStore));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("14[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Количество распознанных объектов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.NumDet));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("15[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Количество прогнозируемых фрагментов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.NumProgFrag));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("15[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Количество фрагментов в обработке");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.NumFrag));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("16,17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время последнего кватерниона");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Tlast));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + "Время последнего кватерниона");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Tmslast));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("19,20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Последний кватернион ориентации, Qo0");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Qlst_0,'f',4));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("21,22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Последний кватернион ориентации, Qo1");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Qlst_1,'f',4));


    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Qlst_2,'f',4));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("23,24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Последний  кватернион ориентации, Qo2");

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("25,26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Последний кватернион ориентации, Qo3");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1_mf.Qlst_3,'f',4));


    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                                          + helpers::format_qstring("Первый кадр", m_kia_settings->m_format_for_desc->shift_for_dtmi * 4)
                                                          + helpers::format_qstring("Второй кадр", m_kia_settings->m_format_for_desc->shift_for_dtmi * 4));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back("");

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                                          + helpers::format_qstring("X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("B", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("S", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("B", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("S", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back("");

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_0_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_0_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_0_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_0_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_0_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_0_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_0_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_0_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_1_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_1_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_1_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_1_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_1_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_1_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_1_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_1_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_2_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_2_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_2_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_2_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_2_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_2_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_2_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_2_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_3_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_3_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_3_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_3_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_3_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_3_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_3_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_3_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_4_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_4_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2_mf.RsLoc_4_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_4_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_4_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_4_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5_mf.RsLoc_4_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_4_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_5_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_5_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_5_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_5_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_5_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_5_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_5_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_5_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_6_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_6_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_6_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_6_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_6_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_6_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_6_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_6_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_7_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_7_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_7_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_7_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_7_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_7_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_7_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_7_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_8_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_8_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_8_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_8_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_8_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_8_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_8_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_8_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_9_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_9_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3_mf.RsLoc_9_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_9_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_9_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_9_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6_mf.RsLoc_9_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_9_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_10_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_10_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_10_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_10_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_10_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_10_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_10_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_10_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_11_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_11_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_11_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_11_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_11_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_11_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_11_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_11_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_12_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_12_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_12_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_12_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_12_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_12_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_12_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_12_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_13_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_13_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_13_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_13_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_13_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_13_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_13_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_13_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_14_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_14_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4_mf.RsLoc_14_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T0_14_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_14_x, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_14_y, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7_mf.RsLoc_14_b, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8_mf.RsLoc_T1_14_S, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back("\n");

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back("");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                                          + helpers::format_qstring("Xc", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("Yc", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("MeanFrag_X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("MeanFrag_Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("ThFrag", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("ObjFrag", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("MultXY", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("Zip_X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                          + helpers::format_qstring("Zip_Y", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back("");

    auto ObjFrag_0_1_2_3 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ObjFrag_0_1_2_3);
    auto MultXY_0_1_2_3 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.MultXY_0_1_2_3);
    auto ZipXY_0_1 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ZipXY_0_0_0_1_1_0_1_1);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_0_1_2_3[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_0_1_2_3[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_0_1[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_0_1[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_1_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_1_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_1_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_1_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_0_1_2_3[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_0_1_2_3[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_0_1[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_0_1[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    auto ZipXY_2_3 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ZipXY_2_0_2_1_3_0_3_1);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_2_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_2_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_2_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_2_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_0_1_2_3[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_0_1_2_3[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_2_3[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_2_3[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_3_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_3_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_3_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_3_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_0_1_2_3[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_0_1_2_3[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_2_3[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_2_3[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    auto ObjFrag_4_5_6_7 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ObjFrag_4_5_6_7);
    auto MultXY_4_5_6_7 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.MultXY_4_5_6_7);
    auto ZipXY_4_5 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ZipXY_4_0_4_1_5_0_5_1);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_4_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_4_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_4_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_4_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_4_5_6_7[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_4_5_6_7[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_4_5[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_4_5[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_5_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_5_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_5_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_5_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_5, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_4_5_6_7[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_4_5_6_7[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_4_5[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_4_5[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    auto ZipXY_6_7 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ZipXY_6_0_6_0_7_0_7_1);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_6_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_6_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_6_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_6_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_4_5_6_7[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_4_5_6_7[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_6_7[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_6_7[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_7_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_7_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_7_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_7_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_7, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_4_5_6_7[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_4_5_6_7[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_6_7[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_6_7[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    auto ObjFrag_8_9_10_11 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ObjFrag_8_9_10_11);
    auto MultXY_8_9_10_11 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.MultXY_8_9_10_11);
    auto ZipXY_8_9 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ZipXY_8_0_8_0_9_0_9_1);

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_8_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_8_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_8_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_8_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_8_9_10_11[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_8_9_10_11[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_8_9[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_8_9[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_9_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_9_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_9_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_9_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_9, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_8_9_10_11[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_8_9_10_11[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_8_9[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_8_9[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    auto ZipXY_10_11 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ZipXY_10_0_10_0_11_0_11_1);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_10_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_10_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_10_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_10_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_8_9_10_11[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_8_9_10_11[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_10_11[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_10_11[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_11_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_11_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_11_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_11_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_11, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_8_9_10_11[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_0_1_2_3[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_10_11[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_10_11[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    auto ObjFrag_12_13_14_Xh = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ObjFrag_12_13_14_Xh);
    auto MultXY_12_13_14_Xh = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.MultXY_12_13_14_Xh);
    auto ZipXY_12_13 = split_data_from_word(m_kia_mko_struct->dtmi_11_mf.ZipXY_12_0_12_0_13_0_13_1);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_12_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_12_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_12_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_12_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_12_13_14_Xh[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_12_13_14_Xh[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_12_13[0], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_12_13[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_13_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_13_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_13_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_13_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_13, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_12_13_14_Xh[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_12_13_14_Xh[1], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_12_13[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(ZipXY_12_13[3], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_14_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9_mf.XYc_14_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_14_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_10_mf.Mean_14_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_11_mf.ThFrag_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(ObjFrag_12_13_14_Xh[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring(QString("%1").arg(QString::number(MultXY_12_13_14_Xh[2], 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring("---", m_kia_settings->m_format_for_desc->shift_for_dtmi) +
            helpers::format_qstring("---", m_kia_settings->m_format_for_desc->shift_for_dtmi)
            );
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Линейная скорость ось X, Vx");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Vx));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Линейная скорость ось Y, Vy");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Vy));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Линейная скорость ось Z, Vz");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Vz));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Угловая скорость ось X, Wx");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Wx));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Угловая скорость ось Y, Wy");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Wy));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Угловая скорость ось Z, Wz");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Wz));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("16, 17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Эпоха");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Epoch));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("18[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Кол-во локализованных объектов на 1-ом кадре в ОО");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.NumL_0));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("18[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Кол-во локализованных объектов на 2-ом кадре в ОО");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.NumL_1));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Максимум гистограммы смещения объектов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.maxH));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("20[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Смещение по оси X максимума гистограммы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.dxmaxH));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("20[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Смещение по оси Y максимума гистограммы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.dymaxH));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("21[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Номер сектора");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.NumSec));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("21[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Допуск распознавания");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.Epsilon));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Интервал времени");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.deltaT));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "СКО решения системы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.m_cur));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Гистограмма яркостей");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back("");

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_0));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_1));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_2));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_3));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_4));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_5));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_6));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_7));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_8));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_9));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_10));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_11));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_12));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_13));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_14));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_12_mf.HistPix_15));
}

void Pio_bokzmf::dtmi_2_3_4_5_6_7_converter(DTMIRaw_2_3_4_5_6_7_MF &dtmiRaw_2_3_4_5_6_7)
{
    dtmiRaw_2_3_4_5_6_7.RsLoc_0_x = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_0_x);
    dtmiRaw_2_3_4_5_6_7.RsLoc_0_y = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_0_y);
    dtmiRaw_2_3_4_5_6_7.RsLoc_0_b = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_0_b);
    dtmiRaw_2_3_4_5_6_7.RsLoc_1_x = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_1_x);
    dtmiRaw_2_3_4_5_6_7.RsLoc_1_y = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_1_y);
    dtmiRaw_2_3_4_5_6_7.RsLoc_1_b = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_1_b);
    dtmiRaw_2_3_4_5_6_7.RsLoc_2_x = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_2_x);
    dtmiRaw_2_3_4_5_6_7.RsLoc_2_y = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_2_y);
    dtmiRaw_2_3_4_5_6_7.RsLoc_2_b = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_2_b);
    dtmiRaw_2_3_4_5_6_7.RsLoc_3_x = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_3_x);
    dtmiRaw_2_3_4_5_6_7.RsLoc_3_y = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_3_y);
    dtmiRaw_2_3_4_5_6_7.RsLoc_3_b = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_3_b);
    dtmiRaw_2_3_4_5_6_7.RsLoc_4_x = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_4_x);
    dtmiRaw_2_3_4_5_6_7.RsLoc_4_y = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_4_y);
    dtmiRaw_2_3_4_5_6_7.RsLoc_4_b = swapHex(dtmiRaw_2_3_4_5_6_7.RsLoc_4_b);
}

std::array<uint16_t, max_el_in_to_word> Pio_bokzmf::split_data_from_word(uint16_t data)
{
    std::array<uint16_t, max_el_in_to_word> ret_arr;
    for (uint16_t ind_shift = 0; ind_shift < max_el_in_to_word; ind_shift++)
    {
        ret_arr[ind_shift] = ((data >> (4 * ind_shift)) & 0x000f);
    }
    return ret_arr;
}
void Pio_bokzmf::decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord)
{
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.clear();
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.clear();
    SHTMI1raw_MF shmti1_raw;
    memcpy(&shmti1_raw, &dataWord,sizeof(shmti1_raw));
    m_kia_mko_struct->st_shtmi1_mf.nAr = shmti1_raw.nAr;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Номер подмассива");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.nAr, 16), 4, '0'));


    m_kia_mko_struct->st_shtmi1_mf.T = swapHex(shmti1_raw.T);
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.T));

    m_kia_mko_struct->st_shtmi1_mf.T = shmti1_raw.Tms;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Tms));

    m_kia_mko_struct->st_shtmi1_mf.KC1 = shmti1_raw.KC1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi1_mf.KC2 = shmti1_raw.KC2;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi1_mf.SerNum = shmti1_raw.SerNum;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Заводской номер");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.T));

    m_kia_mko_struct->st_shtmi1_mf.POST = shmti1_raw.POST;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.POST, 16), 4, '0'));

    uint32_t foc = swapHex(shmti1_raw.Foc);
    memcpy(&m_kia_mko_struct->st_shtmi1_mf.Foc, &foc, sizeof(m_kia_mko_struct->st_shtmi1_mf.Foc));
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("9, 10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Фокусное расстояние");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Foc, 'f', 4));

    m_kia_mko_struct->st_shtmi1_mf.Xo = swapHex(shmti1_raw.Xo);
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("11, 12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Координата Xo гл. точки ВСК");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Xo));

    m_kia_mko_struct->st_shtmi1_mf.Yo = swapHex(shmti1_raw.Yo);
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("13, 14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Координата Yo гл. точки ВСК");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Yo));

    m_kia_mko_struct->st_shtmi1_mf.Texp = shmti1_raw.Texp;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время экспонирования");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Texp));

    m_kia_mko_struct->st_shtmi1_mf.Mean = shmti1_raw.Mean;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Среднее значение синала");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Mean));

    m_kia_mko_struct->st_shtmi1_mf.Sigma = shmti1_raw.Sigma;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "СКО сигнала");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Sigma));


    m_kia_mko_struct->st_shtmi1_mf.rezerv1 = shmti1_raw.rezerv1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Резерв");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.rezerv1));

    m_kia_mko_struct->st_shtmi1_mf.rezerv2 = shmti1_raw.rezerv2;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Резерв");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.rezerv2));

    m_kia_mko_struct->st_shtmi1_mf.cntUPN = shmti1_raw.cntUPN;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик КС УПН");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.cntUPN));

    m_kia_mko_struct->st_shtmi1_mf.Tcmv = shmti1_raw.Tcmv;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Температура КМОП-матрицы");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Tcmv));

    m_kia_mko_struct->st_shtmi1_mf.ConfCS = shmti1_raw.ConfCS;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма конфигурации ПЛИС");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ConfCS));

    m_kia_mko_struct->st_shtmi1_mf.desc = shmti1_raw.desc;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Дескриптор передачи данных");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.desc));

    m_kia_mko_struct->st_shtmi1_mf.ogConstCrc = shmti1_raw.ogConstCrc;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма констант ЭО ЗД");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ogConstCrc));

    m_kia_mko_struct->st_shtmi1_mf.CatCS0 = shmti1_raw.CatCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма каталога 0");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.CatCS0));

    m_kia_mko_struct->st_shtmi1_mf.CatCS1 = shmti1_raw.CatCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма каталога 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.CatCS1));

    m_kia_mko_struct->st_shtmi1_mf.ConstCS0 = shmti1_raw.ConstCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("27", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма констант 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ConstCS0));

    m_kia_mko_struct->st_shtmi1_mf.ConstCS1 = shmti1_raw.ConstCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма констант 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ConstCS1));

    m_kia_mko_struct->st_shtmi1_mf.ProgCS0 = shmti1_raw.ProgCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("29", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма программы 0");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ProgCS0));

    m_kia_mko_struct->st_shtmi1_mf.ProgCS1 = shmti1_raw.ProgCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма программы 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ProgCS1));

    m_kia_mko_struct->st_shtmi1_mf.Ver1 = (shmti1_raw.Ver >> 12);
    m_kia_mko_struct->st_shtmi1_mf.Ver2 = ((shmti1_raw.Ver & 0x0fff) >> 8);
    m_kia_mko_struct->st_shtmi1_mf.Ver3 = ((shmti1_raw.Ver & 0x00ff));
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Номер версии программы");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver1)
                                                              + "." + QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver2)
                                                              + "." + QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver3));

    m_kia_mko_struct->st_shtmi1_mf.cs = shmti1_raw.cs;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрольная сумма");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.cs));
}

void Pio_bokzmf::decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord)
{
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.clear();
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.clear();
    SHTMI2raw_MF shtmi2_raw;
    memcpy(&shtmi2_raw,&dataWord,sizeof(shtmi2_raw));
    m_kia_mko_struct->st_shtmi2_mf.nAr = shtmi2_raw.nAr;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Служебное слово 1");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.nAr, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi2_mf.T = swapHex(shtmi2_raw.T);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.T));

    m_kia_mko_struct->st_shtmi2_mf.Tms = swapHex(shtmi2_raw.Tms);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Tms));

    m_kia_mko_struct->st_shtmi2_mf.KC1 = shtmi2_raw.KC1;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi2_mf.KC2 = shtmi2_raw.KC2;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.KC2, 16), 4, '0'));


    m_kia_mko_struct->st_shtmi2_mf.SerNum = shtmi2_raw.SerNum;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Заводской номер");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.SerNum));

    m_kia_mko_struct->st_shtmi2_mf.POST = shtmi2_raw.POST;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.POST, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi2_mf.Texp = shtmi2_raw.Texp;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время экспонирования");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Texp));

    m_kia_mko_struct->st_shtmi2_mf.Nusd = shtmi2_raw.Nusd;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик полученных УСД");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nusd));

    m_kia_mko_struct->st_shtmi2_mf.Nno = shtmi2_raw.Nno;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик НО");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nno));

    m_kia_mko_struct->st_shtmi2_mf.Nnosl = shtmi2_raw.Nnosl;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Число переходов от НО к слежению");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nnosl));

    m_kia_mko_struct->st_shtmi2_mf.Nto = shtmi2_raw.Nto;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик ТО");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nto));

    m_kia_mko_struct->st_shtmi2_mf.Ntosl = shtmi2_raw.Ntosl;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Число переходов от ТО к слежению");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Ntosl));

    m_kia_mko_struct->st_shtmi2_mf.Nsl = swapHex(shtmi2_raw.Nsl);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("15, 16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик слежения");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nsl));

    m_kia_mko_struct->st_shtmi2_mf.eCount1 = swapHex(shtmi2_raw.eCount1);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 01)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount1));

    m_kia_mko_struct->st_shtmi2_mf.eCount2 = swapHex(shtmi2_raw.eCount2);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 02)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount2));

    m_kia_mko_struct->st_shtmi2_mf.eCount3 = swapHex(shtmi2_raw.eCount3);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 03)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount3));

    m_kia_mko_struct->st_shtmi2_mf.eCount4 = swapHex(shtmi2_raw.eCount4);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 04)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount4));

    m_kia_mko_struct->st_shtmi2_mf.eCount5 = swapHex(shtmi2_raw.eCount5);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 05)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount5));

    m_kia_mko_struct->st_shtmi2_mf.eCount6 = swapHex(shtmi2_raw.eCount6);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 06, 07)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount6));

    m_kia_mko_struct->st_shtmi2_mf.eCount7 = swapHex(shtmi2_raw.eCount7);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 08, 0A)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount7));

    m_kia_mko_struct->st_shtmi2_mf.eCount8 = swapHex(shtmi2_raw.eCount8);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 09, 0B)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount8));

    m_kia_mko_struct->st_shtmi2_mf.eCount9 = swapHex(shtmi2_raw.eCount9);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 0C)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount9));

    m_kia_mko_struct->st_shtmi2_mf.eCount10 = swapHex(shtmi2_raw.eCount10);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 0D)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount10));

    m_kia_mko_struct->st_shtmi2_mf.eCount11 = swapHex(shtmi2_raw.eCount11);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("27[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код XE)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount11));

    m_kia_mko_struct->st_shtmi2_mf.eCount12 = swapHex(shtmi2_raw.eCount12);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("27[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код XF)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount12));

    m_kia_mko_struct->st_shtmi2_mf.eCount13 = swapHex(shtmi2_raw.eCount13);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("28[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 81, 82)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount13));

    m_kia_mko_struct->st_shtmi2_mf.eCount14 = swapHex(shtmi2_raw.eCount14);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("28[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 83, 84, 86)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount14));

    m_kia_mko_struct->st_shtmi2_mf.eCount15 = swapHex(shtmi2_raw.eCount15);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("29[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик сбоев внутренней памяти");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount15));

    m_kia_mko_struct->st_shtmi2_mf.eCount16 = swapHex(shtmi2_raw.eCount16);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("29[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик сбоев внешней памяти");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount16));

    m_kia_mko_struct->st_shtmi2_mf.eCount17 = swapHex(shtmi2_raw.eCount17);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик ошибок регистров датчика изображений");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount17));

    m_kia_mko_struct->st_shtmi2_mf.eCount18 = swapHex(shtmi2_raw.eCount18);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("31[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик записей протокола событий");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount18));

    m_kia_mko_struct->st_shtmi2_mf.eCount19 = swapHex(shtmi2_raw.eCount19);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("31[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Счетчик горячих рестартов");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount19));

    m_kia_mko_struct->st_shtmi2_mf.cs = swapHex(shtmi2_raw.cs);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Контрльная сумма");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2_mf.cs));
}

void Pio_bokzmf::decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t &bshv)
{
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.clear();
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.clear();
    MSHIORRaw_MF mshiorRaw;
    memcpy(&mshiorRaw,&dataWord,sizeof(mshiorRaw));
    m_kia_mko_struct->st_mshior_mf.KC1 = mshiorRaw.KC1;
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior_mf.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_mshior_mf.KC2 = mshiorRaw.KC2;
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior_mf.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_mshior_mf.T = swapHex(mshiorRaw.T);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.T) + " (" + QString::number((int)(bshv - m_kia_mko_struct->st_mshior_mf.T)) +  ")");
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время привязки информации");

    m_kia_mko_struct->st_mshior_mf.Tms = swapHex(mshiorRaw.Tms);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Tms));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Время привязки информации");

    m_kia_mko_struct->st_mshior_mf.Qo0 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo0));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Qo0,'f',4));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("6,7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Кватернион ориентации, Qo0");

    m_kia_mko_struct->st_mshior_mf.Qo1 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Qo1,'f',4));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("8,9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Кватернион ориентации, Qo1");

    m_kia_mko_struct->st_mshior_mf.Qo2 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo2));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Qo2,'f',4));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("10,11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Кватернион ориентации, Qo2");

    m_kia_mko_struct->st_mshior_mf.Qo3 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo3));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Qo3,'f',4));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("12,13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Кватернион ориентации, Qo3");

    m_kia_mko_struct->st_mshior_mf.wox = helpers::uint32_to_float(swapHex(mshiorRaw.wox)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.wox,'f',4));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("14,15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Угловая скорость по оптическим измерениям, Wox");

    m_kia_mko_struct->st_mshior_mf.woy = helpers::uint32_to_float(swapHex(mshiorRaw.woy)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("16,17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Угловая скорость по оптическим измерениям, Woy");
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.woy,'f',4));

    m_kia_mko_struct->st_mshior_mf.woz = helpers::uint32_to_float(swapHex(mshiorRaw.woz)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.woz,'f',4));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("18,19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Угловая скорость по оптическим измерениям, Woz");

    m_kia_mko_struct->st_mshior_mf.Tcmv = swapHex(mshiorRaw.Tcmv);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Tcmv));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Температура КМОП-матрицы");

    m_kia_mko_struct->st_mshior_mf.NumFrag = swapHex(mshiorRaw.NumFrag);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.NumFrag));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("21[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Число выбранных фрагментов");

    m_kia_mko_struct->st_mshior_mf.NumLoc_0 = swapHex(mshiorRaw.NumLoc_0);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.NumLoc_0));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("21[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Число локализованных объектов");

    m_kia_mko_struct->st_mshior_mf.NumDet = swapHex(mshiorRaw.NumDet);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.NumDet));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("22[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Число распознанных объектов");

    m_kia_mko_struct->st_mshior_mf.LightMv5 = swapHex(mshiorRaw.LightMv5);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.LightMv5));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("22[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Средняя яркость 5 звездной величины");

    m_kia_mko_struct->st_mshior_mf.Mean = swapHex(mshiorRaw.Mean);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Mean));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Среднее сигнала");

    m_kia_mko_struct->st_mshior_mf.Sigma = swapHex(mshiorRaw.Sigma);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.Sigma));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "СКО сигнала");

    m_kia_mko_struct->st_mshior_mf.ThMax = swapHex(mshiorRaw.ThMax);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.ThMax));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Максимальный порог на исходных фрагментах");

    m_kia_mko_struct->st_mshior_mf.m_cur = swapHex(mshiorRaw.m_cur);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.m_cur));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "СКО решения системы");

    m_kia_mko_struct->st_mshior_mf.P = swapHex(mshiorRaw.P);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.P));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("27", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Процент заполнения поля зрения при калибровке");

    m_kia_mko_struct->st_mshior_mf.dpf_state = swapHex(mshiorRaw.dpf_state);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_state));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Код состояния дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_total = swapHex(mshiorRaw.dpf_total);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_total));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("29[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Количество отобранных дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_hotpixels = swapHex(mshiorRaw.dpf_hotpixels);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_hotpixels));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("29[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Количество подтвержденных дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_updated = swapHex(mshiorRaw.dpf_updated);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_updated));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("30[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Количество обновленных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_rejected = swapHex(mshiorRaw.dpf_rejected);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_rejected));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("30[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Количество отклонных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_threshold = swapHex(mshiorRaw.dpf_threshold);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_threshold));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("31[7:0]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Порог накопления дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_applied = swapHex(mshiorRaw.dpf_applied);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_applied));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("31[15:8]", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Количество скорректированных пикселей");

    m_kia_mko_struct->st_mshior_mf.ser_num = swapHex(mshiorRaw.ser_num);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior_mf.ser_num));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                              + "Заводской номер");

    m_kia_settings->m_data_for_db->m_norm_qaor = sqrt(pow(m_kia_mko_struct->st_mshior_mf.Qo0,2) + pow(m_kia_mko_struct->st_mshior_mf.Qo1,2) + pow(m_kia_mko_struct->st_mshior_mf.Qo2, 2)  + pow(m_kia_mko_struct->st_mshior_mf.Qo3,2));
}

Pio_bokzmf::~Pio_bokzmf()
{

}


template<typename T>
T Pio_bokzmf::swapHex(T value)
{
    value = ((value & 0x0000ffff) << 16) | (value >> 16);
    return value;
}
