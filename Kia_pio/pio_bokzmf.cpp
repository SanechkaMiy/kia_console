#include "pio_bokzmf.h"
extern "C"
{
#include "Kia_pio/crc.c"
}
Pio_bokzmf::Pio_bokzmf(std::shared_ptr<Kia_mko_struct> kia_mko_struct,
                       std::shared_ptr<Kia_settings> kia_settings)
{
    m_kia_mko_struct = kia_mko_struct;
    m_kia_settings = kia_settings;
    load_array_param_from_json();
    create_list_to_prepare_data();
    create_list_for_mpi_arrays();
}


void Pio_bokzmf::decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{

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
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_1_mf, &dtmi_raw_1, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf));
        break;
    case 1:
        memcpy(&dtmi_raw_2, &dataWord, sizeof(dtmi_raw_2));
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_2_mf, &dtmi_raw_2, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf));
        break;
    case 2:
        memcpy(&dtmi_raw_3,&dataWord,sizeof(dtmi_raw_3));
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_3_mf, &dtmi_raw_3, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf));
        break;
    case 3:
        memcpy(&dtmi_raw_4,&dataWord,sizeof(dtmi_raw_4));
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_4_mf, &dtmi_raw_4, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf));
        break;
    case 4:
        memcpy(&dtmi_raw_5,&dataWord,sizeof(dtmi_raw_5));
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_5_mf, &dtmi_raw_5, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_6_mf, &dtmi_raw_6, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf));
        break;
    case 6:
        memcpy(&dtmi_raw_7,&dataWord,sizeof(dtmi_raw_7));
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_7_mf,&dtmi_raw_7, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf));
        break;
    case 7:
        memcpy(&dtmi_raw_8,&dataWord,sizeof(dtmi_raw_8));
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_8_mf, &dtmi_raw_8, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf));
        break;
    case 8:
        memcpy(&dtmi_raw_9, &dataWord, sizeof(dtmi_raw_9));
        m_kia_mko_struct->st_mloc_mf.calc_cs.push_back(calculate_cs(dataWord));
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
        memcpy(&m_kia_mko_struct->st_mloc_mf.mLoc_9_mf, &dtmi_raw_9, sizeof(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf));
        break;
    }
}

void Pio_bokzmf::decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{
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
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmiRaw_1.T = swapHex(dtmiRaw_1.T);
        dtmiRaw_1.Tlast = swapHex(dtmiRaw_1.Tlast);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf, &dtmiRaw_1, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf));
        for (uint16_t num_q = 0; num_q < m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Qlst.size(); num_q++)
        {
            m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Qlst[num_q] = uint32_to_float(swapHex(dtmiRaw_1.Qlst[num_q]));
        }
        break;
    case 1:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf));
        break;
    case 2:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_3_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_3_mf));
        break;
    case 3:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_4_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_4_mf));
        break;
    case 4:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_5_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_5_mf));
        break;
    case 5:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_6_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_6_mf));
        break;
    case 6:
        memcpy(&dtmiRaw_2_3_4_5_6_7, &dataWord,sizeof(dtmiRaw_2_3_4_5_6_7));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmi_2_3_4_5_6_7_converter(dtmiRaw_2_3_4_5_6_7);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_7_mf, &dtmiRaw_2_3_4_5_6_7, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_7_mf));
        break;
    case 7:
        memcpy(&dtmiRaw_8, &dataWord, sizeof(dtmiRaw_8));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf, &dtmiRaw_8, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf));
        break;
    case 8:
        memcpy(&dtmiRaw_9,&dataWord,sizeof(dtmiRaw_9));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_9_mf, &dtmiRaw_9, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_9_mf));
        break;
    case 9:
        memcpy(&dtmiRaw_10,&dataWord,sizeof(dtmiRaw_10));
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_10_mf, &dtmiRaw_10, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_10_mf));
        break;
        break;
    case 10:
        memcpy(&dtmiRaw_11,&dataWord, sizeof(dtmiRaw_11));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf, &dtmiRaw_11, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf));
        break;
    case 11:
        memcpy(&dtmiRaw_12,&dataWord,sizeof(dtmiRaw_12));
        m_kia_mko_struct->st_dtmi_mf.calc_cs.push_back(calculate_cs(dataWord));
        dtmiRaw_12.Epoch = swapHex(dtmiRaw_12.Epoch);
        memcpy(&m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf, &dtmiRaw_12, sizeof(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf));
        break;
    }


}

void Pio_bokzmf::parse_dtmi_loc()
{
    m_kia_mko_struct->st_mloc_mf.mloc_list_name.clear();
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.clear();
    m_kia_mko_struct->st_mloc_mf.nAr.clear();
    m_kia_mko_struct->st_mloc_mf.cs.clear();
    m_kia_mko_struct->st_mloc_mf.loc_x.clear();
    m_kia_mko_struct->st_mloc_mf.loc_y.clear();
    m_kia_mko_struct->st_mloc_mf.loc_b.clear();
    m_kia_mko_struct->st_mloc_mf.loc_c.clear();

    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.nAr, 0x3001));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.nAr, 0x3002));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.nAr, 0x3003));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.nAr, 0x3004));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.nAr, 0x3005));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.nAr, 0x3006));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.nAr, 0x3007));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.nAr, 0x3008));
    m_kia_mko_struct->st_mloc_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.nAr, 0x3009));
    std::vector<QString> is_norma;
    is_norma.resize(m_kia_mko_struct->st_mloc_mf.nAr.size());
    QString nAr;
    QString check_norma;
    for (uint16_t num_nAr = 0; num_nAr < m_kia_mko_struct->st_mloc_mf.nAr.size(); num_nAr++)
    {
        if (m_kia_mko_struct->st_mloc_mf.nAr[num_nAr].first != m_kia_mko_struct->st_mloc_mf.nAr[num_nAr].second)
        {
            is_norma[num_nAr] = "не норма";
        }
        else
        {
            is_norma[num_nAr] = "норма";
        }
        nAr.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mloc_mf.nAr[num_nAr].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_nAr], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Номер подмассива");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(nAr, m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.nAr, 0x2001, 0x2001));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(check_norma, 0, 0, 0));


    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.cs, 0x42c3));
    m_kia_mko_struct->st_mloc_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.cs, 0x42c3));
    QString cs;
    QString calc_cs;
    check_norma.clear();
    for (uint16_t num_cc = 0; num_cc < m_kia_mko_struct->st_mloc_mf.cs.size(); num_cc++)
    {
        if (m_kia_mko_struct->st_mloc_mf.cs[num_cc].first != m_kia_mko_struct->st_mloc_mf.calc_cs[num_cc])
        {
            is_norma[num_cc] = "не норма";
        }
        else
        {
            is_norma[num_cc] = "норма";
        }
        cs.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mloc_mf.cs[num_cc].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        calc_cs.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mloc_mf.calc_cs[num_cc], 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_cc], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Контрольная сумма");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(cs, m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.cs, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(calc_cs, m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.cs, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(check_norma, 0, 0, 0));


    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.T), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.T, 0, 2e31));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Tms), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Tms, 0, 1000));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.KC1, 16), 4, '0'), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.KC2, 16), 4, '0'), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.KC2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Заводской номер");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.SerNum), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.SerNum, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время экспонирования");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Texp), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Texp, 10, 1023));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Количество локализованных объектов");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.NumLoc), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.NumLoc, 0, 5000));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.NumObj), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.NumObj, 0, 200));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Число пикселей на кадре");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.PixCount), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.PixCount, 0, 65535));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Среднее сигнала");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Mean), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Mean, 0, 4095));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "СКО сигнала");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Sigma), m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Sigma, 0, 6553));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_0_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_0_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_0_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_0_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_1_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_1_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_1_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_1_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_2_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_1_mf.Loc_2_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_2_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_2_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_3_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_3_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_3_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_3_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_4_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_4_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_4_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_4_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_5_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_5_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_5_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_5_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_6_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_6_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_2_mf.Loc_6_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_6_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_7_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_7_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_7_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_7_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_8_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_8_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_8_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_8_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_9_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_9_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_9_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_9_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_10_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_10_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_10_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_3_mf.Loc_10_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_11_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_11_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_11_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_11_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_12_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_12_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_12_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_12_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_13_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_13_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_13_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_13_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_14_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_14_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_14_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_14_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_4_mf.Loc_15_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_15_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_15_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_15_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_16_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_16_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_16_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_16_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_17_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_17_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_17_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_17_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_18_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_18_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_18_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_18_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_19_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_5_mf.Loc_19_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_19_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_19_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_20_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_20_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_20_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_20_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_21_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_21_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_21_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_21_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_22_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_22_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_22_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_22_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_23_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_23_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_6_mf.Loc_23_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_23_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_24_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_24_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_24_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_24_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_25_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_25_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_25_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_25_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_26_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_26_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_26_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_26_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_27_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_27_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_27_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_7_mf.Loc_27_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_28_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_28_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_28_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_28_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_29_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_29_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_29_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_29_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_30_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_30_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_30_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_30_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_31_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_31_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_31_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_31_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_8_mf.Loc_32_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_32_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_32_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_32_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_33_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_33_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_33_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_33_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_34_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_34_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_34_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_34_S, 2, 120));

    m_kia_mko_struct->st_mloc_mf.loc_x.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_35_X, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_y.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_35_Y, 0, 2048));
    m_kia_mko_struct->st_mloc_mf.loc_b.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_35_B, 100, 100000));
    m_kia_mko_struct->st_mloc_mf.loc_c.push_back(std::make_tuple(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Loc_35_S, 2, 120));


    std::array<std::vector<QString>, 4> is_norma_for;
    for (auto& el : is_norma_for)
        el.resize(m_kia_mko_struct->st_mloc_mf.loc_x.size());
    for (uint16_t num = 0; num < m_kia_mko_struct->st_mloc_mf.loc_x.size(); num++)
    {
        if (std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_x[num]) >= std::get<1>(m_kia_mko_struct->st_mloc_mf.loc_x[num])
                && std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_x[num]) <= std::get<2>(m_kia_mko_struct->st_mloc_mf.loc_x[num]))
        {
            is_norma_for[0][num] = "норма";
        }
        else
        {
            is_norma_for[0][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_y[num]) >= std::get<1>(m_kia_mko_struct->st_mloc_mf.loc_y[num])
                && std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_y[num]) <= std::get<2>(m_kia_mko_struct->st_mloc_mf.loc_y[num]))
        {
            is_norma_for[1][num] = "норма";
        }
        else
        {
            is_norma_for[1][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_b[num]) >= std::get<1>(m_kia_mko_struct->st_mloc_mf.loc_b[num])
                && std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_b[num]) <= std::get<2>(m_kia_mko_struct->st_mloc_mf.loc_b[num]))
        {
            is_norma_for[2][num] = "норма";
        }
        else
        {
            is_norma_for[2][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_c[num]) >= std::get<1>(m_kia_mko_struct->st_mloc_mf.loc_c[num])
                && std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_c[num]) <= std::get<2>(m_kia_mko_struct->st_mloc_mf.loc_c[num]))
        {
            is_norma_for[3][num] = "норма";
        }
        else
        {
            is_norma_for[3][num] = "не норма";
        }
    }

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers + m_kia_settings->m_format_for_desc.shift_description)
                                                          + helpers::format_qstring("X", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("B", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("S", m_kia_settings->m_format_for_desc.shift_for_dtmi));
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple("", 0, 0, 0));


    for (uint16_t num = 0; num < m_kia_mko_struct->st_mloc_mf.loc_x.size(); num++)
    {
        m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring(QString::number(num + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
        m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_x[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_y[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_b[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_mloc_mf.loc_c[num]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi)
                        , 0, 0, 0)
                    );

        m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
        m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(is_norma_for[0][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                    helpers::format_qstring(is_norma_for[1][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for[2][num], m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(is_norma_for[3][num], m_kia_settings->m_format_for_desc.shift_for_dtmi)
                , 0, 0, 0)
                );
    }

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Число пикселей для расчета порога");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.nPixNs), m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.nPixNs, 0, 65535));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("29", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Число пикселей выше порога шума");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.nPixGrNs), m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.nPixGrNs, 0, 65535));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Порог");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Th), m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Th, 0, 65535));

    m_kia_mko_struct->st_mloc_mf.mloc_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Температура КМОП матрицы");
    m_kia_mko_struct->st_mloc_mf.mloc_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Tcmv), m_kia_mko_struct->st_mloc_mf.mLoc_9_mf.Tcmv, -75, 150));
}

