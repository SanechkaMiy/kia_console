#ifndef PIO_BOKZM60_H
#define PIO_BOKZM60_H
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include <math.h>
#include "Kia_pio/pio_bokz.h"
#include <fstream>
class Pio_bokzm60 : public Pio_bokz
{
public:
    Pio_bokzm60(std::shared_ptr<Kia_mko_struct> kia_mko_struct, std::shared_ptr<Kia_settings> kia_settings);
    void decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count) override;
    void parse_dtmi_loc() override;
    void parse_dtmi(uint16_t type_orient) override;
    void decrypt(uint16_t key_arr, std::vector<RAW_DATA> raw_data, uint16_t num_arr = 0) override;
    void decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord) override;
    void decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t& bshv) override;

    void decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) override;
    void decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) override;

    std::map<uint16_t, std::map<std::string, uint16_t>> get_index_mpi_array() override;
    ~Pio_bokzm60();
private:
    std::shared_ptr<Kia_mko_struct> m_kia_mko_struct;
    std::shared_ptr<Kia_settings> m_kia_settings;
    void dtimi_loc_converter(DTMILocRaw_2_3_4_5_6_7_8 &dtmi_loc_raw_2_3_4_5_6_7_8);
    void dtmi_2_3_4_converter(DTMIRaw_2_3_4 &dtmiRaw_2_3_4);
    void dtmi_6_7_converter(DTMIRaw_6_7 &dtmiRaw_6_7);
    template < typename T >
    T swapHex(T value);
    float uint32_to_float(uint32_t value);
    void load_array_param_from_json();
    void create_list_to_prepare_data();
    void create_list_for_mpi_arrays();
    void add_to_list_description(uint16_t key_arr, const QString& num_value, const QString& description, const QString &type_data, const QString &name_data);
    std::vector<std::function<void(int16_t key_arr, std::pair<int16_t, std::string>, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double>, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)>> m_prepare_data;
    std::map<uint16_t, std::vector<std::tuple<std::tuple<int16_t, std::string, int16_t>, uint16_t, std::pair<double, double>, double, uint16_t, std::pair<bool, bool>>>> m_data_manage;
};

#endif // PIO_BOKZM60_H
