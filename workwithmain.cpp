#include "workwithmain.h"

WorkWithMain::WorkWithMain(int nPort) :
    m_kia_settings(new Kia_settings()),
    m_kia_timers(new Kia_timers())
{
    QThread::currentThread()->setPriority(QThread::HighPriority);
//    m_run_mko = new QProcess();
//    m_run_mko->start("bash", QStringList() << "-c" << "\"\"source ../kia_console/Kia_resource/autostarttmk.sh\"\"");
//    m_run_mko->waitForStarted();
    std::this_thread::sleep_for(1000ms);
    start_tcp_server(nPort);
    set_kia_settings();
    start_kia_gui();


}

void WorkWithMain::set_kia_settings()
{
    kia_init();
    std::cout << "kia_init" << std::endl;
    m_kia_settings->m_data_for_db->experiment_id = helpers::currentDateTime();

    m_kia_protocol.reset(new Kia_protocol(m_kia_settings));
    m_kia_protocol->create_dir_for_protocols();


    m_kia_db.reset(new Kia_db());
    m_kia_db->set_type_bokz_and_type_bi(m_kia_settings->m_type_bokz, m_kia_settings->m_type_bi);
    m_kia_db->connect_to_db();
    m_kia_settings->m_data_for_db->true_host = m_kia_db->get_mac_address();
    m_kia_settings->m_data_for_db->m_extype_id = "stand";
    m_kia_settings->m_data_for_db->m_description = "Тестовое испытание";
    m_kia_db->start_experiment(m_kia_settings->m_data_for_db->m_extype_id, m_kia_settings->m_data_for_db->m_description,
                               m_kia_settings->m_data_for_db->experiment_id, m_kia_settings->m_data_for_db->true_host);


    //m_kia_matrox.reset(new Kia_matrox());

    m_kia_mpi.reset(new Kia_mpi());

    connect(m_kia_mpi.get(), &Kia_mpi::end_exchange, this, [this](quint16 num_bokz)
    {
        m_bokz[num_bokz]->continue_action();
    });

    connect(m_kia_mpi.get(), SIGNAL(changed_lpi()), this, SLOT(send_data_from_mpi_current_lpi_to_table_settings()));

    init_db();

    init_bi();

    m_kia_ftdi.reset(new Kia_ftdi(m_kia_settings));

    connect(m_kia_ftdi.get(), &Kia_ftdi::end_read_frame, this, [this](quint16 num_bokz)
    {
        m_bokz[num_bokz]->continue_action();
    });

//    connect(m_kia_matrox.get(), &Kia_matrox::end_read_frame, this, [this](quint16 num_bokz)
//    {
//        m_bokz[num_bokz]->continue_action();
//    });

    init_bokz();

    create_func_to_read();
}

void WorkWithMain::close_db_connection()
{

    m_kia_db->end_experiment(m_kia_settings->m_data_for_db->experiment_id, m_kia_settings->m_data_for_db->true_host);
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

    //m_process->terminate();
    cout <<"Destructor WorkWithMain"<<endl;
    delete_all_threads();
    std::cout << "delete all_threads" << std::endl;
    close_db_connection();
    std::cout << "close db connection" << std::endl;
    m_kia_protocol->close_dir_for_protocols();
    std::cout << "close dir for protocols" << std::endl;
    //m_run_mko->terminate();
}


