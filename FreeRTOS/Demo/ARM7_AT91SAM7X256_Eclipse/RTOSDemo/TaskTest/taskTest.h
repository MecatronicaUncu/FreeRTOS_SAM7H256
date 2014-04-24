#ifndef TASK_TEST_H
#define TASK_TEST_H

void vStartTaskTest( unsigned portBASE_TYPE uxPriority );

typedef struct magicstruct{
	volatile int counter;
	volatile int lastModified;
}magicStruct;

#endif