void Pio_bokzmf::parse_dtmi(uint16_t type_orient)
{
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.clear();
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.clear();
    m_kia_mko_struct->st_dtmi_mf.nAr.clear();
    m_kia_mko_struct->st_dtmi_mf.cs.clear();
    m_kia_mko_struct->st_dtmi_mf.qlst.clear();
    m_kia_mko_struct->st_dtmi_mf.HistDef.clear();

    m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x.clear();
    m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y.clear();
    m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b.clear();
    m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s.clear();

    m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x.clear();
    m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y.clear();
    m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b.clear();
    m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s.clear();

    m_kia_mko_struct->st_dtmi_mf.XYc_x.clear();
    m_kia_mko_struct->st_dtmi_mf.XYc_y.clear();
    m_kia_mko_struct->st_dtmi_mf.MeanFrag.clear();
    m_kia_mko_struct->st_dtmi_mf.SigmaFrag.clear();
    m_kia_mko_struct->st_dtmi_mf.ThFrag.clear();
    m_kia_mko_struct->st_dtmi_mf.ObjFrag.clear();
    m_kia_mko_struct->st_dtmi_mf.MultXY.clear();
    m_kia_mko_struct->st_dtmi_mf.ZipXY_X.clear();
    m_kia_mko_struct->st_dtmi_mf.ZipXY_Y.clear();
    m_kia_mko_struct->st_dtmi_mf.HistPix.clear();

    uint32_t ind = 0;
    while(ind < m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf.rs_loc_0_dtmi2.size())
    {
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf.rs_loc_0_dtmi2[ind], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf.rs_loc_0_dtmi2[ind + 1], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf.rs_loc_0_dtmi2[ind + 2], 100, 100000));

        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_3_mf.rs_loc_0_dtmi3[ind], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_3_mf.rs_loc_0_dtmi3[ind + 1], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_3_mf.rs_loc_0_dtmi3[ind + 2], 100, 100000));

        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_4_mf.rs_loc_0_dtmi4[ind], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_4_mf.rs_loc_0_dtmi4[ind + 1], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_4_mf.rs_loc_0_dtmi4[ind + 2], 100, 100000));

        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_5_mf.rs_loc_1_dtmi5[ind], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_5_mf.rs_loc_1_dtmi5[ind + 1], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_5_mf.rs_loc_1_dtmi5[ind + 2], 100, 100000));

        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_6_mf.rs_loc_1_dtmi6[ind], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_6_mf.rs_loc_1_dtmi6[ind + 1], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_6_mf.rs_loc_1_dtmi6[ind + 2], 100, 100000));

        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_7_mf.rs_loc_1_dtmi7[ind], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_7_mf.rs_loc_1_dtmi7[ind + 1], 0, 2048));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_7_mf.rs_loc_1_dtmi7[ind + 2], 100, 100000));

        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.rs_loc_s_0_dtmi8[ind], 2, 120));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.rs_loc_s_0_dtmi8[ind + 1], 2, 120));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.rs_loc_s_0_dtmi8[ind + 2], 2, 120));

        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.rs_loc_s_1_dtmi8[ind], 2, 120));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.rs_loc_s_1_dtmi8[ind + 1], 2, 120));
        m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.rs_loc_s_1_dtmi8[ind + 2], 2, 120));
        ind = ind + 3;
    }

    std::array<std::vector<QString>, 8> is_norma_for_rsLoc;
    for (auto& el: is_norma_for_rsLoc)
        el.resize(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x.size());
    for (uint16_t num = 0; num < m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x.size(); num++)
    {

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x[num]))
        {
            is_norma_for_rsLoc[0][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[0][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y[num]))
        {
            is_norma_for_rsLoc[1][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[1][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b[num]))
        {
            is_norma_for_rsLoc[2][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[2][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s[num]))
        {
            is_norma_for_rsLoc[3][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[3][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x[num]))
        {
            is_norma_for_rsLoc[4][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[4][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y[num]))
        {
            is_norma_for_rsLoc[5][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[5][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b[num]))
        {
            is_norma_for_rsLoc[6][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[6][num] = "не норма";
        }
        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s[num]))
        {
            is_norma_for_rsLoc[7][num] = "норма";
        }
        else
        {
            is_norma_for_rsLoc[7][num] = "не норма";
        }
    }


    ind = 0;
    while (ind < m_kia_mko_struct->st_dtmi_mf.dtmi_10_mf.Mean.size())
    {
        m_kia_mko_struct->st_dtmi_mf.XYc_x.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_9_mf.Xyc[ind] ,11, 2036));
        m_kia_mko_struct->st_dtmi_mf.XYc_y.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_9_mf.Xyc[ind + 1] ,11, 2036));

        m_kia_mko_struct->st_dtmi_mf.MeanFrag.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_10_mf.Mean[ind] ,0, 4095));
        m_kia_mko_struct->st_dtmi_mf.SigmaFrag.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_10_mf.Mean[ind + 1] ,0, 200));
        ind = ind + 2;
    }
    for (uint16_t i = 0; i < m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.ObjFrag.size(); i++)
    {
        auto obj_frag = helpers::split_data_from_word(m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.ObjFrag[i]);
        auto mult_xy = helpers::split_data_from_word(m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.MultXY[i]);
        for (uint16_t num_el = 0; num_el < obj_frag.size(); num_el++)
        {
            m_kia_mko_struct->st_dtmi_mf.ObjFrag.push_back(std::make_tuple(obj_frag[num_el], -m_max_double_value, m_max_double_value));
            m_kia_mko_struct->st_dtmi_mf.MultXY.push_back(std::make_tuple(mult_xy[num_el], -m_max_double_value, m_max_double_value));
        }
    }

    for (uint16_t i = 0; i < m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.ZipXY.size(); i++)
    {
        auto zip_xy = helpers::split_data_from_word(m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.ZipXY[i]);
        uint16_t num_el = 0;
        while(num_el < zip_xy.size())
        {
            m_kia_mko_struct->st_dtmi_mf.ZipXY_X.push_back(std::make_tuple(zip_xy[num_el], -m_max_double_value, m_max_double_value));
            m_kia_mko_struct->st_dtmi_mf.ZipXY_Y.push_back(std::make_tuple(zip_xy[num_el + 1], -m_max_double_value, m_max_double_value));
            num_el = num_el + 2;
        }
    }

    ind = 0;
    while (ind < m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.ThFrag.size())
    {
        m_kia_mko_struct->st_dtmi_mf.ThFrag.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_9_mf.Xyc[ind] ,0, 2e16));
        ind = ind + 1;
    }

    ind = 0;
    while (ind < m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.HistPix.size())
    {
        m_kia_mko_struct->st_dtmi_mf.HistPix.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.HistPix[ind] ,0, 2e16));
        ind = ind + 1;
    }

    m_kia_mko_struct->st_dtmi_mf.ObjFrag.pop_back();
    m_kia_mko_struct->st_dtmi_mf.MultXY.pop_back();
    m_kia_mko_struct->st_dtmi_mf.ZipXY_X.push_back(std::make_tuple(0, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_dtmi_mf.ZipXY_Y.push_back(std::make_tuple(0, -m_max_double_value, m_max_double_value));

    std::array<std::vector<QString>, 10> is_norma_for_continue;
    for (auto& el : is_norma_for_continue)
        el.resize(m_kia_mko_struct->st_dtmi_mf.MeanFrag.size());
    for (uint16_t num = 0; num < m_kia_mko_struct->st_dtmi_mf.MeanFrag.size(); num++)
    {

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.XYc_x[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.XYc_x[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.XYc_x[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.XYc_x[num]))
        {
            is_norma_for_continue[0][num] = "норма";
        }
        else
        {
            is_norma_for_continue[0][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.XYc_y[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.XYc_y[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.XYc_y[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.XYc_y[num]))
        {
            is_norma_for_continue[1][num] = "норма";
        }
        else
        {
            is_norma_for_continue[1][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.MeanFrag[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.MeanFrag[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.MeanFrag[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.MeanFrag[num]))
        {
            is_norma_for_continue[2][num] = "норма";
        }
        else
        {
            is_norma_for_continue[2][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.SigmaFrag[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.SigmaFrag[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.SigmaFrag[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.SigmaFrag[num]))
        {
            is_norma_for_continue[3][num] = "норма";
        }
        else
        {
            is_norma_for_continue[3][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.ThFrag[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.ThFrag[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.ThFrag[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.ThFrag[num]))
        {
            is_norma_for_continue[4][num] = "норма";
        }
        else
        {
            is_norma_for_continue[4][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.ObjFrag[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.ObjFrag[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.ObjFrag[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.ObjFrag[num]))
        {
            is_norma_for_continue[5][num] = "норма";
        }
        else
        {
            is_norma_for_continue[5][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.MultXY[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.MultXY[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.MultXY[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.MultXY[num]))
        {
            is_norma_for_continue[6][num] = "норма";
        }
        else
        {
            is_norma_for_continue[6][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.ZipXY_X[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.ZipXY_X[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.ZipXY_X[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.ZipXY_X[num]))
        {
            is_norma_for_continue[7][num] = "норма";
        }
        else
        {
            is_norma_for_continue[7][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.ZipXY_Y[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.ZipXY_Y[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.ZipXY_Y[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.ZipXY_Y[num]))
        {
            is_norma_for_continue[8][num] = "норма";
        }
        else
        {
            is_norma_for_continue[8][num] = "не норма";
        }

        if (std::get<0>(m_kia_mko_struct->st_dtmi_mf.HistPix[num]) >= std::get<1>(m_kia_mko_struct->st_dtmi_mf.HistPix[num])
                && std::get<0>(m_kia_mko_struct->st_dtmi_mf.HistPix[num]) <= std::get<2>(m_kia_mko_struct->st_dtmi_mf.HistPix[num]))
        {
            is_norma_for_continue[9][num] = "норма";
        }
        else
        {
            is_norma_for_continue[9][num] = "не норма";
        }
    }

    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.nAr, 0x2001));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf.nAr, 0x2002));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_3_mf.nAr, 0x2003));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_4_mf.nAr, 0x2004));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_5_mf.nAr, 0x2005));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_6_mf.nAr, 0x2006));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_7_mf.nAr, 0x2007));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.nAr, 0x2008));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_9_mf.nAr, 0x2009));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_10_mf.nAr, 0x200A));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.nAr, 0x200B));
    m_kia_mko_struct->st_dtmi_mf.nAr.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.nAr, 0x200C));
    std::vector<QString> is_norma;
    is_norma.resize(m_kia_mko_struct->st_dtmi_mf.nAr.size());
    QString nAr;
    QString check_norma;
    for (uint16_t num_nAr = 0; num_nAr < m_kia_mko_struct->st_dtmi_mf.nAr.size(); num_nAr++)
    {
        if (m_kia_mko_struct->st_dtmi_mf.nAr[num_nAr].first != m_kia_mko_struct->st_dtmi_mf.nAr[num_nAr].second)
        {
            is_norma[num_nAr] = "не норма";
        }
        else
        {
            is_norma[num_nAr] = "норма";
        }
        nAr.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_mf.nAr[num_nAr].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_nAr], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Номер подмассива");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(nAr, m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.nAr, 0x2001, 0x2001));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(check_norma,  0, 0, 0));


    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_2_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_3_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_4_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_5_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_6_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_7_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_8_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_9_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_10_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_11_mf.cs, 0x42c3));
    m_kia_mko_struct->st_dtmi_mf.cs.push_back(std::make_pair(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.cs, 0x42c3));
    QString cs;
    QString calc_cs;
    check_norma.clear();
    for (uint16_t num_cc = 0; num_cc < m_kia_mko_struct->st_dtmi_mf.cs.size(); num_cc++)
    {
        if (m_kia_mko_struct->st_dtmi_mf.nAr[num_cc].first != m_kia_mko_struct->st_dtmi_mf.calc_cs[num_cc])
        {
            is_norma[num_cc] = "не норма";
        }
        else
        {
            is_norma[num_cc] = "норма";
        }
        cs.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_mf.cs[num_cc].first, 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        calc_cs.push_back(helpers::format_qstring(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_mf.calc_cs[num_cc], 16), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi));
        check_norma.push_back(helpers::format_qstring(is_norma[num_cc], m_kia_settings->m_format_for_desc.shift_for_dtmi));
    }

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Контрольная сумма");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(cs, m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.cs, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(calc_cs, m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.cs, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + " ");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(check_norma, 0, 0, 0));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.T), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.T, 0, 1e31));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время привязки информации");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tms), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tms, 0, 1000));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.KC1, 16), 4, '0'), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.KC2, 16), 4, '0'), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.KC2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Заводской номер");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.SerNum), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.SerNum, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Слово внутреннего теста");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.POST, 16), 4, '0'), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.POST, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Температура КМОП-матрицы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tcmv), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tcmv, -70, 150));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Среднее сигнала");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Mean), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Mean, 0, 4095));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "СКО сигнала");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Sigma), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Sigma, 0, 6553));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время экспонирования");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Texp), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Texp, 10, 400));
    QString dtmi_1_wd_num_13;
    uint16_t upper;
    if (type_orient == Bokzmf::TO_NO)
    {
        QString dtmi_1_wd_num_13 = "Число пикселей выше порог в НО/ТО";
        upper = 5000;
    }
    else
    {
        dtmi_1_wd_num_13 = "Число локализованных объектов в слежении";
        upper = 200;
    }

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + dtmi_1_wd_num_13);
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.PixCount_NumLoc), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.PixCount_NumLoc, 0, upper));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("14[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Количество зафиксированных объектов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumStore), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumStore, 0, 32));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("14[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Количество распознанных объектов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumDet), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumDet, 0, 30));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("15[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Количество прогнозируемых фрагментов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumProgFrag), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumProgFrag, 0, 150));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("15[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Количество фрагментов в обработке");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumFrag), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.NumFrag, 0, 30));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("16,17", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время последнего кватерниона");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tlast), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tlast, 0, 2e30));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Время последнего кватерниона");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tmslast), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Tmslast, 0, 1000));

    for (uint16_t num_q = 0; num_q < m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Qlst.size(); num_q++)
    {
        m_kia_mko_struct->st_dtmi_mf.qlst.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Qlst[num_q], -1, 1));
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(QString::number(num_q + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Последний кватернион ориентации, Qo" + QString::number(num_q));
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Qlst[num_q],'f',4), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.Qlst[num_q], -1, 1));
    }

    for (uint16_t num = 0; num < m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.HistDef.size(); num++)
    {
        m_kia_mko_struct->st_dtmi_mf.HistDef.push_back(std::make_tuple(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.HistDef[num], 0, 131072));
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(QString::number(num + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Гист. ярк. дефектных пикселей " + QString::number(num + 1));
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.HistDef[num]), m_kia_mko_struct->st_dtmi_mf.dtmi_1_mf.HistDef[num], 0, 131072));
    }

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers + m_kia_settings->m_format_for_desc.shift_description)
                                                          + helpers::format_qstring("Первый кадр", m_kia_settings->m_format_for_desc.shift_for_dtmi * 4)
                                                          + helpers::format_qstring("Второй кадр", m_kia_settings->m_format_for_desc.shift_for_dtmi * 4));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple("", 0, 0, 0));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers + m_kia_settings->m_format_for_desc.shift_description)
                                                          + helpers::format_qstring("X", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("B", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("S", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("X", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("Y", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("B", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("S", m_kia_settings->m_format_for_desc.shift_for_dtmi));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple("", 0, 0, 0));
    for (uint16_t ind = 0; ind < m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x.size(); ind++)
    {
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(QString::number(ind + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_x[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_y[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_b[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_0_s[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_x[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_y[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_b[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.rsLoc_1_s[ind]), 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi),
                        0, 0, 0
                        ));

        m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[0][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                    helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[1][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[2][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[3][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[4][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[5][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[6][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_rsLoc[7][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi),
                0, 0, 0
                ));
    }

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back("\n");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple("", 0, 0, 0));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(" ", m_kia_settings->m_format_for_desc.shift_for_numbers + m_kia_settings->m_format_for_desc.shift_description)
                                                          + helpers::format_qstring("Xc", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("Yc", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("MeanFrag", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("SigmaFrag", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("ThFrag", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("ObjFrag", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("MultXY", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("Zip_X", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("Zip_Y", m_kia_settings->m_format_for_desc.shift_for_dtmi)
                                                          + helpers::format_qstring("HistPix", m_kia_settings->m_format_for_desc.shift_for_dtmi));
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple("", 0, 0, 0));

    for (uint16_t ind = 0; ind < m_kia_mko_struct->st_dtmi_mf.XYc_x.size(); ind++)
    {
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring(QString::number(ind + 1), m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.XYc_x[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.XYc_y[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.MeanFrag[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.SigmaFrag[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.ThFrag[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.ObjFrag[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.MultXY[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.ZipXY_X[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.ZipXY_Y[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                        helpers::format_qstring(QString("%1").arg(QString::number(std::get<0>(m_kia_mko_struct->st_dtmi_mf.HistPix[ind])), 4, '0'), m_kia_settings->m_format_for_desc.shift_for_dtmi),
                        0, 0, 0
                        ));

        m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
        m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back
                (
                    std::make_tuple(
                        helpers::format_qstring(QString("%1").arg(is_norma_for_continue[0][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                    helpers::format_qstring(QString("%1").arg(is_norma_for_continue[1][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[2][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[3][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[4][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[5][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[6][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[7][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[8][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi) +
                helpers::format_qstring(QString("%1").arg(is_norma_for_continue[9][ind]), m_kia_settings->m_format_for_desc.shift_for_dtmi),
                0, 0, 0
                ));
    }

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Линейная скорость ось X, Vx");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Vx), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Vx, -8, 8));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("3", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Линейная скорость ось Y, Vy");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Vy), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Vy, -8, 8));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Линейная скорость ось Z, Vz");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Vz), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Vz, -8, 8));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Угловая скорость ось X, Wx");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Wx), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Wx, -0.17, 0.17));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Угловая скорость ось Y, Wy");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Wy), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Wy, -0.17, 0.17));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Угловая скорость ось Z, Wz");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Wz), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Wz, -0.17, 0.17));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("16, 17", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Эпоха");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Epoch), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Epoch, 0, 1));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("18[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Кол-во локализованных объектов на 1-ом кадре в ОО");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.NumL_0), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.NumL_0, 0, 200));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("18[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Кол-во локализованных объектов на 2-ом кадре в ОО");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.NumL_1), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.NumL_1, 0, 200));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Максимум гистограммы смещения объектов");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.maxH), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.maxH, -1, 200));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("20[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Смещение по оси X максимума гистограммы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.dxmaxH), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.dxmaxH, -45, 45));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("20[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Смещение по оси Y максимума гистограммы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.dymaxH), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.dymaxH, -45, 45));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("21[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Номер сектора");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.NumSec), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.NumSec, 0, 162));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("21[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Допуск распознавания");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Epsilon), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.Epsilon, 10, 200));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "Интервал времени");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.deltaT), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.deltaT, 125, 5000));

    m_kia_mko_struct->st_dtmi_mf.dtmi_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                          + "СКО решения системы");
    m_kia_mko_struct->st_dtmi_mf.dtmi_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.m_cur), m_kia_mko_struct->st_dtmi_mf.dtmi_12_mf.m_cur, 0, 100));
}

void Pio_bokzmf::decrypt(uint16_t key_arr, std::vector<RAW_DATA> raw_data)
{
    auto start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    std::vector<uint8_t> temp_data;
    uint16_t ind_data_manage = 0;
    uint16_t num_data = 0;
    for (uint16_t num_raw_data = 0; num_raw_data < raw_data.size(); num_raw_data++)
    {
        uint16_t num_el = 0;
        m_calculated_cs = calculate_cs(raw_data[num_raw_data].data);
        while(num_el < raw_data[num_raw_data].data.size())
        {
            temp_data.clear();
            for (uint16_t ind = num_el; ind < num_el + std::get<COUNT_EL_IN_ARR>(m_data_manage[key_arr][ind_data_manage]); ind++)
            {
                temp_data.push_back(raw_data[num_raw_data].data[ind]);
            }
            //std::cout << ind_data_manage << std::endl;
            int16_t type_data = std::get<0>(std::get<DM_TYPE_DATA>(m_data_manage[key_arr][ind_data_manage]));
            std::string name_arr = std::get<1>(std::get<DM_TYPE_DATA>(m_data_manage[key_arr][ind_data_manage]));
            int16_t type_arr = std::get<2>(std::get<DM_TYPE_DATA>(m_data_manage[key_arr][ind_data_manage]));
            if (type_data != ITS_REZERV)
            {
                //std::cout << ind_data_manage << " " << num_data << std::endl;
                m_prepare_data[type_data](key_arr, std::make_pair(type_arr, name_arr), num_data, temp_data,
                        std::get<RANGE_VALUE>(m_data_manage[key_arr][ind_data_manage]),
                        std::get<COEF_TO_SCALE>(m_data_manage[key_arr][ind_data_manage]),
                        std::get<TYPE_FORMAT>(m_data_manage[key_arr][ind_data_manage]),
                        std::get<DO_SWAP>(m_data_manage[key_arr][ind_data_manage]));
                num_data++;
            }

            num_el = num_el + std::get<COUNT_EL_IN_ARR>(m_data_manage[key_arr][ind_data_manage]);
            ind_data_manage = ind_data_manage + 1;
        }
    }
    auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    std::cout << end - start << std::endl;
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

void Pio_bokzmf::load_array_param_from_json()
{
    std::string path = "../kia_console/Kia_resource/";
    std::vector<std::pair<std::string, uint16_t>> path_json = {std::make_pair(path + "data_mf_shtmi1.json", MF_SHTMI1), std::make_pair(path + "data_mf_shtmi2.json", MF_SHTMI2),
                                                               std::make_pair(path + "data_mf_mshior.json", MF_MSHIOR), std::make_pair(path + "data_mf_dtmi.json", MF_DTMI)};//, std::make_pair(path + "data_mf_dtmi.json", MF_DTMI),
    //std::make_pair(path + "data_mf_mloc.json", MF_MLOC)
    for (auto path : path_json)
    {
        std::ifstream f(path.first, std::ifstream::in);
        json j;
        f >> j;
        uint16_t count_if_el_is_array = 0;
        for (uint16_t ind = 0; ind < j.size(); ind++)
        {
            QString type_data;
            if (j[std::to_string(ind)].contains("type_data"))
            {
                type_data = QString::fromStdString(j[std::to_string(ind)]["type_data"]);
                count_if_el_is_array++;
            }
            add_to_list_description(path.second, QString::fromStdString(j[std::to_string(ind)]["№ СД"]),
                    QString::fromStdString(j[std::to_string(ind)]["Наименование параметра"]),
                    type_data,
                    QString::fromStdString(j[std::to_string(ind)]["Условное обозначение"]));
        }
        m_kia_mko_struct->m_data[path.second].data.resize(m_kia_mko_struct->m_data[path.second].data_description.size() - count_if_el_is_array);
        f.close();
    }
}

void Pio_bokzmf::create_list_for_mpi_arrays()
{
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    for (uint16_t i = 0; i < 9; i++)
    {
        m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(0, 65535),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(VER, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI1].push_back(std::make_tuple(std::make_tuple(CS, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 5; i++)
    {
        m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 10; i++)
    {
        m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    for (uint16_t i = 0; i < 6; i++)
    {
        m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 2; i++)
    {
        m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_SHTMI2].push_back(std::make_tuple(std::make_tuple(CS, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_kia_mko_struct->m_data[MF_MSHIOR].data.resize(m_kia_mko_struct->m_data[MF_MSHIOR].data_description.size() + 3);

    m_index_mpi_array[MF_MSHIOR]["st1"] = 0;
    m_index_mpi_array[MF_MSHIOR]["st2"] = 1;
    m_index_mpi_array[MF_MSHIOR]["t"] = 2;
    m_index_mpi_array[MF_MSHIOR]["qo0"] = 4;
    m_index_mpi_array[MF_MSHIOR]["qo1"] = 5;
    m_index_mpi_array[MF_MSHIOR]["qo2"] = 6;
    m_index_mpi_array[MF_MSHIOR]["qo3"] = 7;
    m_index_mpi_array[MF_MSHIOR]["alpha"] = m_kia_mko_struct->m_data[MF_MSHIOR].data_description.size();
    m_index_mpi_array[MF_MSHIOR]["delta"] = m_kia_mko_struct->m_data[MF_MSHIOR].data_description.size() + 1;
    m_index_mpi_array[MF_MSHIOR]["azimuth"] = m_kia_mko_struct->m_data[MF_MSHIOR].data_description.size() + 2;

    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 4; i++)
    {
        m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 4, std::make_pair(-1, 1),
                                                           1, TDF_FLOAT, std::make_pair(false, true)));
    }

    for (uint16_t i = 0; i < 3; i++)
    {
        m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 4, std::make_pair(-0.1, 0.1),
                                                           1, TDF_FLOAT, std::make_pair(false, true)));
    }

    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 4; i++)
    {
        m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    for (uint16_t i = 0; i < 6; i++)
    {
        m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    for (uint16_t i = 0; i < 6; i++)
    {
        m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                           1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                       1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "nAr", TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 5; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(false, true)));
    }

    for (uint16_t i = 0; i < 4; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));
    for (uint16_t i = 0; i < 4; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_FLOAT, std::make_pair(false, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 8; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cs", TA_CS), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));



    std::array<std::string, 3> loc_name = {"rsloc0x", "rsloc0y", "rsloc0b"};

    for (uint16_t i = 0; i < 15 * 6; i++)
    {
        if (i % 15 == 0)
        {
            m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                             1, TDF_HEX, std::make_pair(false, true)));
            m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                             1, TDF_HEX, std::make_pair(false, true)));

            m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "nAr", TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                             1, TDF_HEX, std::make_pair(false, true)));
        }

        if (i != 0 && i % 45 == 0)
        {
            loc_name[0] = "rsloc1x";
            loc_name[1] = "rsloc1y";
            loc_name[2] = "rsloc1b";
        }
        //        2,3
        //        4,5
        //        6,7
        //        8,9
        //        10,11
        //        12,13
        //        14,15
        //        16,17
        //        18,19
        //        20,21
        //        22,23
        //        24,25
        //        26,27
        //        28,29,
        //        30,31
        std::string val;
        val = loc_name[i % loc_name.size()];
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_FLOAT), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_FLOAT, std::make_pair(true, true)));

        if (i % 15 == 0)
        {
            m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cs", TA_CS), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                             1, TDF_INT, std::make_pair(false, true)));
        }
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "nAr", TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    string loc_s = "rsloc0s";
    for (uint16_t i = 0; i < 30; i++)
    {

        if (i != 0 && i % 15 == 0)
        {
            loc_s = "rsloc1s";
        }
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, loc_s, TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));


    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cs", TA_CS), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));


    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "nAr", TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    std::array<std::string, 2> xcyc_name = {"xc", "yc"};
    for (uint16_t i = 0; i < 30; i++)
    {

        std::string val;
        val = xcyc_name[i % 2];
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));
    }


    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cs", TA_CS), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));


    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "nAr", TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    std::array<std::string, 2> mean_frag = {"meanfrag", "sigmafrag"};
    for (uint16_t i = 0; i < 30; i++)
    {

        std::string val;
        val = xcyc_name[i % 2];
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));
    }


    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cs", TA_CS), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));



    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "nAr", TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 15; i++)
    {

        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "thfrag", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));
    }

    for (uint16_t i = 0; i < 4; i++)
    {

        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "objfrag", TA_DIV_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));
    }

    for (uint16_t i = 0; i < 4; i++)
    {

        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "multxy", TA_DIV_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));
    }

    for (uint16_t i = 0; i < 7; i++)
    {

        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "zip", TA_DIV_UINT16_AND_DIV_ON_ARR_NAME), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cs", TA_CS), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));


    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));
    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "nAr", TA_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_HEX, std::make_pair(false, true)));


    for (uint16_t i = 0; i < 6; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(false, true)));
    }

    for (uint16_t i = 0; i < 8; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_HEX, std::make_pair(false, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 4, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_FLOAT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 2; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 4; i++)
    {
        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT8, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(false, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));

    for (uint16_t i = 0; i < 16; i++)
    {

        m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "histpix", TA_DIV_UINT16), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                         1, TDF_INT, std::make_pair(true, true)));
    }

    m_data_manage[MF_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cs", TA_CS), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                     1, TDF_INT, std::make_pair(false, true)));
}