void WorkWithMain::delete_all_threads()
{
    for (uint16_t cycl_thr = 0; cycl_thr < m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread.size(); ++cycl_thr)
    {
        if (m_bokz[cycl_thr]->m_is_used_bokz == CS_IS_ON)
        {
            if(m_kia_settings->m_flags_for_thread->m_stop_cyclogram[cycl_thr])
            {
                m_kia_settings->m_flags_for_thread->m_stop_cyclogram[cycl_thr] = false;
                std::cout << "stop full" << std::endl;
            }
        }
    }
    if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
    {
        m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch = false;
    }
    std::cout << "stop thread cyclogram and command" << std::endl;
    for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
    {
        m_kia_timers->m_kia_synch_timer[ind_bi]->stop_timer();
        m_kia_timers->m_kia_bi[ind_bi]->stop_1s_mark();
        m_kia_timers->m_timer[ind_bi]->closeTimerThread();
    }
    std::cout << "stop timers" << std::endl;
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
        if (m_kia_timers->m_kia_bi.size() != 0 && m_kia_timers->m_kia_bi[ind_bi])
        {
            connect(m_kia_timers->m_kia_bi[ind_bi].get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
            connect(m_kia_timers->m_kia_synch_timer[ind_bi].get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
        }
    }
    connect(m_kia_protocol.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    connect(m_kia_db.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));
    connect(m_kia_mpi.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));

    for (auto bokz : m_bokz)
        connect(bokz.get(), SIGNAL(send_to_client(quint16, QStringList)), this, SLOT(slot_send_to_client(quint16, QStringList)));

    send_kia_initial_settings();
    m_kia_timers->m_kia_bi[0]->create_bi_telemetry_list();


    send_mpi_list_command();
    send_mpi_list_other_command();

    send_cyclogram_power_list();
    send_cyclogams_ai_list();
    send_cyclogams_ri_list();
    send_cyclogams_list();
    send_cyclograms_do();
    send_cyclograms_power_do();

    send_pn_list_command();

    send_type_frame();
    send_type_frame_recieve();

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

void WorkWithMain::create_func_to_read()
{
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_command)
    {
        if (std::get<CYCL_NAME>(el) != "separator")
        {
            auto func = [this, el](QStringList data_from_client)
            {
                auto start_exchange = [el](uint16_t num_bokz, uint16_t parametr)
                {
                    std::get<CYCL_FUNC>(el)(num_bokz, parametr);
                };
                check_used_bokz(IS_MPI_COMMAND, start_exchange);
            };
            m_func_to_read[std::get<CYCL_TYPE_TO_SEND>(el)] = func;
        }
    }

    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_mpi_other_command)
    {
        if (std::get<CYCL_NAME>(el) != "separator")
        {
            auto func = [this, el](QStringList data_from_client)
            {
                auto start_exchange = [el](uint16_t num_bokz, uint16_t parametr)
                {
                    std::get<CYCL_FUNC>(el)(num_bokz, parametr);
                };
                check_used_bokz(IS_MPI_COMMAND, start_exchange);
            };
            m_func_to_read[std::get<CYCL_TYPE_TO_SEND>(el)] = func;
        }
    }

    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_state_work)
    {
        if (std::get<CYCL_NAME>(el) != "separator")
        {
            auto func = [this, el](QStringList data_from_client)
            {
                auto start_exchange = [el](uint16_t num_bokz, uint16_t parametr)
                {
                    std::get<CYCL_FUNC>(el)(num_bokz, parametr);
                };
                check_used_bokz(IS_CYCLOGRAM, start_exchange);
            };
            m_func_to_read[std::get<CYCL_TYPE_TO_SEND>(el)] = func;
        }
    }

    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ai)
    {
        if (std::get<CYCL_NAME>(el) != "separator")
        {
            auto func = [this, el](QStringList data_from_client)
            {
                auto start_exchange = [el](uint16_t num_bokz, uint16_t parametr)
                {
                    std::get<CYCL_FUNC>(el)(num_bokz, parametr);
                };
                check_used_bokz(IS_CYCLOGRAM, start_exchange);
            };
            m_func_to_read[std::get<CYCL_TYPE_TO_SEND>(el)] = func;
        }
    }

    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_ri)
    {
        if (std::get<CYCL_NAME>(el) != "separator")
        {
            auto func = [this, el](QStringList data_from_client)
            {
                auto start_exchange = [el](uint16_t num_bokz, uint16_t parametr)
                {
                    std::get<CYCL_FUNC>(el)(num_bokz, parametr);
                };
                check_used_bokz(IS_CYCLOGRAM, start_exchange);
            };
            m_func_to_read[std::get<CYCL_TYPE_TO_SEND>(el)] = func;
        }
    }

    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_power)
    {
        if (std::get<CYCL_NAME>(el) != "separator")
        {
            auto func = [this, el](QStringList data_from_client)
            {
                auto start_exchange = [el](uint16_t num_bokz, uint16_t parametr)
                {
                    std::get<CYCL_FUNC>(el)(num_bokz, parametr);
                };
                check_used_bokz(IS_CYCLOGRAM, start_exchange);
            };
            m_func_to_read[std::get<CYCL_TYPE_TO_SEND>(el)] = func;
        }
    }

    auto func_power_on = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
            {
                if (data_from_client[0].toInt() < BI_ALL_OFF)
                    m_bokz[num_bokz]->m_kia_data->m_data_bi->m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                                                                                        data_from_client[0].toInt());
            }
        }
    };
    m_func_to_read[POWER_ON] = func_power_on;

    auto func_power_off = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
            {
                if (data_from_client[0].toInt() < BI_ALL_OFF)
                    m_bokz[num_bokz]->m_kia_data->m_data_bi->m_is_powered = m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_power_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                                                                                         data_from_client[0].toInt());
            }
        }
    };
    m_func_to_read[POWER_OFF] = func_power_off;

    auto func_on_1s = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
            {
                if (data_from_client[0].toInt() < BI_ALL_OFF)
                    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_1s_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                             data_from_client[0].toInt());
            }
        }
    };
    m_func_to_read[ON_1S] = func_on_1s;

    auto func_off_1s = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
            {
                if (data_from_client[0].toInt() < BI_ALL_OFF)
                    m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_1s_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel,
                                                                                                              data_from_client[0].toInt());
            }
        }
    };
    m_func_to_read[OFF_1S] = func_off_1s;

    auto func_cycl_ai = [this](QStringList data_from_client)
    {
        auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
        {
            m_kia_cyclogram->cyclogram_ai(num_bokz, parametr);
        };
        check_used_bokz(IS_CYCLOGRAM, start_exchange);
    };
    m_func_to_read[CYCLOGRAM_OFFLINE_TEST] = func_cycl_ai;

    auto func_do_full_frames = [this](QStringList data_from_client)
    {
        auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
        {
            m_bokz[num_bokz]->do_frames(m_kia_settings->m_frame_settings.m_type_frame_recieve, Bokz::FULL_FRAME, parametr);
        };
        check_used_bokz(IS_MPI_COMMAND, start_exchange);
    };
    m_func_to_read[DO_FULL_FRAME] = func_do_full_frames;

    auto func_do_bin_frames = [this](QStringList data_from_client)
    {
        auto start_exchange = [this](uint16_t num_bokz, uint16_t parametr)
        {
            m_bokz[num_bokz]->do_frames(m_kia_settings->m_frame_settings.m_type_frame_recieve, Bokz::BIN_FRAME, parametr);
        };
        check_used_bokz(IS_MPI_COMMAND, start_exchange);
    };
    m_func_to_read[DO_BIN_FRAME] = func_do_bin_frames;

    auto func_set_stop = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
            {
                if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    //                    std::cout << "wait continue" << std::endl;
                    //                    while(m_bokz[num_bokz]->m_kia_data->m_data_bokz->m_stop_do_command)
                    //                    {
                    //                        std::this_thread::yield();
                    //                    }
                    //                    std::cout << "set stop do cyclogram" << std::endl;
                    //                    m_bokz[num_bokz]->m_kia_data->m_data_bokz->m_stop_do_cyclogram = true;
                    std::cout << "stop wait continue" << std::endl;
                    m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] = false;
                    //m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[num_bokz].get();
                    std::cout << "full stop" << std::endl;
                }
                //                if (m_kia_settings->m_flags_for_thread->m_stop_command[num_bokz])
                //                {
                //                    m_bokz[num_bokz]->continue_exchange();
                //                    m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] = false;
                //                    m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[num_bokz].get();
                //                }
            }
        }
        if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch)
        {
            m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch = false;
            m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch_thread.get();
        }
    };
    m_func_to_read[CYCLOGRAM_STOP] = func_set_stop;

    auto func_cycl_def_address = [this](QStringList data_from_client)
    {
        m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch = true;
        m_kia_settings->m_flags_for_thread->m_stop_cyclogram_for_one_launch_thread = std::async([this]()
        {
            m_kia_cyclogram->cyclogram_define_address();
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
    };
    m_func_to_read[CYCLOGRAM_DEFINE_ADDRESS] = func_cycl_def_address;

    auto func_set_used_bokz = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            m_bokz[num_bokz]->m_is_used_bokz = data_from_client[num_bokz].toInt();
        }
    };
    m_func_to_read[SET_USED_BOKZ] = func_set_used_bokz;

    auto func_set_used_address = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_address = data_from_client[num_bokz].toInt();
        }
    };
    m_func_to_read[SET_USED_ADDRESS] = func_set_used_address;

    auto func_set_td = [this](QStringList data_from_client)
    {
        for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
        {
            for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
            {
                m_kia_timers->m_kia_bi[ind_bi]->m_kia_data->m_data_bi->m_term_group[num_bokz] = data_from_client[num_bokz].toInt();
            }

        }
    };
    m_func_to_read[SET_TD] = func_set_td;

    auto func_set_num_mpi = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_mpi_index = data_from_client[num_bokz].toInt();
        }
    };
    m_func_to_read[SET_NUM_MPI] = func_set_num_mpi;

    auto func_set_bshv = [this](QStringList data_from_client)
    {
        m_kia_settings->m_data_for_db->bshv[data_from_client[0].toInt()] = data_from_client[1].toInt();

    };
    m_func_to_read[SET_BSHV] = func_set_bshv;

    auto func_set_current_lpi = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_lpi = data_from_client[num_bokz].toInt();
        }
    };
    m_func_to_read[SET_CURRENT_LPI] = func_set_current_lpi;

    auto func_set_used_mpi_in_cycl = [this](QStringList data_from_client)
    {
        for (uint16_t num_mpi_command = 0; num_mpi_command < data_from_client.size(); ++num_mpi_command)
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_mpi_command_in_cyclogram[num_mpi_command] = data_from_client[num_mpi_command].toInt();
    };
    m_func_to_read[SET_USED_MPI_COMMAND_IN_CYCLOGRAM] = func_set_used_mpi_in_cycl;

    auto func_set_cycl_set_if_do_a_lot = [this](QStringList data_from_client)
    {
        for (uint16_t num_param = 0; num_param < data_from_client.size() - 1; ++num_param)
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_param_for_run_a_lot[data_from_client[0].toInt()][num_param] = data_from_client[num_param + 1].toInt();
    };
    m_func_to_read[SET_CYCLOGRAM_SETTINGS_IF_DO_A_LOT] = func_set_cycl_set_if_do_a_lot;

    auto func_set_exc_freq = [this](QStringList data_from_client)
    {
        m_kia_settings->m_freq_bokz = data_from_client[0].toInt();
        for (auto timer : m_kia_timers->m_timer)
            timer->change_divider(m_kia_settings->m_freq_bokz);
    };
    m_func_to_read[SET_EXC_FREQ] = func_set_exc_freq;

    auto func_set_relay_pulse = [this](QStringList data_from_client)
    {
        for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
        {
            m_kia_timers->m_kia_bi[ind_bi]->set_relay_command(data_from_client[TRC_PULSE].toUInt());
        }
    };
    m_func_to_read[SET_RELAY_PULSE] = func_set_relay_pulse;

    auto func_set_relay_pulse_time = [this](QStringList data_from_client)
    {
        for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
        {
            m_kia_timers->m_kia_bi[ind_bi]->set_relay_command_pulse_time(data_from_client[TRC_TIME_PULSE].toUInt());
        }
    };
    m_func_to_read[SET_RELAY_PULSE_TIME] = func_set_relay_pulse_time;

    auto func_set_relay_polar = [this](QStringList data_from_client)
    {
        for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
        {
            m_kia_timers->m_kia_bi[ind_bi]->set_relay_polarity(data_from_client[TRC_POLAR].toUInt());
        }
    };
    m_func_to_read[SET_RELAY_POLAR] = func_set_relay_polar;

    auto func_set_mark_period = [this](QStringList data_from_client)
    {
        for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
        {
            m_kia_timers->m_kia_bi[ind_bi]->set_sec_mark_pulse_time(data_from_client[0].toInt());
        }
    };
    m_func_to_read[SET_SEC_MARK_PERIOD] = func_set_mark_period;

    auto func_set_num_bi = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < data_from_client.size(); ++num_bokz)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi = data_from_client[num_bokz].toInt();
        }
    };
    m_func_to_read[SET_NUM_BI] = func_set_num_bi;

    auto func_set_im_on = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_imitator_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
        }
    };
    m_func_to_read[IMITATOR_ON] = func_set_im_on;

    auto func_set_im_off = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_imitator_bi(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
        }
    };
    m_func_to_read[IMITATOR_OFF] = func_set_im_off;

    auto func_set_contr_comm_on = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->on_contol_command(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
        }
    };
    m_func_to_read[CONROL_COMMAND_ON] = func_set_contr_comm_on;

    auto func_set_contr_comm_off = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
                m_kia_timers->m_kia_bi[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->off_contol_command(num_bokz, m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel);
        }
    };
    m_func_to_read[CONROL_COMMAND_OFF] = func_set_contr_comm_off;

    auto func_set_used_ch = [this](QStringList data_from_client)
    {
        for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_num_used_channel = data_from_client[num_bokz].toInt();
        }
    };
    m_func_to_read[SET_USED_CHANNEL] = func_set_used_ch;

    auto func_set_upn = [this](QStringList data_from_client)
    {
        auto type_upn_command = data_from_client[0].toInt();
        data_from_client.pop_front();
        auto start_exchange = [this, type_upn_command, data_from_client](uint16_t num_bokz, uint16_t parametr)
        {
            m_bokz[num_bokz]->upn(type_upn_command, data_from_client, parametr);
        };
        check_used_bokz(IS_MPI_COMMAND, start_exchange);
    };
    m_func_to_read[SET_UPN] = func_set_upn;

    auto func_get_chpn = [this](QStringList data_from_client)
    {
        auto start_exchange = [this, data_from_client](uint16_t num_bokz, uint16_t parametr)
        {
            m_bokz[num_bokz]->chpn(data_from_client, parametr);
        };
        check_used_bokz(IS_MPI_COMMAND, start_exchange);
    };
    m_func_to_read[GET_CHPN] = func_get_chpn;

    auto func_set_ai_skip_or_stop = [this](QStringList data_from_client)
    {
        m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_skip_fails_for_continue = data_from_client[0].toInt();
    };
    m_func_to_read[SET_AI_SKIP_OR_STOP] = func_set_ai_skip_or_stop;

    auto func_debugging_command = [this](QStringList data_from_client)
    {
        bool ok;
        uint16_t is_dec_or_hex = 16;
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
                                                                         data_from_client[CS_SUB_ADDRESS].toInt(), data_from_client[CS_WORD_DATA].toInt(),
                                                                         data_from_client[CS_STRUCT_ID].toStdString(), data_from_client[CS_STRUCT_ID_DESCK].toStdString());
    };
    m_func_to_read[DEBUGGING_COMMAND] = func_debugging_command;

    auto func_set_is_off_power_in_tp = [this](QStringList data_from_client)
    {
        m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_off_power_for_tp = data_from_client[0].toInt();
    };
    m_func_to_read[SET_IS_OFF_POWER_IN_TP] = func_set_is_off_power_in_tp;

    auto func_set_do_cyclogram_in_tp = [this](QStringList data_from_client)
    {
        for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size(); ++num_cyclogram)
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_tp[num_cyclogram] = data_from_client[num_cyclogram].toInt();
    };
    m_func_to_read[SET_DO_CYCLOGRAM_IN_TP] = func_set_do_cyclogram_in_tp;

    auto func_set_count_to_do_cyclogram_in_tp = [this](QStringList data_from_client)
    {
        for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size(); ++num_cyclogram)
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_count_to_do_cyclogram_in_tp[num_cyclogram] = data_from_client[num_cyclogram].toInt();
    };
    m_func_to_read[SET_COUNT_TO_DO_CYCLOGRAM_IN_TP] = func_set_count_to_do_cyclogram_in_tp;

    auto func_set_do_cyclogram_in_ai = [this](QStringList data_from_client)
    {
        for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size(); ++num_cyclogram)
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_ai[num_cyclogram] = data_from_client[num_cyclogram].toInt();
    };
    m_func_to_read[SET_DO_CYCLOGRAM_IN_AI] = func_set_do_cyclogram_in_ai;

    auto func_set_is_do_cyclogram_in_do = [this](QStringList data_from_client)
    {
        for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size() - 1; ++num_cyclogram)
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_cyclogram_in_do[data_from_client[0].toInt()][num_cyclogram] =
                    data_from_client[num_cyclogram + 1].toInt();
    };
    m_func_to_read[SET_DO_CYCLOGRAM_IN_DO] = func_set_is_do_cyclogram_in_do;

    auto func_set_pause_do_cyclogram_in_do = [this](QStringList data_from_client)
    {
        for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size() - 1; ++num_cyclogram)
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_sleep_to_command_in_do_cyclogram[data_from_client[0].toInt()][num_cyclogram] =
                    data_from_client[num_cyclogram + 1].toInt();
    };
    m_func_to_read[SET_PAUSE_DO_CYCLOGRAM_IN_DO] = func_set_pause_do_cyclogram_in_do;

    auto func_set_type_frame_recive = [this](QStringList data_from_client)
    {
        m_kia_settings->m_frame_settings.m_type_frame_recieve =
                data_from_client[0].toInt();
    };
    m_func_to_read[SET_TYPE_FRAME_RECIEVE] = func_set_type_frame_recive;

    auto func_set_type_frame = [this](QStringList data_from_client)
    {
        m_kia_settings->m_frame_settings.m_type_frame = data_from_client[0].toInt();

    };
    m_func_to_read[SET_TYPE_FRAME] = func_set_type_frame;

    auto func_set_do_cyclogram_power_in_do = [this](QStringList data_from_client)
    {
        for (uint16_t num_cyclogram = 0; num_cyclogram < data_from_client.size() - 1; ++num_cyclogram)
        {
            m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_do_in_power_cycl[data_from_client[0].toInt()][num_cyclogram] = data_from_client[num_cyclogram + 1].toInt();
        }
    };
    m_func_to_read[SET_DO_CYCLOGRAM_POWER_IN_DO] = func_set_do_cyclogram_power_in_do;
}

