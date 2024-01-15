#ifndef KIA_HELP_FUNCTIONS_H
#define KIA_HELP_FUNCTIONS_H
#include <QString>
#include <map>
#include "mainStruct.h"
namespace helpers
{
const int32_t second_for_1_jan_2000 = 946080000;
inline namespace angular_transform
{
    QString get_degreze(double value);
    QString get_minutes(double value);
    QString get_seconds(double value);
}


QString get_status_zkr(uint16_t value, uint16_t shift);
QString get_count_sec_fail_mark(uint16_t value, uint16_t shift);
QString get_dev_ready(uint16_t value, uint16_t shift);
QString get_status_orientation(uint16_t value, uint16_t shift);
QString get_mode_orientation(uint16_t value, uint16_t shift);
QString get_command_wait(uint16_t value, uint16_t shift);
QString get_command_complete(uint16_t value, uint16_t shift);
QString get_last_usd(uint16_t value, uint16_t shift);
QString get_status_error(uint16_t value, uint16_t shift);

float uint32_to_float(uint32_t value);
std::string currentDateTime();
uint32_t current_hours();
float decodeDateTime();
std::pair<uint32_t, uint16_t> get_seconds_for_bshv();

QString format_qstring(const QString& str, const int16_t &shift, const char &fillchar = ' ');
};
#endif // KIA_HELP_FUNCTIONS_H
