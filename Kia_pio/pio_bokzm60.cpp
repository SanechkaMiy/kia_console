#include "pio_bokzm60.h"

Pio_bokzm60::Pio_bokzm60(std::shared_ptr<Kia_mko_struct> kia_mko_struct, std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_mko_struct(kia_mko_struct),
    m_kia_settings(kia_settings)
{

}

void Pio_bokzm60::decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.clear();
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.clear();
    DTMILocRaw_1 dtmi_raw_1;
    DTMILocRaw_2_3_4_5_6_7_8 dtmi_loc_raw_2_3_4_5_6_7_8;
    DTMILocRaw_9 dtmi_raw_9;
    switch (count)
    {
    case 0:
        memcpy(&dtmi_raw_1,&dataWord,sizeof(dtmi_raw_1));
        dtmi_raw_1.CC1 = dtmi_raw_1.CC1;
        dtmi_raw_1.CC2 = dtmi_raw_1.CC2;
        dtmi_raw_1.T = swapHex(dtmi_raw_1.T);
        dtmi_raw_1.KC1 = dtmi_raw_1.KC1;
        dtmi_raw_1.KC2 = dtmi_raw_1.KC2;
        dtmi_raw_1.SerNum = dtmi_raw_1.SerNum;
        dtmi_raw_1.Texp = dtmi_raw_1.Texp;
        dtmi_raw_1.NumLoc = dtmi_raw_1.NumLoc;
        dtmi_raw_1.NumObj = dtmi_raw_1.NumObj;
        dtmi_raw_1.Mean = swapHex(dtmi_raw_1.Mean);
        dtmi_raw_1.Sigma = swapHex(dtmi_raw_1.Sigma);
        dtmi_raw_1.Loc_0_0 = swapHex(dtmi_raw_1.Loc_0_0);
        dtmi_raw_1.Loc_0_1 = swapHex(dtmi_raw_1.Loc_0_1);
        dtmi_raw_1.Loc_0_2 = swapHex(dtmi_raw_1.Loc_0_2);
        dtmi_raw_1.Loc_0_3 = swapHex(dtmi_raw_1.Loc_0_3);
        dtmi_raw_1.Loc_1_0 = swapHex(dtmi_raw_1.Loc_1_0);
        dtmi_raw_1.Loc_1_1 = swapHex(dtmi_raw_1.Loc_1_1);
        dtmi_raw_1.Loc_1_2 = swapHex(dtmi_raw_1.Loc_1_2);
        dtmi_raw_1.Loc_1_3 = swapHex(dtmi_raw_1.Loc_1_3);
        dtmi_raw_1.Loc_2_0 = swapHex(dtmi_raw_1.Loc_2_0);
        memcpy(&m_kia_mko_struct->dtmiLoc_1, &dtmi_raw_1, sizeof(m_kia_mko_struct->dtmiLoc_1));
        break;
    case 1:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->dtmiLoc_2, &dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(m_kia_mko_struct->dtmiLoc_2));
        break;
    case 2:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->dtmiLoc_3, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->dtmiLoc_3));
        break;
    case 3:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->dtmiLoc_4, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->dtmiLoc_4));
        break;
    case 4:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->dtmiLoc_5, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->dtmiLoc_5));
        break;
    case 5:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->dtmiLoc_6, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->dtmiLoc_6));
        break;
    case 6:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->dtmiLoc_7,&dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->dtmiLoc_7));
        break;
    case 7:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->dtmiLoc_8, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->dtmiLoc_8));
        break;
    case 8:
        memcpy(&dtmi_raw_9,&dataWord,sizeof(dtmi_raw_9));
        dtmi_raw_9.CC1 = dtmi_raw_9.CC1;
        dtmi_raw_9.CC2 = dtmi_raw_9.CC2;
        dtmi_raw_9.Loc_3_4 = swapHex(dtmi_raw_9.Loc_3_4);
        dtmi_raw_9.Loc_5_6 = swapHex(dtmi_raw_9.Loc_5_6);
        dtmi_raw_9.Loc_7_8 = swapHex(dtmi_raw_9.Loc_7_8);
        dtmi_raw_9.Loc_9_10 = swapHex(dtmi_raw_9.Loc_9_10);
        dtmi_raw_9.Loc_11_12 = swapHex(dtmi_raw_9.Loc_11_12);
        dtmi_raw_9.Loc_13_14 = swapHex(dtmi_raw_9.Loc_13_14);
        dtmi_raw_9.Loc_15_16 = swapHex(dtmi_raw_9.Loc_15_16);
        dtmi_raw_9.Loc_17_18 = swapHex(dtmi_raw_9.Loc_17_18);
        dtmi_raw_9.Loc_19_20 = swapHex(dtmi_raw_9.Loc_19_20);
        dtmi_raw_9.Loc_21_22 = swapHex(dtmi_raw_9.Loc_21_22);
        dtmi_raw_9.Loc_23_24 = swapHex(dtmi_raw_9.Loc_23_24);
        dtmi_raw_9.Loc_25_26 = swapHex(dtmi_raw_9.Loc_25_26);
        dtmi_raw_9.Loc_27_28 = swapHex(dtmi_raw_9.Loc_27_28);
        dtmi_raw_9.Loc_29_30 = swapHex(dtmi_raw_9.Loc_29_30);
        dtmi_raw_9.rezerv = dtmi_raw_9.rezerv;
        memcpy(&m_kia_mko_struct->dtmiLoc_9, &dtmi_raw_9, sizeof(m_kia_mko_struct->dtmiLoc_9));
        break;
    }


    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Служебное слово 1");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.CC1, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.CC1, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Служебное слово 2");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.CC2, 16), 4, '0') +
                                                               " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.CC2, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Время привязки информации");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_1.T));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Сериальный номер");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_1.SerNum));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Время экспонирования");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_1.Texp));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Количество локализованных объектов");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_1.NumLoc));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_1.NumObj));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("11, 12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Среднее значение сигнала");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_1.Mean));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("13, 14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "СКО сигнала");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_1.Sigma));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                                               + helpers::format_qstring("X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                               + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                               + helpers::format_qstring("B", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                                               + helpers::format_qstring("C", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back("");

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                          + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_0_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_0_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                          + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_1_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_1_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_1_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_1_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                          + " ");

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_1.Loc_2_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_2.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_3.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_4.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_5.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_6.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_7.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("27", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("29", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_8.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmiLoc_9.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                                               + "Резерв");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(QString::number(m_kia_mko_struct->dtmiLoc_9.rezerv));
}