void Pio_bokzmf::create_list_to_prepare_data()
{
    auto add_to_int16_t = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        int16_t temp;
        memcpy(&temp, &value[0], sizeof(temp));
        QString is_norma;
        if (temp * scale >= range.first && temp * scale <= range.second)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }

        auto format_str = get_format_str(type_format, static_cast<int16_t>(temp * scale));

        m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(format_str, temp * scale, is_norma);
    };
    m_prepare_data.push_back(add_to_int16_t);

    auto add_to_int32_t = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        int32_t temp;
        memcpy(&temp, &value[0], sizeof(temp));

        if (do_proc.first)
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

        auto format_str = QString::number(static_cast<int32_t>(temp * scale));
        m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(format_str, temp * scale, is_norma);
    };
    m_prepare_data.push_back(add_to_int32_t);

    auto add_to_float = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        int32_t temp = 0;
        memcpy(&temp, &value[0], sizeof(temp));
        if (do_proc.first)
            temp = swapHex(temp);
        float temp_float = 0;
        if (do_proc.second)
            temp_float = uint32_to_float(temp);
        QString is_norma;
        if (temp_float * scale >= range.first && temp_float * scale <= range.second)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }
        auto format_str = QString::number(static_cast<float>(temp_float * scale), 'f',4);
        m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(format_str, temp_float * scale, is_norma);
    };
    m_prepare_data.push_back(add_to_float);

    auto add_to_int8_t = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
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
            auto format_str = get_format_str(type_format, static_cast<int8_t>(el * scale));
            m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(format_str, el * scale, is_norma);
        }
    };
    m_prepare_data.push_back(add_to_int8_t);

    auto convert_to_ver = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        uint16_t temp;
        memcpy(&temp, &value[0], sizeof(temp));

        QString is_norma;
        if (temp * scale >= range.first && temp * scale <= range.second)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }
        auto ver1 = (temp >> 12);
        auto ver2 = ((temp & 0x0fff) >> 8);
        auto ver3 = ((temp & 0x00ff));

        m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(QString::number(ver1)
                                                                           + "." + QString::number(ver2)
                                                                           + "." + QString::number(ver3), temp * scale, is_norma);
    };
    m_prepare_data.push_back(convert_to_ver);

    auto convert_cs = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        uint16_t temp;
        memcpy(&temp, &value[0], sizeof(temp));

        QString is_norma;
        if (temp * scale == m_calculated_cs)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }

        m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(QString::number(temp * scale) + "(" + QString::number(m_calculated_cs) + ")",
                                                                           temp * scale, is_norma);
    };
    m_prepare_data.push_back(convert_cs);

    std::vector<std::function<std::vector<std::pair<std::string, std::tuple<QString, double, QString>>> (std::vector<uint8_t> value, std::string name_arr, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)>> list_to_prepare_data_for_arr;
    auto arr_float = [this](std::vector<uint8_t> value, std::string name_arr, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
    {
        std::vector<std::pair<std::string, std::tuple<QString, double, QString>>> data;
        int32_t temp = 0;
        memcpy(&temp, &value[0], sizeof(temp));
        if (do_proc.first)
            temp = swapHex(temp);
        float temp_float = 0.0;
        if (do_proc.second)
            temp_float = uint32_to_float(temp);
        QString is_norma;
        if (temp_float * scale >= range.first && temp_float * scale <= range.second)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }
        auto format_str = QString::number(static_cast<float>(temp_float * scale), 'f',4);
        std::cout << name_arr << " " <<  format_str.toStdString() << std::endl;
        data.push_back(std::make_pair(name_arr, make_tuple(format_str, temp_float * scale, is_norma)));
        return data;
    };
    list_to_prepare_data_for_arr.push_back(arr_float);

    auto arr_uint16 = [this](std::vector<uint8_t> value, std::string name_arr, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
    {
        int16_t temp;
        memcpy(&temp, &value[0], sizeof(temp));

        std::vector<std::pair<std::string, std::tuple<QString, double, QString>>> data;
        QString is_norma;
        if (temp * scale >= range.first && temp * scale <= range.second)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }

        auto format_str = get_format_str(type_format, static_cast<int16_t>(temp * scale));
        data.push_back(std::make_pair(name_arr, make_tuple(format_str, temp * scale, is_norma)));
        return data;
    };
    list_to_prepare_data_for_arr.push_back(arr_uint16);

    auto arr_uint8 = [this](std::vector<uint8_t> value, std::string name_arr, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
    {
        std::vector<std::pair<std::string, std::tuple<QString, double, QString>>> data;
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
            auto format_str = get_format_str(type_format, static_cast<int8_t>(el * scale));
            data.push_back(std::make_pair(name_arr, make_tuple(format_str, el * scale, is_norma)));
        }


        return data;
    };
    list_to_prepare_data_for_arr.push_back(arr_uint8);

    auto arr_div_uint16 = [this](std::vector<uint8_t> value, std::string name_arr, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
    {
        std::vector<std::pair<std::string, std::tuple<QString, double, QString>>> data;
        int16_t temp;
        memcpy(&temp, &value[0], sizeof(temp));
        auto div_array = helpers::split_data_from_word(temp);
        for (auto el_arr : div_array)
        {
            QString is_norma;
            if (el_arr * scale >= range.first && el_arr * scale <= range.second)
            {
                is_norma.clear();
            }
            else
            {
                is_norma = "(не норма)";
            }

            auto format_str = get_format_str(type_format, static_cast<int16_t>(el_arr * scale));
            std::cout << name_arr << " " <<  format_str.toStdString() << std::endl;
            data.push_back(std::make_pair(name_arr, make_tuple(format_str, el_arr * scale, is_norma)));
        }
        return data;
    };
    list_to_prepare_data_for_arr.push_back(arr_div_uint16);

    auto arr_cs = [this](std::vector<uint8_t> value, std::string name_arr, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
    {
        std::vector<std::pair<std::string, std::tuple<QString, double, QString>>> data;
        int16_t temp;
        memcpy(&temp, &value[0], sizeof(temp));
        QString is_norma;
        if (temp * scale == m_calculated_cs)
        {
            is_norma.clear();
        }
        else
        {
            is_norma = "(не норма)";
        }

        auto format_str = QString::number(temp * scale) + "(" + QString::number(m_calculated_cs) + ")";
        data.push_back(std::make_pair(name_arr, make_tuple(format_str, temp * scale, is_norma)));
        return data;
    };
    list_to_prepare_data_for_arr.push_back(arr_cs);

    auto arr_div_uint16_with_dif_name = [this](std::vector<uint8_t> value, std::string name_arr, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
    {
        std::vector<std::pair<std::string, std::tuple<QString, double, QString>>> data;
        int16_t temp;
        memcpy(&temp, &value[0], sizeof(temp));
        auto div_array = helpers::split_data_from_word(temp);
        for (uint16_t num_arr = 0; num_arr < div_array.size(); num_arr++)
        {
            std::string add_name;
            QString is_norma;
            if (div_array[num_arr] * scale >= range.first && num_arr * scale <= range.second)
            {
                is_norma.clear();
            }
            else
            {
                is_norma = "(не норма)";
            }
            if (num_arr % 2 == 0)
            {
                add_name = name_arr + "_x";
            }
            else
            {
                add_name = name_arr + "_y";
            }
            auto format_str = get_format_str(type_format, static_cast<int16_t>(div_array[num_arr] * scale));
            data.push_back(std::make_pair(add_name, make_tuple(format_str, div_array[num_arr] * scale, is_norma)));
        }
        return data;
    };
    list_to_prepare_data_for_arr.push_back(arr_div_uint16_with_dif_name);

    auto add_to_arr = [this, list_to_prepare_data_for_arr](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double> range,
            double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        auto data = list_to_prepare_data_for_arr[type_name_arr.first](value, type_name_arr.second, do_proc, range, scale, type_format);
        for (const auto& el : data)
            m_kia_mko_struct->m_data[key_arr].data_array[el.first].push_back(el.second);
        num_data--;
    };
    m_prepare_data.push_back(add_to_arr);
}


void Pio_bokzmf::decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord)
{
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.clear();
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.clear();
    SHTMI1raw_MF shmti1_raw;
    memcpy(&shmti1_raw, &dataWord,sizeof(shmti1_raw));
    m_kia_mko_struct->st_shtmi1_mf.nAr = shmti1_raw.nAr;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Номер подмассива");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.nAr, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.nAr, 0x1001, 0x1001));


    m_kia_mko_struct->st_shtmi1_mf.T = (shmti1_raw.T);
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.T), m_kia_mko_struct->st_shtmi1_mf.T, 0, 2e31));

    m_kia_mko_struct->st_shtmi1_mf.T = shmti1_raw.Tms;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Tms), m_kia_mko_struct->st_shtmi1_mf.Tms, 0, 1000));

    m_kia_mko_struct->st_shtmi1_mf.KC1 = shmti1_raw.KC1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.KC1), m_kia_mko_struct->st_shtmi1_mf.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1_mf.KC2 = shmti1_raw.KC2;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.KC2), m_kia_mko_struct->st_shtmi1_mf.KC2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1_mf.SerNum = shmti1_raw.SerNum;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Заводской номер");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.SerNum), m_kia_mko_struct->st_shtmi1_mf.SerNum, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1_mf.POST = shmti1_raw.POST;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.POST, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.POST, -m_max_double_value, m_max_double_value));

    uint32_t foc = swapHex(shmti1_raw.Foc);
    memcpy(&m_kia_mko_struct->st_shtmi1_mf.Foc, &foc, sizeof(m_kia_mko_struct->st_shtmi1_mf.Foc));
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("9, 10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Фокусное расстояние");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Foc), m_kia_mko_struct->st_shtmi1_mf.Foc, 31, 44));

    m_kia_mko_struct->st_shtmi1_mf.Xo = swapHex(shmti1_raw.Xo);
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("11, 12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Координата Xo гл. точки ВСК");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Xo), m_kia_mko_struct->st_shtmi1_mf.Xo, -4, 4));

    m_kia_mko_struct->st_shtmi1_mf.Yo = swapHex(shmti1_raw.Yo);
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("13, 14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Координата Yo гл. точки ВСК");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Xo), m_kia_mko_struct->st_shtmi1_mf.Yo, -4, 4));

    m_kia_mko_struct->st_shtmi1_mf.Texp = shmti1_raw.Texp;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("15", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время экспонирования");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Texp), m_kia_mko_struct->st_shtmi1_mf.Texp, 10, 1023));

    m_kia_mko_struct->st_shtmi1_mf.Mean = shmti1_raw.Mean;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("16", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Среднее значение синала");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Mean), m_kia_mko_struct->st_shtmi1_mf.Mean, 0, 4095));

    m_kia_mko_struct->st_shtmi1_mf.Sigma = shmti1_raw.Sigma;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "СКО сигнала");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Sigma), m_kia_mko_struct->st_shtmi1_mf.Sigma, 0, 16384));


    m_kia_mko_struct->st_shtmi1_mf.rezerv1 = shmti1_raw.rezerv1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Резерв");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.rezerv1), m_kia_mko_struct->st_shtmi1_mf.rezerv1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1_mf.rezerv2 = shmti1_raw.rezerv2;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Резерв");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.rezerv2), m_kia_mko_struct->st_shtmi1_mf.rezerv2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi1_mf.cntUPN = shmti1_raw.cntUPN;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик КС УПН");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.cntUPN), m_kia_mko_struct->st_shtmi1_mf.cntUPN, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.Tcmv = shmti1_raw.Tcmv;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("21", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Температура КМОП-матрицы");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Tcmv), m_kia_mko_struct->st_shtmi1_mf.Tcmv, -75, 150));

    m_kia_mko_struct->st_shtmi1_mf.ConfCS = shmti1_raw.ConfCS;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма конфигурации ПЛИС");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.ConfCS), m_kia_mko_struct->st_shtmi1_mf.ConfCS, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.desc = shmti1_raw.desc;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Дескриптор передачи данных");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.desc), m_kia_mko_struct->st_shtmi1_mf.desc, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.ogConstCrc = shmti1_raw.ogConstCrc;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма констант ЭО ЗД");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.ogConstCrc, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.ogConstCrc, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.CatCS0 = shmti1_raw.CatCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма каталога 0");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.CatCS0, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.CatCS0, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.CatCS1 = shmti1_raw.CatCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма каталога 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.CatCS1, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.CatCS1, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.ConstCS0 = shmti1_raw.ConstCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("27", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма констант 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.ConstCS0, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.ConstCS0, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.ConstCS1 = shmti1_raw.ConstCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма констант 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.ConstCS1, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.ConstCS1, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.ProgCS0 = shmti1_raw.ProgCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("29", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма программы 0");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.ProgCS0, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.ProgCS0, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.ProgCS1 = shmti1_raw.ProgCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма программы 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.ProgCS1, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.ProgCS1, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.Ver1 = (shmti1_raw.Ver >> 12);
    m_kia_mko_struct->st_shtmi1_mf.Ver2 = ((shmti1_raw.Ver & 0x0fff) >> 8);
    m_kia_mko_struct->st_shtmi1_mf.Ver3 = ((shmti1_raw.Ver & 0x00ff));
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("31", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Номер версии программы");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver1)
                                                                              + "." + QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver2)
                                                                              + "." + QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver3), m_kia_mko_struct->st_shtmi1_mf.Ver1, 0, 65535));

    m_kia_mko_struct->st_shtmi1_mf.cs = shmti1_raw.cs;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi1_mf.cs, 16), 4, '0'), m_kia_mko_struct->st_shtmi1_mf.cs, 0, 65535));

    auto calc_cs = calculate_cs(dataWord);
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(calc_cs, 16), 4, '0'), calc_cs, 0, 2e31));

}

