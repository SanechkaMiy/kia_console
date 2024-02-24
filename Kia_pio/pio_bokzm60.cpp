#include "pio_bokzm60.h"
#include <limits>
Pio_bokzm60::Pio_bokzm60(std::shared_ptr<Kia_mko_struct> kia_mko_struct, std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_mko_struct(kia_mko_struct),
    m_kia_settings(kia_settings)
{
    create_list_to_prepare_data();
}

void Pio_bokzm60::decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{
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
        for (uint16_t num_loc = 0; num_loc < dtmi_raw_1.Loc.size(); num_loc++)
        {
            dtmi_raw_1.Loc[num_loc] = swapHex(dtmi_raw_1.Loc[num_loc]);
        }
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1, &dtmi_raw_1, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1));
        break;
    case 1:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2, &dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2));
        break;
    case 2:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3));
        break;
    case 3:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4));
        break;
    case 4:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5));
        break;
    case 5:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6));
        break;
    case 6:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7,&dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7));
        break;
    case 7:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        dtimi_loc_converter(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8, &dtmi_loc_raw_2_3_4_5_6_7_8, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8));
        break;
    case 8:
        memcpy(&dtmi_raw_9,&dataWord,sizeof(dtmi_raw_9));
        dtmi_raw_9.CC1 = dtmi_raw_9.CC1;
        dtmi_raw_9.CC2 = dtmi_raw_9.CC2;
        for (uint16_t num_loc = 0; num_loc < dtmi_loc_raw_2_3_4_5_6_7_8.Loc.size(); num_loc++)
        {
            dtmi_raw_9.Loc[num_loc] = swapHex(dtmi_raw_9.Loc[num_loc]);
        }
        dtmi_raw_9.rezerv = dtmi_raw_9.rezerv;
        memcpy(&m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9, &dtmi_raw_9, sizeof(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9));
        break;
    }

}

void Pio_bokzm60::decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{
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
        for (uint16_t num_loc = 0; num_loc < dtmiRaw_1.loc.size(); num_loc++)
        {
            dtmiRaw_1.loc[num_loc] = swapHex(dtmiRaw_1.loc[num_loc]);
        }
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_1, &dtmiRaw_1, sizeof(m_kia_mko_struct->st_dtmi.dtmi_1));
        break;
    case 1:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        dtmi_2_3_4_converter(dtmiRaw_2_3_4);
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_2, &dtmiRaw_2_3_4, sizeof(m_kia_mko_struct->st_dtmi.dtmi_2));
        break;
    case 2:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        dtmi_2_3_4_converter(dtmiRaw_2_3_4);
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_3, &dtmiRaw_2_3_4, sizeof(m_kia_mko_struct->st_dtmi.dtmi_3));
        break;
    case 3:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        dtmi_2_3_4_converter(dtmiRaw_2_3_4);
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_4, &dtmiRaw_2_3_4, sizeof(m_kia_mko_struct->st_dtmi.dtmi_4));
        break;
    case 4:
        memcpy(&dtmiRaw_5,&dataWord,sizeof(dtmiRaw_5));
        dtmiRaw_5.CC1 = dtmiRaw_5.CC1;
        dtmiRaw_5.CC2 = dtmiRaw_5.CC2;
        for (uint16_t num_loc = 0; num_loc < dtmiRaw_5.loc.size(); num_loc++)
        {
            dtmiRaw_5.loc[num_loc] = swapHex(dtmiRaw_5.loc[num_loc]);
        }
        dtmiRaw_5.Wo_x = swapHex(dtmiRaw_5.Wo_x);
        dtmiRaw_5.Wo_y = swapHex(dtmiRaw_5.Wo_y);
        dtmiRaw_5.Wo_z = swapHex(dtmiRaw_5.Wo_z);
        dtmiRaw_5.XYc_0_0 = swapHex(dtmiRaw_5.XYc_0_0);
        dtmiRaw_5.XYc_0_1 = swapHex(dtmiRaw_5.XYc_0_1);
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_5, &dtmiRaw_5, sizeof(m_kia_mko_struct->st_dtmi.dtmi_5));
        break;
    case 5:
        memcpy(&dtmiRaw_6_7,&dataWord,sizeof(dtmiRaw_6_7));
        dtmi_6_7_converter(dtmiRaw_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_6, &dtmiRaw_6_7, sizeof(m_kia_mko_struct->st_dtmi.dtmi_6));
        break;
    case 6:
        memcpy(&dtmiRaw_6_7,&dataWord,sizeof(dtmiRaw_6_7));
        dtmi_6_7_converter(dtmiRaw_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_7, &dtmiRaw_6_7, sizeof(m_kia_mko_struct->st_dtmi.dtmi_7));
        break;
    case 7:
        memcpy(&dtmiRaw_8,&dataWord,sizeof(dtmiRaw_8));
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_8, &dtmiRaw_8,sizeof(m_kia_mko_struct->st_dtmi.dtmi_8));
        break;
    case 8:
        memcpy(&dtmiRaw_9,&dataWord,sizeof(dtmiRaw_9));
        dtmiRaw_9.TOlg = swapHex(dtmiRaw_9.TOlg);
        dtmiRaw_9.QOlg_0 = swapHex(dtmiRaw_9.QOlg_0);
        dtmiRaw_9.QOlg_1 = swapHex(dtmiRaw_9.QOlg_1);
        dtmiRaw_9.QOlg_2 = swapHex(dtmiRaw_9.QOlg_2);
        dtmiRaw_9.QOlg_3 = swapHex(dtmiRaw_9.QOlg_3);
        dtmiRaw_9.Epoch = swapHex(dtmiRaw_9.Epoch);
        memcpy(&m_kia_mko_struct->st_dtmi.dtmi_9, &dtmiRaw_9, sizeof(m_kia_mko_struct->st_dtmi.dtmi_9));
        break;
    }

}

