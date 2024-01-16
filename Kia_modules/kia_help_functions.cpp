#include "kia_help_functions.h"

QString helpers::angular_transform::get_degreze(double value)
{
    value = value * 180 / PI;
    QString ret = QString("%1").arg(QString::number(value, 'f', 3), -8) + "°" + " ";
    return ret;
}

QString helpers::angular_transform::get_minutes(double value)
{
    value = value * 180 / PI;
    auto minutes = value - (int)value;
    minutes = 60 * minutes;
    QString ret = QString("%1").arg(QString::number((int)minutes, 'f', 3), -8) + "'" + " ";
    return ret;
}

QString helpers::angular_transform::get_seconds(double value)
{
    value = value * 180 / PI;
    auto minutes = value - (int)value;
    minutes = 60 * minutes;
    auto seconds = minutes - (int)minutes;
    seconds = 60 * seconds;
    QString ret = QString("%1").arg(QString::number(seconds, 'f', 3), -8) + "\"" + " ";
    return ret;
}


QString helpers::get_status_zkr(uint16_t value, uint16_t shift)
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

QString helpers::get_count_sec_fail_mark(uint16_t value, uint16_t shift)
{
    return QString::number((value & (0x0001 << shift)) + (value & (0x0001 << (shift + 1))) + (value & (0x0001 << (shift + 2))) + (value & (0x0001 << (shift + 3))));
}

QString helpers::get_dev_ready(uint16_t value, uint16_t shift)
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


QString helpers::get_status_orientation(uint16_t value, uint16_t shift)
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

QString helpers::get_mode_orientation(uint16_t value, uint16_t shift)
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

QString helpers::get_command_wait(uint16_t value, uint16_t shift)
{
    if ((value & (0x0001 << shift)) != 0)
    {
        return "1 - выполнение команды завершено";
    }
    else
    {
        return "0 - команда выполняется";
    }
}

QString helpers::get_command_complete(uint16_t value, uint16_t shift)
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

QString helpers::get_last_usd(uint16_t value, uint16_t shift)
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

QString helpers::get_status_error(uint16_t value, uint16_t shift)
{
    switch(value >> shift)
    {
    case 0x0001:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - конец первой фазы НО(не ошибка)";
        break;
    case 0x0005:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - засветка";
        break;
    case 0x0006:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - локализовано менее 4-х объектов в НО или менее 3-х при слежении";
        break;
    case 0x0008:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - с апр.инф-ии распознано менее 3 звезд";
        break;
    case 0x0009:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - без апр.инф-ии распознано менее 4 звезд";
        break;
    case 0x000A:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - неверно задан апр.кватернион";
        break;
    case 0x000B:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - ошибочная переменная";
        break;
    case 0x000D:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - грубые измерения";
        break;
    case 0x000E:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - ошибка фрагмента";
        break;
    case 0x0080:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - получено неподдерживемое УСД";
        break;
    case 0x0081:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - ошбика ввода 1";
        break;
    case 0x0082:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - ошибка ввода 2";
        break;
    case 0x0083:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - ошибка ввода 3";
        break;
    case 0x0084:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - тайм-аут расчета";
        break;
    default:
        return QString("%1").arg(QString::number(value >> shift, 16), 2, '0') + " - ошибки нет";
        break;
    }
}

float helpers::uint32_to_float(uint32_t value)
{
    uint32_t masca = 0x00000001;
    uint32_t temp = 0;
    float result = 0.0;
    for (int i = 0; i < 32; ++i)
    {
        temp = (value>>i) & (masca);
        if (i < 31)
        {
            if (temp == 1)
            {
                //printf("%04x\n", temp);
                result = result + pow(2,(-31 + i));
                //cout<<" "<<i<<" "<<result<<endl;

            }
        }
        if (i == 31)
        {
            if (temp == 1)
            {
                result = -result;
            }
        }

    }
    return result;
}

string helpers::currentDateTime()
{
    std::time_t t = std::time(nullptr);
    std::tm* now_t = std::localtime(&t);
    char buffer[128];
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    /* UTC: -3:00 = 24 - 3 = 21 */
    typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 24 > >::type > Days;
    Days days = std::chrono::duration_cast<Days>(duration);
    duration -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    char data[50];
    strftime(data, sizeof(data), "%Y-%m-%d", now_t);
    sprintf(buffer,"%s %02i:%02ld:%02ld.%03ld", data, now_t->tm_hour, minutes.count(), seconds.count(), milliseconds.count());
    return buffer;
}

uint32_t helpers::current_hours()
{
    std::time_t t = std::time(nullptr);
    std::tm* now_t = std::localtime(&t);
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    /* UTC: -3:00 = 24 - 3 = 21 */
    typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 24 > >::type > Days;
    Days days = std::chrono::duration_cast<Days>(duration);
    duration -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    //return minutes.count();
    return now_t->tm_hour;
}

float helpers::decodeDateTime()
{
    const float J_GOD = 36525.0;
    const float JD2000 = 2451545.0;
    const float JToG = 1720994.5;
    const float DInm = 30.600;
    const float DInY = 365.25;
    std::time_t t = std::time(nullptr);
    std::tm* now_t = std::localtime(&t);
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    /* UTC: -3:00 = 24 - 3 = 21 */
    typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 24 > >::type > Days;
    Days days = std::chrono::duration_cast<Days>(duration);
    duration -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    float Yn = 1900 + now_t->tm_year;
    float Mn = 1 + now_t->tm_mon;
    float DD;
    DD = now_t->tm_mday + (now_t->tm_hour) / 24 + minutes.count() / (24 * 60) + seconds.count() / (24 * 60 * 60) + milliseconds.count() / (24 * 60 * 60 * 1000);
    if (Mn <= 2)
    {
        Yn = Yn - 1;
        Mn = Mn + 12;
    }
    float A;
    A = Yn / 100;
    float B;
    B = 2 - A + A / 4;
    float Dn;
    Dn = trunc(DInY * Yn);
    float Hn;
    Hn = trunc(DInm * (Mn + 1));
    float JD;
    JD = Dn + Hn + DD + JToG + B;
    float Fl;
    Fl = (JD - JD2000) / J_GOD;
    return Fl;
}

QString helpers::format_qstring(const QString &str, const int16_t &shift, const char &fillchar)
{
    return QString("%1").arg(str, shift, fillchar);
}

std::pair<uint32_t, uint16_t> helpers::get_seconds_for_bshv()
{
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    /* UTC: -3:00 = 24 - 3 = 21 */
    typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 24 > >::type > Days;
    Days days = std::chrono::duration_cast<Days>(duration);
    duration -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    time_t sec;
    sec = time (NULL);
    uint32_t sec_whole_part = sec - helpers::second_for_1_jan_2000;
    return {sec_whole_part, milliseconds.count()};
}

std::array<uint16_t, helpers::max_el_in_to_word> helpers::split_data_from_word(uint16_t data)
{
    std::array<uint16_t, max_el_in_to_word> ret_arr;
    for (uint16_t ind_shift = 0; ind_shift < max_el_in_to_word; ind_shift++)
    {
        ret_arr[ind_shift] = ((data >> (4 * ind_shift)) & 0x000f);
    }
    return ret_arr;
}