void Pio_bokzm60::decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{
    m_kia_mko_struct->st_dtmi.dtmi_list_data.clear();
    m_kia_mko_struct->st_dtmi.dtmi_list_name.clear();
    DTMIRaw_1 dtmiRaw_1;
    DTMIRaw_2_3_4 dtmiRaw_2_3_4;
    DTMIRaw_5 dtmiRaw_5;
    DTMIRaw_6_7 dtmiRaw_6_7;
    DTMIRaw_8 dtmiRaw_8;
    DTMIRaw_9 dtmiRaw_9;
    switch (count)
    {
    case 0:
        memcpy(&dtmiRaw_1,&dataWord,sizeof(dtmiRaw_1));
        dtmiRaw_1.CC1 = dtmiRaw_1.CC1;
        dtmiRaw_1.CC2 = dtmiRaw_1.CC2;
        dtmiRaw_1.T = swapHex(dtmiRaw_1.T);
        dtmiRaw_1.KC1 = dtmiRaw_1.KC1;
        dtmiRaw_1.KC2 = dtmiRaw_1.KC2;
        dtmiRaw_1.SerNum = dtmiRaw_1.SerNum;
        dtmiRaw_1.Texp = dtmiRaw_1.Texp;
        dtmiRaw_1.NumLoc = dtmiRaw_1.NumLoc;
        dtmiRaw_1.NumObj = dtmiRaw_1.NumObj;
        dtmiRaw_1.NumFrag = dtmiRaw_1.NumFrag;
        dtmiRaw_1.Epsilon = dtmiRaw_1.Epsilon;
        dtmiRaw_1.deltaT = swapHex(dtmiRaw_1.deltaT);
        dtmiRaw_1.Loc_0_0 = swapHex(dtmiRaw_1.Loc_0_0);
        dtmiRaw_1.Loc_0_1 = swapHex(dtmiRaw_1.Loc_0_1);
        dtmiRaw_1.Loc_0_2 = swapHex(dtmiRaw_1.Loc_0_2);
        dtmiRaw_1.Loc_0_3 = swapHex(dtmiRaw_1.Loc_0_3);
        dtmiRaw_1.Loc_1_0 = swapHex(dtmiRaw_1.Loc_1_0);
        dtmiRaw_1.Loc_1_1 = swapHex(dtmiRaw_1.Loc_1_1);
        dtmiRaw_1.Loc_1_2 = swapHex(dtmiRaw_1.Loc_1_2);
        dtmiRaw_1.Loc_1_3 = swapHex(dtmiRaw_1.Loc_1_3);
        dtmiRaw_1.Loc_2_0 = swapHex(dtmiRaw_1.Loc_2_0);
        memcpy(&m_kia_mko_struct->dtmi_1, &dtmiRaw_1, sizeof(m_kia_mko_struct->dtmi_1));
        break;
    case 1:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        dtmi_2_3_4_converter(dtmiRaw_2_3_4);
        memcpy(&m_kia_mko_struct->dtmi_2, &dtmiRaw_2_3_4, sizeof(m_kia_mko_struct->dtmi_2));
        break;
    case 2:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        dtmi_2_3_4_converter(dtmiRaw_2_3_4);
        memcpy(&m_kia_mko_struct->dtmi_3, &dtmiRaw_2_3_4, sizeof(m_kia_mko_struct->dtmi_3));
        break;
    case 3:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        dtmi_2_3_4_converter(dtmiRaw_2_3_4);
        memcpy(&m_kia_mko_struct->dtmi_4, &dtmiRaw_2_3_4, sizeof(m_kia_mko_struct->dtmi_4));
        break;
    case 4:
        memcpy(&dtmiRaw_5,&dataWord,sizeof(dtmiRaw_5));
        dtmiRaw_5.CC1 = dtmiRaw_5.CC1;
        dtmiRaw_5.CC2 = dtmiRaw_5.CC2;
        dtmiRaw_5.Loc_3_4 = swapHex(dtmiRaw_5.Loc_3_4);
        dtmiRaw_5.Loc_5_6 = swapHex(dtmiRaw_5.Loc_5_6);
        dtmiRaw_5.Loc_7_8 = swapHex(dtmiRaw_5.Loc_7_8);
        dtmiRaw_5.Loc_9_10 = swapHex(dtmiRaw_5.Loc_9_10);
        dtmiRaw_5.Loc_11_12 = swapHex(dtmiRaw_5.Loc_11_12);
        dtmiRaw_5.Loc_13_14 = swapHex(dtmiRaw_5.Loc_13_14);
        dtmiRaw_5.Loc_15_16 = swapHex(dtmiRaw_5.Loc_15_16);
        dtmiRaw_5.Loc_17_18 = swapHex(dtmiRaw_5.Loc_17_18);
        dtmiRaw_5.Loc_19_20 = swapHex(dtmiRaw_5.Loc_19_20);
        dtmiRaw_5.Loc_21_22 = swapHex(dtmiRaw_5.Loc_21_22);
        dtmiRaw_5.Wo_x = swapHex(dtmiRaw_5.Wo_x);
        dtmiRaw_5.Wo_y = swapHex(dtmiRaw_5.Wo_y);
        dtmiRaw_5.Wo_z = swapHex(dtmiRaw_5.Wo_z);
        dtmiRaw_5.XYc_0_0 = swapHex(dtmiRaw_5.XYc_0_0);
        dtmiRaw_5.XYc_0_1 = swapHex(dtmiRaw_5.XYc_0_1);
        memcpy(&m_kia_mko_struct->dtmi_5, &dtmiRaw_5, sizeof(m_kia_mko_struct->dtmi_5));
        break;
    case 5:
        memcpy(&dtmiRaw_6_7,&dataWord,sizeof(dtmiRaw_6_7));
        dtmi_6_7_converter(dtmiRaw_6_7);
        memcpy(&m_kia_mko_struct->dtmi_6, &dtmiRaw_6_7, sizeof(m_kia_mko_struct->dtmi_6));
        break;
    case 6:
        memcpy(&dtmiRaw_6_7,&dataWord,sizeof(dtmiRaw_6_7));
        dtmi_6_7_converter(dtmiRaw_6_7);
        memcpy(&m_kia_mko_struct->dtmi_7, &dtmiRaw_6_7, sizeof(m_kia_mko_struct->dtmi_7));
        break;
    case 7:
        memcpy(&dtmiRaw_8,&dataWord,sizeof(dtmiRaw_8));
        memcpy(&m_kia_mko_struct->dtmi_8, &dtmiRaw_8,sizeof(m_kia_mko_struct->dtmi_8));
        break;
    case 8:
        memcpy(&dtmiRaw_9,&dataWord,sizeof(dtmiRaw_9));
        dtmiRaw_9.TOlg = swapHex(dtmiRaw_9.TOlg);
        dtmiRaw_9.QOlg_0 = swapHex(dtmiRaw_9.QOlg_0);
        dtmiRaw_9.QOlg_1 = swapHex(dtmiRaw_9.QOlg_1);
        dtmiRaw_9.QOlg_2 = swapHex(dtmiRaw_9.QOlg_2);
        dtmiRaw_9.QOlg_3 = swapHex(dtmiRaw_9.QOlg_3);
        dtmiRaw_9.Epoch = swapHex(dtmiRaw_9.Epoch);
        memcpy(&m_kia_mko_struct->dtmi_9, &dtmiRaw_9, sizeof(m_kia_mko_struct->dtmi_9));
        break;
    }
    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Служебное слово 1");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_2.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_3.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_4.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_5.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_6.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_7.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_8.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_9.CC1, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Служебное слово 2");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_2.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_3.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_4.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_5.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_6.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_7.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_8.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_9.CC2, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Время привязки информации");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.T));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->dtmi_1.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Сериальный номер");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.SerNum));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Время экспонирования");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.Texp));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество локализованных объектов");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.NumLoc));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.NumObj));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество фрагментов");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.NumFrag));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Допуск распознавания");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.Epsilon));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("13,14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Интервал времени");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_1.deltaT,'f',4));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                  + helpers::format_qstring("X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + helpers::format_qstring("B", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + helpers::format_qstring("C", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back("");

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_0_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_0_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_1_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_1_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_1_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_1_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_1.Loc_2_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_2.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_3.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_4.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Угловая скорость по оптическим измерениям, Wox");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_5.Wo_x, 'f', 4));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Угловая скорость по оптическим измерениям, Woy");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_5.Wo_y, 'f', 4));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Угловая скорость по оптическим измерениям, Woz");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(QString::number(m_kia_mko_struct->dtmi_5.Wo_z, 'f', 4));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                  + helpers::format_qstring("Xc", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + helpers::format_qstring("Yc", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + helpers::format_qstring("ThFrag", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + helpers::format_qstring("ObjFrag", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back("");

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.XYc_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_5.XYc_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );


    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_5, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_5, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_7, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_7, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_6.XYc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_9, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_9, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_11, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_11, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_13, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.ObjFrag_13, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9.ObjFrag_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
            (
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_7.XYc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_8.TheFrag_15, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(QString::number(m_kia_mko_struct->dtmi_9.ObjFrag_15, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );
}

void Pio_bokzm60::decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord)
{
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.clear();
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.clear();
    SHTMI1raw shmti1_raw;
    memcpy(&shmti1_raw, &dataWord,sizeof(shmti1_raw));
    m_kia_mko_struct->st_shtmi1.CC1 = shmti1_raw.CC1;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 1");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.CC1, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi1.CC2 = shmti1_raw.CC2;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 2");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.CC2, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi1.T = swapHex(shmti1_raw.T);
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время привязки информации");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.T));

    m_kia_mko_struct->st_shtmi1.KC1 = shmti1_raw.KC1;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi1.KC2 = shmti1_raw.KC2;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi1.SerNum = shmti1_raw.SerNum;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Сериальный номер БОКЗ-М60");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.T));

    m_kia_mko_struct->st_shtmi1.POST = shmti1_raw.POST;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.POST, 16), 4, '0'));

    uint32_t foc = swapHex(shmti1_raw.Foc);
    memcpy(&m_kia_mko_struct->st_shtmi1.Foc, &foc, sizeof(m_kia_mko_struct->st_shtmi1.Foc));
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("9, 10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Фокусное расстояние");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.Foc, 'f', 4));

    m_kia_mko_struct->st_shtmi1.Xo = swapHex(shmti1_raw.Xo);
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("11, 12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координата Xo гл. точки ФПЗС");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.Xo));

    m_kia_mko_struct->st_shtmi1.Yo = swapHex(shmti1_raw.Yo);
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("13, 14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координата Yo гл. точки ФПЗС");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.Yo));

    m_kia_mko_struct->st_shtmi1.Texp = shmti1_raw.Texp;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время экспонирования");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.Texp));

    m_kia_mko_struct->st_shtmi1.Mt = shmti1_raw.Mt;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Среднее темнового сигнала");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.Mt));

    m_kia_mko_struct->st_shtmi1.St = shmti1_raw.St;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "СКО темневого сигнала");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.St));

    m_kia_mko_struct->st_shtmi1.Ndef = shmti1_raw.Ndef;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Количество дефектов");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.Ndef));

    m_kia_mko_struct->st_shtmi1.rezerv1 = shmti1_raw.rezerv1;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv1));

    m_kia_mko_struct->st_shtmi1.rezerv2 = shmti1_raw.rezerv2;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv2));

    m_kia_mko_struct->st_shtmi1.rezerv3 = shmti1_raw.rezerv3;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv3));

    m_kia_mko_struct->st_shtmi1.rezerv4 = shmti1_raw.rezerv4;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv4));

    m_kia_mko_struct->st_shtmi1.rezerv5 = shmti1_raw.rezerv5;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv5));

    m_kia_mko_struct->st_shtmi1.rezerv6 = shmti1_raw.rezerv6;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv6));

    m_kia_mko_struct->st_shtmi1.rezerv7 = shmti1_raw.rezerv7;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv7));

    m_kia_mko_struct->st_shtmi1.rezerv8 = shmti1_raw.rezerv8;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv8));

    m_kia_mko_struct->st_shtmi1.rezerv9 = shmti1_raw.rezerv9;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("27", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv9));

    m_kia_mko_struct->st_shtmi1.rezerv10 = shmti1_raw.rezerv10;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv10));

    m_kia_mko_struct->st_shtmi1.rezerv11 = shmti1_raw.rezerv11;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("29", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.rezerv11));

    m_kia_mko_struct->st_shtmi1.XCF = shmti1_raw.XCF;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "X-индентификтор");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.XCF, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi1.Years = (shmti1_raw.Date >> 12);
    m_kia_mko_struct->st_shtmi1.Month = ((shmti1_raw.Date & 0x0fff) >> 8);
    m_kia_mko_struct->st_shtmi1.Days = ((shmti1_raw.Date & 0x00ff));
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Дата создания ПО");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(2000 + m_kia_mko_struct->st_shtmi1.Years)
                                      + "." + QString::number(m_kia_mko_struct->st_shtmi1.Month)
                                      + "." + QString::number(m_kia_mko_struct->st_shtmi1.Days));

    m_kia_mko_struct->st_shtmi1.Ver1 = (shmti1_raw.Ver >> 12);
    m_kia_mko_struct->st_shtmi1.Ver2 = ((shmti1_raw.Ver & 0x0fff) >> 8);
    m_kia_mko_struct->st_shtmi1.Ver3 = ((shmti1_raw.Ver & 0x00ff));
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Номер версии ПО");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1.Ver1)
                                      + "." + QString::number(m_kia_mko_struct->st_shtmi1.Ver2)
                                      + "." + QString::number(m_kia_mko_struct->st_shtmi1.Ver3));

}

