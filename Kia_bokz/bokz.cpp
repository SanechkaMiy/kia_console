#include "bokz.h"
Bokz::Bokz()
{

}

void Bokz::parse_mko_protocols(std::shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_data> kia_data, int32_t bshv, uint16_t num_bokz)
{
    uint16_t shift_for_numbers = -8;
    uint16_t shift_description = -50;
    QString str_mpi_protocol;
    str_mpi_protocol.push_back(helpers::format_qstring("", shift_for_numbers + 3, '-') + helpers::format_qstring(" " + QString::fromStdString(kia_data->m_data_db->struct_id_desc) + " ", shift_description,'-') + '\n');

    QString lpi;
    if (kia_data->m_data_mpi->m_lpi == 0)
    {
        lpi = "A";
    }
    else
    {
        lpi = "B";
    }
    str_mpi_protocol.push_back(QString("%1 %2 %3 %4 %5 %6 %7\n").arg("", -5).arg("БШВ", -11).arg("МПИ", -11).arg("ФОРМАТ",-11).arg("АДРЕС", -11).arg("ЛПИ",-11).arg("ДАТА И ВРЕМЯ"));
    str_mpi_protocol.push_back(QString("%1 %2 %3 %4 %5 %6 %7\n").arg("", -5)
                               .arg(QString::number(bshv),-11).arg(QString::number(kia_data->m_data_mpi->m_mpi_index), -11)
                               .arg(QString::number(kia_data->m_data_mpi->m_format), -11).arg(QString::number(kia_data->m_data_mpi->m_address),-11)
                               .arg(lpi,-11).arg(QString::fromStdString(kia_data->m_data_db->m_datetime)));
    str_mpi_protocol.push_back(QString("%1 %2 %3\n").arg("КС:", -5)
                               .arg(QString("0x%1")
                                    .arg(QString::number(kia_data->m_data_mpi->m_code_word, 16), 4, '0'), -11)
                               .arg(QString("%1-%2-%3-%4").arg(QString::number(kia_data->m_data_mpi->m_address), 2, '0')
                                    .arg(QString::number(kia_data->m_data_mpi->m_direction), 1, '0')
                                    .arg(QString::number(kia_data->m_data_mpi->m_sub_address), 2, '0')
                                    .arg(QString::number(kia_data->m_data_mpi->m_word_data), 2, '0')));
    if (kia_data->m_data_mpi->m_format == DATA_BC_RT || kia_data->m_data_mpi->m_format == DATA_BC_RT_BRCST)
    {
        str_mpi_protocol.push_back("СД:");

        for (uint16_t ind = 0; ind < kia_data->m_data_mpi->m_word_data; ++ind)
        {
            uint16_t shift = 5;
            if (ind == 0)
                shift = 2;
            str_mpi_protocol.push_back(QString("%1 %2").arg("", -shift).arg(QString("0x%1").arg(QString::number(kia_data->m_data_mpi->m_data_to_exc[ind], 16), 4, '0')));
            if (ind % 7 == 0 && ind != 0)
                str_mpi_protocol.push_back("\n");
        }
        str_mpi_protocol.push_back("\n");
    }
    if (kia_data->m_data_mpi->m_status_exchange == KiaS_SUCCESS)
    {
        str_mpi_protocol.push_back(QString("%1 %2 %3\n").arg("ОС:", -5)
                                   .arg(QString("0x%1")
                                        .arg(QString::number(kia_data->m_data_mpi->m_wOs, 16), 4, '0'), -11)
                                   .arg(QString("%1-%2-%3-%4-%5-%6-%7-%8-%9-%10").arg(QString::number(kia_data->m_data_mpi->m_wOs >> 11), 2, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs & (0x0001 << 10)) >> 10), 1, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 9)) >> 9), 1, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 8)) >> 8), 1, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 5)) >> 5), 3, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 4)) >> 4), 1, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 3)) >> 3), 1, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 2)) >> 2), 1, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 1)) >> 2), 1, '0')
                                        .arg(QString::number((kia_data->m_data_mpi->m_wOs  & (0x0001 << 0)) >> 0), 1, '0')));

        str_mpi_protocol.push_back(QString("%1").arg("ИС:"));
        uint16_t shift = 5;
        for (int i = 0; i<=3; i++)
        {
            for (int j = 0; j<=7; j++)
            {
                if (i == 0 && j == 0)
                    shift = 2;
                else
                    shift = 5;
                str_mpi_protocol.push_back(QString("%1 %2").arg("", -shift)
                                           .arg(QString("0x%1").arg(QString::number(kia_data->m_data_mpi->m_data_word[i * 8 + j + 1 +
                                                                    kia_data->m_data_mpi->m_format], 16), 4, '0')));
            }
            str_mpi_protocol.push_back("\n");
        }
        str_mpi_protocol.push_back("\n");
    }
    else
    {

        QString error;
        switch(kia_data->m_data_mpi->m_wResult)
        {
        case 8:
            error = "ошибка таймаута при приеме";
            break;
        }

        str_mpi_protocol.push_back(QString("%1 %2 %3\n").arg("", -5)
                                   .arg(QString("%1")
                                        .arg(QString::number(kia_data->m_data_mpi->m_nInt)), -11)
                                   .arg(QString("обмен с ошибками")));
        str_mpi_protocol.push_back(QString("%1 %2 %3\n").arg("", -5)
                                   .arg(QString("%1")
                                        .arg(QString::number(kia_data->m_data_mpi->m_wResult)), -11)
                                   .arg(error));
    }
    kia_protocol->save_and_out_to_mko_protocols(num_bokz, str_mpi_protocol);
}

