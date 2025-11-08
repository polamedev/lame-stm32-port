#pragma once

#include <lame/drivers/Pin.h>

#include <st_hal.h>

struct Pin_Impl {
    GPIO_TypeDef *GPIOx;
    uint16_t      GPIO_Pin;
};

Pin Pin_init(struct Pin_Impl *handle, GPIO_InitTypeDef *initStruct);