void Pio_bokzm60::parse_dtmi_loc()
{
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.clear();
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.clear();
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.clear();
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.clear();
    m_kia_mko_struct->st_dtmi_loc.loc_x.clear();
    m_kia_mko_struct->st_dtmi_loc.loc_y.clear();
    m_kia_mko_struct->st_dtmi_loc.loc_b.clear();
    m_kia_mko_struct->st_dtmi_loc.loc_c.clear();

    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9.CC1, 0x42c3));
    std::vector<QString> is_norma;
    is_norma.resize(m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.size());
    QString dtmi_cc1;
    QString check_norma;
    for (uint16_t num_cc = 0; num_cc < m_kia_mko_struct->st_dtmi_loc.dtmi_cc1.size(); num_cc++)
    {
        if (m_kia_mko_struct->st_dtmi_loc.dtmi_cc1[num_cc].first != m_kia_mko_struct->st_dtmi_loc.dtmi_cc1[num_cc].second)
        {
            is_norma[num_cc] = "не норма";
        }
        else
        {
            is_norma[num_cc] = "норма";
        }
        dtmi_cc1.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmi_cc1[num_cc].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_cc], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Служебное слово 1");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(dtmi_cc1, m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.CC1, 0x42c3, 0x42c3));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(check_norma,
                                                                               0, 0, 0));

    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.CC2, 0x7aaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2.CC2, 0x8aaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3.CC2, 0x9aaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4.CC2, 0xaaaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5.CC2, 0xbaaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6.CC2, 0xcaaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7.CC2, 0xdaaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8.CC2, 0xeaaa));
    m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9.CC2, 0xfaaa));
    is_norma.resize(m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.size());
    QString dtmi_cc2;
    check_norma.clear();
    for (uint16_t num_cc = 0; num_cc < m_kia_mko_struct->st_dtmi_loc.dtmi_cc2.size(); num_cc++)
    {
        if (m_kia_mko_struct->st_dtmi_loc.dtmi_cc2[num_cc].first != m_kia_mko_struct->st_dtmi_loc.dtmi_cc2[num_cc].second)
        {
            is_norma[num_cc] = "не норма";
        }
        else
        {
            is_norma[num_cc] = "норма";
        }
        dtmi_cc2.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmi_cc2[num_cc].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_cc], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Служебное слово 2");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(dtmi_cc2, m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.CC2, 0x7aaa, 0x7aaa));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + " ");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(check_norma,
                                                                               0, 0, 0));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Время привязки информации");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.T), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.T, 0, 1e+31));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.KC1, 16), 4, '0'), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.KC1,
                                                                               -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.KC2, 16), 4, '0'), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.KC2,
                                                                               -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Сериальный номер");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.SerNum), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.SerNum,
                                                                               -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Время экспонирования");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Texp), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Texp,
                                                                               -10, 1023));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Количество локализованных объектов");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.NumLoc), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.NumLoc,
                                                                               0, 65535));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.NumObj), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.NumObj,
                                                                               0, 200));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("11, 12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "Среднее значение сигнала");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Mean), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Mean,
                                                                               0, 4095));

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("13, 14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + "СКО сигнала");
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Sigma), m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Sigma,
                                                                               0, 4095));

    uint32_t ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Loc[ind + 2], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_1.Loc[ind + 3], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2.Loc[ind + 3], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2.Loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2.Loc[ind + 1], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_2.Loc[ind + 2], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3.Loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3.Loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3.Loc[ind + 2], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_3.Loc[ind + 3], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4.Loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4.Loc[ind + 2], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4.Loc[ind + 3], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_4.Loc[ind], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5.Loc[ind + 2], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5.Loc[ind + 3], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5.Loc[ind], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_5.Loc[ind + 1], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6.Loc[ind + 3], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6.Loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6.Loc[ind + 1], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_6.Loc[ind + 2], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7.Loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7.Loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7.Loc[ind + 2], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_7.Loc[ind + 3], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8.Loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8.Loc[ind + 2], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8.Loc[ind + 3], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_8.Loc[ind], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9.Loc.size())
    {
        m_kia_mko_struct->st_dtmi_loc.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9.Loc[ind + 2], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9.Loc[ind + 3], 0, 512));
        m_kia_mko_struct->st_dtmi_loc.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9.Loc[ind], 100, 100000));
        m_kia_mko_struct->st_dtmi_loc.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_loc.dtmiLoc_9.Loc[ind + 1], 2, 120));
        ind = ind + 4;
    }
    std::array<std::vector<QString>, 4> is_norma_for_loc;
    for (auto& el :is_norma_for_loc)
        el.resize(m_kia_mko_struct->st_dtmi_loc.loc_x.size());
    for (uint16_t num_loc = 0; num_loc < m_kia_mko_struct->st_dtmi_loc.loc_x.size(); num_loc++)
    {

        if (std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_x[num_loc]) >= std::get<1>(m_kia_mko_struct->st_dtmi_loc.loc_x[num_loc])
                && std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_x[num_loc]) <= std::get<2>(m_kia_mko_struct->st_dtmi_loc.loc_x[num_loc]))
        {
            is_norma_for_loc[0][num_loc] = "норма";
        }
        else
        {
            is_norma_for_loc[0][num_loc] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_y[num_loc]) >= std::get<1>(m_kia_mko_struct->st_dtmi_loc.loc_y[num_loc])
                && std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_y[num_loc]) <= std::get<2>(m_kia_mko_struct->st_dtmi_loc.loc_y[num_loc]))
        {
            is_norma_for_loc[1][num_loc] = "норма";
        }
        else
        {
            is_norma_for_loc[1][num_loc] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_b[num_loc]) >= std::get<1>(m_kia_mko_struct->st_dtmi_loc.loc_b[num_loc])
                && std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_b[num_loc]) <= std::get<2>(m_kia_mko_struct->st_dtmi_loc.loc_b[num_loc]))
        {
            is_norma_for_loc[2][num_loc] = "норма";
        }
        else
        {
            is_norma_for_loc[2][num_loc] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_c[num_loc]) >= std::get<1>(m_kia_mko_struct->st_dtmi_loc.loc_c[num_loc])
                && std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_c[num_loc]) <= std::get<2>(m_kia_mko_struct->st_dtmi_loc.loc_c[num_loc]))
        {
            is_norma_for_loc[3][num_loc] = "норма";
        }
        else
        {
            is_norma_for_loc[3][num_loc] = "не норма";
        }
    }

    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers + m_kia_settings->m_format_for_desc.shift_description)
                                                               + helpers::format_qstring("X", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                               + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                               + helpers::format_qstring("B", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                               + helpers::format_qstring("C", m_kia_settings->m_format_for_desc.shift_for_dtmi));
    m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back(std::make_tuple("", 0, 0, 0));

    for (uint16_t num_loc = 0; num_loc < m_kia_mko_struct->st_dtmi_loc.loc_x.size(); num_loc++)
    {
        m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring(QString::number(num_loc + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                                   + " ");
        m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_x[num_loc]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_y[num_loc]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_b[num_loc]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_loc.loc_c[num_loc]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi)
                        , 0, 0, 0)
                    );

        m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                                   + " ");
        m_kia_mko_struct->st_dtmi_loc.dtmi_loc_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(is_norma_for_loc[0][num_loc], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                    helpers::format_qstring(is_norma_for_loc[1][num_loc], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for_loc[2][num_loc], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for_loc[3][num_loc], m_kia_settings->m_format_for_desc.shift_for_dtmi)
                , 0, 0, 0)
                );
    }


}

