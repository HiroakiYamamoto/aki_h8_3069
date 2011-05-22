#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

int serial_init(int index);				/* intialize devices */
int serial_is_send_enable(int index);			/* Is it possible to send data? */
int serial_send_byte(int index, unsigned char b);	/* send a character */
int serial_is_recv_enable(int index);			/* Is it possible to receive data? */
unsigned char serial_recv_byte(int index);		/* receive a character */
int serial_intr_is_send_enable(int index);		/* Is interruption for transmission enabled? */
void serial_intr_send_enable(int index);		/* enable interruption for transmission */
void serial_intr_send_disable(int index);		/* disable interruption for transmission */
int serial_intr_is_recv_enable(int index);		/* Is interruption for receipt enabled? */
void serial_intr_recv_enable(int index);		/* enable interruption for receipt */
void serial_intr_recv_disable(int index);		/* disable interruption for receipt */

#endif