void Pio_bokzmf::decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord)
{
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.clear();
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.clear();
    SHTMI2raw_MF shtmi2_raw;
    memcpy(&shtmi2_raw,&dataWord,sizeof(shtmi2_raw));
    m_kia_mko_struct->st_shtmi2_mf.nAr = shtmi2_raw.nAr;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Служебное слово 1");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.nAr, 16), 4, '0'), m_kia_mko_struct->st_shtmi2_mf.nAr, 0x1002, 0x1002));

    m_kia_mko_struct->st_shtmi2_mf.T = (shtmi2_raw.T);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("2,3", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.T), m_kia_mko_struct->st_shtmi2_mf.T, 0, 2e30));

    m_kia_mko_struct->st_shtmi2_mf.Tms = (shtmi2_raw.Tms);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Tms), m_kia_mko_struct->st_shtmi2_mf.Tms, 0, 1000));

    m_kia_mko_struct->st_shtmi2_mf.KC1 = shtmi2_raw.KC1;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.KC1, 16), 4, '0'), m_kia_mko_struct->st_shtmi2_mf.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi2_mf.KC2 = shtmi2_raw.KC2;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("6", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.KC2, 16), 4, '0'), m_kia_mko_struct->st_shtmi2_mf.KC2, -m_max_double_value, m_max_double_value));


    m_kia_mko_struct->st_shtmi2_mf.SerNum = shtmi2_raw.SerNum;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Заводской номер");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.SerNum), m_kia_mko_struct->st_shtmi2_mf.SerNum, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi2_mf.POST = shtmi2_raw.POST;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("8", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Слово внутреннего теста");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_shtmi2_mf.POST, 16), 4, '0'), m_kia_mko_struct->st_shtmi2_mf.POST, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_shtmi2_mf.Texp = shtmi2_raw.Texp;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("9", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время экспонирования");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Texp), m_kia_mko_struct->st_shtmi2_mf.Texp, 10, 1023));

    m_kia_mko_struct->st_shtmi2_mf.Nusd = shtmi2_raw.Nusd;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("10", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик полученных УСД");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nusd), m_kia_mko_struct->st_shtmi2_mf.Nusd, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.Nno = shtmi2_raw.Nno;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("11", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик НО");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nno), m_kia_mko_struct->st_shtmi2_mf.Nno, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.Nnosl = shtmi2_raw.Nnosl;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("12", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Число переходов от НО к слежению");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nnosl), m_kia_mko_struct->st_shtmi2_mf.Nnosl, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.Nto = shtmi2_raw.Nto;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("13", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик ТО");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nto), m_kia_mko_struct->st_shtmi2_mf.Nto, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.Ntosl = shtmi2_raw.Ntosl;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("14", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Число переходов от ТО к слежению");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Ntosl), m_kia_mko_struct->st_shtmi2_mf.Ntosl, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.Nsl = swapHex(shtmi2_raw.Nsl);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("15,16", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик слежения");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.Nsl), m_kia_mko_struct->st_shtmi2_mf.Nsl, 0, 2e32));

    m_kia_mko_struct->st_shtmi2_mf.eCount1 = (shtmi2_raw.eCount1);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("17", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 01)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount1), m_kia_mko_struct->st_shtmi2_mf.eCount1, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount2 = (shtmi2_raw.eCount2);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("18", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 02)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount2), m_kia_mko_struct->st_shtmi2_mf.eCount2, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount3 = (shtmi2_raw.eCount3);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 03)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount3), m_kia_mko_struct->st_shtmi2_mf.eCount3, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount4 = (shtmi2_raw.eCount4);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 04)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount4), m_kia_mko_struct->st_shtmi2_mf.eCount4, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount5 = (shtmi2_raw.eCount5);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("21", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 05)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount5), m_kia_mko_struct->st_shtmi2_mf.eCount5, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount6 = (shtmi2_raw.eCount6);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("22", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 06, 07)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount6), m_kia_mko_struct->st_shtmi2_mf.eCount6, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount7 = (shtmi2_raw.eCount7);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 08, 0A)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount7), m_kia_mko_struct->st_shtmi2_mf.eCount7, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount8 = (shtmi2_raw.eCount8);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 09, 0B)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount8), m_kia_mko_struct->st_shtmi2_mf.eCount8, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount9 = (shtmi2_raw.eCount9);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 0C)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount9), m_kia_mko_struct->st_shtmi2_mf.eCount9, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount10 = (shtmi2_raw.eCount10);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 0D)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount10), m_kia_mko_struct->st_shtmi2_mf.eCount10, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount11 = shtmi2_raw.eCount11;
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("27[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код XE)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount11), m_kia_mko_struct->st_shtmi2_mf.eCount11, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.eCount12 = (shtmi2_raw.eCount12);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("27[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код XF)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount12), m_kia_mko_struct->st_shtmi2_mf.eCount12, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.eCount13 = (shtmi2_raw.eCount13);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("28[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 81, 82)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount13), m_kia_mko_struct->st_shtmi2_mf.eCount13, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.eCount14 = (shtmi2_raw.eCount14);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("28[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик статуса St2 (код 83, 84, 86)");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount14), m_kia_mko_struct->st_shtmi2_mf.eCount14, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.eCount15 = (shtmi2_raw.eCount15);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("29[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик сбоев внутренней памяти");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount15), m_kia_mko_struct->st_shtmi2_mf.eCount15, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.eCount16 = (shtmi2_raw.eCount16);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("29[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик сбоев внешней памяти");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount16), m_kia_mko_struct->st_shtmi2_mf.eCount16, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.eCount17 = (shtmi2_raw.eCount17);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("30", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик ошибок регистров датчика изображений");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount17), m_kia_mko_struct->st_shtmi2_mf.eCount17, 0, 65535));

    m_kia_mko_struct->st_shtmi2_mf.eCount18 = (shtmi2_raw.eCount18);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("31[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик записей протокола событий");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount18), m_kia_mko_struct->st_shtmi2_mf.eCount18, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.eCount19 = (shtmi2_raw.eCount19);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("31[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Счетчик горячих рестартов");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.eCount19), m_kia_mko_struct->st_shtmi2_mf.eCount19, 0, 255));

    m_kia_mko_struct->st_shtmi2_mf.cs = (shtmi2_raw.cs);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Контрольная сумма");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_shtmi2_mf.cs), m_kia_mko_struct->st_shtmi2_mf.cs, 0, 2e31));

    auto calc_cs = calculate_cs(dataWord);
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_name.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + " ");
    m_kia_mko_struct->st_shtmi2_mf.shtmi2_list_data.push_back(std::make_tuple(QString::number(calc_cs), calc_cs, 0, 2e31));

}