void WorkWithMain::kia_init()
{
    m_kia_load_initial_settings.reset(new Kia_load_initial_settings(m_kia_settings));

    m_kia_settings->m_timer_interval = 1000;

    m_kia_settings->m_frame_settings.m_type_frame_recieve = Bokz::FTDI_USB;

    m_kia_settings->m_frame_settings.m_type_frame = Bokz::FULL_FRAME;

    Kia_port m_kia_port(m_kia_settings);
    m_kia_port.check_used_bi_ports(m_kia_settings->m_type_bi);
    m_kia_settings->m_data_for_db->bshv.resize(m_kia_settings->m_data_for_bi->m_count_bi);
    m_kia_settings->m_count_bokz = m_kia_settings->m_data_for_bi->m_count_bi * m_kia_settings->m_data_for_bi->m_count_channel_bi[m_kia_settings->m_type_bi];

    m_kia_settings->m_flags_for_thread->m_stop_cyclogram.resize(m_kia_settings->m_count_bokz);
    m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread.resize(m_kia_settings->m_count_bokz);

    m_kia_settings->m_flags_for_thread->m_stop_command.resize(m_kia_settings->m_count_bokz);
    m_kia_settings->m_flags_for_thread->m_stop_command_thread.resize(m_kia_settings->m_count_bokz);

    m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info.resize(m_kia_settings->m_count_bokz);

    qRegisterMetaType<Kia_protocol_parametrs>();
    qRegisterMetaType<Kia_frame_parametrs>();
    qRegisterMetaType<Kia_mko_struct>();
    qRegisterMetaType<Kia_data>();
    qRegisterMetaType<DATA>();
}

