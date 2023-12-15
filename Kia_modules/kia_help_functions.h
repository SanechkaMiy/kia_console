#ifndef KIA_HELP_FUNCTIONS_H
#define KIA_HELP_FUNCTIONS_H
#include <QString>
#include <map>
#include "mainStruct.h"
QString get_degreze(double value);
QString get_minutes(double value);
QString get_seconds(double value);
QString get_status_zkr(uint16_t value, uint16_t shift);
QString get_count_sec_fail_mark(uint16_t value, uint16_t shift);
QString get_dev_ready(uint16_t value, uint16_t shift);
QString get_status_orientation(uint16_t value, uint16_t shift);
QString get_mode_orientation(uint16_t value, uint16_t shift);
QString get_command_wait(uint16_t value, uint16_t shift);
QString get_command_complete(uint16_t value, uint16_t shift);
QString get_last_usd(uint16_t value, uint16_t shift);

float uint32_to_float(uint32_t value);
std::string currentDateTime();
uint32_t current_hours();
float decodeDateTime();

QString format_qstring(const QString& str, const int16_t &shift, const char &fillchar = ' ');
#endif // KIA_HELP_FUNCTIONS_H