void Pio_bokzm60::parse_dtmi(uint16_t type_orient)
{
    m_kia_mko_struct->st_dtmi.dtmi_list_data.clear();
    m_kia_mko_struct->st_dtmi.dtmi_list_name.clear();
    m_kia_mko_struct->st_dtmi.dtmi_cc1.clear();
    m_kia_mko_struct->st_dtmi.dtmi_cc2.clear();
    m_kia_mko_struct->st_dtmi.loc_x.clear();
    m_kia_mko_struct->st_dtmi.loc_y.clear();
    m_kia_mko_struct->st_dtmi.loc_b.clear();
    m_kia_mko_struct->st_dtmi.loc_c.clear();
    m_kia_mko_struct->st_dtmi.XY_x.clear();
    m_kia_mko_struct->st_dtmi.XY_y.clear();
    m_kia_mko_struct->st_dtmi.ObjFrag.clear();
    m_kia_mko_struct->st_dtmi.ThFrag.clear();

    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_1.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_2.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_3.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_4.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_5.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_6.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_7.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_8.CC1, 0x42c3));
    m_kia_mko_struct->st_dtmi.dtmi_cc1.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_9.CC1, 0x42c3));
    std::vector<QString> is_norma;
    is_norma.resize(m_kia_mko_struct->st_dtmi.dtmi_cc1.size());
    QString dtmi_cc1;
    QString check_norma;
    for (uint16_t num_cc = 0; num_cc < m_kia_mko_struct->st_dtmi.dtmi_cc1.size(); num_cc++)
    {
        if (m_kia_mko_struct->st_dtmi.dtmi_cc1[num_cc].first != m_kia_mko_struct->st_dtmi.dtmi_cc1[num_cc].second)
        {
            is_norma[num_cc] = "не норма";
        }
        else
        {
            is_norma[num_cc] = "норма";
        }
        dtmi_cc1.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi.dtmi_cc1[num_cc].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_cc], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Служебное слово 1");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(dtmi_cc1, m_kia_mko_struct->st_dtmi.dtmi_1.CC1, 0x42c3, 0x42c3));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(check_norma,
                                                                       0, 0, 0));


    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_1.CC2, 0x7aaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_2.CC2, 0x8aaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_3.CC2, 0x9aaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_4.CC2, 0xaaaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_5.CC2, 0xbaaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_6.CC2, 0xcaaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_7.CC2, 0xdaaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_8.CC2, 0xeaaa));
    m_kia_mko_struct->st_dtmi.dtmi_cc2.push_back(std::make_pair(m_kia_mko_struct->st_dtmi.dtmi_9.CC2, 0xfaaa));
    is_norma.resize(m_kia_mko_struct->st_dtmi.dtmi_cc2.size());
    QString dtmi_cc2;
    check_norma.clear();
    for (uint16_t num_cc = 0; num_cc < m_kia_mko_struct->st_dtmi.dtmi_cc2.size(); num_cc++)
    {
        if (m_kia_mko_struct->st_dtmi.dtmi_cc2[num_cc].first != m_kia_mko_struct->st_dtmi.dtmi_cc2[num_cc].second)
        {
            is_norma[num_cc] = "не норма";
        }
        else
        {
            is_norma[num_cc] = "норма";
        }
        dtmi_cc2.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi.dtmi_cc2[num_cc].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_cc], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Служебное слово 2");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(dtmi_cc2, m_kia_mko_struct->st_dtmi.dtmi_1.CC2, 0x7aaa, 0x7aaa));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + " ");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(check_norma,
                                                                       0, 0, 0));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Время привязки информации");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.T), m_kia_mko_struct->st_dtmi.dtmi_1.T, 0, 1e31));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.KC1, 16), 4, '0'), m_kia_mko_struct->st_dtmi.dtmi_1.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.KC2, 16), 4, '0'), m_kia_mko_struct->st_dtmi.dtmi_1.KC2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Сериальный номер");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.SerNum), m_kia_mko_struct->st_dtmi.dtmi_1.SerNum, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Время экспонирования");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.Texp), m_kia_mko_struct->st_dtmi.dtmi_1.Texp, 10, 1023));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Количество локализованных объектов");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.NumLoc), m_kia_mko_struct->st_dtmi.dtmi_1.NumLoc, 0, 65535));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.NumObj), m_kia_mko_struct->st_dtmi.dtmi_1.NumObj, 0, 32));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Количество фрагментов");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.NumFrag), m_kia_mko_struct->st_dtmi.dtmi_1.NumFrag, 0, 32));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Допуск распознавания");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.Epsilon), m_kia_mko_struct->st_dtmi.dtmi_1.Epsilon, 150, 450));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("13,14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Интервал времени");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_1.deltaT), m_kia_mko_struct->st_dtmi.dtmi_1.deltaT, 0, 86400));
    uint32_t ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_1.loc.size())
    {
        m_kia_mko_struct->st_dtmi.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_1.loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_1.loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_1.loc[ind + 2], 100, 100000));
        m_kia_mko_struct->st_dtmi.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_1.loc[ind + 3], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_2.loc.size())
    {
        m_kia_mko_struct->st_dtmi.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_2.loc[ind + 3], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_2.loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_2.loc[ind + 1], 100, 100000));
        m_kia_mko_struct->st_dtmi.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_2.loc[ind + 2], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_3.loc.size())
    {
        m_kia_mko_struct->st_dtmi.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_3.loc[ind], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_3.loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_3.loc[ind + 2], 100, 100000));
        m_kia_mko_struct->st_dtmi.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_3.loc[ind + 3], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_4.loc.size())
    {
        m_kia_mko_struct->st_dtmi.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_4.loc[ind + 1], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_4.loc[ind + 2], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_4.loc[ind + 3], 100, 100000));
        m_kia_mko_struct->st_dtmi.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_4.loc[ind], 2, 120));
        ind = ind + 4;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_5.loc.size())
    {
        m_kia_mko_struct->st_dtmi.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_5.loc[ind + 2], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_5.loc[ind + 3], 0, 512));
        m_kia_mko_struct->st_dtmi.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_5.loc[ind], 100, 100000));
        m_kia_mko_struct->st_dtmi.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_5.loc[ind + 1], 2, 120));
        ind = ind + 4;
    }
    std::array<std::vector<QString>, 4> is_norma_for_loc;
    for (auto& el : is_norma_for_loc)
        el.resize(m_kia_mko_struct->st_dtmi.loc_x.size());
    for (uint16_t num = 0; num < m_kia_mko_struct->st_dtmi.loc_x.size(); num++)
    {

        if (std::get<0>(m_kia_mko_struct->st_dtmi.loc_x[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.loc_x[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.loc_x[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.loc_x[num]))
        {
            is_norma_for_loc[0][num] = "норма";
        }
        else
        {
            is_norma_for_loc[0][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi.loc_y[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.loc_y[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.loc_y[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.loc_y[num]))
        {
            is_norma_for_loc[1][num] = "норма";
        }
        else
        {
            is_norma_for_loc[1][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi.loc_b[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.loc_b[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.loc_b[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.loc_b[num]))
        {
            is_norma_for_loc[2][num] = "норма";
        }
        else
        {
            is_norma_for_loc[2][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi.loc_c[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.loc_c[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.loc_c[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.loc_c[num]))
        {
            is_norma_for_loc[3][num] = "норма";
        }
        else
        {
            is_norma_for_loc[3][num] = "не норма";
        }
    }


    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers + m_kia_settings->m_format_for_desc.shift_description)
                                                       + helpers::format_qstring("X", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                       + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                       + helpers::format_qstring("B", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                       + helpers::format_qstring("C", m_kia_settings->m_format_for_desc.shift_for_dtmi));
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple("", 0, 0, 0));

    for (uint16_t num = 0; num < m_kia_mko_struct->st_dtmi.loc_x.size(); num++)
    {
        m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring(QString::number(num + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + " ");
        m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.loc_x[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.loc_y[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.loc_b[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.loc_c[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi)
                        , 0, 0, 0)
                    );

        m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + " ");
        m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(is_norma_for_loc[0][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                    helpers::format_qstring(is_norma_for_loc[1][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for_loc[2][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for_loc[3][num], m_kia_settings->m_format_for_desc.shift_for_dtmi)
                , 0, 0, 0)
                );
    }


    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Угловая скорость по оптическим измерениям, Wox");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_5.Wo_x, 'f', 4), m_kia_mko_struct->st_dtmi.dtmi_5.Wo_x, -0.1, 0.1));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Угловая скорость по оптическим измерениям, Woy");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_5.Wo_y, 'f', 4), m_kia_mko_struct->st_dtmi.dtmi_5.Wo_y, -0.1, 0.1));

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                       + "Угловая скорость по оптическим измерениям, Woz");
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi.dtmi_5.Wo_z, 'f', 4), m_kia_mko_struct->st_dtmi.dtmi_5.Wo_z, -0.1, 0.1));

    m_kia_mko_struct->st_dtmi.XY_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_5.XYc_0_0, 11, 2036));
    m_kia_mko_struct->st_dtmi.XY_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_5.XYc_0_1, 11, 2036));
    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_6.XYc.size())
    {
        m_kia_mko_struct->st_dtmi.XY_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_6.XYc[ind], 11, 2036));
        m_kia_mko_struct->st_dtmi.XY_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_6.XYc[ind + 1], 11, 2036));

        m_kia_mko_struct->st_dtmi.XY_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_7.XYc[ind], 11, 2036));
        m_kia_mko_struct->st_dtmi.XY_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_7.XYc[ind + 1], 11, 2036));
        ind = ind + 2;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_8.ThFrag.size())
    {
        m_kia_mko_struct->st_dtmi.ThFrag.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_8.ThFrag[ind], 0, 2e16));
        ind = ind + 1;
    }

    ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi.dtmi_8.ObjFrag.size())
    {
        m_kia_mko_struct->st_dtmi.ObjFrag.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_8.ObjFrag[ind], -m_max_double_value, m_max_double_value));
        ind = ind + 1;
    }
    m_kia_mko_struct->st_dtmi.ObjFrag.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_9.ObjFrag_14, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_dtmi.ObjFrag.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi.dtmi_9.ObjFrag_15, -m_max_double_value, m_max_double_value));

    std::array<std::vector<QString>, 4> is_norma_for_xy;
    for (auto& el : is_norma_for_xy)
        el.resize(m_kia_mko_struct->st_dtmi.XY_x.size());

    for (uint16_t num = 0; num < m_kia_mko_struct->st_dtmi.XY_x.size(); num++)
    {
        if (std::get<0>(m_kia_mko_struct->st_dtmi.XY_x[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.XY_x[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.XY_x[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.XY_x[num]))
        {
            is_norma_for_xy[0][num] = "норма";
        }
        else
        {
            is_norma_for_xy[0][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi.XY_y[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.XY_y[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.XY_y[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.XY_y[num]))
        {
            is_norma_for_xy[1][num] = "норма";
        }
        else
        {
            is_norma_for_xy[1][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi.ThFrag[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.ThFrag[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.ThFrag[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.ThFrag[num]))
        {
            is_norma_for_xy[2][num] = "норма";
        }
        else
        {
            is_norma_for_xy[2][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi.ObjFrag[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi.ObjFrag[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi.ObjFrag[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi.ObjFrag[num]))
        {
            is_norma_for_xy[3][num] = "норма";
        }
        else
        {
            is_norma_for_xy[3][num] = "не норма";
        }
    }

    m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers + m_kia_settings->m_format_for_desc.shift_description)
                                                       + helpers::format_qstring("Xc", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                       + helpers::format_qstring("Yc", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                       + helpers::format_qstring("ThFrag", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                       + helpers::format_qstring("ObjFrag", m_kia_settings->m_format_for_desc.shift_for_dtmi));
    m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back(std::make_tuple("", 0, 0, 0));
    for (uint16_t num = 0; num < m_kia_mko_struct->st_dtmi.XY_x.size(); num++)
    {
        m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring(QString::number(num + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + " ");
        m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.XY_x[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.XY_y[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.ThFrag[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi.ObjFrag[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi)
                        , 0, 0, 0)
                    );

        m_kia_mko_struct->st_dtmi.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + " ");
        m_kia_mko_struct->st_dtmi.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(is_norma_for_xy[0][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                    helpers::format_qstring(is_norma_for_xy[1][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for_xy[2][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for_xy[3][num], m_kia_settings->m_format_for_desc.shift_for_dtmi)
                , 0, 0, 0)
                );
    }

}

void Pio_bokzm60::decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord)
{

    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.clear();
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.clear();
    SHTMI1raw shmti1_raw;
    memcpy(&shmti1_raw, &dataWord,sizeof(shmti1_raw));
    m_kia_mko_struct->st_shtmi1.CC1 = shmti1_raw.CC1;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Служебное слово 1");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.CC1, 16), 4, '0'), m_kia_mko_struct->st_shtmi1.CC1, 0x42c3, 0x42c3));

    m_kia_mko_struct->st_shtmi1.CC2 = shmti1_raw.CC2;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Служебное слово 2");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.CC2, 16), 4, '0'), m_kia_mko_struct->st_shtmi1.CC2, 0x5aaa, 0x5aaa));

    m_kia_mko_struct->st_shtmi1.T = swapHex(shmti1_raw.T);
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Время привязки информации");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.T), m_kia_mko_struct->st_shtmi1.T, 0, 2e+31));

    m_kia_mko_struct->st_shtmi1.KC1 = shmti1_raw.KC1;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.KC1, 16), 4, '0'), m_kia_mko_struct->st_shtmi1.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1.KC2 = shmti1_raw.KC2;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.KC2, 16), 4, '0'), m_kia_mko_struct->st_shtmi1.KC2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1.SerNum = shmti1_raw.SerNum;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Сериальный номер БОКЗ-М60");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.SerNum), m_kia_mko_struct->st_shtmi1.SerNum, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1.POST = shmti1_raw.POST;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.POST, 16), 4, '0'), m_kia_mko_struct->st_shtmi1.POST, -m_max_double_value, m_max_double_value));

    uint32_t foc = swapHex(shmti1_raw.Foc);
    memcpy(&m_kia_mko_struct->st_shtmi1.Foc, &foc, sizeof(m_kia_mko_struct->st_shtmi1.Foc));
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("9, 10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Фокусное расстояние");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.Foc, 'f', 4), m_kia_mko_struct->st_shtmi1.Foc, 55, 64));

    m_kia_mko_struct->st_shtmi1.Xo = swapHex(shmti1_raw.Xo);
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("11, 12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Координата Xo гл. точки ФПЗС");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.Xo), m_kia_mko_struct->st_shtmi1.Xo, -4, 4));

    m_kia_mko_struct->st_shtmi1.Yo = swapHex(shmti1_raw.Yo);
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("13, 14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Координата Yo гл. точки ФПЗС");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.Yo), m_kia_mko_struct->st_shtmi1.Yo, -4, 4));

    m_kia_mko_struct->st_shtmi1.Texp = shmti1_raw.Texp;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Время экспонирования");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.Texp), m_kia_mko_struct->st_shtmi1.Texp, 10, 1023));

    m_kia_mko_struct->st_shtmi1.Mt = shmti1_raw.Mt;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Среднее темнового сигнала");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.Mt), m_kia_mko_struct->st_shtmi1.Mt, 0, 4095));

    m_kia_mko_struct->st_shtmi1.St = shmti1_raw.St;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "СКО темневого сигнала");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.St), m_kia_mko_struct->st_shtmi1.St, 0, 16384));

    m_kia_mko_struct->st_shtmi1.Ndef = shmti1_raw.Ndef;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Количество дефектов");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.Ndef), m_kia_mko_struct->st_shtmi1.Ndef, 0, 16384));

    m_kia_mko_struct->st_shtmi1.XCF = shmti1_raw.XCF;
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "X-индентификтор");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1.XCF, 16), 4, '0'), m_kia_mko_struct->st_shtmi1.XCF, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1.Years = (shmti1_raw.Date >> 12);
    m_kia_mko_struct->st_shtmi1.Month = ((shmti1_raw.Date & 0x0fff) >> 8);
    m_kia_mko_struct->st_shtmi1.Days = ((shmti1_raw.Date & 0x00ff));
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Дата создания ПО");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(2000 + m_kia_mko_struct->st_shtmi1.Years)
                                                                           + "." + QString::number(m_kia_mko_struct->st_shtmi1.Month)
                                                                           + "." + QString::number(m_kia_mko_struct->st_shtmi1.Days), shmti1_raw.Date, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1.Ver1 = (shmti1_raw.Ver >> 12);
    m_kia_mko_struct->st_shtmi1.Ver2 = ((shmti1_raw.Ver & 0x0fff) >> 8);
    m_kia_mko_struct->st_shtmi1.Ver3 = ((shmti1_raw.Ver & 0x00ff));
    m_kia_mko_struct->st_shtmi1.shtmi1_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Номер версии ПО");
    m_kia_mko_struct->st_shtmi1.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1.Ver1)
                                                                           + "." + QString::number(m_kia_mko_struct->st_shtmi1.Ver2)
                                                                           + "." + QString::number(m_kia_mko_struct->st_shtmi1.Ver3), shmti1_raw.Ver, -m_max_double_value, m_max_double_value));

}

