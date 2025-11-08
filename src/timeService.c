#include <st_hal.h>

unsigned millis()
{
    return HAL_GetTick();
}