void Pio_bokzm60::decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord)
{
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.clear();
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.clear();
    SHTMI2raw shtmi2_raw;
    memcpy(&shtmi2_raw,&dataWord,sizeof(shtmi2_raw));
    m_kia_mko_struct->st_shtmi2.CC1 = shtmi2_raw.CC1;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 1");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.CC1, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi2.CC2 = shtmi2_raw.CC2;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 2");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.CC2, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi2.T = swapHex(shtmi2_raw.T);
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время привязки информации");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.T));

    m_kia_mko_struct->st_shtmi2.KC1 = shtmi2_raw.KC1;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi2.KC2 = shtmi2_raw.KC2;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.KC2, 16), 4, '0'));


    m_kia_mko_struct->st_shtmi2.SerNum = shtmi2_raw.SerNum;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Сериальный номер БОКЗ-М60");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.SerNum));

    m_kia_mko_struct->st_shtmi2.POST = shtmi2_raw.POST;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.POST, 16), 4, '0'));

    m_kia_mko_struct->st_shtmi2.Texp = shtmi2_raw.Texp;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время экспонирования");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.Texp));

    m_kia_mko_struct->st_shtmi2.Nusd = shtmi2_raw.Nusd;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик полученных УСД");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.Nusd));

    m_kia_mko_struct->st_shtmi2.Nno = shtmi2_raw.Nno;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик НО");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.Nno));

    m_kia_mko_struct->st_shtmi2.Nnosl = shtmi2_raw.Nnosl;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Число переходов от НО к слежению");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.Nnosl));

    m_kia_mko_struct->st_shtmi2.Nto = shtmi2_raw.Nto;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик ТО");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.Nto));

    m_kia_mko_struct->st_shtmi2.Ntosl = shtmi2_raw.Ntosl;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Число переходов от ТО к слежению");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.Ntosl));

    m_kia_mko_struct->st_shtmi2.Nsl = swapHex(shtmi2_raw.Nsl);
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("15, 16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик слежения");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.Nsl));
    uint16_t counter_eCount = 16;
    for (uint16_t count_ind = 0; count_ind < counter_eCount; count_ind++)
    {
        m_kia_mko_struct->st_shtmi2.eCount[count_ind] = shtmi2_raw.eCount[count_ind];
        m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring(QString::number(count_ind + 17), m_kia_settings->m_format_for_desc->shift_for_numbers)
                                          + QString("Счетчик") + QString::number(count_ind));
        m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi2.eCount[count_ind]));
    }
}