void Pio_bokzm60::decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord)
{
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.clear();
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.clear();
    SHTMI2raw shtmi2_raw;
    memcpy(&shtmi2_raw,&dataWord,sizeof(shtmi2_raw));
    m_kia_mko_struct->st_shtmi2.CC1 = shtmi2_raw.CC1;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Служебное слово 1");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.CC1, 16), 4, '0'), m_kia_mko_struct->st_shtmi2.CC1, 0x42c3, 0x42c3));

    m_kia_mko_struct->st_shtmi2.CC2 = shtmi2_raw.CC2;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Служебное слово 2");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.CC2, 16), 4, '0'), m_kia_mko_struct->st_shtmi2.CC2, 0x6aaa, 0x6aaa));

    m_kia_mko_struct->st_shtmi2.T = swapHex(shtmi2_raw.T);
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Время привязки информации");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.T), m_kia_mko_struct->st_shtmi2.T, 0, 2e+31));

    m_kia_mko_struct->st_shtmi2.KC1 = shtmi2_raw.KC1;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.KC1, 16), 4, '0'), m_kia_mko_struct->st_shtmi2.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi2.KC2 = shtmi2_raw.KC2;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.KC2, 16), 4, '0'), m_kia_mko_struct->st_shtmi2.KC2, -m_max_double_value, m_max_double_value));


    m_kia_mko_struct->st_shtmi2.SerNum = shtmi2_raw.SerNum;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Сериальный номер БОКЗ-М60");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.SerNum), m_kia_mko_struct->st_shtmi2.SerNum, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi2.POST = shtmi2_raw.POST;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2.POST, 16), 4, '0'), m_kia_mko_struct->st_shtmi2.POST, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi2.Texp = shtmi2_raw.Texp;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Время экспонирования");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.Texp), m_kia_mko_struct->st_shtmi2.Texp, 10, 1023));

    m_kia_mko_struct->st_shtmi2.Nusd = shtmi2_raw.Nusd;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Счетчик полученных УСД");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.Nusd), m_kia_mko_struct->st_shtmi2.Nusd, 0, 65535));

    m_kia_mko_struct->st_shtmi2.Nno = shtmi2_raw.Nno;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Счетчик НО");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.Nno), m_kia_mko_struct->st_shtmi2.Nno, 0, 65535));

    m_kia_mko_struct->st_shtmi2.Nnosl = shtmi2_raw.Nnosl;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Число переходов от НО к слежению");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.Nnosl), m_kia_mko_struct->st_shtmi2.Nnosl, 0, 65535));

    m_kia_mko_struct->st_shtmi2.Nto = shtmi2_raw.Nto;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Счетчик ТО");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.Nto), m_kia_mko_struct->st_shtmi2.Nto, 0, 65535));

    m_kia_mko_struct->st_shtmi2.Ntosl = shtmi2_raw.Ntosl;
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Число переходов от ТО к слежению");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.Ntosl), m_kia_mko_struct->st_shtmi2.Ntosl, 0, 65535));

    m_kia_mko_struct->st_shtmi2.Nsl = swapHex(shtmi2_raw.Nsl);
    m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring("15, 16", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Счетчик слежения");
    m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.Nsl), m_kia_mko_struct->st_shtmi2.Nsl, 0, 65535));

    uint16_t counter_eCount = 16;
    for (uint16_t count_ind = 0; count_ind < counter_eCount; count_ind++)
    {
        m_kia_mko_struct->st_shtmi2.eCount[count_ind] = shtmi2_raw.eCount[count_ind];
        m_kia_mko_struct->st_shtmi2.shtmi2_list_name.push_back(helpers::format_qstring(QString::number(count_ind + 17), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                               + QString("Счетчик") + QString::number(count_ind));
        m_kia_mko_struct->st_shtmi2.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2.eCount[count_ind]), m_kia_mko_struct->st_shtmi2.eCount[count_ind], 0, 65535));

    }
}

