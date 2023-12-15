#include "pio_bokzmf.h"

Pio_bokzmf::Pio_bokzmf(std::shared_ptr<Kia_mko_struct> kia_mko_struct,
                       std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_mko_struct(kia_mko_struct),
    m_kia_settings(kia_settings)
{

}

void Pio_bokzmf::decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{

}

void Pio_bokzmf::decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count)
{

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
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("19", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.rezerv1));

    m_kia_mko_struct->st_shtmi1_mf.rezerv2 = shmti1_raw.rezerv2;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.rezerv2));

    m_kia_mko_struct->st_shtmi1_mf.cntUPN = shmti1_raw.cntUPN;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Счетчик КС УПН");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.cntUPN));

    m_kia_mko_struct->st_shtmi1_mf.Tcmv = shmti1_raw.Tcmv;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Температура КМОП-матрицы");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Tcmv));

    m_kia_mko_struct->st_shtmi1_mf.ConfCS = shmti1_raw.ConfCS;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Контрольная сумма конфигурации ПЛИС");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ConfCS));

    m_kia_mko_struct->st_shtmi1_mf.desc = shmti1_raw.desc;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Дескриптор передачи данных");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.desc));

    m_kia_mko_struct->st_shtmi1_mf.ogConstCrc = shmti1_raw.ogConstCrc;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Контрольная сумма констант ЭО ЗД");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ogConstCrc));

    m_kia_mko_struct->st_shtmi1_mf.CatCS0 = shmti1_raw.CatCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Контрольная сумма каталога 0");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.CatCS0));

    m_kia_mko_struct->st_shtmi1_mf.CatCS1 = shmti1_raw.CatCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Контрольная сумма каталога 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.CatCS1));

    m_kia_mko_struct->st_shtmi1_mf.ProgCS0 = shmti1_raw.ProgCS0;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Контрольная сумма программы 0");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ProgCS0));

    m_kia_mko_struct->st_shtmi1_mf.ProgCS1 = shmti1_raw.ProgCS1;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Контрольная сумма программы 1");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.ProgCS1));

    m_kia_mko_struct->st_shtmi1_mf.Ver1 = (shmti1_raw.Ver >> 12);
    m_kia_mko_struct->st_shtmi1_mf.Ver2 = ((shmti1_raw.Ver & 0x0fff) >> 8);
    m_kia_mko_struct->st_shtmi1_mf.Ver3 = ((shmti1_raw.Ver & 0x00ff));
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("32", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Номер версии ПО");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver1)
                                      + "." + QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver2)
                                      + "." + QString::number(m_kia_mko_struct->st_shtmi1_mf.Ver3));

    m_kia_mko_struct->st_shtmi1_mf.cs = shmti1_raw.cs;
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_name.push_back(helpers::format_qstring("20", m_kia_settings->m_format_for_desc->shift_for_numbers)
                                      + "Резерв");
    m_kia_mko_struct->st_shtmi1_mf.shtmi1_list_data.push_back(QString::number(m_kia_mko_struct->st_shtmi1_mf.cs));
}

void Pio_bokzmf::decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord)
{

}

void Pio_bokzmf::decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t &bshv)
{

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
