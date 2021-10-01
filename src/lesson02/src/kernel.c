#include "printf.h"
#include "utils.h"
#include "mini_uart.h"

void kernel_main_el2(void)
{
	uart_init();
	init_printf(0, putc);
	printf("Exception level: %d \r\n", get_el());
}

void kernel_main_el1(void)
{
	printf("Exception level: %d \r\n", get_el());

	while (1) {
		uart_send(uart_recv());
	}
}
