#include "defines.h"
#include "serial.h"
#include "lib.h"

/* ��ʸ������ */
int putc(unsigned char c)
{
  if (c == '\n')
    serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
  return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

/* ʸ�������� */
int puts(unsigned char *str)
{
  while (*str)
    putc(*(str++));
  return 0;
}
