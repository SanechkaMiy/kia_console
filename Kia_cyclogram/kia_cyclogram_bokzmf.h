#ifndef KIA_CYCLOGRAM_BOKZMF_H
#define KIA_CYCLOGRAM_BOKZMF_H
#include "Kia_bokz/bokz.h"
#include "kia_protocol.h"
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include "kia_cyclogram.h"
#include <utility>

class Kia_cyclogram_bokzmf : public Kia_cyclogram
{
public:
    Kia_cyclogram_bokzmf(std::shared_ptr<Kia_timers> kia_timers, std::vector<std::shared_ptr<Bokz> > bokz,
                         shared_ptr<Kia_protocol> kia_protocol, std::shared_ptr<Kia_settings> kia_settings);

    uint16_t cyclogram_state_on(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_state_off(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_no(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_to(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_ai(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_loc(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    void cyclogram_define_address(uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_operation(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_operation_no(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_operation_to(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_operation_loc(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_1s_mark(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_check_address(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_test_mko(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_test_synchro(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_technical_run(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_zkr(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_full_frames(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
private:
    uint16_t start_no(uint16_t &num_bokz) override;
    uint16_t start_to(uint16_t &num_bokz) override;
    uint16_t start_loc(uint16_t &num_bokz, uint16_t count_do_loc = 0) override;
    uint16_t start_regular_cyclogram(uint16_t &num_bokz, uint16_t count_do_cyclogram = 0) override;

    void wait_some_time(uint16_t& num_bokz, const uint16_t& wait_s) override;
    void wait_for_bi_takt(uint16_t& num_bokz) override;
    void wait_some_time_for_one_launch(const uint16_t& wait_s) override;
    void save_to_protocol(uint16_t& num_bokz, QString str_to_protocol,  uint16_t parametr = EP_DOALL) override;
    void preset_before_exchange(uint16_t num_bokz);
    void create_mpi_commands();
    void create_list_cyclograms_for_tp();
    void check_work_lpi(uint16_t& num_bokz, const uint16_t& lpi);
    std::shared_ptr<Kia_timers> m_kia_timers;
    std::vector<std::shared_ptr<Bokz>> m_bokz;
    shared_ptr<Kia_protocol> m_kia_protocol;
    std::shared_ptr<Kia_settings> m_kia_settings;
};

#endif // KIA_CYCLOGRAM_BOKZMF_H