void Pio_bokzm60::decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t &bshv)
{
    m_kia_mko_struct->st_mshior.mshior_list_name.clear();
    m_kia_mko_struct->st_mshior.mshior_list_data.clear();
    MSHIORRaw mshiorRaw;
    memcpy(&mshiorRaw,&dataWord,sizeof(mshiorRaw));
    m_kia_mko_struct->st_mshior.KC1 = mshiorRaw.KC1;
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior.KC1, 16), 4, '0'));

    m_kia_mko_struct->st_mshior.KC2 = mshiorRaw.KC2;
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior.KC2, 16), 4, '0'));

    m_kia_mko_struct->st_mshior.T = swapHex(mshiorRaw.T);
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.T) + " (" + QString::number((int)(bshv - m_kia_mko_struct->st_mshior.T)) +  ")");
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время привязки информации");

    m_kia_mko_struct->st_mshior.OZx = helpers::uint32_to_float(swapHex(mshiorRaw.OZx));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.OZx,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("5,6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координаты оси OZx ПСК в ИСК");

    m_kia_mko_struct->st_mshior.OZy = helpers::uint32_to_float(swapHex(mshiorRaw.OZy));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.OZy,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("7,8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координаты оси OZy ПСК в ИСК");

    m_kia_mko_struct->st_mshior.OZz = helpers::uint32_to_float(swapHex(mshiorRaw.OZz));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.OZz,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("9,10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координаты оси OZz ПСК в ИСК");

    m_kia_mko_struct->st_mshior.Qo0 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo0));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.Qo0,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("11,12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo0");

    m_kia_mko_struct->st_mshior.Qo1 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo1));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.Qo1,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("13,14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo0");

    m_kia_mko_struct->st_mshior.Qo2 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo2));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.Qo2,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("15,16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo2");

    m_kia_mko_struct->st_mshior.Qo3 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo3));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.Qo3,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("17,18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo3");

    m_kia_mko_struct->st_mshior.wox = helpers::uint32_to_float(swapHex(mshiorRaw.wox)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.wox,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("19,20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Угловая скорость по оптическим измерениям, Wox");

    m_kia_mko_struct->st_mshior.woy = helpers::uint32_to_float(swapHex(mshiorRaw.woy)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("21,22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Угловая скорость по оптическим измерениям, Woy");
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.woy,'f',4));

    m_kia_mko_struct->st_mshior.woz = helpers::uint32_to_float(swapHex(mshiorRaw.woz)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(QString::number(m_kia_mko_struct->st_mshior.woz,'f',4));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("23,24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Угловая скорость по оптическим измерениям, Woz");

    m_kia_settings->m_data_for_db->m_norm_qaor = sqrt(pow(m_kia_mko_struct->st_mshior.Qo0,2) + pow(m_kia_mko_struct->st_mshior.Qo1,2) + pow(m_kia_mko_struct->st_mshior.Qo2, 2)  + pow(m_kia_mko_struct->st_mshior.Qo3,2));
}

