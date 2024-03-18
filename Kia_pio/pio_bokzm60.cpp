#include "pio_bokzm60.h"
#include <limits>
Pio_bokzm60::Pio_bokzm60(std::shared_ptr<Kia_mko_struct> kia_mko_struct, std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_mko_struct(kia_mko_struct),
    m_kia_settings(kia_settings)
{
    load_array_param_from_json();
    create_list_to_prepare_data();
    create_list_for_mpi_arrays();

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

}

void Pio_bokzm60::parse_dtmi(uint16_t type_orient)
{

}

void Pio_bokzm60::decrypt(uint16_t key_arr, std::vector<RAW_DATA> raw_data, uint16_t num_arr)
{
    auto start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    std::vector<uint16_t> temp_data;
    uint16_t ind_data_manage = 0;
    uint16_t num_data = 0;
    for (uint16_t num_raw_data = 0; num_raw_data < raw_data.size(); num_raw_data++)
    {
        uint16_t num_el = 0;
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

void Pio_bokzm60::decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord)
{

}

void Pio_bokzm60::decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord)
{

}

void Pio_bokzm60::decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t &bshv)
{

}

void Pio_bokzm60::decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr)
{

}

void Pio_bokzm60::decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr)
{

}

std::map<uint16_t, std::map<string, uint16_t> > Pio_bokzm60::get_index_mpi_array()
{
    return m_index_mpi_array;
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

float Pio_bokzm60::uint32_to_float(uint32_t value)
{
    uint32_t masca = 0x00000001;
    uint32_t temp = 0;
    float result = 0.0;
    for (int i = 0; i < 32; ++i)
    {
        temp = (value>>i) & (masca);
        if (i < 31)
        {
            if (temp == 1)
            {
                //printf("%04x\n", temp);
                result = result + pow(2,(-31 + i));
                //cout<<" "<<i<<" "<<result<<endl;

            }
        }
        if (i == 31)
        {
            if (temp == 1)
            {
                result = -result;
            }
        }

    }
    return result;
}

void Pio_bokzm60::load_array_param_from_json()
{
    std::vector<std::pair<std::string, uint16_t>> path_json = {std::make_pair("data_m60_mshior.json", M60_MSHIOR), std::make_pair("data_m60_shtmi1.json", M60_SHTMI1),
                                                               std::make_pair("data_m60_shtmi2.json", M60_SHTMI2), std::make_pair("data_m60_dtmi.json", M60_DTMI),
                                                               std::make_pair("data_m60_dtmiloc.json", M60_DTMI_LOC)};
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
            add_to_list_description(path.second, QString::fromStdString(j[std::to_string(ind)]["  № СД"]),
                    QString::fromStdString(j[std::to_string(ind)]["  Наименование параметра"]),
                    type_data,
                    QString::fromStdString(j[std::to_string(ind)]["Условное обозначение"]));
        }
        m_kia_mko_struct->m_data[path.second].data.resize(m_kia_mko_struct->m_data[path.second].data_description.size() - count_if_el_is_array);
        f.close();
    }

}