void Pio_bokzm60::decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t &bshv)
{
    m_kia_mko_struct->st_mshior.mshior_list_name.clear();
    m_kia_mko_struct->st_mshior.mshior_list_data.clear();

    RAW_DATA raw_data;
    memcpy(&raw_data, &dataWord, sizeof(raw_data));

    std::vector<int16_t> temp_data;
    for (uint16_t num_el = 0; num_el < raw_data.data.size(); num_el++)
    {
        temp_data.clear();
        for (uint16_t ind = num_el; ind < num_el + std::get<COUNT_EL_IN_ARR>(m_data_manage[MSHI_OR][num_el]); ind++)
        {
            temp_data.push_back(raw_data.data[ind]);
        }
        m_prepare_data[std::get<DM_TYPE_DATA>(m_data_manage[MSHI_OR][num_el])](temp_data, std::get<RANGE_VALUE>(m_data_manage[MSHI_OR][num_el]),
                                                                               std::get<COEF_TO_SCALE>(m_data_manage[MSHI_OR][num_el]),
                                                                               std::get<TYPE_FORMAT>(m_data_manage[MSHI_OR][num_el]),
                                                                               std::get<DO_SWAP>(m_data_manage[MSHI_OR][num_el]));
    }

    MSHIORRaw mshiorRaw;
    memcpy(&mshiorRaw,&dataWord,sizeof(mshiorRaw));
    m_kia_mko_struct->st_mshior.KC1 = mshiorRaw.KC1;
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior.KC1, 16), 4, '0'), m_kia_mko_struct->st_mshior.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mshior.KC2 = mshiorRaw.KC2;
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior.KC2, 16), 4, '0'), m_kia_mko_struct->st_mshior.KC2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mshior.T = swapHex(mshiorRaw.T);
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.T) + " (" + QString::number((int)(bshv - m_kia_mko_struct->st_mshior.T)) +  ")",
                                                                           m_kia_mko_struct->st_mshior.T, 0, 2e+31));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Время привязки информации");

    m_kia_mko_struct->st_mshior.OZx = helpers::uint32_to_float(swapHex(mshiorRaw.OZx));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.OZx,'f',4), m_kia_mko_struct->st_mshior.OZx, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("5,6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Координаты оси OZx ПСК в ИСК");

    m_kia_mko_struct->st_mshior.OZy = helpers::uint32_to_float(swapHex(mshiorRaw.OZy));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.OZy,'f',4), m_kia_mko_struct->st_mshior.OZy, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("7,8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Координаты оси OZy ПСК в ИСК");

    m_kia_mko_struct->st_mshior.OZz = helpers::uint32_to_float(swapHex(mshiorRaw.OZz));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.OZz,'f',4), m_kia_mko_struct->st_mshior.OZz, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("9,10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Координаты оси OZz ПСК в ИСК");

    m_kia_mko_struct->st_mshior.Qo0 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo0));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.Qo0,'f',4), m_kia_mko_struct->st_mshior.Qo0, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("11,12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Кватернион ориентации, Qo0");

    m_kia_mko_struct->st_mshior.Qo1 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo1));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.Qo1,'f',4), m_kia_mko_struct->st_mshior.Qo1, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("13,14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Кватернион ориентации, Qo1");

    m_kia_mko_struct->st_mshior.Qo2 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo2));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.Qo2,'f',4), m_kia_mko_struct->st_mshior.Qo2, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("15,16", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Кватернион ориентации, Qo2");

    m_kia_mko_struct->st_mshior.Qo3 = helpers::uint32_to_float(swapHex(mshiorRaw.Qo3));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.Qo3,'f',4), m_kia_mko_struct->st_mshior.Qo3, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("17,18", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Кватернион ориентации, Qo3");

    m_kia_mko_struct->st_mshior.wox = helpers::uint32_to_float(swapHex(mshiorRaw.wox)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.wox,'f',4), m_kia_mko_struct->st_mshior.wox, -0.1, 0.1));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("19,20", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Угловая скорость по оптическим измерениям, Wox");

    m_kia_mko_struct->st_mshior.woy = helpers::uint32_to_float(swapHex(mshiorRaw.woy)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("21,22", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Угловая скорость по оптическим измерениям, Woy");
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.woy,'f',4), m_kia_mko_struct->st_mshior.woy, -0.1, 0.1));

    m_kia_mko_struct->st_mshior.woz = helpers::uint32_to_float(swapHex(mshiorRaw.woz)) * M_PI * (pow(2, -5));
    m_kia_mko_struct->st_mshior.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior.woz,'f',4), m_kia_mko_struct->st_mshior.woz, -0.1, 0.1));
    m_kia_mko_struct->st_mshior.mshior_list_name.push_back(helpers::format_qstring("23,24", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                           + "Угловая скорость по оптическим измерениям, Woz");

    m_kia_settings->m_data_for_db->m_norm_qaor = sqrt(pow(m_kia_mko_struct->st_mshior.Qo0,2) + pow(m_kia_mko_struct->st_mshior.Qo1,2) + pow(m_kia_mko_struct->st_mshior.Qo2, 2)  + pow(m_kia_mko_struct->st_mshior.Qo3,2));
}

