#ifndef PIO_BOKZM60_H
#define PIO_BOKZM60_H
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include <math.h>
#include "Kia_pio/pio_bokz.h"
class Pio_bokzm60 : public Pio_bokz
{
public:
    Pio_bokzm60(std::shared_ptr<Kia_mko_struct> kia_mko_struct, std::shared_ptr<Kia_settings> kia_settings);
    void decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t& bshv) override;
    ~Pio_bokzm60();
private:
    std::shared_ptr<Kia_mko_struct> m_kia_mko_struct;
    std::shared_ptr<Kia_settings> m_kia_settings;
    void dtimi_loc_converter(DTMILocRaw_2_3_4_5_6_7_8 &dtmi_loc_raw_2_3_4_5_6_7_8);
    void dtmi_2_3_4_converter(DTMIRaw_2_3_4 &dtmiRaw_2_3_4);
    void dtmi_6_7_converter(DTMIRaw_6_7 &dtmiRaw_6_7);
    template < typename T >
    T swapHex(T value);
};

#endif // PIO_BOKZM60_H