void Pio_bokzm60::create_list_to_prepare_data()
{
    auto add_to_int16_t = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
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

            auto format_str = get_format_str(type_format, static_cast<int16_t>(el * scale));

            m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(format_str, el * scale, is_norma);
        }
    };
    m_prepare_data.push_back(add_to_int16_t);

    auto add_to_int32_t = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
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

    auto add_to_float = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        int32_t temp = 0;
        memcpy(&temp, &value[0], sizeof(temp));
        if (do_proc.first)
            temp = swapHex(temp);
        float temp_float;
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

    auto add_to_int8_t = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
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
            auto format_str = get_format_str(type_format, static_cast<int8_t>(el * scale));
            m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(format_str, el * scale, is_norma);
        }
    };
    m_prepare_data.push_back(add_to_int8_t);

    auto convert_to_data = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
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
            auto years = (el >> 12);
            auto month = ((el & 0x0fff) >> 8);
            auto days = ((el & 0x00ff));

            m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(QString::number(2000 + years)
                                                                               + "." + QString::number(month)
                                                                               + "." + QString::number(days), el * scale, is_norma);
        }
    };
    m_prepare_data.push_back(convert_to_data);

    auto convert_to_ver = [this](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint16_t> value, std::pair<double, double> range, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
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
            auto ver1 = (el >> 12);
            auto ver2 = ((el & 0x0fff) >> 8);
            auto ver3 = ((el & 0x00ff));

            m_kia_mko_struct->m_data[key_arr].data[num_data] = std::make_tuple(QString::number(ver1)
                                                                               + "." + QString::number(ver2)
                                                                               + "." + QString::number(ver3), el * scale, is_norma);
        }
    };
    m_prepare_data.push_back(convert_to_ver);


    std::vector<std::function<std::tuple<QString, double, QString>(std::vector<uint16_t> value, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)>> list_to_prepare_data_for_arr;
    auto arr_float = [this](std::vector<uint16_t> value, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
    {
        int32_t temp = 0;
        memcpy(&temp, &value[0], sizeof(temp));
        if (do_proc.first)
            temp = swapHex(temp);
        float temp_float;
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
        return make_tuple(format_str, temp_float * scale, is_norma);
    };
    list_to_prepare_data_for_arr.push_back(arr_float);

    auto arr_uint16 = [this](std::vector<uint16_t> value, std::pair<bool, bool> do_proc, std::pair<double, double> range, double scale, uint16_t type_format)
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

            auto format_str = get_format_str(type_format, static_cast<int16_t>(el * scale));
            return make_tuple(format_str, el * scale, is_norma);
        }
    };
    list_to_prepare_data_for_arr.push_back(arr_uint16);

    auto add_to_arr = [this, list_to_prepare_data_for_arr](int16_t key_arr, std::pair<int16_t, std::string> type_name_arr, uint16_t& num_data, std::vector<uint16_t> value, std::pair<double, double> range,
            double scale, uint16_t type_format, std::pair<bool, bool> do_proc)
    {
        auto data = list_to_prepare_data_for_arr[type_name_arr.first](value, do_proc, range, scale, type_format);
        m_kia_mko_struct->m_data[key_arr].data_array[type_name_arr.second].push_back(data);
        num_data--;
    };
    m_prepare_data.push_back(add_to_arr);
}

