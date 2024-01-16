#include "workwithmain.h"

WorkWithMain::WorkWithMain(int nPort) :
    m_kia_settings(new Kia_settings()),
    m_kia_timers(new Kia_timers())
{
    QThread::currentThread()->setPriority(QThread::HighPriority);
    start_tcp_server(nPort);
    set_kia_settings();

    start_kia_gui();
}

void WorkWithMain::set_kia_settings()
{
    kia_init();

    m_kia_settings->m_data_for_db->experiment_id = helpers::currentDateTime();

    m_kia_protocol.reset(new Kia_protocol(m_kia_settings));
    m_kia_protocol->create_dir_for_protocols();

    m_kia_db.reset(new Kia_db(m_kia_settings));
    m_kia_settings->m_data_for_db->true_host = m_kia_db->get_mac_address();
    m_kia_settings->m_data_for_db->m_extype_id = "stand";
    m_kia_settings->m_data_for_db->m_description = "Тестовое испытание";
    m_kia_db->start_experiment();


    m_kia_matrox.reset(new Kia_matrox(m_kia_settings));

    m_kia_mpi.reset(new Kia_mpi(m_kia_settings));

    connect(m_kia_mpi.get(), SIGNAL(changed_lpi()), this, SLOT(send_data_from_mpi_current_lpi_to_table_settings()));

    for (uint16_t num_conn = 0; num_conn < constants::max_count_same_connection; ++num_conn)
    {
        m_kia_bi_db[num_conn].reset(new Kia_db(m_kia_settings));
        m_kia_bi_db[num_conn]->start_commit();

        m_kia_bokz_db[num_conn].reset(new Kia_db(m_kia_settings, m_kia_settings->m_freq_bokz / 5));
        m_kia_bokz_db[num_conn]->start_commit();
    }
    for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
    {
        m_kia_timers->m_timer.push_back(std::make_shared<Timer>(ind_bi, m_kia_settings->m_timer_interval, m_kia_settings->m_freq_bokz, m_kia_settings));
        switch(m_kia_settings->m_type_bi)
        {
        case TYPE_BI_BKPIK:
            m_kia_timers->m_kia_bi.push_back(std::make_shared<Kia_bkpik>(ind_bi, m_kia_bi_db, m_kia_protocol, m_kia_settings));
            break;
        case TYPE_BI_BIU:
            m_kia_timers->m_kia_bi.push_back(std::make_shared<Kia_biu>(ind_bi, m_kia_bi_db, m_kia_protocol, m_kia_settings));
            break;
        }
        m_kia_timers->m_kia_synch_timer.push_back(std::make_shared<Kia_synch_timer>(ind_bi, m_kia_timers->m_timer[ind_bi], m_kia_timers->m_kia_bi[ind_bi], m_kia_settings, m_kia_protocol));
        m_kia_timers->m_timer[ind_bi]->start();
    }
    m_kia_ftdi.reset(new Kia_ftdi(m_kia_settings));
    switch(m_kia_settings->m_type_bokz)
    {
    case TYPE_BOKZ_BOKZM60:
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_count_bokz; ++num_bokz)
            m_bokz.push_back(std::make_shared<BokzM60>(num_bokz, m_kia_bokz_db, m_kia_mpi,
                                                       m_kia_protocol, m_kia_settings,
                                                       m_kia_ftdi));
        m_kia_cyclogram.reset(new Kia_cyclogram_bokzm60(m_kia_timers, m_bokz, m_kia_protocol, m_kia_settings));
        break;
    case TYPE_BOKZ_BOKZMF:
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_count_bokz; ++num_bokz)
            m_bokz.push_back(std::make_shared<Bokzmf>(num_bokz, m_kia_bokz_db, m_kia_mpi,
                                                      m_kia_protocol, m_kia_settings));
        m_kia_cyclogram.reset(new Kia_cyclogram_bokzmf(m_kia_timers, m_bokz, m_kia_protocol, m_kia_settings));
        break;
    }

}

void WorkWithMain::close_db_connection()
{

    m_kia_db->end_experiment();
    m_kia_db->close_connect();
    for (uint16_t num_conn = 0; num_conn < constants::max_count_same_connection; ++num_conn)
    {
        m_kia_bokz_db[num_conn]->stop_commit();
        m_kia_bokz_db[num_conn]->close_connect();

        m_kia_bi_db[num_conn]->stop_commit();
        m_kia_bi_db[num_conn]->close_connect();
    }

}

