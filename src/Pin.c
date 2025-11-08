#include <lame/port/Pin_Impl.h>

static void enablePortClock(const GPIO_TypeDef *GPIOx)
{

    if (GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if (GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if (GPIOx == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
    else if (GPIOx == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
}

Pin Pin_init(struct Pin_Impl *handle, GPIO_InitTypeDef *initStruct)
{
    enablePortClock(handle->GPIOx);

    HAL_GPIO_Init(handle->GPIOx, initStruct);

    return handle;
}

void Pin_SetActive(Pin handle, bool state)
{
    if (state) {
        HAL_GPIO_WritePin(handle->GPIOx, handle->GPIO_Pin, GPIO_PIN_SET);
    }
    else {
        HAL_GPIO_WritePin(handle->GPIOx, handle->GPIO_Pin, GPIO_PIN_RESET);
    }
}

bool Pin_GetActive(const Pin handle)
{
    return HAL_GPIO_ReadPin(handle->GPIOx, handle->GPIO_Pin) == GPIO_PIN_SET;
}

void Pin_Toggle(Pin handle)
{
    HAL_GPIO_TogglePin(handle->GPIOx, handle->GPIO_Pin);
}