void Pio_bokzm60::decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr)
{

}

void Pio_bokzm60::decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr)
{

}

Pio_bokzm60::~Pio_bokzm60()
{

}

void Pio_bokzm60::dtimi_loc_converter(DTMILocRaw_2_3_4_5_6_7_8 &dtmi_loc_raw_2_3_4_5_6_7_8)
{
    dtmi_loc_raw_2_3_4_5_6_7_8.CC1 = dtmi_loc_raw_2_3_4_5_6_7_8.CC1;
    dtmi_loc_raw_2_3_4_5_6_7_8.CC2 = dtmi_loc_raw_2_3_4_5_6_7_8.CC2;
    for (uint16_t num_loc = 0; num_loc < dtmi_loc_raw_2_3_4_5_6_7_8.Loc.size(); num_loc++)
    {
        dtmi_loc_raw_2_3_4_5_6_7_8.Loc[num_loc] = swapHex(dtmi_loc_raw_2_3_4_5_6_7_8.Loc[num_loc]);
    }
}

void Pio_bokzm60::dtmi_2_3_4_converter(DTMIRaw_2_3_4 &dtmiRaw_2_3_4)
{
    dtmiRaw_2_3_4.CC1 = dtmiRaw_2_3_4.CC1;
    dtmiRaw_2_3_4.CC2 = dtmiRaw_2_3_4.CC2;
    for (uint16_t num_loc = 0; num_loc < dtmiRaw_2_3_4.loc.size(); num_loc++)
    {
        dtmiRaw_2_3_4.loc[num_loc] = swapHex(dtmiRaw_2_3_4.loc[num_loc]);
    }
}

