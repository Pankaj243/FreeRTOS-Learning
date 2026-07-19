/*
=========================================
Vehicle Health Monitoring System
FreeRTOS Simulation
Author : Pankaj Kumbhar
ID : pankajkumbhar444gmail.com
start date : 19-07-2026
=========================================
*/

#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


QueueHandle_t xQueue;
SemaphoreHandle_t xMutex;

typedef enum
{
    SENSOR_TEMP,
    SENSOR_SPEED,
    SENSOR_BATTERY,
    SENSOR_PRESSURE
} SensorType;

typedef struct
{
    SensorType sensorType;
    float value;
} SensorData;

static float SENSOR_TEMP_ = 25.0f;
static float SENSOR_SPEED_ = 0.0f;
static float SENSOR_BATTERY_ = 12.6f;
static float SENSOR_PRESSURE_ = 32.2f;

void TemperatureTask(void* pvParameter)
{
    SensorData data;
    static float temperature = 98.0f;   // Initial value

    while (1)
    {

        temperature += (rand() % 3) - 1;
        if (temperature < 20.0f)
        {
            temperature = 20.0f;
        }
        else if (temperature > 120.0f)
        {
            temperature = 120.0f;
        }

        data.sensorType = SENSOR_TEMP;
        data.value = temperature;

        xQueueSend(xQueue, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void SpeedTask(void* pvParameter)
{
    SensorData data;
    static int speed = 0;

    while (1)
    {
        speed += (rand() % 11) - 5;
        if (speed < 0)
        {
            speed = 0;
        }
        else if (speed > 180)
        {
            speed = 180;
        }

        data.sensorType = SENSOR_SPEED;
        data.value = (float)speed;

        xQueueSend(xQueue, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void BatteryVoltageTask(void* pvParameter)
{
    SensorData data;
    static float batt = 12.6f;
    while (1)
    {
        batt += ((rand() % 3) - 1) * 0.1f;
        if (batt < 11.5f)
        {
            batt = 11.5f;
        }
        else if (batt > 14.5f)
        {
            batt = 14.5f;
        }
        data.sensorType = SENSOR_BATTERY;
        data.value = batt;
        xQueueSend(xQueue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
void PressureTask(void* pvParameter)
{
    SensorData data;
    static float press = 32.2f;
    while (1)
    {
        press += ((rand() % 3) - 1) * 0.1;
        if (press < 28.0f)
        {
            press = 28.0f;
        }
        else if (press > 36.0f)
        {
            press = 36.0f;
        }
        data.sensorType = SENSOR_PRESSURE;
        data.value = press;
        xQueueSend(xQueue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Alarm(void* pvParameter)
{

    while(1)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        if (SENSOR_TEMP_ > 100)
        {
            printf("***** WARNING *****\n");
            printf("Engine Temperature High\n");
        }
        
        if (SENSOR_SPEED_ > 120)
        {
            printf("***** WARNING *****\n");
            printf("Car Speed High\n");
        }

        if (SENSOR_PRESSURE_ > 34)
        {
            printf("***** WARNING *****\n");
            printf("Tire Pressuer High\n");
        }
        else if(SENSOR_PRESSURE_ < 30)
        {
            printf("***** WARNING *****\n");
            printf("Tire Pressuer Low\n");
        }
        
        if (SENSOR_BATTERY_ > 14.2)
        {
            printf("***** WARNING *****\n");
            printf("High battery voltage\n");
        }
        else if (SENSOR_BATTERY_ < 11.8)
        {
            printf("***** WARNING *****\n");
            printf("Low battery voltage\n");
        }

        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void DashboardTask(void* pvParameter)
{
    SensorData data;
    
    FILE* fp = fopen("sensor_data.txt", "w");

    while (1)
    {
        xQueueReceive(xQueue, &data, portMAX_DELAY);
        switch (data.sensorType)
        {
        case SENSOR_TEMP:
            SENSOR_TEMP_ = data.value;
            break;

        case SENSOR_SPEED:
            SENSOR_SPEED_ = data.value;
            break;

        case SENSOR_BATTERY:
            SENSOR_BATTERY_ = data.value;
            break;

        case SENSOR_PRESSURE:
            SENSOR_PRESSURE_ = data.value;
            break;
        }
        xSemaphoreTake(xMutex, portMAX_DELAY);
        //printf("---------------------------------------\nTemperature : %.2f C\nSpeed : %.0f km / h\nBattery : %.2f V\nPressure : %.2f PSI\n", SENSOR_TEMP_, SENSOR_SPEED_, SENSOR_BATTERY_, SENSOR_PRESSURE_);
        printf("------------------------------------------\n");
        printf("Temperature : %.2f C\n", SENSOR_TEMP_);
        printf("Speed : %.0f km / h\n", SENSOR_SPEED_);
        printf("Battery : %.2f V\n", SENSOR_BATTERY_);
        printf("Pressure : %.2f PSI\n\n", SENSOR_PRESSURE_);
        
        if (fp)
        {
            fprintf(fp, "%.2f,%.0f,%.2f,%.2f\n",
                SENSOR_TEMP_,
                SENSOR_SPEED_,
                SENSOR_BATTERY_,
                SENSOR_PRESSURE_);
            fflush(fp);
            vTaskDelay(pdMS_TO_TICKS(200));
        }
        xSemaphoreGive(xMutex);
    }
    fclose(fp);
}

int main()
{
    xQueue = xQueueCreate(10, sizeof(SensorData));
    xMutex = xSemaphoreCreateMutex();

    xTaskCreate(TemperatureTask, "temp", 512, NULL, 2, NULL);
    xTaskCreate(SpeedTask, "speed", 512, NULL, 2, NULL);
    xTaskCreate(BatteryVoltageTask, "battery", 512, NULL, 2, NULL);
    xTaskCreate(PressureTask, "pressure", 512, NULL, 2, NULL);
    xTaskCreate(DashboardTask, "display", 512, NULL, 1, NULL);

    xTaskCreate(Alarm, "temp_alarm", 512, NULL, 1, NULL);
    //xTaskCreate(SpeedAlarm, "speed_alarm", 512, NULL, 1, NULL);
    //xTaskCreate(BatteryAlarm, "battery_alarm", 512, NULL, 1, NULL);
    //xTaskCreate(PressuerAlarm, "presseue_alarm", 512, NULL, 1, NULL);

    vTaskStartScheduler();

    for (;;);
}