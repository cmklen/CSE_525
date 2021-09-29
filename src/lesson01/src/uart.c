#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

#define CLK_FRQ 250000000
#define BAUD_RATE 9600

void uart_send ( char c )
{
	while(1) {
		if(get32(UART_FR)&0x20) 
			break;
	}
	put32(UART_DR, c);
}

char uart_recv ( void )
{
	while(1) {
		if(get32(UART_FR)&0x10) 
			break;
	}
	return(get32(UART_DR)&0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
	unsigned int selector;
	// unsigned int baud_rate = (CLK_FRQ / (8*BAUD_RATE)) - 1;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 2<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 2<<15;                      // set alt5 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	put32(UART_CR,0);            
	put32(UART_IMSC, 0);    

	put32(UART_IBRD,26);                
	put32(UART_FBRD,3);               
	put32(UART_LCRH,(1<<4) | (3<<5));              
	put32(UART_CR, 1 | (1<<8) | (1<<9));             

}
