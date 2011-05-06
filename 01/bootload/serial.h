#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

int serial_init(int index); /* intialize devices */
int serial_is_send_enable(int index); /* Is it possible to send data? */
int serial_send_byte(int index, unsigned char b); /* send a character */
int serial_is_recv_enable(int index); /* Is it possible to receive data? */
unsigned char serial_recv_byte(int index); /* receive a character */

#endif
