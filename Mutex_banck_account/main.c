
//Banking project using mutex
#include <stdio.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
int balance = 0;
SemaphoreHandle_t mutex;

void Deposite(void *pvParameter)
{

	while (1)
	{
		xSemaphoreTake(mutex, portMAX_DELAY);
		balance += 100;
		printf("deposite to account : %d\n", balance);
		xSemaphoreGive(mutex);
		vTaskDelay(pdMS_TO_TICKS(2000));
	}

}
void Widraw(void * pvParameter)
{
	while (1)
	{
		xSemaphoreTake(mutex, portMAX_DELAY);
		balance -=50;
		printf("widraw from account : %d\n", balance);
		xSemaphoreGive(mutex);
		vTaskDelay(pdMS_TO_TICKS(3000));
	}
}void CheckBalance(void *pvParameter)
{
	while(1)
	{
		xSemaphoreTake(mutex, portMAX_DELAY);
		printf("your current balance is : %d\n", balance);
		xSemaphoreGive(mutex);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

int main()
{
	mutex = xSemaphoreCreateMutex();
	if(mutex != NULL)
	{
		xTaskCreate(Deposite, "diposite", 512, NULL, 2, NULL);
		xTaskCreate(Widraw, "Widraw", 512, NULL, 2, NULL);
		xTaskCreate(CheckBalance, "Balance", 512, NULL, 2, NULL);
	}
	else{
		printf("Mutex creation is failed !!!");
	}
	vTaskStartScheduler();
	for (;;);
}