void Pio_bokzm60::create_list_for_mpi_arrays()
{
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(55, 64),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-4, 4),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-4, 4),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(10, 1023),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 4095),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 16384),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 16384),
                                                        1, TDF_INT, std::make_pair(true, true)));


    for (uint16_t count = 0; count < 11; count++)
    {
        m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                            1, TDF_HEX, std::make_pair(true, true)));
    }


    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(DATA, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI1].push_back(std::make_tuple(std::make_tuple(VER, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(10, 1023),
                                                        1, TDF_INT, std::make_pair(true, true)));

    for (uint16_t num_counter = 0; num_counter < 5; num_counter++)
    {
        m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 65535),
                                                            1, TDF_INT, std::make_pair(true, true)));
    }

    m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(0, 2e31),
                                                        1, TDF_INT, std::make_pair(true, true)));

    for (uint16_t num_counter = 0; num_counter < 16; num_counter++)
    {
        m_data_manage[M60_SHTMI2].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 65535),
                                                            1, TDF_INT, std::make_pair(true, true)));
    }

    m_index_mpi_array[M60_MSHIOR]["st1"] = 0;
    m_index_mpi_array[M60_MSHIOR]["st2"] = 1;
    m_index_mpi_array[M60_MSHIOR]["t"] = 2;
    m_index_mpi_array[M60_MSHIOR]["qo0"] = 6;
    m_index_mpi_array[M60_MSHIOR]["qo1"] = 7;
    m_index_mpi_array[M60_MSHIOR]["qo2"] = 8;
    m_index_mpi_array[M60_MSHIOR]["qo3"] = 9;
    m_index_mpi_array[M60_MSHIOR]["alpha"] = 13;
    m_index_mpi_array[M60_MSHIOR]["delta"] = 14;
    m_index_mpi_array[M60_MSHIOR]["azimuth"] = 15;

    m_kia_mko_struct->m_data[M60_MSHIOR].data.resize(m_kia_mko_struct->m_data[M60_MSHIOR].data_description.size() + 3);


    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));

    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        1, TDF_FLOAT, std::make_pair(true, true)));

    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        PI * pow(2, -5), TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        PI * pow(2, -5), TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                        PI * pow(2, -5), TDF_FLOAT, std::make_pair(true, true)));

    for (uint16_t count = 0; count < 8; count++)
    {
        m_data_manage[M60_MSHIOR].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                            1, TDF_HEX, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(10, 1023),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 65535),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 32),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 32),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(150, 450),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(0, 86400),
                                                      1, TDF_FLOAT, std::make_pair(true, true)));
    //13 ind
    for (uint16_t i = 0; i < 2; i++)
    {
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "locx", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "locy", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "locb", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "locs", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "locx", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_FLOAT, std::make_pair(true, true)));

    std::array<std::string, 4> loc_name = {"locy", "locb", "locs", "locx"};


    for (uint16_t i = 0; i < 15 * 3; i++)
    {
        if (i % 15 == 0)
        {
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
        }
        std::string val;
        val = loc_name[i % 4];
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }
    loc_name[0] = "locb";
    loc_name[1] = "locs";
    loc_name[2] = "locx";
    loc_name[3] = "locy";

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    for (uint16_t i = 0; i < 10; i++)
    {
        std::string val;
        val = loc_name[i % 4];
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }
    for (uint16_t i = 0; i < 3; i++)
    {
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "xc", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_FLOAT, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "yc", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_FLOAT, std::make_pair(true, true)));

    std::array<std::string, 2> xcyc_name = {"xc", "yc"};
    for (uint16_t i = 0; i < 15 * 2; i++)
    {
        if (i % 15 == 0)
        {
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_HEX, std::make_pair(true, true)));
        }

        std::string val;
        val = xcyc_name[i % 2];
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));

    for (uint16_t i = 0; i < 16; i++)
    {
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "thfrag", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_INT, std::make_pair(true, true)));
    }
    for (uint16_t i = 0; i < 14; i++)
    {
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "objfrag", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_INT, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_HEX, std::make_pair(true, true)));

    for (uint16_t i = 0; i < 2; i++)
    {
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ARR, "objfrag", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_INT, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_INT, std::make_pair(true, true)));
    for(uint16_t i = 0; i < 4; i++)
    {
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }
    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(FLOAT, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                      1, TDF_FLOAT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 200),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 200),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 200),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-45, 45),
                                                      1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-45, 45),
                                                      1, TDF_INT, std::make_pair(true, true)));


    for(uint16_t i = 0; i < 11; i++)
    {
        m_data_manage[M60_DTMI].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(10, 1023),
                                                          1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 65535),
                                                          1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT16, "", TA_NONE), 1, std::make_pair(0, 200),
                                                          1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(0, 4095),
                                                          1, TDF_INT, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(INT32, "", TA_NONE), 2, std::make_pair(0, 4095),
                                                          1, TDF_INT, std::make_pair(true, true)));

    for (uint16_t i = 0; i < 2; i++)
    {
        m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "locx", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_FLOAT, std::make_pair(true, true)));
        m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "locy", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_FLOAT, std::make_pair(true, true)));
        m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "locb", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_FLOAT, std::make_pair(true, true)));
        m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "locs", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                              1, TDF_FLOAT, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "locx", TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));

    loc_name[0] = "locy";
    loc_name[1] = "locb";
    loc_name[2] = "locs";
    loc_name[3] = "locx";

    for (uint16_t i = 0; i < 15 * 7; i++)
    {
        if (i % 15 == 0)
        {
            m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                                  1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                                  1, TDF_HEX, std::make_pair(true, true)));

            m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                                  1, TDF_HEX, std::make_pair(true, true)));
            m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                                  1, TDF_HEX, std::make_pair(true, true)));
        }
        std::string val;
        val = loc_name[i % 4];
        m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "cc1", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, "cc2", TA_UINT16), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));

    loc_name[0] = "locb";
    loc_name[1] = "locs";
    loc_name[2] = "locx";
    loc_name[3] = "locy";
    for (uint16_t i = 0; i < 14; i++)
    {
        std::string val;
        val = loc_name[i % 4];
        m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ARR, val, TA_FLOAT), 2, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_FLOAT, std::make_pair(true, true)));
    }

    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
    m_data_manage[M60_DTMI_LOC].push_back(std::make_tuple(std::make_tuple(ITS_REZERV, "", TA_NONE), 1, std::make_pair(-m_max_double_value, m_max_double_value),
                                                          1, TDF_HEX, std::make_pair(true, true)));
}

void Pio_bokzm60::add_to_list_description(uint16_t key_arr, const QString &num_value, const QString &description, const QString &type_data, const QString &name_data)
{
    m_kia_mko_struct->m_data[key_arr].data_description.push_back(std::make_tuple(helpers::format_qstring(num_value, m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                                                 + description, type_data, name_data));
}

template<typename T>
T Pio_bokzm60::swapHex(T value)
{
    value = ((value & 0x0000ffff) << 16) | ((value & 0xffff0000) >> 16);
    return value;
}

