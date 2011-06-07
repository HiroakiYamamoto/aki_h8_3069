#include "defines.h"
#include "kozos.h"
#include "interrupt.h"
#include "lib.h"

/* start system task and user thread */
static int start_threads(int argc, char *argv[])
{
	kz_run(test08_1_main, "command", 0x100, 0, NULL);
	return 0;
}

int main(void)
{
	INTR_DISABLE; /* disable interruption */

	puts("kozos boot succeed!\n");

	/* start OS */
	kz_start(start_threads, "start", 0x100, 0, NULL);
	/* process does not return here */
	
	return 0;
}