void Pio_bokzm60::dtmi_6_7_converter(DTMIRaw_6_7 &dtmiRaw_6_7)
{
    dtmiRaw_6_7.CC1 = dtmiRaw_6_7.CC1;
    dtmiRaw_6_7.CC2 = dtmiRaw_6_7.CC2;
    for (uint16_t num_loc = 0; num_loc < dtmiRaw_6_7.XYc.size(); num_loc++)
    {
        dtmiRaw_6_7.XYc[num_loc] = swapHex(dtmiRaw_6_7.XYc[num_loc]);
    }
}



void Pio_bokzm60::create_list_to_prepare_data()
{

    auto add_to_int16_t = [this](std::vector<int16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, bool do_swap_hex)
    {
        for (auto el : value)
        {
            QString is_norma;
            if (el * scale >= range.first && el * scale <= range.second)
            {
                is_norma.clear();
            }
            else
            {
                is_norma = "(не норма)";
            }
            auto format_str = get_format_str(type_format, el * scale);
            m_kia_mko_struct->m_data.data.push_back(std::make_tuple(format_str, el * scale, is_norma));
        }
    };
    m_prepare_data.push_back(add_to_int16_t);

    auto add_to_int32_t = [this](std::vector<int16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, bool do_swap_hex)
    {
        int32_t temp = 0;
        memcpy(&temp, &value, sizeof(temp));
        if (do_swap_hex)
            temp = swapHex(temp);
        QString is_norma;
        if (temp * scale >= range.first && temp * scale <= range.second)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }
        auto format_str = get_format_str(type_format, temp * scale);
        m_kia_mko_struct->m_data.data.push_back(std::make_tuple(format_str, temp * scale, is_norma));
    };
    m_prepare_data.push_back(add_to_int32_t);

    auto add_to_float = [this](std::vector<int16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, bool do_swap_hex)
    {
        int32_t temp = 0;
        memcpy(&temp, &value, sizeof(temp));
        if (do_swap_hex)
            temp = swapHex(temp);
        float temp_float = 0;
        memcpy(&temp_float, &value, sizeof(temp));
        QString is_norma;
        if (temp_float * scale >= range.first && temp_float * scale <= range.second)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }
        auto format_str = get_format_str(type_format, temp_float * scale);
        m_kia_mko_struct->m_data.data.push_back(std::make_tuple(format_str, temp_float * scale, is_norma));
    };
    m_prepare_data.push_back(add_to_float);

    auto add_to_int8_t = [this](std::vector<int16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, bool do_swap_hex)
    {
        std::array<int8_t, 2> temp;
        memcpy(&temp, &value, sizeof(temp));
        for (auto el : temp)
        {
            QString is_norma;
            if (el * scale >= range.first && el * scale <= range.second)
            {
                is_norma.clear();
            }
            else
            {
                is_norma = "(не норма)";
            }
            auto format_str = get_format_str(type_format, el * scale);
            m_kia_mko_struct->m_data.data.push_back(std::make_tuple(format_str, el * scale, is_norma));
        }
    };
    m_prepare_data.push_back(add_to_int8_t);
}

void Pio_bokzm60::create_list_for_mpi_arrays()
{

    m_data_manage[MSHI_OR].push_back(std::make_tuple(INT16, 1, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_HEX, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(INT16, 1, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_HEX, true));

    m_data_manage[MSHI_OR].push_back(std::make_tuple(INT16, 1, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_HEX, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(INT16, 1, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_HEX, true));

    m_data_manage[MSHI_OR].push_back(std::make_tuple(INT32, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_INT, true));

    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_FLOAT, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_FLOAT, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_FLOAT, true));

    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_FLOAT, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_FLOAT, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_FLOAT, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), 1, TDF_FLOAT, true));

    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), PI * pow(2, -5), TDF_FLOAT, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), PI * pow(2, -5), TDF_FLOAT, true));
    m_data_manage[MSHI_OR].push_back(std::make_tuple(FLOAT, 2, std::make_pair(-m_max_double_value, m_max_double_value), PI * pow(2, -5), TDF_FLOAT, true));
}

template<typename T>
T Pio_bokzm60::swapHex(T value)
{
    value = ((value & 0x0000ffff) << 16) | (value >> 16);
    return value;
}

