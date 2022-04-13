#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;

void handleWifi(void *params)
{
    while (true)
    {
        vTaskDelay(5000/ portTICK_PERIOD_MS);
        printf("GET IP \n\n");
        vTaskDelay(5000/ portTICK_PERIOD_MS);
        xTaskNotifyGive(receiverHandler);
    }
}

void initMqtt(void *params)
{
    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("MQTT Start\n\n");
    }
}

void initWifi(void)
{
     xTaskCreate(&handleWifi, "handleWIFI", 2048, NULL, configMAX_PRIORITIES-1, NULL);
}

void connections(void)
{
    initWifi();
    xTaskCreate(&initMqtt, "MQTT Start", 2048, NULL, configMAX_PRIORITIES-1, &receiverHandler);
}

void app_main(void)
{
    connections();
}