#ifndef PIO_BOKZMF_H
#define PIO_BOKZMF_H
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include <math.h>
#include "Kia_pio/pio_bokz.h"
#include "Kia_modules/kia_help_functions.h"
const uint16_t max_el_in_to_word = 4;
class Pio_bokzmf : public Pio_bokz
{
public:
    Pio_bokzmf(std::shared_ptr<Kia_mko_struct> kia_mko_struct,
               std::shared_ptr<Kia_settings> kia_settings);
    void decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t& bshv) override;
    ~Pio_bokzmf();
private:
    std::shared_ptr<Kia_mko_struct> m_kia_mko_struct;
    std::shared_ptr<Kia_settings> m_kia_settings;
    void dtmi_2_3_4_5_6_7_converter(DTMIRaw_2_3_4_5_6_7_MF &dtmiRaw_2_3_4_5_6_7);
    std::array<uint16_t, max_el_in_to_word> split_data_from_word(uint16_t data);
    template < typename T >
    T swapHex(T value);
};

#endif // PIO_BOKZMF_H
