#pragma once

#include <lame/drivers/Pin.h>

#include <st_hal.h>

struct PinImpl {
    GPIO_TypeDef *GPIOx;
    uint16_t      GPIO_Pin;
};

Pin Pin_init(struct PinImpl *handle, GPIO_InitTypeDef *initStruct);
