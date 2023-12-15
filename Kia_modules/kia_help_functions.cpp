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
    QString ret = QString("%1").arg(QString::number(value, 'f', 3), -9) + "'" + " ";
    return ret;
}

QString get_seconds(double value)
{
    value = value * 180 / PI;
    value = value * 3600;
    QString ret = QString("%1").arg(QString::number(value, 'f', 3), -11) + "\"" + " ";
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
        return "1 - выполнение команды завершено";
    }
    else
    {
        return "0 - команда выполняется";
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

float uint32_to_float(uint32_t value)
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

string currentDateTime()
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

uint32_t current_hours()
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

float decodeDateTime()
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

QString format_qstring(const QString &str, const int16_t &shift, const char &fillchar)
{
    return QString("%1").arg(str, shift, fillchar);
}