void WorkWithMain::init_db()
{
    for (uint16_t num_conn = 0; num_conn < constants::max_count_same_connection; ++num_conn)
    {
        m_kia_bi_db[num_conn].reset(new Kia_db());
        m_kia_bi_db[num_conn]->set_type_bokz_and_type_bi(m_kia_settings->m_type_bokz, m_kia_settings->m_type_bi);
        m_kia_bi_db[num_conn]->connect_to_db();
        m_kia_bi_db[num_conn]->start_commit();

        m_kia_bokz_db[num_conn].reset(new Kia_db());
        m_kia_bokz_db[num_conn]->set_type_bokz_and_type_bi(m_kia_settings->m_type_bokz, m_kia_settings->m_type_bi);
        m_kia_bokz_db[num_conn]->connect_to_db();
        m_kia_bokz_db[num_conn]->start_commit();
    }
}

void WorkWithMain::init_bi()
{
    for (uint16_t ind_bi = 0; ind_bi < m_kia_settings->m_data_for_bi->m_count_bi; ind_bi++)
    {
        m_kia_timers->m_timer.push_back(std::make_shared<Timer>(ind_bi, m_kia_settings->m_timer_interval, m_kia_settings->m_freq_bokz, m_kia_settings));
        switch(m_kia_settings->m_type_bi)
        {
        case TYPE_BI_BKPIK:
            m_kia_timers->m_kia_bi.push_back(std::make_shared<Kia_bkpik>(ind_bi, m_kia_settings));
            break;
        case TYPE_BI_BIU:
            m_kia_timers->m_kia_bi.push_back(std::make_shared<Kia_biu>(ind_bi, m_kia_settings));
            break;
        }

        m_kia_bi_db[TYPE_RAW]->add_device_to_experiment(m_kia_bi_db[TYPE_RAW]->get_type_bi_string(m_kia_settings->m_type_bi), ind_bi,
                                                        m_kia_settings->m_data_for_db->experiment_id,
                                                        m_kia_settings->m_data_for_db->true_host);

        m_parse_db_bi.push_back(std::make_shared<ParseToDB>(m_kia_bi_db, m_kia_timers->m_kia_bi[ind_bi]->m_kia_data, m_kia_settings));
        m_parse_db_bi[ind_bi]->create_list_func_to_send_bi();

        connect(m_kia_timers->m_kia_bi[ind_bi].get(), SIGNAL(send_data_to_db_bi(qint16, quint16)), m_parse_db_bi[ind_bi].get(), SLOT(send_data_to_db_for_bi(qint16, quint16)));
        connect(m_kia_timers->m_kia_bi[ind_bi].get(), SIGNAL(send_to_save_protocol(Kia_protocol_parametrs)), m_kia_protocol.get(), SLOT(preset_before_save_and_out(Kia_protocol_parametrs)));

        if (m_kia_timers->m_kia_bi.size() != 0 && m_kia_timers->m_kia_bi[ind_bi])
            m_kia_timers->m_kia_synch_timer.push_back(std::make_shared<Kia_synch_timer>(ind_bi, m_kia_timers->m_timer[ind_bi], m_kia_timers->m_kia_bi[ind_bi], m_kia_settings));
        m_kia_timers->m_timer[ind_bi]->start();
    }
}

