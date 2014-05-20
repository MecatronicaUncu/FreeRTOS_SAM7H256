#include <stdlib.h>
/* Includes del Scheduler */
#include "FreeRTOS.h"
#include "task.h"
/* Include de taskTest */
#include "taskTest.h"

/* Tamaño de pila */
#define testSTACK_SIZE	configMINIMAL_STACK_SIZE

/* Contador utilizado para identificar las tareas */
static volatile unsigned taskCounter   = 0;

/* Contador, definido en taskTest.h*/
static magicStruct myStruct;

/* Port de la tarea con el macro para la arquitectura */
static portTASK_FUNCTION_PROTO( vTaskTest, pvParameters );

/* Función para crear las tareas, en un bucle */
void vStartTaskTest( unsigned portBASE_TYPE uxPriority ){
	/* Creamos 8 tareas TaskTest iguales */
	int i;
	for(i = 0; i < 7; ++i ){
		xTaskCreate( vTaskTest, "Tasksx", testSTACK_SIZE, NULL, uxPriority, ( TaskHandle_t * ) NULL );
	}
}

/* Definición de la tarea TaskTest */
static portTASK_FUNCTION( vTaskTest, pvParameters ){
	TickType_t taskRate, xLastFlashTime;
	unsigned portBASE_TYPE taskID;

	/* Evito errores del compilador */
	( void ) pvParameters;

	/* Identificamos cada tarea con un taskID único */
	portENTER_CRITICAL();
	{
		taskID = taskCounter;
		taskCounter++;
	}
	portEXIT_CRITICAL();

	/* Calculamos el periodo de la tarea utilizando taskID */
	taskRate = 100 + ( 100 * ( TickType_t ) taskID );
	taskRate /= portTICK_PERIOD_MS;

	/* Inicialización de xLastFlashTime */
	xLastFlashTime = xTaskGetTickCount();

	for(;;){
		/* Programa principal:
		 * La tarea se "duerme" taskRate ms
		 * Luego, incrementa el contador en myStruct,
		 * indicando su taskID
		 */
		vTaskDelayUntil( &xLastFlashTime, taskRate );
		myStruct.counter++;
		myStruct.lastModified = taskID;
	}
}
