#ifndef KIA_HELP_FUNCTIONS_H
#define KIA_HELP_FUNCTIONS_H
#include <QString>
#include <map>
#include "mainStruct.h"
namespace helpers
{
const int32_t second_for_1_jan_2000 = 946080000;
const uint16_t max_el_in_to_word = 4;
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
QString get_last_usd(uint16_t value, uint16_t shift, std::map<uint16_t, QString> usd);
QString get_status_error_m60(uint16_t value, uint16_t shift);

QString get_status(uint16_t value, uint16_t shift, QString is_true, QString is_false);
QString get_status_error_mf(uint16_t value, uint16_t shift);
QString get_status_dev(uint16_t value, uint16_t shift);
std::string currentDateTime();
uint32_t current_hours();
float decodeDateTime();
std::pair<uint32_t, uint16_t> get_seconds_for_bshv();

QString format_qstring(const QString& str, const int16_t &shift, const char &fillchar = ' ');

std::array<uint16_t, max_el_in_to_word> split_data_from_word(uint16_t data);
};
#endif // KIA_HELP_FUNCTIONS_H
