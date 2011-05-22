#ifndef _INTERRUPT_H_INCLUDED_
#define _INTERRUPT_H_INCLUDED_

/* These symbols are defined in the linker script. */
extern char softvec;
#define SOFTVEC_ADDR (&softvec)

typedef short softvec_type_t;

typedef void (*softvec_handler_t)(softvec_type_t type, unsigned long sp);

#define SOFTVECS ((softvec_handler_t *)SOFTVEC_ADDR)

#define INTR_ENABLE asm volatile ("andc.b #0x3f,ccr")
#define INTR_DISABLE asm volatile ("orc.b #0xc0,ccr")

/* initialize the software interruption vector */
int softvec_init(void);

/* set the software vector interruption vector */
int softvec_setintr(softvec_type_t, softvec_handler_t handler);

/* common interruption handler */
void interrupt(softvec_type_t type, unsigned long sp);

#endif
