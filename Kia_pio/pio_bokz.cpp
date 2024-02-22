#include "pio_bokz.h"

Pio_bokz::Pio_bokz()
{
    m_max_double_value = numeric_limits<double>::max();
}


QString Pio_bokz::get_format_str(uint16_t type_format, double value)
{
    QString format_str;
    switch(type_format)
    {
    case TDF_INT:
        format_str = QString::number(value);
        break;
    case TDF_HEX:
        format_str = QString("0x%1").arg(QString::number(static_cast<int>(value), 16), 4, '0');
        break;
    case TDF_FLOAT:
        format_str = QString::number(value,'f',4);
        break;
    }
    return format_str;
}