void WorkWithMain::init_bokz()
{
    uint16_t shift_interval = 0;
    for (uint16_t num_bokz = 0; num_bokz < m_kia_settings->m_count_bokz; ++num_bokz)
    {
        switch(m_kia_settings->m_type_bokz)
        {
        case TYPE_BOKZ_BOKZM60:
            m_bokz.push_back(std::make_shared<BokzM60>(num_bokz, m_kia_settings));
            m_kia_cyclogram.reset(new Kia_cyclogram_bokzm60(m_kia_timers, m_bokz, m_kia_settings));
            break;
        case TYPE_BOKZ_BOKZMF:
            m_bokz.push_back(std::make_shared<Bokzmf>(num_bokz, m_kia_settings));
            m_kia_timers->m_timer[m_bokz[num_bokz]->m_kia_data->m_data_bi->m_num_used_bi]->change_interval(shift_interval);
            m_kia_cyclogram.reset(new Kia_cyclogram_bokzmf(m_kia_timers, m_bokz, m_kia_settings));
            break;
        }
        m_kia_bokz_db[TYPE_RAW]->add_device_to_experiment(m_kia_bokz_db[TYPE_RAW]->get_type_bokz_string(m_kia_settings->m_type_bokz), num_bokz,
                                                          m_kia_settings->m_data_for_db->experiment_id,
                                                          m_kia_settings->m_data_for_db->true_host);

        m_parse_db_bokz.push_back(std::make_shared<ParseToDB>(m_kia_bokz_db, m_bokz[num_bokz]->m_kia_data, m_kia_settings));
        m_parse_db_bokz[num_bokz]->create_list_func_to_send_bokz();

        connect(m_bokz[num_bokz].get(), SIGNAL(send_data_to_db(qint16, QString, quint16, qint32, DATA)), m_parse_db_bokz[num_bokz].get(), SLOT(send_data_to_db_slot(qint16, QString, quint16, qint32, DATA)));

        connect(m_bokz[num_bokz].get(), SIGNAL(send_data_to_db_bokz(qint16, quint16, qint32, Kia_mko_struct)), m_parse_db_bokz[num_bokz].get(), SLOT(send_data_to_db_for_bokz(qint16, quint16, qint32, Kia_mko_struct)));
        connect(m_bokz[num_bokz].get(), SIGNAL(send_data_to_db_for_frames(quint16, qint32)), m_parse_db_bokz[num_bokz].get(), SLOT(send_data_to_db_for_frames(quint16, qint32)));
        connect(m_bokz[num_bokz].get(), SIGNAL(send_data_to_db_for_mpi(quint16, qint32)), m_parse_db_bokz[num_bokz].get(), SLOT(send_data_to_db_for_mpi(quint16, qint32)));

        connect(m_bokz[num_bokz].get(), SIGNAL(send_to_save_protocol(Kia_protocol_parametrs)), m_kia_protocol.get(), SLOT(preset_before_save_and_out(Kia_protocol_parametrs)));
        connect(m_bokz[num_bokz].get(), SIGNAL(save_to_frames_protocols(const Kia_frame_parametrs&)), m_kia_protocol.get(), SLOT(save_to_frames_protocols(const Kia_frame_parametrs&)));

        connect(m_bokz[num_bokz].get(), SIGNAL(do_exchange(Kia_data*)), m_kia_mpi.get(), SLOT(do_exchange(Kia_data*)));

        connect(m_bokz[num_bokz].get(), &Bokz::do_frame, this, [this](Kia_frame_parametrs* kia_frame_parametrs)
        {
            m_kia_ftdi->do_read_frame(kia_frame_parametrs);
            //m_kia_matrox->do_read_frame(kia_frame_parametrs);
        });


    }
}