Pio_bokzm60::~Pio_bokzm60()
{

}

void Pio_bokzm60::dtimi_loc_converter(DTMILocRaw_2_3_4_5_6_7_8 &dtmi_loc_raw_2_3_4_5_6_7_8)
{
    dtmi_loc_raw_2_3_4_5_6_7_8.CC1 = dtmi_loc_raw_2_3_4_5_6_7_8.CC1;
    dtmi_loc_raw_2_3_4_5_6_7_8.CC2 = dtmi_loc_raw_2_3_4_5_6_7_8.CC2;
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_3_4 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_3_4);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_5_6 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_5_6);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_7_8 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_7_8);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_9_10 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_9_10);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_11_12 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_11_12);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_13_14 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_13_14);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_15_16 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_15_16);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_17_18 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_17_18);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_19_20 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_19_20);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_21_22 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_21_22);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_23_24 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_23_24);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_25_26 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_25_26);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_27_28 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_27_28);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_29_30 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_29_30);
    dtmi_loc_raw_2_3_4_5_6_7_8.Loc_31_32 = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc_31_32);
}

void Pio_bokzm60::dtmi_2_3_4_converter(DTMIRaw_2_3_4 &dtmiRaw_2_3_4)
{
    dtmiRaw_2_3_4.CC1 = dtmiRaw_2_3_4.CC1;
    dtmiRaw_2_3_4.CC2 = dtmiRaw_2_3_4.CC2;
    dtmiRaw_2_3_4.Loc_3_4 = swapHex(dtmiRaw_2_3_4.Loc_3_4);
    dtmiRaw_2_3_4.Loc_5_6 = swapHex(dtmiRaw_2_3_4.Loc_5_6);
    dtmiRaw_2_3_4.Loc_7_8 = swapHex(dtmiRaw_2_3_4.Loc_7_8);
    dtmiRaw_2_3_4.Loc_9_10 = swapHex(dtmiRaw_2_3_4.Loc_9_10);
    dtmiRaw_2_3_4.Loc_11_12 = swapHex(dtmiRaw_2_3_4.Loc_11_12);
    dtmiRaw_2_3_4.Loc_13_14 = swapHex(dtmiRaw_2_3_4.Loc_13_14);
    dtmiRaw_2_3_4.Loc_15_16 = swapHex(dtmiRaw_2_3_4.Loc_15_16);
    dtmiRaw_2_3_4.Loc_17_18 = swapHex(dtmiRaw_2_3_4.Loc_17_18);
    dtmiRaw_2_3_4.Loc_19_20 = swapHex(dtmiRaw_2_3_4.Loc_19_20);
    dtmiRaw_2_3_4.Loc_21_22 = swapHex(dtmiRaw_2_3_4.Loc_21_22);
    dtmiRaw_2_3_4.Loc_23_24 = swapHex(dtmiRaw_2_3_4.Loc_23_24);
    dtmiRaw_2_3_4.Loc_25_26 = swapHex(dtmiRaw_2_3_4.Loc_25_26);
    dtmiRaw_2_3_4.Loc_27_28 = swapHex(dtmiRaw_2_3_4.Loc_27_28);
    dtmiRaw_2_3_4.Loc_29_30 = swapHex(dtmiRaw_2_3_4.Loc_29_30);
    dtmiRaw_2_3_4.Loc_31_32 = swapHex(dtmiRaw_2_3_4.Loc_31_32);
}