void Pio_bokzmf::decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t &bshv)
{
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.clear();
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.clear();
    MSHIORRaw_MF mshiorRaw;
    memcpy(&mshiorRaw,&dataWord,sizeof(mshiorRaw));
    m_kia_mko_struct->st_mshior_mf.KC1 = mshiorRaw.KC1;
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("1", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Код состояния 1 (Status1)");
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior_mf.KC1, 16), 4, '0'), m_kia_mko_struct->st_mshior_mf.KC1, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mshior_mf.KC2 = mshiorRaw.KC2;
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("2", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Код состояния 2 (Status2)");
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString("0x%1").arg(QString::number(m_kia_mko_struct->st_mshior_mf.KC2, 16), 4, '0'), m_kia_mko_struct->st_mshior_mf.KC2, -m_max_double_value, m_max_double_value));

    m_kia_mko_struct->st_mshior_mf.T = (mshiorRaw.T);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.T)
                                                                              + " (" + QString::number((int)(bshv / m_kia_settings->m_freq_bokz - m_kia_mko_struct->st_mshior_mf.T)) +  ")", m_kia_mko_struct->st_mshior_mf.T, 0, 2e30));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("3,4", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время привязки информации");

    m_kia_mko_struct->st_mshior_mf.Tms = (mshiorRaw.Tms);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Tms), m_kia_mko_struct->st_mshior_mf.Tms, 0, 1000));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("5", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Время привязки информации");
    m_kia_mko_struct->st_mshior_mf.Qo0 = uint32_to_float(mshiorRaw.Qo0);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Qo0,'f',8), m_kia_mko_struct->st_mshior_mf.Qo0, 0, 1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("6,7", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Кватернион ориентации, Qo0");


    m_kia_mko_struct->st_mshior_mf.Qo1 = uint32_to_float((mshiorRaw.Qo1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Qo1,'f',8), m_kia_mko_struct->st_mshior_mf.Qo1, -1, 1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("8,9", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Кватернион ориентации, Qo1");

    m_kia_mko_struct->st_mshior_mf.Qo2 = uint32_to_float((mshiorRaw.Qo2));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Qo2,'f',8), m_kia_mko_struct->st_mshior_mf.Qo2, -1, 1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("10,11", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Кватернион ориентации, Qo2");

    m_kia_mko_struct->st_mshior_mf.Qo3 = uint32_to_float((mshiorRaw.Qo3));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Qo3,'f',8), m_kia_mko_struct->st_mshior_mf.Qo3, -1, 1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("12,13", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Кватернион ориентации, Qo3");

    m_kia_mko_struct->st_mshior_mf.wox = uint32_to_float((mshiorRaw.wox));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.wox,'f',8), m_kia_mko_struct->st_mshior_mf.wox, -0.1, 0.1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("14,15", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Угловая скорость по оптическим измерениям, Wox");

    m_kia_mko_struct->st_mshior_mf.woy = uint32_to_float((mshiorRaw.woy));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("16,17", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Угловая скорость по оптическим измерениям, Woy");
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.woy,'f', 8), m_kia_mko_struct->st_mshior_mf.woy, -0.1, 0.1));

    m_kia_mko_struct->st_mshior_mf.woz = uint32_to_float((mshiorRaw.woz));
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.woz,'f', 8), m_kia_mko_struct->st_mshior_mf.woz, -0.1, 0.1));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("18,19", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Угловая скорость по оптическим измерениям, Woz");

    m_kia_mko_struct->st_mshior_mf.Tcmv = mshiorRaw.Tcmv / 10;
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Tcmv), m_kia_mko_struct->st_mshior_mf.Tcmv, -75, 150));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Температура КМОП-матрицы");

    m_kia_mko_struct->st_mshior_mf.NumFrag = (mshiorRaw.NumFrag);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.NumFrag), m_kia_mko_struct->st_mshior_mf.NumFrag, 0, 30));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("21[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Число выбранных фрагментов");

    m_kia_mko_struct->st_mshior_mf.NumLoc_0 = (mshiorRaw.NumLoc_0);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.NumLoc_0),
                                                                              m_kia_mko_struct->st_mshior_mf.NumLoc_0, 0, 200));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("21[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Число локализованных объектов");

    m_kia_mko_struct->st_mshior_mf.NumDet = (mshiorRaw.NumDet);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.NumDet), m_kia_mko_struct->st_mshior_mf.NumDet, 0, 30));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("22[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Число распознанных объектов");

    m_kia_mko_struct->st_mshior_mf.LightMv5 = (mshiorRaw.LightMv5);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.LightMv5), m_kia_mko_struct->st_mshior_mf.LightMv5, 0, 12750));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("22[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Средняя яркость 5 звездной величины");

    m_kia_mko_struct->st_mshior_mf.Mean = (mshiorRaw.Mean);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Mean), m_kia_mko_struct->st_mshior_mf.Mean, 0, 4095));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("23", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Среднее сигнала");

    m_kia_mko_struct->st_mshior_mf.Sigma = (mshiorRaw.Sigma / 10);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.Sigma), m_kia_mko_struct->st_mshior_mf.Sigma, 0, 4095));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("24", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "СКО сигнала");

    m_kia_mko_struct->st_mshior_mf.ThMax = (mshiorRaw.ThMax);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.ThMax), m_kia_mko_struct->st_mshior_mf.ThMax, 0, 4095));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("25", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Максимальный порог на исходных фрагментах");

    m_kia_mko_struct->st_mshior_mf.m_cur = (mshiorRaw.m_cur);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.m_cur), m_kia_mko_struct->st_mshior_mf.m_cur, 0, 05));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("26", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "СКО решения системы");

    m_kia_mko_struct->st_mshior_mf.P = (mshiorRaw.P);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.P), m_kia_mko_struct->st_mshior_mf.P, 0, 100));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("27", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Процент заполнения поля зрения при калибровке");

    m_kia_mko_struct->st_mshior_mf.dpf_state = (mshiorRaw.dpf_state);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_state), m_kia_mko_struct->st_mshior_mf.dpf_state, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("28", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Код состояния дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_total = (mshiorRaw.dpf_total);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_total), m_kia_mko_struct->st_mshior_mf.dpf_total, 0, 255));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("29[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Количество отобранных дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_hotpixels = (mshiorRaw.dpf_hotpixels);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_hotpixels), m_kia_mko_struct->st_mshior_mf.dpf_hotpixels, 0, 130560));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("29[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Количество подтвержденных дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_updated = (mshiorRaw.dpf_updated);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_updated), m_kia_mko_struct->st_mshior_mf.dpf_updated, 0, 6400));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("30[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Количество обновленных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_rejected = (mshiorRaw.dpf_rejected);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_rejected), m_kia_mko_struct->st_mshior_mf.dpf_rejected, 0, 1023));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("30[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Количество отклонных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_threshold = (mshiorRaw.dpf_threshold);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_threshold), m_kia_mko_struct->st_mshior_mf.dpf_threshold, 0, 255));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("31[7:0]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Порог накопления дефектных пикселей");

    m_kia_mko_struct->st_mshior_mf.dpf_applied = (mshiorRaw.dpf_applied);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.dpf_applied), m_kia_mko_struct->st_mshior_mf.dpf_applied, 0, 1023));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("31[15:8]", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Количество скорректированных пикселей");

    m_kia_mko_struct->st_mshior_mf.ser_num = (mshiorRaw.ser_num);
    m_kia_mko_struct->st_mshior_mf.mshior_list_data.push_back(std::make_tuple(QString::number(m_kia_mko_struct->st_mshior_mf.ser_num), m_kia_mko_struct->st_mshior_mf.ser_num, -m_max_double_value, m_max_double_value));
    m_kia_mko_struct->st_mshior_mf.mshior_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                              + "Заводской номер");

    m_kia_settings->m_data_for_db->m_norm_qaor = sqrt(pow(m_kia_mko_struct->st_mshior_mf.Qo0,2) + pow(m_kia_mko_struct->st_mshior_mf.Qo1,2) + pow(m_kia_mko_struct->st_mshior_mf.Qo2, 2)  + pow(m_kia_mko_struct->st_mshior_mf.Qo3,2));
}

