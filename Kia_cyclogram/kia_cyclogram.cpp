#include "kia_cyclogram.h"

Kia_cyclogram::Kia_cyclogram()
{
}

void Kia_cyclogram::sleep_for_pause(uint32_t time_in_microseconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(time_in_microseconds));
}
