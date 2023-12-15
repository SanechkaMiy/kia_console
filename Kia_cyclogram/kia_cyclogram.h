#ifndef KIA_CYCLOGRAM_H
#define KIA_CYCLOGRAM_H
#include "timer.h"
#include "kia_synch_timer.h"
#include "Kia_bokz/bokz.h"
#include "Kia_bi/kia_bi.h"
#include "kia_protocol.h"
#include "mainStruct.h"
#include "Kia_mko_struct.h"
struct Kia_timers
{
    std::vector<shared_ptr<Timer>> m_timer;
    std::vector<shared_ptr<Kia_synch_timer>> m_kia_synch_timer;
    std::vector<shared_ptr<Kia_bi>> m_kia_bi;
};

class Kia_cyclogram
{
public:
    Kia_cyclogram();
    virtual uint16_t cyclogram_state_on(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_state_off(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_no(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_to(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_ai(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_loc(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual void cyclogram_define_address(uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_operation(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_operation_no(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_operation_to(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_1s_mark(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_check_address(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_test_mko(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_test_synchro(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_technical_run(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_zkr(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual uint16_t cyclogram_full_frames(uint16_t &num_bokz, uint16_t parametr = EP_DOALL) = 0;
    virtual ~Kia_cyclogram(){};

private:
    virtual uint16_t start_no(uint16_t &num_bokz) = 0;
    virtual uint16_t start_to(uint16_t &num_bokz) = 0;
    virtual uint16_t start_loc(uint16_t &num_bokz, uint16_t count_do_loc = 0) = 0;
    virtual uint16_t start_regular_cyclogram(uint16_t &num_bokz, uint16_t count_do_cyclogram = 0) = 0;

    virtual void wait_some_time(uint16_t& num_bokz, const uint16_t& wait_s) = 0;
    virtual void wait_for_bi_takt(uint16_t& num_bokz) = 0;
    virtual void wait_some_time_for_one_launch(const uint16_t& wait_s) = 0;
    virtual void check_work_lpi(uint16_t& num_bokz, const uint16_t& lpi) = 0;
    virtual void save_to_protocol(uint16_t& num_bokz, QString str_to_protocol,  uint16_t parametr = EP_DOALL) = 0;
    std::vector<shared_ptr<Timer>> m_timer;
    std::vector<shared_ptr<Kia_synch_timer>> m_kia_synch_timer;
    std::vector<std::shared_ptr<Bokz>> m_bokz;
    std::vector<shared_ptr<Kia_bi>> m_kia_bi;
    shared_ptr<Kia_protocol> m_kia_protocol;
    std::shared_ptr<Kia_settings> m_kia_settings;
};

#endif // KIA_CYCLOGRAM_H
