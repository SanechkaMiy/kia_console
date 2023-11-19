#include "kia_help_functions.h"
QString get_degreze(double value)
{
    value = value * 180 / PI;
    QString ret = QString("%1").arg(QString::number((int)value), -5) + "°" + " ";
    return ret;
}

QString get_minutes(double value)
{
    value = value * 180 / PI;
    value = value * 60;
    QString ret = QString("%1").arg(QString::number(value, 'f', 3), -9) + "''" + " ";
    return ret;
}

QString get_seconds(double value)
{
    value = value * 180 / PI;
    value = value * 3600;
    QString ret = QString("%1").arg(QString::number(value, 'f', 3), -11) + "'" + " ";
    return ret;
}


QString get_status_zkr(uint16_t value, uint16_t shift)
{
    if ((value & (0x0001 << shift)) != 0)
    {
        if (shift == 2)
            return "1 - крышка открыта";
        else
            return "1 - крышка закрыта";
    }
    else
    {
        if (shift == 2)
            return "0 - крышка не открыта";
        else
            return "0 - крышка не закрыта";
    }
}

QString get_count_sec_fail_mark(uint16_t value, uint16_t shift)
{
    return QString::number((value & (0x0001 << shift)) + (value & (0x0001 << (shift + 1))) + (value & (0x0001 << (shift + 2))) + (value & (0x0001 << (shift + 3))));
}

QString get_dev_ready(uint16_t value, uint16_t shift)
{
    if ((value & (0x0001 << shift)) != 0)
    {
        return "1 - прибор к работе готов";
    }
    else
    {
        return "0 - прибор к работе не готов";
    }
}


QString get_status_orientation(uint16_t value, uint16_t shift)
{
    if ((value & (0x0001 << shift)) != 0)
    {
        return "1 - да";
    }
    else
    {
        return "0 - нет";
    }
}

QString get_mode_orientation(uint16_t value, uint16_t shift)
{
    if ((value & (0x0001 << shift)) != 0)
    {
        return "1 - прибор находится в одном из режимов НО, ТО";
    }
    else
    {
        return "0 - прибор не находится в одном из режимов НО, ТО";
    }
}

QString get_command_wait(uint16_t value, uint16_t shift)
{
    if ((value & (0x0001 << shift)) != 0)
    {
        return "1 - команда выполняется";
    }
    else
    {
        return "0 - команда не выполняется";
    }
}

QString get_command_complete(uint16_t value, uint16_t shift)
{
    if ((value & (0x0001 << shift)) != 0)
    {
        return "1 - выполнение команды завершено успешно";
    }
    else
    {
        return "0 - выполнение команды завершено неуспешно";
    }
}

QString get_last_usd(uint16_t value, uint16_t shift)
{
    std::map<uint16_t, QString> usd;
    usd[1] = "ОКР";
    usd[2] = "ЗКР";
    usd[3] = "НО";
    usd[4] = "ТО";
    usd[5] = "ЛОК";
    usd[6] = "ОТКЛР";
    if (value != 0 && (value & (0x000f << shift)) < 7)
        return QString::number((value & (0x000f << shift))) + " - " + usd[(value & (0x000f << shift))];
    else if ((value & (0x000f << shift)) >= 7)
        return QString::number((value & (0x000f << shift))) + " - резерв";
    else
        return "0 - последнего переданного УСД не было";
}
