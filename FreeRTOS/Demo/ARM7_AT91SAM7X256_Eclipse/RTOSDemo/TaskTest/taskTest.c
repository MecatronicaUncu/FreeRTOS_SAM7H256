#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo program include files. */
#include "taskTest.h"

#define testSTACK_SIZE		configMINIMAL_STACK_SIZE

/* Variable used by the created tasks to calculate the LED number to use, and
the rate at which they should flash the LED. */
static volatile unsigned taskCounter   = 0;
static magicStruct myStruct;

/* The task that is created three times. */
static portTASK_FUNCTION_PROTO( vTaskTest, pvParameters );

/*-----------------------------------------------------------*/

void vStartTaskTest( unsigned portBASE_TYPE uxPriority )
{

	int i;
	for(i = 0; i < 7; ++i )
	{
		/* Spawn the task. */
		xTaskCreate( vTaskTest, "Tasksx", testSTACK_SIZE, NULL, uxPriority, ( TaskHandle_t * ) NULL );
	}
}
/*-----------------------------------------------------------*/

static portTASK_FUNCTION( vTaskTest, pvParameters )
{
	TickType_t taskRate, xLastFlashTime;
	unsigned portBASE_TYPE taskID;

	/* The parameters are not used. */
	( void ) pvParameters;

	/* Calculate the LED and flash rate. */
	portENTER_CRITICAL();
	{
		/* See which of the eight LED's we should use. */
		taskID = taskCounter;

		/* Update so the next task uses the next LED. */
		taskCounter++;
	}
	portEXIT_CRITICAL();

	taskRate = 100 + ( 100 * ( TickType_t ) taskCounter );
	taskRate /= portTICK_PERIOD_MS;

	/* We will turn the LED on and off again in the delay period, so each
	delay is only half the total period. */
	taskRate /= ( TickType_t ) 2;

	/* We need to initialise xLastFlashTime prior to the first call to
	vTaskDelayUntil(). */
	xLastFlashTime = xTaskGetTickCount();

	for(;;)
	{
		/* Delay for half the flash period then turn the LED on. */
		vTaskDelayUntil( &xLastFlashTime, taskRate );
		myStruct.counter++;
		myStruct.lastModified = taskID;
	}
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */

