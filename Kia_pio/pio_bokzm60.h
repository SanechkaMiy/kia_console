#ifndef PIO_BOKZM60_H
#define PIO_BOKZM60_H
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include <math.h>
#include "Kia_pio/pio_bokz.h"
class Pio_bokzm60 : public Pio_bokz
{
    enum TYPE_DATA
    {
        ITS_REZERV = -1,
        INT16 = 0,
        INT32 = 1,
        FLOAT = 2,
        DATE = 3,
        VER = 4,
        ARR = 5

    };
    enum TYPE_ARR
    {
        TA_NONE = -1,
        TA_FLOAT = 0,
        TA_UINT16 = 1
    };

public:
    Pio_bokzm60(std::shared_ptr<Kia_mko_struct> kia_mko_struct, std::shared_ptr<Kia_settings> kia_settings);
    void decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void parse_dtmi_loc() override;
    void parse_dtmi(uint16_t type_orient) override;
    void decrypt(uint16_t key_arr, std::vector<RAW_DATA> raw_data) override;
    void decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t& bshv) override;

    void decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) override;
    void decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) override;

    ~Pio_bokzm60();
private:
    float uint32_to_float(uint32_t value);

    void load_array_param_from_json();
    void create_list_for_mpi_arrays();
    void create_list_to_prepare_data();
};

#endif // PIO_BOKZM60_H