WorkWithMain::~WorkWithMain()
{
    m_process->terminate();
    cout <<"Destructor WorkWithMain"<<endl;
    delete_all_threads();
    close_db_connection();
    m_kia_protocol->close_dir_for_protocols();
}

void WorkWithMain::shtmi1(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->shtmi1(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::shtmi2(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->shtmi2(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::mshior( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->mshior(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::os(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->os(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::synchro(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->synchro(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::skor(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->skor(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::smti(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->smti(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::vmti(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->vmti(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_no(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_no(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_to(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_to(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_loc(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_loc(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_otclp(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_otclp(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_bshv(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_bshv(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_restart(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_restart(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_oo(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_oo(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_zkr(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_zkr(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::command_full_exp(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->command_full_exp(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::kvaor( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->kvaor(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::vskou( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->vskou(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::dtmi_or_dtmi_loc(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->dtmi_or_dtmi_loc(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);

}

void WorkWithMain::mloc(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->mloc(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::do_frames(uint16_t type_frame, uint16_t parametr)
{
    auto start_exchange = [this, type_frame](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->do_frames(m_type_frame_recieve, type_frame, parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::set_epsilon(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {

        m_bokz[num_bokz]->set_epsilon(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_epsilon, parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::get_epsilon(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->get_epsilon(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);

}

void WorkWithMain::set_focus(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->set_focus(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::get_focus(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->get_focus(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::set_texp(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->set_texp(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_texp, parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::get_texp(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_bokz[num_bokz]->get_texp(parametr);
    };
    check_used_bokz(IS_MPI_COMMAND, start_exchange, parametr);
}

void WorkWithMain::set_stop()
{
    for (uint16_t cycl_thr = 0; cycl_thr < m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread.size(); ++cycl_thr)
    {
        if ((m_bokz[cycl_thr]->m_is_used_bokz == CS_IS_ON) && (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[cycl_thr]))
        {
            m_kia_settings->m_flags_for_thread->m_stop_cyclogram[cycl_thr] = false;
            m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[cycl_thr].get();
        }
    }
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
    {
        m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch = false;
        m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch_thread.get();
    }
}

void WorkWithMain::delete_all_threads()
{
    for (uint16_t cycl_thr = 0; cycl_thr < m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread.size(); ++cycl_thr)
    {
        if ((m_bokz[cycl_thr]->m_is_used_bokz == CS_IS_ON) && (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[cycl_thr]))
        {
            m_kia_settings->m_flags_for_thread->m_stop_cyclogram[cycl_thr] = false;
            m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[cycl_thr].get();
        }
    }

    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
    {
        m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch = false;
        m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch_thread.get();
    }

    for (uint16_t command_th = 0; command_th < m_kia_settings->m_flags_for_thread->m_stop_command_thread.size(); ++command_th)
    {
        if ((m_bokz[command_th]->m_is_used_bokz == CS_IS_ON) && (m_kia_settings->m_flags_for_thread->m_stop_command[command_th]))
        {
            m_kia_settings->m_flags_for_thread->m_stop_command[command_th] = false;
            m_kia_settings->m_flags_for_thread->m_stop_command_thread[command_th].get();
        }
    }

    for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
    {
        m_kia_timers->m_kia_synch_timer[ind_bi]->stop_timer();
        m_kia_timers->m_kia_bi[ind_bi]->stop_1s_mark();
        m_kia_timers->m_timer[ind_bi]->closeTimerThread();
    }
}

void WorkWithMain::cyclogram_ai( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_ai(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_state_on( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_state_on(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_state_off( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_state_off(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_oo(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_oo(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_no( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_no(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_to( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_to(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);

}
void WorkWithMain::cyclogram_loc( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_loc(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}
void WorkWithMain::cyclogram_define_address( uint16_t parametr)
{
    m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch = true;
    m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch_thread = std::async([this, parametr]()
    {
        m_kia_cyclogram->cyclogram_define_address(parametr);
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
        {
            QStringList correct_adress;
            correct_adress.push_back(QString::number(TS_ADDRESS));
            for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_count_bokz; num_bokz++)
            {
                correct_adress.push_back(QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address));
            }
            emit send_to_client(SEND_DATA_TO_SETTINGS_WINDOW, correct_adress);
        }
    });
}

void WorkWithMain::cyclogram_operation( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_operation(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_1s_mark( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_1s_mark(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_test_mko( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_test_mko(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_test_synchro( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_test_synchro(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_technical_run( uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_technical_run(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_zkr(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_zkr(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_full_frames(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_full_frames(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::cyclogram_check_address(uint16_t parametr)
{
    auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
    {
        m_kia_cyclogram->cyclogram_check_address(num_bokz, parametr);
    };
    check_used_bokz(IS_CYCLOGRAM, start_exchange, parametr);
}

void WorkWithMain::slot_send_to_client(quint16 num, QStringList data_for_client)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << data_for_client << m_kia_settings->m_type_bokz << m_kia_settings->m_type_bi << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pClientSocket->write(arrBlock);
}

void WorkWithMain::delete_connection()
{
    std::cout << "disconnection" << std::endl;
    disconnect(this, SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    disconnect(m_kia_protocol.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
    {
        disconnect(m_kia_timers->m_kia_bi[ind_bi].get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
        disconnect(m_kia_timers->m_kia_synch_timer[ind_bi].get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    }
    disconnect(m_kia_mpi.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    disconnect(m_kia_db.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    for (auto bokz : m_bokz)
        disconnect(bokz.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    m_pClientSocket->deleteLater();
}

void WorkWithMain::new_connection_slot()
{
    std::cout << "connection" << std::endl;
    m_pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(m_pClientSocket, SIGNAL(disconnected()), this, SLOT(delete_connection()));
    connect(m_pClientSocket, SIGNAL(readyRead()), this, SLOT(slot_read_client()));
    connect(this, SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
    {
        connect(m_kia_timers->m_kia_bi[ind_bi].get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
        connect(m_kia_timers->m_kia_synch_timer[ind_bi].get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    }
    connect(m_kia_protocol.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    connect(m_kia_db.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    connect(m_kia_mpi.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));

    for (auto bokz : m_bokz)
        connect(bokz.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));

    send_kia_initial_settings();
    send_mpi_list_command();
    send_mpi_list_other_command();
    send_cyclogams_ai_list();
    send_cyclogams_ri_list();
    send_cyclogams_list();
    send_cyclograms_do();
    send_info_about_connection();
    m_kia_db->send_status_connection_to_db();

    m_kia_mpi->send_data_from_mpi_num_mpi_to_table_settings();
    send_type_bi_to_table_settings();

    kia_profile_load();
}

void WorkWithMain::start_tcp_server(uint16_t nPort)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        QMessageBox::critical(0,"Server Error",
                              "Unable to start the server" +
                              m_ptcpServer->errorString());
        m_ptcpServer->close();
    }
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(new_connection_slot()));
}

void WorkWithMain::kia_init()
{
    m_kia_load_initial_settings.reset(new Kia_load_initial_settings(m_kia_settings));

    m_kia_settings->m_timer_interval = 1000;

    Kia_port m_kia_port(m_kia_settings);
    m_kia_port.check_used_bi_ports(m_kia_settings->m_type_bi);

    m_kia_settings->m_data_for_db->bshv.resize(m_kia_settings->m_data_for_bi->m_count_bi);
    m_kia_settings->m_count_bokz = m_kia_settings->m_data_for_bi->m_count_bi * m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi];

    m_kia_settings->m_flags_for_thread->m_stop_cyclogram.resize(m_kia_settings->m_count_bokz);
    m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread.resize(m_kia_settings->m_count_bokz);

    m_kia_settings->m_flags_for_thread->m_stop_command.resize(m_kia_settings->m_count_bokz);
    m_kia_settings->m_flags_for_thread->m_stop_command_thread.resize(m_kia_settings->m_count_bokz);

    m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info.resize(m_kia_settings->m_count_bokz);
}

void WorkWithMain::start_kia_gui()
{
    QStringList arguments;
    m_process = new QProcess();
    //m_process->start("bash", QStringList() << "-c" << "\"\"source /home/alexander/Project/kia/kia_gui_run.sh\"\"");
    //m_process->waitForStarted();
}

bool WorkWithMain::check_used_bokz(uint16_t type_command, std::function<void (uint16_t, uint16_t)> start_exchange, uint16_t parametr)
{
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] = KiaS_FAIL;
    for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
    {
        if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
            if (type_command == IS_CYCLOGRAM)
            {
                if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] = false;
                    m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[num_bokz].get();
                }
                m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] = true;
                m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info[num_bokz] = true;
                m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[num_bokz] = std::async([this, num_bokz, start_exchange, parametr]()
                {
                    start_exchange(num_bokz, parametr);
                    m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info[num_bokz] = false;
                });
            }
            else
            {
                if (m_kia_settings->m_flags_for_thread->m_stop_command[num_bokz])
                {
                    m_kia_settings->m_flags_for_thread->m_stop_command[num_bokz] = false;
                    m_kia_settings->m_flags_for_thread->m_stop_command_thread[num_bokz].get();
                }
                m_kia_settings->m_flags_for_thread->m_stop_command[num_bokz] = true;
                m_kia_settings->m_flags_for_thread->m_stop_command_thread[num_bokz] = std::async([num_bokz, start_exchange, parametr]()
                {
                    start_exchange(num_bokz, parametr);
                });
            }
        }
    }
    return true;
}

void WorkWithMain::send_kia_initial_settings()
{
    QStringList settings;
    settings.push_back(QString::number(m_kia_settings->m_data_for_bi->m_count_bi));
    emit send_to_client(SET_KIA_GUI_SETTINGS, settings);
}

void WorkWithMain::send_mpi_list_command()
{
    QStringList mpi_command;
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command)
    {
        mpi_command.push_back(std::get<CYCL_NAME>(el));
        mpi_command.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
    }
    emit send_to_client(SEND_MPI_COMMAND, mpi_command);
}

void WorkWithMain::send_mpi_list_other_command()
{
    QStringList mpi_other_command;
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command)
    {
        mpi_other_command.push_back(std::get<CYCL_NAME>(el));
        mpi_other_command.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
    }
    emit send_to_client(SEND_OTHER_MPI_COMMAND, mpi_other_command);
}

void WorkWithMain::send_cyclogams_list()
{
    QStringList cyclograms;
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_tp)
    {
        cyclograms.push_back(std::get<CYCL_NAME>(el));
        cyclograms.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
    }
    emit send_to_client(SEND_CYCLOGRAMS_TP, cyclograms);
}

void WorkWithMain::send_cyclogams_ai_list()
{
    QStringList cyclograms;
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai)
    {
        cyclograms.push_back(std::get<CYCL_NAME>(el));
        cyclograms.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
    }
    emit send_to_client(SEND_CYCLOGRAMS_AI, cyclograms);
}

void WorkWithMain::send_cyclogams_ri_list()
{
    QStringList cyclograms;
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri)
    {
        cyclograms.push_back(std::get<CYCL_NAME>(el));
        cyclograms.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
    }
    emit send_to_client(SEND_CYCLOGRAMS_RI, cyclograms);
}

void WorkWithMain::send_cyclograms_do()
{
    for (auto cycl : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_cycl_do)
    {
        QStringList commands;
        for (auto el : cycl)
        {
            commands.push_back(std::get<CYCL_NAME>(el));
            commands.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
        }
        if (commands.size() != 0)
            emit send_to_client(SEND_CYCLOGRAMS_DO, commands);
    }
}

void WorkWithMain::kia_profile_load()
{
    QStringList load_profile;
    emit send_to_client(LOAD_PROFILE, load_profile);
}

void WorkWithMain::send_type_bi_to_table_settings()
{
    QStringList list_bi;
    list_bi.push_back(QString::number(TS_TYPE_BI));
    for (auto el : m_kia_settings->m_data_for_bi->m_num_bi)
        list_bi.push_back(QString::number(el));
    emit send_to_client(SEND_DATA_TO_SETTINGS_WINDOW, list_bi);
}

void WorkWithMain::send_info_about_connection()
{
    QStringList con_info;
    con_info.push_back(QString::fromStdString(m_kia_settings->m_data_for_db->experiment_id));
    emit send_to_client(CONNECT_TO_CORE, con_info);
}



void WorkWithMain::send_data_from_mpi_current_lpi_to_table_settings()
{
    QStringList correct_lpi;
    correct_lpi.push_back(QString::number(TS_LPI));
    for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
    {
        correct_lpi.push_back(QString::number(m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi));
    }
    emit send_to_client(SEND_DATA_TO_SETTINGS_WINDOW, correct_lpi);
}

void WorkWithMain::slot_read_client()
{
    QDataStream in(m_pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    for(;;)
    {
        if (!m_nNextBlockSize)
        {
            if (m_pClientSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (m_pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }
        QVector<QString> data_from_client;
        qint16 num;
        qint16 type_bokz;
        qint16 type_bi;
        in >> data_from_client >> type_bokz >> type_bi >> num;
        m_kia_settings->m_type_bokz = type_bokz;
        m_kia_settings->m_type_bi = type_bi;
        uint16_t is_dec_or_hex = 16;
        bool ok;
        //std::cout << num << std::endl;
        switch (num)
        {
        case SHTMI_1:
            shtmi1();
            break;
        case SHTMI_2:
            shtmi2();
            break;
        case MSHI_OR:
            mshior();
            break;
        case DTMI_ONE:
            dtmi_or_dtmi_loc(EP_NOFULLEXCHANGE);
            break;
        case MLOCK_ONE:
            mloc(EP_NOFULLEXCHANGE);
            break;
        case SMTI:
            smti();
            break;
        case VMTI:
            vmti();
            break;
        case SYNCHRO:
            synchro();
            break;
        case SKOR:
            skor();
            break;
        case CYCLOGRAM_OO:
            cyclogram_no();
            break;
        case CYCLOGRAM_NO:
            cyclogram_no();
            break;
        case CYCLOGRAM_TO:
            cyclogram_to();
            break;
        case CYCLOGRAM_LOC:
            cyclogram_loc();
            break;
        case CYCLOGRAM_STATE_ON:
            cyclogram_state_on();
            break;
        case CYCLOGRAM_STATE_OFF:
            cyclogram_state_off();
            break;
        case COMMAND_FULL_EXP:
            command_full_exp();
            break;
        case POWER_ON:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                {
                    if (data_from_client[0].toInt() < BI_ALL_OFF)
                        m_bokz[num_bokz]->m_kia_data->m_data_bi->m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                                                                                            data_from_client[0].toInt());
                }
            }
            break;
        case POWER_OFF:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                {
                    if (data_from_client[0].toInt() < BI_ALL_OFF)
                        m_bokz[num_bokz]->m_kia_data->m_data_bi->m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                                                                                             data_from_client[0].toInt());
                }
            }
            break;
        case ON_1S:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                {
                    if (data_from_client[0].toInt() < BI_ALL_OFF)
                        m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_1s_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                                 data_from_client[0].toInt());
                }
            }
            break;
        case OFF_1S:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                {
                    if (data_from_client[0].toInt() < BI_ALL_OFF)
                        m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_1s_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                                  data_from_client[0].toInt());
                }
            }
            break;
        case COMMAND_NO:
            command_no();
            break;
        case COMMAND_TO:
            command_to();
            break;
        case COMMAND_LOC:
            command_loc();
            break;
        case COMMAND_OTCLP:
            command_otclp();
            break;
        case COMMAND_OO:
            command_oo();
            break;
        case COMMAND_RESTART:
            command_restart();
            break;
        case COMMAND_BSHV:
            command_bshv();
            break;
        case CYCLOGRAM_OFFLINE_TEST:
            cyclogram_ai();
            break;
        case CYCLOGRAM_STOP:
            set_stop();
            break;
        case CYCLOGRAM_DEFINE_ADDRESS:
            cyclogram_define_address();
            break;
        case COMMAND_OS:
            os();
            break;
        case COMMAND_VSKOU:
            vskou();
            break;
        case SET_USED_BOKZ:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                m_bokz[num_bokz]->m_is_used_bokz = data_from_client[num_bokz].toInt();
            }
            break;
        case SET_USED_ADDRESS:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address = data_from_client[num_bokz].toInt();
            }
            break;
        case SET_TD:
            for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
            {
                for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
                {
                    m_kia_timers->m_kia_bi[ind_bi]->m_kia_data->m_data_bi->m_term_group[num_bokz] = data_from_client[num_bokz].toInt();
                }

            }
            break;
        case SET_NUM_MPI:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_mpi_index = data_from_client[num_bokz].toInt();
            }
            break;
        case SET_QA:
            array<double, constants::size_qa> qa;
            for (uint16_t qa_index = 1; qa_index < data_from_client.size(); ++qa_index)
                qa[qa_index - 1] = data_from_client[qa_index].toDouble();
            for (auto el : qa)
            {
                cout << el << endl;
            }
            memcpy(&m_bokz[data_from_client[0].toInt()]->m_kia_data->m_data_mpi->m_qa, &qa, sizeof(qa));
            break;
        case SET_W:
            array<uint16_t, constants::size_w> w;
            for (uint16_t w_index = 0; w_index < data_from_client.size(); ++w_index)
                w[w_index] = data_from_client[w_index + 1].toDouble();
            for (auto el : data_from_client)
            {
                cout << el.toFloat() << endl;
            }
            memcpy(&m_bokz[data_from_client[0].toInt()]->m_kia_data->m_data_mpi->m_w, &w,sizeof(w));
            break;
        case SET_BSHV:
            m_kia_settings->m_data_for_db->bshv[data_from_client[0].toInt()] = data_from_client[1].toInt();
            break;
        case CYCLOGRAM_OPERATION:
            cyclogram_operation();
            break;
        case CYCLOGRAM_1S_MARK:
            cyclogram_1s_mark();
            break;
        case CYCLOGRAM_TEST_MKO:
            cyclogram_test_mko();
            break;
        case CYCLOGRAM_TECH_RUN:
            cyclogram_technical_run();
            break;
        case SET_CURRENT_LPI:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = data_from_client[num_bokz].toInt();
            }
            break;
        case SET_USED_MPI_COMMAND_IN_CYCLOGRAM:
            for (uint16_t num_mpi_command = 0; num_mpi_command < data_from_client.size(); ++num_mpi_command)
                m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram[num_mpi_command] = data_from_client[num_mpi_command].toInt();
            break;
        case SET_CYCLOGRAM_SETTINGS_IF_DO_A_LOT:
            for (uint16_t num_param = 0; num_param < data_from_client.size() - 1; ++num_param)
                m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[data_from_client[0].toInt()][num_param] = data_from_client[num_param + 1].toInt();
            break;
        case SET_EXC_FREQ:
            m_kia_settings->m_freq_bokz = data_from_client[0].toInt();
            for (auto timer : m_kia_timers->m_timer)
                timer->change_divider(m_kia_settings->m_freq_bokz);
            break;
        case CYCLOGRAM_ZKR:
            cyclogram_zkr();
            break;
        case DO_FULL_FRAME:
            do_frames(Bokz::FULL_FRAME, EP_NOPROTECTEDEXCHANGE);
            break;
        case DO_BIN_FRAME:
            do_frames(Bokz::BIN_FRAME, EP_NOPROTECTEDEXCHANGE);
            break;
        case CYCL_FULL_FRAMES:
            cyclogram_full_frames();
            break;
        case SET_RELAY_PULSE:
            printf("relay command %04x\n", data_from_client[TRC_PULSE].toUInt());
            for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
            {
                m_kia_timers->m_kia_bi[ind_bi]->set_relay_command(data_from_client[TRC_PULSE].toUInt());

            }
            break;
        case SET_RELAY_PULSE_TIME:
            std::cout << "pulse time " << data_from_client[TRC_TIME_PULSE].toUInt() << std::endl;
            for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
            {
                m_kia_timers->m_kia_bi[ind_bi]->set_relay_command_pulse_time(data_from_client[TRC_TIME_PULSE].toUInt());

            }
            break;
        case SET_RELAY_POLAR:
            std::cout << "polar " << data_from_client[TRC_POLAR].toUInt() << std::endl;
            for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
            {
                m_kia_timers->m_kia_bi[ind_bi]->set_relay_polarity(data_from_client[TRC_POLAR].toUInt());
            }
            break;
        case SET_SEC_MARK_PERIOD:
            for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
            {
                m_kia_timers->m_kia_bi[ind_bi]->set_sec_mark_pulse_time(data_from_client[0].toInt());
            }
            break;
        case SET_NUM_BI:
            for (uint16_t num_bokz = 0; num_bokz < data_from_client.size(); ++num_bokz)
            {
                m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi = data_from_client[num_bokz].toInt();
            }
            break;
        case IMITATOR_ON:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_imitator_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
            }
            break;
        case IMITATOR_OFF:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_imitator_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
            }
            break;
        case CONROL_COMMAND_ON:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_contol_command(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
            }
            break;
        case CONROL_COMMAND_OFF:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_contol_command(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
            }
            break;
        case SET_USED_CHANNEL:
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel = data_from_client[num_bokz].toInt();
            }
            break;
        case SET_EPSILON:
            m_bokz[data_from_client[0].toInt()]->m_kia_data->m_data_mpi->m_epsilon = data_from_client[1].toInt();
            set_epsilon();
            break;
        case GET_EPSILON:
            get_epsilon();
            break;
        case SET_FOCUS:
            m_bokz[data_from_client[0].toInt()]->m_kia_data->m_data_mpi->m_focus_data[FOCUS] = data_from_client[1].toFloat();
            set_focus();
            break;
        case GET_FOCUS:
            get_focus();
            break;
        case SET_TEXP:
            m_bokz[data_from_client[0].toInt()]->m_kia_data->m_data_mpi->m_texp = data_from_client[1].toInt();
            set_texp();
            break;
        case GET_TEXP:
            get_texp();
            break;
        case SET_CORD_X:
            m_bokz[data_from_client[0].toInt()]->m_kia_data->m_data_mpi->m_focus_data[CORD_X] = data_from_client[1].toFloat();
            set_focus();
            break;
        case SET_CORD_Y:
            m_bokz[data_from_client[0].toInt()]->m_kia_data->m_data_mpi->m_focus_data[CORD_Y] = data_from_client[1].toFloat();
            set_focus();
            break;
        case CYCLOGRAM_TEST_ADRESS:
            cyclogram_check_address();
            break;
        case CYCLOGRAM_SYNCHRO:
            cyclogram_test_synchro();
            break;
        case SET_AI_SKIP_OR_STOP:
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_skip_fails_for_continue = data_from_client[0].toInt();
            break;
        case DEBUGGING_COMMAND:
            m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] = KiaS_FAIL;
            if (data_from_client[CS_DIRECTION].toInt() == 0)
            {
                for (uint16_t num_word = 0; num_word < data_from_client[CS_WORD_DATA].toInt(); ++num_word)
                {
                    if (data_from_client[CS_DATA_TO_EXC + num_word][0] == "0")
                        is_dec_or_hex = 16;
                    else
                        is_dec_or_hex = 10;
                    m_bokz[data_from_client[CS_NUM_BOKZ].toInt()]->m_kia_data->m_data_mpi->m_data_to_exc[num_word] = data_from_client[CS_DATA_TO_EXC + num_word].toInt(&ok, is_dec_or_hex);
                }
            }
            m_bokz[data_from_client[CS_NUM_BOKZ].toInt()]->debugging_command(data_from_client[CS_DIRECTION].toInt(), data_from_client[CS_FORMAT].toInt(),
                                                                             data_from_client[CS_SUB_ADDRESS].toInt(), data_from_client[CS_WORD_DATA].toInt(), data_from_client[CS_STRUCT_ID].toStdString(), data_from_client[CS_STRUCT_ID_DESCK].toStdString());
            break;
        case COMMAND_ZKR:
            command_zkr();
            break;
        case SET_IS_OFF_POWER_IN_TP:
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_off_power_for_tp = data_from_client[0].toInt();
            break;
        case SET_DO_CYCLOGRAM_IN_TP:
            for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size(); ++num_cyclogram)
                m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp[num_cyclogram] = data_from_client[num_cyclogram].toInt();

            break;
        case SET_COUNT_TO_DO_CYCLOGRAM_IN_TP:
            for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size(); ++num_cyclogram)
                m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp[num_cyclogram] = data_from_client[num_cyclogram].toInt();
            break;
        case SET_DO_CYCLOGRAM_IN_AI:
            for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size(); ++num_cyclogram)
                m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_ai[num_cyclogram] = data_from_client[num_cyclogram].toInt();
            break;

        case SET_DO_CYCLOGRAM_IN_DO:
            for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size() - 1; ++num_cyclogram)
                m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[data_from_client[0].toInt()][num_cyclogram] = data_from_client[num_cyclogram + 1].toInt();
            break;
        case SET_PAUSE_DO_CYCLOGRAM_IN_DO:
            for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size() - 1; ++num_cyclogram)
                m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[data_from_client[0].toInt()][num_cyclogram] = data_from_client[num_cyclogram + 1].toInt();
            break;
        }
        m_nNextBlockSize = 0;
    }
}