QString Bokz::set_data_from_mko_struct(QStringList list_name, std::vector<std::tuple<QString, double, double, double> > list_data)
{
    int16_t shift_for_numbers = -8;
    int16_t shift_description = -50;
    QString str_protocol;
    for (uint16_t num_list = 0; num_list < list_name.size(); ++num_list)
    {
        uint16_t do_shift_left = 0;
        if (std::get<PAD_NAME>(list_data[num_list])[0] == '-')
            do_shift_left = 1;
        QString is_norma = "";
        if (std::get<PAD_VALUE>(list_data[num_list]) < std::get<PAD_LOW_INTERVAL>(list_data[num_list]) ||
                std::get<PAD_VALUE>(list_data[num_list]) > std::get<PAD_HIGH_INTERVAL>(list_data[num_list]))
        {
            is_norma = "(не норма)";
        }
        str_protocol.push_back(helpers::format_qstring(list_name[num_list],
                                                       shift_description
                                                       + shift_for_numbers + do_shift_left)
                               + std::get<PAD_NAME>(list_data[num_list]) + is_norma + "\n");
    }
    return str_protocol;
}

std::tuple<double, double, double> Bokz::math_alpha_delta_azimut(double Qo0, double Qo1, double Qo2, double Qo3)
{
    auto De = asinm(Qo0 * Qo0 - Qo1 * Qo1 - Qo2 * Qo2 + Qo3 * Qo3);
    auto cDe = cos(De);
    auto sA = 2 * (Qo2 * Qo3 - Qo0 * Qo1) / cDe;
    auto cA  = 2 * (Qo1 * Qo3 + Qo0 * Qo2) / cDe;
    auto Al = atan2m(sA, cA);
    sA = 2 * (Qo1 * Qo3 - Qo0 * Qo2) / cDe;
    cA = 2 * (Qo2 * Qo3 + Qo0 * Qo1) / cDe;
    auto Az = atan2m(sA, cA);
    //Al = Al * RTS;
    //De = De * RTS;
    //Az = Az * RTS;
    return {Al, De, Az};
}

double Bokz::atan2m(double y, double x)
{
    double ang;

    if (fabs(x) > 1e-10f) ang = atan2(y, x);
    else
    {
        if (y > 0.f) ang = PI/2.f;
        else ang = -PI/2.f;
    }
    if (ang<0.f) ang += PI2;
    return ang;
}

double Bokz::asinm(double x)
{
    if (x > 1.f) x = 1.f;
    else if (x < -1.f) x = -1.f;

    return asin(x);
}

