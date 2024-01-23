#ifndef PIO_BOKZ_H
#define PIO_BOKZ_H
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include <math.h>
#include "Kia_modules/kia_help_functions.h"
class Pio_bokz
{
public:
    Pio_bokz();
    virtual void decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count) = 0;
    virtual void decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count) = 0;
    virtual void decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord) = 0;
    virtual void decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord) = 0;
    virtual void decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t& bshv) = 0;

    virtual void decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) = 0;
    virtual void decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) = 0;
    virtual ~Pio_bokz() = default;
private:

};

#endif // PIO_BOKZ_H
