#include <stdio.h>
#include <string.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"


TaskHandle_t receiverHandler = NULL;

TaskHandle_t receiverHandler1 = NULL;
TaskHandle_t receiverHandler2 = NULL;
TaskHandle_t receiverHandler3 = NULL;
TaskHandle_t receiverHandler4 = NULL;

void task1(void *params)
{
    while (true)
    {
        xTaskNotifyWait(0x00, 0, NULL, portMAX_DELAY);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        int i=0;
        while(i<2)
        {
            printf("\n TASK 1- LED 2s \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            i= i+ 1;

        }
    // xEventGroupSetBits(evtGrp, gottask1);
    xTaskNotify(receiverHandler1, 0, eSetBits);
    
    }
}
void task2(void *params)
{
    while (true)
    {
        xTaskNotifyWait(0x00, 0, NULL, portMAX_DELAY);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        int i=0;
        while(i<5)
        {
            printf("\n TASK 2- LED 1s \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(1000/ portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(1000/ portTICK_PERIOD_MS);
            i= i+ 2;
        }
        
        // xEventGroupSetBits(evtGrp, gottask2);
        xTaskNotify(receiverHandler2, 0, eSetBits);
    }
}

void task3(void *params)
{
    while (true)
    {
        xTaskNotifyWait(0x00, 0, NULL, portMAX_DELAY);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        for(int i=0; i<10; i++)
        {
            printf("\n TASK 3- LED 500ms \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(500/ portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(500/ portTICK_PERIOD_MS);
        }
        // xEventGroupSetBits(evtGrp, gottask3);
        xTaskNotify(receiverHandler3, 0, eSetBits);
    }
}

void task4(void *params)
{
    while (true)
    {
        xTaskNotifyWait(0x00, 0, NULL, portMAX_DELAY);
        const int SET_GPIO = 2;
        gpio_pad_select_gpio(SET_GPIO);
        gpio_set_direction(SET_GPIO, GPIO_MODE_OUTPUT);
        for(int i=0; i<20; i++)
        {
            printf("\n TASK 4- LED 250ms \n\n");
            gpio_set_level((gpio_num_t)SET_GPIO, 1);
            vTaskDelay(250/ portTICK_PERIOD_MS);
            gpio_set_level((gpio_num_t)SET_GPIO, 0);
            vTaskDelay(250/ portTICK_PERIOD_MS);
        }
        // xEventGroupSetBits(evtGrp, gottask4);
        xTaskNotify(receiverHandler4, 0, eSetBits);
    }
}



void app_main(void)
{

    xTaskCreate(&task1, "LED 1", 2048, NULL, configMAX_PRIORITIES-1, &receiverHandler4);
    xTaskNotify(receiverHandler4, 0, eSetBits);
    xTaskCreate(&task2, "LED 2", 2048, NULL, configMAX_PRIORITIES-1, &receiverHandler1);
    xTaskCreate(&task3, "LED 3", 2048, NULL, configMAX_PRIORITIES-1, &receiverHandler2);
    xTaskCreate(&task4, "LED 4", 2048, NULL, configMAX_PRIORITIES-1, &receiverHandler3);   

}
