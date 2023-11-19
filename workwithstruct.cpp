#include "workwithstruct.h"

WorkWithStruct::WorkWithStruct(std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_settings(kia_settings)
{
    
}

void WorkWithStruct::workWithTransferDTMILoc(DTMILocRaw_2_3_4_5_6_7_8 &dtmi_loc_raw_2_3_4_5_6_7_8)
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

void WorkWithStruct::workWithTransferDTMIRaw_2_3_4(DTMIRaw_2_3_4 &dtmiRaw_2_3_4)
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

void WorkWithStruct::workWithTransferDTMIRaw_6_7(DTMIRaw_6_7 &dtmiRaw_6_7)
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

string WorkWithStruct::currentDateTime()
{
    std::time_t t = std::time(nullptr);
    std::tm* now_t = std::localtime(&t);
    char buffer[128];
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    /* UTC: -3:00 = 24 - 3 = 21 */
    typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 24 > >::type > Days;
    Days days = std::chrono::duration_cast<Days>(duration);
    duration -= days;
    
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;
    
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;
    
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    char data[50];
    strftime(data, sizeof(data), "%Y-%m-%d", now_t);
    sprintf(buffer,"%s %02i:%02ld:%02ld.%03ld", data, now_t->tm_hour, minutes.count(), seconds.count(), milliseconds.count());
    return buffer;
}

uint32_t WorkWithStruct::current_hours()
{
    std::time_t t = std::time(nullptr);
    std::tm* now_t = std::localtime(&t);
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    /* UTC: -3:00 = 24 - 3 = 21 */
    typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 24 > >::type > Days;
    Days days = std::chrono::duration_cast<Days>(duration);
    duration -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    return minutes.count();
    //return now_t->tm_hour;
}

float WorkWithStruct::decodeDateTime()
{
    const float J_GOD = 36525.0;
    const float JD2000 = 2451545.0;
    const float JToG = 1720994.5;
    const float DInm = 30.600;
    const float DInY = 365.25;
    std::time_t t = std::time(nullptr);
    std::tm* now_t = std::localtime(&t);
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    /* UTC: -3:00 = 24 - 3 = 21 */
    typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 24 > >::type > Days;
    Days days = std::chrono::duration_cast<Days>(duration);
    duration -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    float Yn = 1900 + now_t->tm_year;
    float Mn = 1 + now_t->tm_mon;
    float DD;
    DD = now_t->tm_mday + (now_t->tm_hour) / 24 + minutes.count() / (24 * 60) + seconds.count() / (24 * 60 * 60) + milliseconds.count() / (24 * 60 * 60 * 1000);
    if (Mn <= 2)
    {
        Yn = Yn - 1;
        Mn = Mn + 12;
    }
    float A;
    A = Yn / 100;
    float B;
    B = 2 - A + A / 4;
    float Dn;
    Dn = trunc(DInY * Yn);
    float Hn;
    Hn = trunc(DInm * (Mn + 1));
    float JD;
    JD = Dn + Hn + DD + JToG + B;
    float Fl;
    Fl = (JD - JD2000) / J_GOD;
    return Fl;
}

QString WorkWithStruct::format(const QString &str, const int16_t &shift, const char &fillchar)
{
    return QString("%1").arg(str, shift, fillchar);
}

float WorkWithStruct::uint32_to_float(uint32_t value)
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


void WorkWithStruct::workWithDTMI(array<uint16_t, constants::packetSize> dataWord, uint16_t count, DTMI &dtmi,
                                  DTMI_1 &dtmi_1, DTMI_2 &dtmi_2, DTMI_3 &dtmi_3, DTMI_4 &dtmi_4, DTMI_5 &dtmi_5,
                                  DTMI_6 &dtmi_6, DTMI_7 &dtmi_7, DTMI_8 &dtmi_8, DTMI_9 &dtmi_9)
{
    dtmi.dtmi_list_data.clear();
    dtmi.dtmi_list_name.clear();
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
        memcpy(&dtmi_1,&dtmiRaw_1,sizeof(dtmi_1));
        break;
    case 1:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        workWithTransferDTMIRaw_2_3_4(dtmiRaw_2_3_4);
        memcpy(&dtmi_2,&dtmiRaw_2_3_4,sizeof(dtmi_2));
        break;
    case 2:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        workWithTransferDTMIRaw_2_3_4(dtmiRaw_2_3_4);
        memcpy(&dtmi_3,&dtmiRaw_2_3_4,sizeof(dtmi_3));
        break;
    case 3:
        memcpy(&dtmiRaw_2_3_4,&dataWord,sizeof(dtmiRaw_2_3_4));
        workWithTransferDTMIRaw_2_3_4(dtmiRaw_2_3_4);
        memcpy(&dtmi_4,&dtmiRaw_2_3_4,sizeof(dtmi_4));
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
        memcpy(&dtmi_5,&dtmiRaw_5,sizeof(dtmi_5));
        break;
    case 5:
        memcpy(&dtmiRaw_6_7,&dataWord,sizeof(dtmiRaw_6_7));
        workWithTransferDTMIRaw_6_7(dtmiRaw_6_7);
        memcpy(&dtmi_6,&dtmiRaw_6_7,sizeof(dtmi_6));
        break;
    case 6:
        memcpy(&dtmiRaw_6_7,&dataWord,sizeof(dtmiRaw_6_7));
        workWithTransferDTMIRaw_6_7(dtmiRaw_6_7);
        memcpy(&dtmi_7,&dtmiRaw_6_7,sizeof(dtmi_7));
        break;
    case 7:
        memcpy(&dtmiRaw_8,&dataWord,sizeof(dtmiRaw_8));
        memcpy(&dtmi_8,&dtmiRaw_8,sizeof(dtmi_8));
        break;
    case 8:
        memcpy(&dtmiRaw_9,&dataWord,sizeof(dtmiRaw_9));
        dtmiRaw_9.TOlg = swapHex(dtmiRaw_9.TOlg);
        dtmiRaw_9.QOlg_0 = swapHex(dtmiRaw_9.QOlg_0);
        dtmiRaw_9.QOlg_1 = swapHex(dtmiRaw_9.QOlg_1);
        dtmiRaw_9.QOlg_2 = swapHex(dtmiRaw_9.QOlg_2);
        dtmiRaw_9.QOlg_3 = swapHex(dtmiRaw_9.QOlg_3);
        dtmiRaw_9.Epoch = swapHex(dtmiRaw_9.Epoch);
        memcpy(&dtmi_9,&dtmiRaw_9,sizeof(dtmi_9));
        break;
    }
    dtmi.dtmi_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Служебное слово 1");
    dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_1.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_2.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_3.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_4.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_5.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_6.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_7.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_8.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_9.CC1, 16), 4, '0'));

    dtmi.dtmi_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Служебное слово 2");
    dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_1.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_2.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_3.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_4.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_5.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_6.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_7.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_8.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_9.CC2, 16), 4, '0'));

    dtmi.dtmi_list_name.push_back(format("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Время привязки информации");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.T));

    dtmi.dtmi_list_name.push_back(format("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Код состояния 1 (Status1)");
    dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_1.KC1, 16), 4, '0'));

    dtmi.dtmi_list_name.push_back(format("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Код состояния 2 (Status2)");
    dtmi.dtmi_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_1.KC2, 16), 4, '0'));

    dtmi.dtmi_list_name.push_back(format("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Сериальный номер");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.SerNum));

    dtmi.dtmi_list_name.push_back(format("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Время экспонирования");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.Texp));

    dtmi.dtmi_list_name.push_back(format("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество локализованных объектов");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.NumLoc));

    dtmi.dtmi_list_name.push_back(format("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество зафиксированных объектов");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.NumObj));

    dtmi.dtmi_list_name.push_back(format("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество фрагментов");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.NumFrag));

    dtmi.dtmi_list_name.push_back(format("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Допуск распознавания");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.Epsilon));

    dtmi.dtmi_list_name.push_back(format("13,14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Интервал времени");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_1.deltaT,'f',4));

    dtmi.dtmi_list_name.push_back(format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                  + format("X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("B", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("C", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    dtmi.dtmi_list_data.push_back("");

    dtmi.dtmi_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_1.Loc_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_1.Loc_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_1.Loc_0_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_1.Loc_0_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_1.Loc_1_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_1.Loc_1_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_1.Loc_1_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_1.Loc_1_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_1.Loc_2_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_2.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_2.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_2.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_2.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_3.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_3.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_3.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_3.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_3.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_4.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_4.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_4.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_4.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_4.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_5.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_5.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Угловая скорость по оптическим измерениям, Wox");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_5.Wo_x, 'f', 4));

    dtmi.dtmi_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Угловая скорость по оптическим измерениям, Woy");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_5.Wo_y, 'f', 4));

    dtmi.dtmi_list_name.push_back(format("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Угловая скорость по оптическим измерениям, Woz");
    dtmi.dtmi_list_data.push_back(QString::number(dtmi_5.Wo_z, 'f', 4));

    dtmi.dtmi_list_name.push_back(format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                  + format("Xc", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("Yc", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("ThFrag", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("ObjFrag", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    dtmi.dtmi_list_data.push_back("");

    dtmi.dtmi_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_5.XYc_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_5.XYc_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );


    dtmi.dtmi_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_6.XYc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_6.XYc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_6.XYc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_6.XYc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_6.XYc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_5, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_5, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_6.XYc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_6.XYc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_7, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_7, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_6.XYc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_7.XYc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_9, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_9, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_7.XYc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_7.XYc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_11, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_11, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_7.XYc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_7.XYc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_13, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.ObjFrag_13, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_7.XYc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_9.ObjFrag_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi.dtmi_list_name.push_back(format("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi.dtmi_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_7.XYc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_7.XYc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_8.TheFrag_15, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_9.ObjFrag_15, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );
}

void WorkWithStruct::workWithDTMILoc(array<uint16_t, constants::packetSize> dataWord, uint16_t count, DTMILoc &dtmi_loc, DTMILoc_1 &dtmi_loc_1,
                                     DTMILoc_2 &dtmi_loc_2, DTMILoc_3 &dtmi_loc_3, DTMILoc_4 &dtmi_loc_4,
                                     DTMILoc_5 &dtmi_loc_5, DTMILoc_6 &dtmi_loc_6, DTMILoc_7 &dtmi_loc_7, DTMILoc_8 &dtmi_loc_8, DTMILoc_9 &dtmi_loc_9)
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
        dtmi_raw_1.Loc_0_0 = swapHex(dtmi_raw_1.Loc_0_0);
        dtmi_raw_1.Loc_0_1 = swapHex(dtmi_raw_1.Loc_0_1);
        dtmi_raw_1.Loc_0_2 = swapHex(dtmi_raw_1.Loc_0_2);
        dtmi_raw_1.Loc_0_3 = swapHex(dtmi_raw_1.Loc_0_3);
        dtmi_raw_1.Loc_1_0 = swapHex(dtmi_raw_1.Loc_1_0);
        dtmi_raw_1.Loc_1_1 = swapHex(dtmi_raw_1.Loc_1_1);
        dtmi_raw_1.Loc_1_2 = swapHex(dtmi_raw_1.Loc_1_2);
        dtmi_raw_1.Loc_1_3 = swapHex(dtmi_raw_1.Loc_1_3);
        dtmi_raw_1.Loc_2_0 = swapHex(dtmi_raw_1.Loc_2_0);
        memcpy(&dtmi_loc_1, &dtmi_raw_1, sizeof(dtmi_loc_1));
        break;
    case 1:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        workWithTransferDTMILoc(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&dtmi_loc_2,&dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(dtmi_loc_2));
        break;
    case 2:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        workWithTransferDTMILoc(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&dtmi_loc_3,&dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(dtmi_loc_3));
        break;
    case 3:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        workWithTransferDTMILoc(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&dtmi_loc_4,&dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(dtmi_loc_4));
        break;
    case 4:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        workWithTransferDTMILoc(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&dtmi_loc_5,&dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(dtmi_loc_5));
        break;
    case 5:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        workWithTransferDTMILoc(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&dtmi_loc_6,&dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(dtmi_loc_6));
        break;
    case 6:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        workWithTransferDTMILoc(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&dtmi_loc_7,&dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(dtmi_loc_7));
        break;
    case 7:
        memcpy(&dtmi_loc_raw_2_3_4_5_6_7_8,&dataWord,sizeof(dtmi_loc_raw_2_3_4_5_6_7_8));
        workWithTransferDTMILoc(dtmi_loc_raw_2_3_4_5_6_7_8);
        memcpy(&dtmi_loc_8, &dtmi_loc_raw_2_3_4_5_6_7_8,sizeof(dtmi_loc_8));
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
        memcpy(&dtmi_loc_9,&dtmi_raw_9,sizeof(dtmi_loc_9));
        break;
    }
    
    dtmi_loc.dtmi_loc_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Служебное слово 1");
    dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_loc_1.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_2.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_3.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_4.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_5.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_6.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_7.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_8.CC1, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_9.CC1, 16), 4, '0'));

    dtmi_loc.dtmi_loc_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Служебное слово 2");
    dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_loc_1.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_2.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_3.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_4.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_5.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_6.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_7.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_8.CC2, 16), 4, '0') +
                                  " " + QString("0x%1").arg(QString::number(dtmi_loc_9.CC2, 16), 4, '0'));

    dtmi_loc.dtmi_loc_list_name.push_back(format("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Время привязки информации");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_1.T));

    dtmi_loc.dtmi_loc_list_name.push_back(format("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Код состояния 1 (Status1)");
    dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_loc_1.KC1, 16), 4, '0'));

    dtmi_loc.dtmi_loc_list_name.push_back(format("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Код состояния 2 (Status2)");
    dtmi_loc.dtmi_loc_list_data.push_back(QString("0x%1").arg(QString::number(dtmi_loc_1.KC2, 16), 4, '0'));

    dtmi_loc.dtmi_loc_list_name.push_back(format("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Сериальный номер");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_1.SerNum));

    dtmi_loc.dtmi_loc_list_name.push_back(format("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Время экспонирования");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_1.Texp));

    dtmi_loc.dtmi_loc_list_name.push_back(format("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество локализованных объектов");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_1.NumLoc));

    dtmi_loc.dtmi_loc_list_name.push_back(format("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Количество зафиксированных объектов");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_1.NumObj));

    dtmi_loc.dtmi_loc_list_name.push_back(format("11, 12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Среднее значение сигнала");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_1.Mean));

    dtmi_loc.dtmi_loc_list_name.push_back(format("13, 14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "СКО сигнала");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_1.Sigma));

    dtmi_loc.dtmi_loc_list_name.push_back(format(" ", m_kia_settings->m_format_for_desc->shift_for_numbers + m_kia_settings->m_format_for_desc->shift_description)
                                  + format("X", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("Y", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("B", m_kia_settings->m_format_for_desc->shift_for_dtmi)
                                  + format("C", m_kia_settings->m_format_for_desc->shift_for_dtmi));
    dtmi_loc.dtmi_loc_list_data.push_back("");

    dtmi_loc.dtmi_loc_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_0_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_0_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_0_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_0_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_1_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_1_1, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_1_2, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_1_3, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("3", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_1.Loc_2_0, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_2.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_3.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_4.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_5.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_6.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_7.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("27", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("29", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_8.Loc_31_32, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_3_4, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_5_6, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_7_8, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_9_10, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_11_12, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_13_14, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("31", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_15_16, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_17_18, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_19_20, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_21_22, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + " ");
    dtmi_loc.dtmi_loc_list_data.push_back
            (
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_23_24, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_25_26, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_27_28, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi) +
                format(QString("%1").arg(QString::number(dtmi_loc_9.Loc_29_30, 'f', 4), 4, '0'), m_kia_settings->m_format_for_desc->shift_for_dtmi)
                );

    dtmi_loc.dtmi_loc_list_name.push_back(format("", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                  + "Резерв");
    dtmi_loc.dtmi_loc_list_data.push_back(QString::number(dtmi_loc_9.rezerv));
}

void WorkWithStruct::workWithSHTMI1(array<uint16_t, constants::packetSize> dataWord, SHTMI1 &shtmi1)
{
    shtmi1.shtmi1_list_name.clear();
    shtmi1.shtmi1_list_data.clear();
    SHTMI1raw shmti1_raw;
    memcpy(&shmti1_raw, &dataWord,sizeof(shmti1_raw));
    shtmi1.CC1 = shmti1_raw.CC1;
    shtmi1.shtmi1_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 1");
    shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(shtmi1.CC1, 16), 4, '0'));

    shtmi1.CC2 = shmti1_raw.CC2;
    shtmi1.shtmi1_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 2");
    shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(shtmi1.CC2, 16), 4, '0'));

    shtmi1.T = swapHex(shmti1_raw.T);
    shtmi1.shtmi1_list_name.push_back(format("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время привязки информации");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.T));

    shtmi1.KC1 = shmti1_raw.KC1;
    shtmi1.shtmi1_list_name.push_back(format("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 1 (Status1)");
    shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(shtmi1.KC1, 16), 4, '0'));

    shtmi1.KC2 = shmti1_raw.KC2;
    shtmi1.shtmi1_list_name.push_back(format("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 2 (Status2)");
    shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(shtmi1.KC2, 16), 4, '0'));

    shtmi1.SerNum = shmti1_raw.SerNum;
    shtmi1.shtmi1_list_name.push_back(format("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Сериальный номер БОКЗ-М60");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.T));

    shtmi1.POST = shmti1_raw.POST;
    shtmi1.shtmi1_list_name.push_back(format("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Слово внутреннего теста");
    shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(shtmi1.POST, 16), 4, '0'));

    auto foc = swapHex(shmti1_raw.Foc);
    memcpy(&shtmi1.Foc, &foc, sizeof(shtmi1.Foc));
    shtmi1.shtmi1_list_name.push_back(format("9, 10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Фокусное расстояние");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.Foc, 'f', 4));

    shtmi1.Xo = swapHex(shmti1_raw.Xo);
    shtmi1.shtmi1_list_name.push_back(format("11, 12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координата Xo гл. точки ФПЗС");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.Xo));

    shtmi1.Yo = swapHex(shmti1_raw.Yo);
    shtmi1.shtmi1_list_name.push_back(format("13, 14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координата Yo гл. точки ФПЗС");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.Yo));

    shtmi1.Texp = shmti1_raw.Texp;
    shtmi1.shtmi1_list_name.push_back(format("15", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время экспонирования");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.Texp));

    shtmi1.Mt = shmti1_raw.Mt;
    shtmi1.shtmi1_list_name.push_back(format("16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Среднее темнового сигнала");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.Mt));

    shtmi1.St = shmti1_raw.St;
    shtmi1.shtmi1_list_name.push_back(format("17", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "СКО темневого сигнала");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.St));

    shtmi1.Ndef = shmti1_raw.Ndef;
    shtmi1.shtmi1_list_name.push_back(format("18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Количество дефектов");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.Ndef));

    shtmi1.rezerv1 = shmti1_raw.rezerv1;
    shtmi1.shtmi1_list_name.push_back(format("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv1));

    shtmi1.rezerv2 = shmti1_raw.rezerv2;
    shtmi1.shtmi1_list_name.push_back(format("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv2));

    shtmi1.rezerv3 = shmti1_raw.rezerv3;
    shtmi1.shtmi1_list_name.push_back(format("21", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv3));

    shtmi1.rezerv4 = shmti1_raw.rezerv4;
    shtmi1.shtmi1_list_name.push_back(format("22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv4));

    shtmi1.rezerv5 = shmti1_raw.rezerv5;
    shtmi1.shtmi1_list_name.push_back(format("23", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv5));

    shtmi1.rezerv6 = shmti1_raw.rezerv6;
    shtmi1.shtmi1_list_name.push_back(format("24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv6));

    shtmi1.rezerv7 = shmti1_raw.rezerv7;
    shtmi1.shtmi1_list_name.push_back(format("25", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv7));

    shtmi1.rezerv8 = shmti1_raw.rezerv8;
    shtmi1.shtmi1_list_name.push_back(format("26", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv8));

    shtmi1.rezerv9 = shmti1_raw.rezerv9;
    shtmi1.shtmi1_list_name.push_back(format("27", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv9));

    shtmi1.rezerv10 = shmti1_raw.rezerv10;
    shtmi1.shtmi1_list_name.push_back(format("28", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv10));

    shtmi1.rezerv11 = shmti1_raw.rezerv11;
    shtmi1.shtmi1_list_name.push_back(format("29", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.rezerv11));

    shtmi1.XCF = shmti1_raw.XCF;
    shtmi1.shtmi1_list_name.push_back(format("30", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "X-индентификтор");
    shtmi1.shtmi1_list_data.push_back(QString("0x%1").arg(QString::number(shtmi1.XCF, 16), 4, '0'));

    shtmi1.Years = (shmti1_raw.Date >> 12);
    shtmi1.Month = ((shmti1_raw.Date & 0x0fff) >> 8);
    shtmi1.Days = ((shmti1_raw.Date & 0x00ff));
    shtmi1.shtmi1_list_name.push_back(format("31", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Дата создания ПО");
    shtmi1.shtmi1_list_data.push_back(QString::number(2000 + shtmi1.Years)
                                      + "." + QString::number(shtmi1.Month)
                                      + "." + QString::number(shtmi1.Days));

    shtmi1.Ver1 = (shmti1_raw.Ver >> 12);
    shtmi1.Ver2 = ((shmti1_raw.Ver & 0x0fff) >> 8);
    shtmi1.Ver3 = ((shmti1_raw.Ver & 0x00ff));
    shtmi1.shtmi1_list_name.push_back(format("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Номер версии ПО");
    shtmi1.shtmi1_list_data.push_back(QString::number(shtmi1.Ver1)
                                      + "." + QString::number(shtmi1.Ver2)
                                      + "." + QString::number(shtmi1.Ver3));
    
}

void WorkWithStruct::workWithSHTMI2(array<uint16_t, constants::packetSize> dataWord, SHTMI2 &shtmi2, int countSize)
{
    shtmi2.shtmi2_list_name.clear();
    shtmi2.shtmi2_list_data.clear();
    SHTMI2raw shtmi2_raw;
    memcpy(&shtmi2_raw,&dataWord,sizeof(shtmi2_raw));
    shtmi2.CC1 = shtmi2_raw.CC1;
    shtmi2.shtmi2_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 1");
    shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(shtmi2.CC1, 16), 4, '0'));

    shtmi2.CC2 = shtmi2_raw.CC2;
    shtmi2.shtmi2_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Служебное слово 2");
    shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(shtmi2.CC2, 16), 4, '0'));

    shtmi2.T = swapHex(shtmi2_raw.T);
    shtmi2.shtmi2_list_name.push_back(format("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время привязки информации");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.T));

    shtmi2.KC1 = shtmi2_raw.KC1;
    shtmi2.shtmi2_list_name.push_back(format("5", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 1 (Status1)");
    shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(shtmi2.KC1, 16), 4, '0'));

    shtmi2.KC2 = shtmi2_raw.KC2;
    shtmi2.shtmi2_list_name.push_back(format("6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 2 (Status2)");
    shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(shtmi2.KC2, 16), 4, '0'));


    shtmi2.SerNum = shtmi2_raw.SerNum;
    shtmi2.shtmi2_list_name.push_back(format("7", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Сериальный номер БОКЗ-М60");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.SerNum));

    shtmi2.POST = shtmi2_raw.POST;
    shtmi2.shtmi2_list_name.push_back(format("8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Слово внутреннего теста");
    shtmi2.shtmi2_list_data.push_back(QString("0x%1").arg(QString::number(shtmi2.POST, 16), 4, '0'));

    shtmi2.Texp = shtmi2_raw.Texp;
    shtmi2.shtmi2_list_name.push_back(format("9", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время экспонирования");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.Texp));

    shtmi2.Nusd = shtmi2_raw.Nusd;
    shtmi2.shtmi2_list_name.push_back(format("10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик полученных УСД");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.Nusd));

    shtmi2.Nno = shtmi2_raw.Nno;
    shtmi2.shtmi2_list_name.push_back(format("11", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик НО");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.Nno));

    shtmi2.Nnosl = shtmi2_raw.Nnosl;
    shtmi2.shtmi2_list_name.push_back(format("12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Число переходов от НО к слежению");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.Nnosl));

    shtmi2.Nto = shtmi2_raw.Nto;
    shtmi2.shtmi2_list_name.push_back(format("13", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик ТО");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.Nto));

    shtmi2.Ntosl = shtmi2_raw.Ntosl;
    shtmi2.shtmi2_list_name.push_back(format("14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Число переходов от ТО к слежению");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.Ntosl));

    shtmi2.Nsl = swapHex(shtmi2_raw.Nsl);
    shtmi2.shtmi2_list_name.push_back(format("15, 16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик слежения");
    shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.Nsl));

    for (uint16_t count_ind = 0; count_ind < countSize; count_ind++)
    {
        shtmi2.eCount[count_ind] = shtmi2_raw.eCount[count_ind];
        shtmi2.shtmi2_list_name.push_back(format(QString::number(count_ind + 17), m_kia_settings->m_format_for_desc->shift_for_numbers)
                                          + QString("Счетчик") + QString::number(count_ind));
        shtmi2.shtmi2_list_data.push_back(QString::number(shtmi2.eCount[count_ind]));
    }
}

void WorkWithStruct::workWithMSHIOR(array<uint16_t, constants::packetSize> dataWord, MSHIOR &mshior)
{
    mshior.mshior_list_name.clear();
    mshior.mshior_list_data.clear();
    MSHIORRaw mshiorRaw;
    memcpy(&mshiorRaw,&dataWord,sizeof(mshiorRaw));
    mshior.KC1 = mshiorRaw.KC1;
    mshior.mshior_list_name.push_back(format("1", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 1 (Status1)");
    mshior.mshior_list_data.push_back(QString("0x%1").arg(QString::number(mshior.KC1, 16), 4, '0'));

    mshior.KC2 = mshiorRaw.KC2;
    mshior.mshior_list_name.push_back(format("2", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Код состояния 2 (Status2)");
    mshior.mshior_list_data.push_back(QString("0x%1").arg(QString::number(mshior.KC2, 16), 4, '0'));

    mshior.T = swapHex(mshiorRaw.T);
    mshior.mshior_list_data.push_back(QString::number(mshior.T));
    mshior.mshior_list_name.push_back(format("3,4", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Время привязки информации");

    mshior.OZx = uint32_to_float(swapHex(mshiorRaw.OZx));
    mshior.mshior_list_data.push_back(QString::number(mshior.OZx,'f',4));
    mshior.mshior_list_name.push_back(format("5,6", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координаты оси OZx ПСК в ИСК");

    mshior.OZy = uint32_to_float(swapHex(mshiorRaw.OZy));
    mshior.mshior_list_data.push_back(QString::number(mshior.OZy,'f',4));
    mshior.mshior_list_name.push_back(format("7,8", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координаты оси OZy ПСК в ИСК");

    mshior.OZz = uint32_to_float(swapHex(mshiorRaw.OZz));
    mshior.mshior_list_data.push_back(QString::number(mshior.OZz,'f',4));
    mshior.mshior_list_name.push_back(format("9,10", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Координаты оси OZz ПСК в ИСК");

    mshior.Qo0 = uint32_to_float(swapHex(mshiorRaw.Qo0));
    mshior.mshior_list_data.push_back(QString::number(mshior.Qo0,'f',4));
    mshior.mshior_list_name.push_back(format("11,12", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo0");

    mshior.Qo1 = uint32_to_float(swapHex(mshiorRaw.Qo1));
    mshior.mshior_list_data.push_back(QString::number(mshior.Qo1,'f',4));
    mshior.mshior_list_name.push_back(format("13,14", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo0");

    mshior.Qo2 = uint32_to_float(swapHex(mshiorRaw.Qo2));
    mshior.mshior_list_data.push_back(QString::number(mshior.Qo2,'f',4));
    mshior.mshior_list_name.push_back(format("15,16", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo2");

    mshior.Qo3 = uint32_to_float(swapHex(mshiorRaw.Qo3));
    mshior.mshior_list_data.push_back(QString::number(mshior.Qo3,'f',4));
    mshior.mshior_list_name.push_back(format("17,18", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Кватернион ориентации, Qo3");

    mshior.wox = uint32_to_float(swapHex(mshiorRaw.wox)) * M_PI * (pow(2, -5));
    mshior.mshior_list_data.push_back(QString::number(mshior.wox,'f',4));
    mshior.mshior_list_name.push_back(format("19,20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Угловая скорость по оптическим измерениям, Wox");

    mshior.woy = uint32_to_float(swapHex(mshiorRaw.woy)) * M_PI * (pow(2, -5));
    mshior.mshior_list_name.push_back(format("21,22", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Угловая скорость по оптическим измерениям, Woy");
    mshior.mshior_list_data.push_back(QString::number(mshior.woy,'f',4));

    mshior.woz = uint32_to_float(swapHex(mshiorRaw.woz)) * M_PI * (pow(2, -5));
    mshior.mshior_list_data.push_back(QString::number(mshior.woz,'f',4));
    mshior.mshior_list_name.push_back(format("23,24", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Угловая скорость по оптическим измерениям, Woz");

    m_kia_settings->m_data_for_db->m_norm_qaor = sqrt(pow(mshior.Qo0,2) + pow(mshior.Qo1,2) + pow(mshior.Qo2, 2)  + pow(mshior.Qo3,2));

}

template<typename T>
T WorkWithStruct::swapHex(T value)
{
    value = ((value & 0x0000ffff) << 16) | (value >> 16);
    return value;
}
