#ifndef KIA_MPI_H
#define KIA_MPI_H

#include <QObject>
#include "Kia_modules/kia_help_functions.h"
#include <queue>
extern "C"
{
#include "ltmkUsb.h"
}
struct Kia_mpi_data
{
    uint16_t m_code_word = 0;
    uint16_t m_address = 0;
    uint16_t m_word_data = 1;
    uint16_t m_sub_address = 0;
    uint16_t m_format = 0;
    uint16_t m_direction = 0;
    uint16_t m_base = 0;
    uint16_t m_lpi = 0;
    uint16_t m_nInt = 0;
    uint16_t m_wResult = 0;
    uint16_t m_answer_word;
    uint16_t m_mpi_index = 0;
    uint16_t m_sub_array_id{0};
    int32_t m_exchange_counter{0};

    std::pair<uint16_t, QString> m_status_exchange{};

    std::string send_time{};
    std::string receive_time{};

    array<uint16_t, constants::packetSize> m_data_for_exchange;
    array<uint16_t, constants::packetSize> m_data_word;
}; Q_DECLARE_METATYPE(Kia_mpi_data)

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
    void execute_exchange(Kia_mpi_data* mpi_data, uint16_t num_bokz);
public slots:
    void do_exchange(Kia_mpi_data* mpi_data, uint16_t num_bokz);
signals:
    void send_to_client(quint16, QStringList);
    void changed_lpi();
    void end_exchange(quint16);
private:
    void reset(Kia_mpi_data* mpi_data);
    array<uint16_t, constants::max_tmk_dev> m_mpi_num;
    uint16_t m_count_chip = 0;
    std::future<void> m_mpi_thread;
    std::atomic_bool m_mpi_stop{false};
    std::queue<std::tuple<std::string, Kia_mpi_data*, uint16_t>> m_data;
    std::condition_variable m_cv;
    std::mutex m_mtx;
};

#endif // KIA_MPI_H
