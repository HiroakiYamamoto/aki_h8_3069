#include "defines.h"
#include "serial.h"
#include "xmodem.h"
#include "elf.h"
#include "lib.h"

static int init(void)
{
	/* Followings are the symbols defined in linker script. */
	extern int erodata, data_start, edata, bss_start, ebss;

	/*
	 * Initialize the data area and BSS area. After the procedure,
	 * global variables are initialized.
	 */
	memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
	memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

	/* Initialize the serial device. */
	serial_init(SERIAL_DEFAULT_DEVICE);

	return 0;
}

/* hexadecimal dumping of a memory */
static int dump(char *buf, long size)
{
	long i;

	if (size < 0) {
		puts("no data.\n");
		return -1;
	}
	for (i = 0; i < size; i++) {
		putxval(buf[i], 2);
		if ((i & 0xf) == 15) {
			puts("\n");
		} else {
			if ((i & 0xf) == 7) puts(" ");
			puts(" ");
		}
	}
	puts("\n");

	return 0;
}

static void wait()
{
	volatile long i;
	for (i = 0; i < 300000; i++)
		;
}

int main(void)
{
	static char buf[16];
	static long size = -1;
	static unsigned char *loadbuf = NULL;
	extern int buffer_start; /* This buffer is defined in the linker script */
	char *entry_point;
	void (*f)(void);

	init();

	puts("Hello World!\n");
	puts("kzload (kozos boot loader) started.\n");

	while (1) {
		puts("kzload> "); /* display of prompt */
		gets(buf); /* receipt of commands via serial */

		if (!strcmp(buf, "load")) { /* file download in XMODEM */
			loadbuf = (char *)(&buffer_start);
			size = xmodem_recv(loadbuf);
			wait();	/* Wait until transfer application terminates and terminal console can be controled. */
			if (size < 0) {
				puts("\nXMODEM receive error!\n");
			} else {
				puts("\nXMODEM receive succeeded.\n");
			}
		} else if (!strcmp(buf, "dump")) { /* hexadecimal dump of a memory */
			puts("size: ");
			putxval(size, 0);
			puts("\n");
			dump(loadbuf, size);
		} else if (!strcmp(buf, "run")) { /* execute ELF files */
			entry_point = elf_load(loadbuf); /* load ELF files to a memory */
			if (!entry_point) {
				puts("run error!\n");
			} else {
				puts("starting from entry point: ");
				putxval((unsigned long)entry_point, 0);
				puts("\n");
				f = (void (*)(void))entry_point;
				f(); /* operation is switched to the loaded program at this point */
			}
		} else {
			puts("unknown.\n");
		}
	}

	return 0;
}