void Pio_bokzm60::dtmi_6_7_converter(DTMIRaw_6_7 &dtmiRaw_6_7)
{
    dtmiRaw_6_7.CC1 = dtmiRaw_6_7.CC1;
    dtmiRaw_6_7.CC2 = dtmiRaw_6_7.CC2;
    dtmiRaw_6_7.XYc_3_4 = swapHex(dtmiRaw_6_7.XYc_3_4);
    dtmiRaw_6_7.XYc_5_6 = swapHex(dtmiRaw_6_7.XYc_5_6);
    dtmiRaw_6_7.XYc_7_8 = swapHex(dtmiRaw_6_7.XYc_7_8);
    dtmiRaw_6_7.XYc_9_10 = swapHex(dtmiRaw_6_7.XYc_9_10);
    dtmiRaw_6_7.XYc_11_12 = swapHex(dtmiRaw_6_7.XYc_11_12);
    dtmiRaw_6_7.XYc_13_14 = swapHex(dtmiRaw_6_7.XYc_13_14);
    dtmiRaw_6_7.XYc_15_16 = swapHex(dtmiRaw_6_7.XYc_15_16);
    dtmiRaw_6_7.XYc_17_18 = swapHex(dtmiRaw_6_7.XYc_17_18);
    dtmiRaw_6_7.XYc_19_20 = swapHex(dtmiRaw_6_7.XYc_19_20);
    dtmiRaw_6_7.XYc_21_22 = swapHex(dtmiRaw_6_7.XYc_21_22);
    dtmiRaw_6_7.XYc_23_24 = swapHex(dtmiRaw_6_7.XYc_23_24);
    dtmiRaw_6_7.XYc_25_26 = swapHex(dtmiRaw_6_7.XYc_25_26);
    dtmiRaw_6_7.XYc_27_28 = swapHex(dtmiRaw_6_7.XYc_27_28);
    dtmiRaw_6_7.XYc_29_30 = swapHex(dtmiRaw_6_7.XYc_29_30);
    dtmiRaw_6_7.XYc_31_32 = swapHex(dtmiRaw_6_7.XYc_31_32);
}

template<typename T>
T Pio_bokzm60::swapHex(T value)
{
    value = ((value & 0x0000ffff) << 16) | (value >> 16);
    return value;
}
