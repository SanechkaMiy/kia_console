#include "bokzmr.h"

BokzMR::BokzMR(uint16_t num_bokz, std::array<std::shared_ptr<Kia_db>, constants::max_count_same_connection> kia_db, std::vector<shared_ptr<Timer> > timer, std::vector<std::shared_ptr<Kia_synch_timer> > kia_synch_timer, std::vector<shared_ptr<Kia_bi> > kia_bi, shared_ptr<Kia_mpi> kia_mpi, shared_ptr<Kia_protocol> kia_protocol, shared_ptr<Kia_matrox> kia_matrox, std::shared_ptr<Kia_settings> kia_settings, shared_ptr<Kia_ftdi> kia_ftdi)
{

}

BokzMR::~BokzMR()
{
    m_kia_mko_struct.reset(new Kia_mko_struct_bokzmr());
}

void BokzMR::set_bokz_settings()
{

}

uint16_t BokzMR::shtmi1(uint16_t parametr)
{

}

uint16_t BokzMR::shtmi2(uint16_t parametr)
{

}

uint16_t BokzMR::mshior(uint16_t parametr)
{

}

uint16_t BokzMR::dtmi_or_dtmi_loc(uint16_t parametr)
{

}

uint16_t BokzMR::smti(uint16_t parametr)
{

}

uint16_t BokzMR::vmti(uint16_t parametr)
{

}

uint16_t BokzMR::synchro(uint16_t parametr)
{

}

uint16_t BokzMR::skor(uint16_t parametr)
{

}

uint16_t BokzMR::command_no(uint16_t parametr)
{

}

uint16_t BokzMR::command_to(uint16_t parametr)
{

}

uint16_t BokzMR::command_full_exp(uint16_t parametr)
{

}

uint16_t BokzMR::command_loc(uint16_t parametr)
{

}

uint16_t BokzMR::command_otclp(uint16_t parametr)
{

}

uint16_t BokzMR::command_openkr(uint16_t parametr)
{

}

uint16_t BokzMR::command_zkr(uint16_t parametr)
{

}

uint16_t BokzMR::kvaor(uint16_t parametr)
{

}

uint16_t BokzMR::os(uint16_t parametr)
{

}

uint16_t BokzMR::vskou(uint16_t parametr)
{

}

uint16_t BokzMR::initial_state(uint16_t parametr)
{

}

uint16_t BokzMR::block_ou(uint16_t parametr)
{

}

uint16_t BokzMR::unblock_ou(uint16_t parametr)
{

}

uint16_t BokzMR::do_frames(uint16_t parametr)
{

}

uint16_t BokzMR::set_epsilon(float command, uint16_t parametr)
{

}

uint16_t BokzMR::get_epsilon(uint16_t parametr)
{

}

uint16_t BokzMR::set_focus(uint16_t parametr)
{

}

uint16_t BokzMR::get_focus(uint16_t parametr)
{

}

uint16_t BokzMR::set_texp(uint16_t command, uint16_t parametr)
{

}

uint16_t BokzMR::get_texp(uint16_t parametr)
{

}

void BokzMR::preset_before_exchange()
{

}
