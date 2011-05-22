#include "defines.h"
#include "intr.h"
#include "interrupt.h"

/* initialize the software interruption vector */
int softvec_init(void)
{
	int type;
	for (type = 0; type < SOFTVEC_TYPE_NUM; type++)
		softvec_setintr(type, NULL);
	return 0;
}

/* set the software interruption vector */
int softvec_setintr(softvec_type_t type, softvec_handler_t handler)
{
	SOFTVECS[type] = handler;
	return 0;
}

/*
 * commont interruption handler
 * switch to each handler according to the software interruption vector
 */
void interrupt(softvec_type_t type, unsigned long sp)
{
	softvec_handler_t handler = SOFTVECS[type];
	if (handler)
		handler(type, sp);
}