void Pio_bokzmf::decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr)
{
    CHPN_1_MF_raw chpn_1_MF_raw;
    CHPN_2_MF_raw chpn_2_MF_raw;
    switch(num_arr)
    {
    case 0:
        memcpy(&chpn_1_MF_raw, &dataWord, sizeof(chpn_1_MF_raw));
        chpn_1_MF_raw.Epsilon = swapHex(chpn_1_MF_raw.Epsilon);
        chpn_1_MF_raw.Foc = swapHex(chpn_1_MF_raw.Foc);
        chpn_1_MF_raw.XG = swapHex(chpn_1_MF_raw.YG);
        chpn_1_MF_raw.YG = swapHex(chpn_1_MF_raw.YG);
        for (auto& el : chpn_1_MF_raw.m_pr)
            el = swapHex(el);
        memcpy(&m_kia_mko_struct->st_chpn_mf.chpn_1_mf, &chpn_1_MF_raw, sizeof(m_kia_mko_struct->st_chpn_mf.chpn_1_mf));

        break;
    case 1:
        memcpy(&chpn_2_MF_raw, &dataWord, sizeof(chpn_2_MF_raw));
        chpn_2_MF_raw.extBrightThres = swapHex(chpn_2_MF_raw.extBrightThres);
        chpn_2_MF_raw.extOmegaLocalThres = swapHex(chpn_2_MF_raw.extOmegaLocalThres);
        chpn_2_MF_raw.KSigmaNO = swapHex(chpn_2_MF_raw.KSigmaNO);
        chpn_2_MF_raw.KSigmaSL = swapHex(chpn_2_MF_raw.KSigmaSL);
        memcpy(&m_kia_mko_struct->st_chpn_mf.chpn_2_mf, &chpn_2_MF_raw, sizeof(m_kia_mko_struct->st_chpn_mf.chpn_2_mf));
        break;
    }
}

