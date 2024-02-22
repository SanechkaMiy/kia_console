#ifndef PIO_BOKZ_H
#define PIO_BOKZ_H
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include <math.h>
#include "Kia_modules/kia_help_functions.h"
class Pio_bokz
{
public:
    enum TYPE_DATA
    {
        INT16 = 0,
        INT32 = 1,
        INT8 = 2,
        FLOAT = 3
    };

    enum DATA_MANAGE
    {
        DM_TYPE_DATA = 0,
        COUNT_EL_IN_ARR = 1,
        RANGE_VALUE = 2,
        COEF_TO_SCALE = 3,
        TYPE_FORMAT = 4,
        DO_SWAP = 5,
    };

    enum TYPE_DATA_FORMAT
    {
        TDF_INT = 0,
        TDF_HEX = 1,
        TDF_FLOAT = 2
    };
    Pio_bokz();
    virtual void decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count) = 0;
    virtual void decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count) = 0;
    virtual void parse_dtmi_loc() = 0;
    virtual void parse_dtmi(uint16_t type_orient) = 0;
    virtual void decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord) = 0;
    virtual void decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord) = 0;
    virtual void decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t& bshv) = 0;

    virtual void decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) = 0;
    virtual void decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) = 0;
    virtual ~Pio_bokz() = default;
    double m_max_double_value;
    QString get_format_str(uint16_t type_format, double value);
private:

};

#endif // PIO_BOKZ_H
