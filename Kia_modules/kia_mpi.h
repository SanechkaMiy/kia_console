#ifndef KIA_MPI_H
#define KIA_MPI_H

#include <QObject>
#include "Kia_modules/kia_help_functions.h"
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
    uint16_t execute_exchange(std::shared_ptr<Kia_data> kia_data);
    void send_mpi_dev();
    void send_data_from_mpi_num_mpi_to_table_settings();
signals:
    void send_to_client(quint16, QStringList);
    void changed_lpi();
private:
    void reset(std::shared_ptr<Kia_data> kia_data);
    array<uint16_t, constants::max_tmk_dev> m_mpi_num;
    uint16_t m_count_chip = 0;
};

#endif // KIA_MPI_H