void Pio_bokzmf::decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr)
{
    CHKD_1_MF_raw chkd_1_MF_raw;
    CHKD_2_MF_raw chkd_2_MF_raw;
    switch(num_arr)
    {
    case 0:
        memcpy(&chkd_1_MF_raw, &dataWord, sizeof(chkd_1_MF_raw));
        for (auto& el : chkd_1_MF_raw.KofDX)
            el = swapHex(el);
        memcpy(&m_kia_mko_struct->st_chkd_mf.chkd_1_mf, &chkd_1_MF_raw, sizeof(m_kia_mko_struct->st_chkd_mf.chkd_1_mf));

        break;
    case 1:
        memcpy(&chkd_2_MF_raw, &dataWord, sizeof(chkd_2_MF_raw));
        for (auto& el : chkd_2_MF_raw.KofDY)
            el = swapHex(el);
        memcpy(&m_kia_mko_struct->st_chkd_mf.chkd_2_mf, &chkd_2_MF_raw, sizeof(m_kia_mko_struct->st_chkd_mf.chkd_2_mf));
        break;
    }
}



Pio_bokzmf::~Pio_bokzmf()
{

}

float Pio_bokzmf::uint32_to_float(uint32_t value)
{
    auto result = *(float*)(&value);
    return result;
}

uint16_t Pio_bokzmf::calculate_cs(array<uint8_t, constants::packetSize * 2> dataWord)
{
    std::array<uint16_t, 31> temp;
    memcpy(&temp, &dataWord[2 * 2], sizeof(temp));
    return Crc16(temp.data(), temp.size());
}

uint16_t Pio_bokzmf::calculate_cs(array<uint16_t, constants::packetSize> dataWord)
{
    std::array<uint16_t, 31> temp;
    memcpy(&temp, &dataWord[2 * 2], sizeof(temp));
    return Crc16(temp.data(), temp.size());
}
