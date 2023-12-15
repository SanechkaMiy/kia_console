#include "kia_mpi.h"

Kia_mpi::Kia_mpi(shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings) :
    m_kia_protocol(kia_protocol),
    m_kia_settings(kia_settings)
{
    init();
}

Kia_mpi::~Kia_mpi()
{
    close();
}

void Kia_mpi::init()
{
    printf("tmk is open = %d\n",TmkOpen());
    for (int hTmk = 0; hTmk < constants::max_tmk_dev; ++hTmk)
    {
        if (tmkconfig(hTmk) == 0)
        {
            tmkselect(hTmk);
            bcreset();
            m_mpi_num[m_count_chip] = hTmk;
            printf("Device number -  %d\n", hTmk);
            m_count_chip++;
        }

    }
}

void Kia_mpi::close()
{
    tmkdone(ALL_TMKS);
    TmkClose();
}

uint16_t Kia_mpi::execute_exchange(std::shared_ptr<Kia_data> kia_data, uint16_t &num_bokz)
{
    reset(kia_data);

    tmkselect(kia_data->m_data_mpi->m_mpi_index);
    kia_data->m_data_db->send_time = helpers::currentDateTime();
    bcdefbus(kia_data->m_data_mpi->m_lpi);
    bcdefbase(kia_data->m_data_mpi->m_base);
    bcputw(0, kia_data->m_data_mpi->m_code_word);
    if (kia_data->m_data_mpi->m_format == DATA_BC_RT)
        bcputblk(1, kia_data->m_data_mpi->m_data_to_exc.data(), kia_data->m_data_mpi->m_data_to_exc.size() - 1);
    kia_data->m_data_db->m_datetime = helpers::currentDateTime();
    bcstart(kia_data->m_data_mpi->m_base, kia_data->m_data_mpi->m_format);
    tmkwaitevents(1 << kia_data->m_data_mpi->m_mpi_index, 1000);
    TTmkEventData tmkEvD;
    tmkgetevd(&tmkEvD);
    kia_data->m_data_mpi->m_wResult = tmkEvD.bc.wResult;
    kia_data->m_data_mpi->m_nInt = tmkEvD.nInt;
    kia_data->m_data_db->waw1 = tmkEvD.bc.wAW1;
    kia_data->m_data_db->waw1 = tmkEvD.bc.wAW2;
    m_kia_settings->m_data_for_db->m_exchange_counter++;
    if ((kia_data->m_data_mpi->m_wResult == 0) && (kia_data->m_data_mpi->m_nInt == 1))//Есть ли ошибка обмена
    {
        kia_data->m_data_mpi->m_status_exchange = KiaS_SUCCESS;
    }
    else
    {
        m_kia_settings->m_data_to_protocols->m_count_of_exc_fail[num_bokz]++;
        kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
    }
    bcgetblk(0, kia_data->m_data_mpi->m_data_word.data(), constants::packetSize);
    kia_data->m_data_db->receive_time = helpers::currentDateTime();
    if (kia_data->m_data_mpi->m_format == DATA_BC_RT)
        kia_data->m_data_mpi->m_wOs = kia_data->m_data_mpi->m_data_word[kia_data->m_data_mpi->m_word_data + 1];
    else
        kia_data->m_data_mpi->m_wOs = kia_data->m_data_mpi->m_data_word[1];

    parse_mko_protocols(num_bokz, kia_data);
    emit changed_lpi();
    return kia_data->m_data_mpi->m_status_exchange;
}

void Kia_mpi::reset(std::shared_ptr<Kia_data> kia_data)
{
    array<uint16_t, constants::packetSize> data_to_reset;
    data_to_reset.fill(0x0a00);
    bcdefbus(kia_data->m_data_mpi->m_lpi);
    bcdefbase(kia_data->m_data_mpi->m_base);
    bcputblk(0, data_to_reset.data(), data_to_reset.size());
}

void Kia_mpi::parse_mko_protocols(uint16_t &num_bokz, std::shared_ptr<Kia_data> kia_data)
{
    QString str_mpi_protocol;
    str_mpi_protocol.push_back(helpers::format_qstring("", m_kia_settings->m_format_for_desc->shift_for_numbers + 3, '-') + helpers::format_qstring(" " + QString::fromStdString(kia_data->m_data_db->struct_id_desc) + " ", m_kia_settings->m_format_for_desc->shift_description,'-') + '\n');

    str_mpi_protocol.push_back(QString("%1 %2 %3 %4 %5 %6 %7\n").arg("", -5).arg("БШВ", -11).arg("МПИ", -11).arg("ФОРМАТ",-11).arg("address", -11).arg("ЛПИ",-11).arg("ДАТА И ВРЕМЯ"));
    str_mpi_protocol.push_back(QString("%1 %2 %3 %4 %5 %6 %7\n").arg("", -5)
                               .arg(QString::number(m_kia_settings->m_data_for_db->bshv[kia_data->m_data_bi->m_num_used_bi]),-11).arg(QString::number(kia_data->m_data_mpi->m_mpi_index), -11)
            .arg(QString::number(kia_data->m_data_mpi->m_format), -11).arg(QString::number(kia_data->m_data_mpi->m_address),-11)
            .arg(QString::number(kia_data->m_data_mpi->m_lpi),-11).arg(QString::fromStdString(kia_data->m_data_db->m_datetime)));
    str_mpi_protocol.push_back(QString("%1 %2 %3\n").arg("КС:", -5)
                               .arg(QString("0x%1")
                                    .arg(QString::number(kia_data->m_data_mpi->m_code_word, 16), 4, '0'), -11)
                               .arg(QString("%1-%2-%3-%4").arg(QString::number(kia_data->m_data_mpi->m_address), 2, '0')
                                    .arg(QString::number(kia_data->m_data_mpi->m_direction), 1, '0')
                                    .arg(QString::number(kia_data->m_data_mpi->m_sub_address), 2, '0')
                                    .arg(QString::number(kia_data->m_data_mpi->m_word_data), 2, '0')));
    if (kia_data->m_data_mpi->m_format == DATA_BC_RT)
    {
        for (uint16_t ind = 0; ind < kia_data->m_data_mpi->m_word_data; ++ind)
            str_mpi_protocol.push_back(QString("%1 %2").arg("", -5).arg(QString("0x%1").arg(QString::number(kia_data->m_data_mpi->m_data_to_exc[ind], 16), 4, '0')));
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
    m_kia_protocol->save_and_out_to_mko_protocols(num_bokz, str_mpi_protocol);
}

void Kia_mpi::send_data_from_mpi_num_mpi_to_table_settings()
{
    QStringList correct_mpi_dev;
    correct_mpi_dev.push_back(QString::number(TS_MPI));
    for (uint16_t num_mpi = 0; num_mpi <  m_count_chip; ++num_mpi)
        correct_mpi_dev.push_back(QString::number(m_mpi_num[num_mpi]));
    emit send_to_client(SEND_DATA_TO_SETTINGS_WINDOW, correct_mpi_dev);
}

