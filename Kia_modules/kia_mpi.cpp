#include "kia_mpi.h"



Kia_mpi::Kia_mpi()
{
    enum MPI_FORMAT
    {
        TYPE_COMMAND = 0,
        DATA = 1,
        NUM_DEV = 2
    };

    m_mpi_thread = std::async([this]()
    {
        init();
        m_mpi_stop = true;
        while(m_mpi_stop)
        {
            wait_for_event();
            if (std::get<TYPE_COMMAND>(m_data.front()) == "stop_mpi")
            {
                close();
                break;
            }
            if (std::get<TYPE_COMMAND>(m_data.front()) == "exchange")
            {
                execute_exchange(std::get<DATA>(m_data.front()), std::get<NUM_DEV>(m_data.front()));
            }
            m_data.pop();
        }
    });

}

Kia_mpi::~Kia_mpi()
{
    std::lock_guard lock(m_mtx);
    Kia_mpi_data kia_data;
    m_data.push(std::make_tuple("stop_mpi", &kia_data, 0));
    m_cv.notify_all();
    m_mpi_stop = false;
    m_mpi_thread.get();
    std::cout << "stop mpi" << std::endl;
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

void Kia_mpi::execute_exchange(Kia_mpi_data* mpi_data, uint16_t num_bokz)
{
    reset(mpi_data);
    tmkselect(mpi_data->m_mpi_index);
    mpi_data->send_time = helpers::currentDateTime();
    bcdefbus(mpi_data->m_lpi);
    bcdefbase(mpi_data->m_base);
    bcputw(0, mpi_data->m_code_word);
    if (mpi_data->m_format == DATA_BC_RT)
        bcputblk(1, mpi_data->m_data_for_exchange.data(), mpi_data->m_data_for_exchange.size() - 1);

    bcstart(mpi_data->m_base, mpi_data->m_format);
    tmkwaitevents(1 << mpi_data->m_mpi_index, 1000);
    TTmkEventData tmkEvD;
    tmkgetevd(&tmkEvD);
    mpi_data->m_wResult = tmkEvD.bc.wResult;
    mpi_data->m_nInt = tmkEvD.nInt;
    if ((mpi_data->m_wResult == 0) && (mpi_data->m_nInt == 1))//Есть ли ошибка обмена
    {
        mpi_data->m_status_exchange = {KiaS_SUCCESS, " - УСПЕХ"};
    }
    else
    {
        mpi_data->m_status_exchange = {KiaS_FAIL, " - ОШИБКА"};
    }
    bcgetblk(0, mpi_data->m_data_word.data(), constants::packetSize);

    mpi_data->receive_time = helpers::currentDateTime();
    if (mpi_data->m_format == DATA_BC_RT)
        mpi_data->m_answer_word = mpi_data->m_data_word[mpi_data->m_word_data + 1];
    else
        mpi_data->m_answer_word  = mpi_data->m_data_word[1];
    emit changed_lpi();
    emit end_exchange(num_bokz);
}

void Kia_mpi::do_exchange(Kia_mpi_data *mpi_data, uint16_t num_bokz)
{
    std::lock_guard lock(m_mtx);
    m_data.push(std::make_tuple("exchange", mpi_data, num_bokz));
    m_cv.notify_all();
}
void Kia_mpi::reset(Kia_mpi_data *mpi_data)
{
    array<uint16_t, constants::packetSize> data_to_reset;
    data_to_reset.fill(0x0a00);
    bcdefbus(mpi_data->m_lpi);
    bcdefbase(mpi_data->m_base);
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

