#ifndef PIO_BOKZ_H
#define PIO_BOKZ_H
#include "mainStruct.h"
#include "Kia_mko_struct.h"
#include <math.h>
#include "Kia_modules/kia_help_functions.h"
#include <fstream>
class Pio_bokz
{
public:

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

    enum TYPE_PROTOCOL_STR
    {
        STRING_SHOW = 0,
        DOUBLE_VALUE = 1,
        STATUS = 2,

    };

    Pio_bokz();
    virtual void decrypt_dtmi_loc(array<uint16_t, constants::packetSize> dataWord, uint16_t count) = 0;
    virtual void decrypt_dtmi(array<uint16_t, constants::packetSize> dataWord, uint16_t count) = 0;
    virtual void parse_dtmi_loc() = 0;
    virtual void parse_dtmi(uint16_t type_orient) = 0;
    virtual void decrypt(uint16_t key_arr, std::vector<RAW_DATA> raw_data) = 0;
    virtual void decrypt_shtmi1(array<uint16_t, constants::packetSize> dataWord) = 0;
    virtual void decrypt_shtmi2(array<uint16_t, constants::packetSize> dataWord) = 0;
    virtual void decrypt_mshior(array<uint16_t, constants::packetSize> dataWord, int32_t& bshv) = 0;

    virtual void decrypt_chpn(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) = 0;
    virtual void decrypt_chkd(array<uint16_t, constants::packetSize> dataWord, uint16_t num_arr) = 0;

    virtual ~Pio_bokz() = default;

    double m_max_double_value;

    std::map<uint16_t, std::map<std::string, uint16_t>> get_index_mpi_array();

    std::map<uint16_t, std::map<std::string, uint16_t>> m_index_mpi_array;

    QString get_format_str(uint16_t type_format, uint16_t value)
    {
        QString format_str;
        switch(type_format)
        {
        case TDF_INT:
            format_str = QString::number(value);
            break;
        case TDF_HEX:
            format_str = QString("0x%1").arg(QString::number(value, 16), 4, '0');
            break;
        }
        return format_str;
    }

    std::vector<std::function<void(int16_t key_arr, std::pair<int16_t, std::string>, uint16_t& num_data, std::vector<uint8_t> value, std::pair<double, double>, double scale, uint16_t type_format, std::pair<bool, bool> do_proc)>> m_prepare_data;
    std::map<uint16_t, std::vector<std::tuple<std::tuple<int16_t, std::string, int16_t>, uint16_t, std::pair<double, double>, double, uint16_t, std::pair<bool, bool>>>> m_data_manage;
    std::shared_ptr<Kia_mko_struct> m_kia_mko_struct;
    std::shared_ptr<Kia_settings> m_kia_settings;

    template < typename T >
    T swapHex(T value)
    {
        value = ((value & 0x0000ffff) << 16) | ((value & 0xffff0000) >> 16);
        return value;
    }

    void add_to_list_description(uint16_t key_arr, const QString& num_value, const QString& description, const QString &type_data, const QString &name_data);

private:
};

#endif // PIO_BOKZ_H
