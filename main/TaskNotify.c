#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

uint count = 0;

TaskHandle_t handler1;
TaskHandle_t handler2;

void task1(void *params)
{
    
    while (true)
    { 
        // printf("COUNT1: %d \n\n", count);

        // if (ulTaskNotifyTake( pdFALSE, portMAX_DELAY))
        if (xTaskNotifyWait(0xffffffff, 0, NULL, portMAX_DELAY))
        {
            printf("COUNT1: %d \n\n", count);
            count++;
            vTaskDelay(1000/ portTICK_PERIOD_MS);
            xTaskNotify(handler2, 0, eSetValueWithOverwrite);
        }
    }
}

void task2(void *params)
{
    while (true)
    { 
        // printf("COUNT2: %d \n\n", count);

        if (xTaskNotifyWait( 0xffffffff, 0, NULL, portMAX_DELAY))
        {
        printf("COUNT2: %d \n\n", count);
        count++;
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        xTaskNotify(handler1, 0, eSetValueWithOverwrite);
        }
    }
}


void app_main(void)
{
  xTaskCreate(&task1, "COUNTER 1", 2048, NULL, configMAX_PRIORITIES-1, &handler1);
  xTaskCreate(&task2, "COUNTER 2", 2048, NULL, configMAX_PRIORITIES-1, &handler2);
  xTaskNotify(handler1, count, eSetBits);

}
