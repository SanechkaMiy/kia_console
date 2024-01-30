#include "kia_cyclogram.h"

Kia_cyclogram::Kia_cyclogram()
{

}

void Kia_cyclogram::sleep_for_pause(uint32_t time_in_microseconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(time_in_microseconds));
}

void Kia_cyclogram::post_exchange(uint16_t check_value, QString& is_success)
{
    if (check_value == KiaS_SUCCESS)
    {
        is_success = " - УСПЕХ!";
    }
    else
    {
        is_success = " - ОШИБКА!";
    }
}
