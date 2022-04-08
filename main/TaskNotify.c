#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

const int SET_GPIO = 2;

TaskHandle_t receiverHandler;

void handleWifi(void *params)
{
    uint32_t countLed = 0;

    while (true)
    {
        countLed ++;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        xTaskNotify(receiverHandler, countLed, eSetValueWithOverwrite);
        gpio_set_level((gpio_num_t)SET_GPIO, 1);
        vTaskDelay(2000/ portTICK_PERIOD_MS);

        printf("\n\nGET IP \n\n"); 
        printf("\n\nMQTT Start\n\n");

    }
}
void statusLed(void *params)
{
    uint32_t rxInt;

    while (true)
    {
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        xTaskNotifyWait(0xffffffff, 0, &rxInt, portMAX_DELAY);
        gpio_set_level((gpio_num_t)SET_GPIO, 0);
        
        printf("\n---- %d\n", rxInt);
        vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    xTaskCreate(&handleWifi, "handleWIFI", 2048, NULL, 2, NULL);
    xTaskCreate(&statusLed, "MQTT Connected", 2048, NULL, 2, &receiverHandler);

}