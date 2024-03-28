#include "pio_bokz.h"

Pio_bokz::Pio_bokz()
{
    m_max_double_value = numeric_limits<double>::max();

}

std::map<uint16_t, std::map<string, uint16_t> > Pio_bokz::get_index_mpi_array()
{
    return m_index_mpi_array;;
}


void Pio_bokz::add_to_list_description(uint16_t key_arr, const QString &num_value, const QString &description, const QString &type_data, const QString &name_data)
{
    m_kia_mko_struct->m_data[key_arr].data_description.push_back(std::make_tuple(helpers::format_qstring(num_value, m_kia_settings->m_format_for_desc.shift_for_numbers)
                                                                                 + description, type_data, name_data));
}
