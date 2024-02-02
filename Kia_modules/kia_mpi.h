#ifndef KIA_MPI_H
#define KIA_MPI_H

#include <QObject>
#include "Kia_modules/kia_help_functions.h"
#include <queue>
extern "C"
{
#include "ltmkUsb.h"
}
class Kia_mpi : public QObject
{
    Q_OBJECT
public:
    Kia_mpi();
    ~Kia_mpi();
    void init();
    void close();
    void wait_for_event();
    void send_mpi_dev();
    void send_data_from_mpi_num_mpi_to_table_settings();
    void execute_exchange(Kia_data* kia_data);
public slots:
    void do_exchange(Kia_data* kia_data);
signals:
    void send_to_client(quint16, QStringList);
    void changed_lpi();
    void end_exchange(quint16);
private:
    void reset(Kia_data* kia_data);
    array<uint16_t, constants::max_tmk_dev> m_mpi_num;
    uint16_t m_count_chip = 0;
    std::future<void> m_mpi_thread;
    std::atomic_bool m_mpi_stop{false};
    std::queue<std::pair<std::string, Kia_data*>> m_data;
    std::condition_variable m_cv;
    std::mutex m_mtx;
};

#endif // KIA_MPI_H
