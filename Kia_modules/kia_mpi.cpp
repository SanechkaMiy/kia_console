#include "kia_mpi.h"

Kia_mpi::Kia_mpi()
{
    m_mpi_thread = std::async([this]()
    {
        init();
        m_mpi_stop = true;
        while(m_mpi_stop)
        {
            wait_for_event();
            if (m_data.front().first == "stop_mpi")
            {
                close();
                break;
            }
            if (m_data.front().first == "exchange")
            {
                execute_exchange(m_data.front().second);
            }
            m_data.pop();
        }
    });

}

Kia_mpi::~Kia_mpi()
{
    std::lock_guard lock(m_mtx);
    Kia_data kia_data;
    m_data.push(std::make_pair("stop_mpi", &kia_data));
    m_cv.notify_all();
    m_mpi_stop = false;
    m_mpi_thread.get();

}

void Kia_mpi::init()
{
    printf("tmk is open = %d\n",TmkOpen());
    //    int hTmk = 8;
    //    if (tmkconfig(hTmk) == 0)
    //    {
    //        tmkselect(hTmk);
    //        bcreset();
    //        m_mpi_num[m_count_chip] = hTmk;
    //        printf("Device number -  %d\n", hTmk);
    //        m_count_chip++;
    //    }

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

void Kia_mpi::wait_for_event()
{
    std::mutex m;
    std::unique_lock lk(m);
    m_cv.wait(lk, [this]
    {
        return  !m_data.empty();
    });
}

void Kia_mpi::execute_exchange(Kia_data* kia_data)
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
    if ((kia_data->m_data_mpi->m_wResult == 0) && (kia_data->m_data_mpi->m_nInt == 1))//Есть ли ошибка обмена
    {
        kia_data->m_data_mpi->m_status_exchange = KiaS_SUCCESS;
    }
    else
    {
        kia_data->m_data_bokz->m_count_fail[0]++;
        kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
    }
    bcgetblk(0, kia_data->m_data_mpi->m_data_word.data(), constants::packetSize);
    kia_data->m_data_db->receive_time = helpers::currentDateTime();
    if (kia_data->m_data_mpi->m_format == DATA_BC_RT)
        kia_data->m_data_mpi->m_wOs = kia_data->m_data_mpi->m_data_word[kia_data->m_data_mpi->m_word_data + 1];
    else
        kia_data->m_data_mpi->m_wOs = kia_data->m_data_mpi->m_data_word[1];
    if ((kia_data->m_data_mpi->m_wOs & (0x0001 << 15)) == 1)
    {
        kia_data->m_data_bokz->m_count_fail[4]++;
    }
    emit changed_lpi();
    emit end_exchange(kia_data->m_data_mpi->m_num_bokz);
}

void Kia_mpi::do_exchange(Kia_data* kia_data)
{
    std::lock_guard lock(m_mtx);
    m_data.push(std::make_pair("exchange", kia_data));
    m_cv.notify_all();
}
void Kia_mpi::reset(Kia_data* kia_data)
{
    array<uint16_t, constants::packetSize> data_to_reset;
    data_to_reset.fill(0x0a00);
    bcdefbus(kia_data->m_data_mpi->m_lpi);
    bcdefbase(kia_data->m_data_mpi->m_base);
    bcputblk(0, data_to_reset.data(), data_to_reset.size());
}

void Kia_mpi::send_data_from_mpi_num_mpi_to_table_settings()
{
    QStringList correct_mpi_dev;
    correct_mpi_dev.push_back(QString::number(TS_MPI));
    for (uint16_t num_mpi = 0; num_mpi <  m_count_chip; ++num_mpi)
        correct_mpi_dev.push_back(QString::number(m_mpi_num[num_mpi]));
    if (m_count_chip == 0)
        correct_mpi_dev.push_back("-");
    emit send_to_client(SEND_DATA_TO_SETTINGS_WINDOW, correct_mpi_dev);
}

