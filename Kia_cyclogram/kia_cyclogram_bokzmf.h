#ifndef KIA_CYCLOGRAM_BOKZMF_H
#define KIA_CYCLOGRAM_BOKZMF_H
#include "Kia_bokz/bokzmf.h"
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include "kia_cyclogram.h"
#include <utility>
class Kia_cyclogram_bokzmf : public Kia_cyclogram
{
public:
    enum STATE_CYCLOGRAM_ORDER
    {
        SCO_OO = 0,
        SCO_LOC = 1,
    };
    enum COMMAND_IN_OO
    {
        CIO_UPN_KD = 0,
        CIO_OO = 1,
        CIO_BSHV = 2,
        CIO_SKOR = 3,
        CIO_CHKD = 4
    };
    enum POWER_CYCLOGRAM_ORDER
    {
        PCO_STATE_ON = 0,
        PCO_STATE_OFF = 1,
        PCO_RESTART = 2
    };

    enum COMMAND_IN_STATE_ON
    {
        CISN_UPN = 0,
    };
    enum PARAM_IF_A_LOT
    {
        PIL_TP = 0
    };

    enum TYPE_PAUSE_IN_CYCLOGRAMS
    {
        WAIT_FOR_TAKT = 0,
        WAIT_AFTER_POWER = 1,
        WAIT_OTCLR = 2,
        WAIT_RESTART = 3,
        WAIT_LOC = 4,
        WAIT_MSHIOR_IN_OO = 5,
        WAIT_AFTER_OFF_POWER = 6,
    };

    Kia_cyclogram_bokzmf(std::shared_ptr<Kia_timers> kia_timers, std::vector<std::shared_ptr<Bokz> > bokz, std::shared_ptr<Kia_settings> kia_settings);

    uint16_t cyclogram_state_on(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_state_off(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t do_restart(uint16_t num_bokz, uint16_t parametr = EP_DOALL) override;

    uint16_t cyclogram_oo(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_no(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_to(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_ai(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_loc(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    void cyclogram_define_address(uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_operation(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) override;
    uint16_t cyclogram_operation_oo(uint16_t &num_bokz, uint16_t count_do_cyclogram, uint16_t parametr = EP_DOALL) override;
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
    void set_cyclogram_settings();
    uint16_t start_state_on(uint16_t num_bokz, uint16_t parametr = EP_DOALL);
    uint16_t start_loc(uint16_t &num_bokz, uint16_t parametr = EP_DOALL, uint16_t count_do_loc = 0);
    uint16_t start_regular_cyclogram(uint16_t &num_bokz, uint16_t count_do_cyclogram = 0, uint16_t parametr = EP_DOALL) override;
    uint16_t do_oo(uint16_t &num_bokz, int64_t &begin_skor_time, uint16_t parametr = EP_DOALL);
    void wait_some_time(uint16_t& num_bokz, const uint16_t& wait_s);
    void wait_for_bi_takt(uint16_t& num_bokz);
    void wait_some_time_for_one_launch(const uint16_t& wait_s);
    void save_to_protocol(uint16_t& num_bokz, QString str_to_protocol,  uint16_t parametr = EP_DOALL) override;
    void create_list_power_cyclograms();
    void create_func_type_do_oo();
    void create_mpi_commands();
    void create_list_other_mpi_commands();
    void create_list_command_for_oo();
    void create_list_command_for_state_on();
    void create_list_cyclograms_for_state_work();
    void create_list_command_for_loc();
    void create_list_cyclograms_for_ri();
    void create_list_cyclograms_for_tp();
    void create_list_chpn();


    void check_work_lpi(uint16_t& num_bokz, const uint16_t& lpi);
    std::shared_ptr<Kia_timers> m_kia_timers;
    std::vector<std::shared_ptr<Bokz>> m_bokz;
    std::shared_ptr<Kia_settings> m_kia_settings;
    std::vector<std::function<uint16_t(uint16_t, uint16_t, uint16_t)>> m_type_do_oo;
};

#endif // KIA_CYCLOGRAM_BOKZMF_H