void WorkWithMain::start_kia_gui()
{
    QStringList arguments;
    m_process = new QProcess();
    m_process->start("bash", QStringList() << "-c" << "\"\"source ../../kia_gui_run.sh\"\"");
    m_process->waitForStarted();
}

bool WorkWithMain::check_used_bokz(uint16_t type_command, std::function<void (uint16_t, uint16_t)> start_exchange, uint16_t parametr)
{
    m_kia_settings->m_data_to_protocols->m_is_protocol_used[SP_DO_AI] = KiaS_FAIL;

    for (auto el : m_kia_bokz_db)
    {
        el->set_interval_to_send();
    }

    for (uint16_t num_bokz = 0; num_bokz < m_bokz.size(); ++num_bokz)
    {
        if (m_bokz[num_bokz]->m_is_used_bokz == CS_IS_ON)
        {
            m_bokz[num_bokz]->m_kia_data->m_data_mpi->m_status_exchange = KiaS_FAIL;
            m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info[num_bokz] = false;
            if (type_command == IS_CYCLOGRAM)
            {

                if (m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz])
                {
                    m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] = false;
                    m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info[num_bokz] = false;
                    //m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[num_bokz].get();
                }
                m_kia_settings->m_flags_for_thread->m_stop_cyclogram[num_bokz] = true;
                m_kia_settings->m_data_to_protocols->m_stop_spam_in_system_info[num_bokz] = true;
                m_kia_settings->m_flags_for_thread->m_stop_cyclogram_thread[num_bokz] = std::async([this, num_bokz, start_exchange, parametr]()
                {
                    start_exchange(num_bokz, parametr);
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

void WorkWithMain::send_bi_telemetry_list()
{
}

void WorkWithMain::send_kia_initial_settings()
{
    QStringList settings;
    settings.push_back(QString::number(m_kia_settings->m_data_for_bi->m_count_bi));
    emit send_to_client(SET_KIA_GUI_SETTINGS, settings);
}

void WorkWithMain::send_cyclogram_power_list()
{
    QStringList cyclograms;
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_cyclograms_power)
    {
        cyclograms.push_back(std::get<CYCL_NAME>(el));
        cyclograms.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
    }
    emit send_to_client(SEND_CYCLOGRAMS_POWER, cyclograms);
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

void WorkWithMain::send_pn_list_command()
{
    QStringList command;
    for (auto el : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_commands_to_pn)
    {
        command.push_back(std::get<TP_NAME>(el));
        command.push_back(std::get<TP_KEY>(el));
        command.push_back(QString::number(std::get<TP_TYPE_VIEW>(el)));
        command.push_back(QString::number(std::get<TP_TYPE_COMMAND>(el)));
    }
    emit send_to_client(SEND_PN_COMMAND, command);
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

void WorkWithMain::send_cyclograms_power_do()
{
    for (auto cycl : m_kia_cyclogram->m_kia_data_cyclogram->m_wait_and_param_for_cyclogram->m_command_do_in_cycl_power)
    {
        QStringList commands;
        for (auto el : cycl)
        {
            commands.push_back(std::get<CYCL_NAME>(el));
            commands.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
        }
        if (commands.size() != 0)
            emit send_to_client(SEND_CYCLOGRAMS_POWER_DO, commands);
    }
}

void WorkWithMain::send_type_frame()
{
    QStringList type_frame;
    for (auto el : m_bokz[0]->m_kia_data->m_data_bokz->m_func_type_frames)
    {
        type_frame.push_back(std::get<CYCL_NAME>(el));
        type_frame.push_back(QString::number(std::get<CYCL_TYPE_TO_SEND>(el)));
    }
    emit send_to_client(SEND_TYPE_FRAME, type_frame);
}

void WorkWithMain::send_type_frame_recieve()
{
    QStringList type_frame_recieve;
    for (auto el : m_bokz[0]->m_kia_data->m_data_bokz->m_func_type_frame_recieve)
    {
        type_frame_recieve.push_back(std::get<CYCL_NAME>(el));
    }
    emit send_to_client(SEND_TYPE_FRAME_RECIEVE, type_frame_recieve);
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
        QStringList data_from_client;
        qint16 num;
        qint16 type_bokz;
        qint16 type_bi;
        in >> data_from_client >> type_bokz >> type_bi >> num;
        m_kia_settings->m_type_bokz = type_bokz;
        m_kia_settings->m_type_bi = type_bi;

        for(auto const& imap: m_func_to_read)
        {
            if (num == imap.first)
                m_func_to_read[num](data_from_client);
        }

        m_nNextBlockSize = 0;
    }
}
