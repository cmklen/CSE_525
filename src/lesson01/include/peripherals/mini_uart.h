#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

#define UART_OFFSET (PBASE + 0x201000)

#define UART_DR   (UART_OFFSET +0x00)
#define UART_FR (UART_OFFSET + 0x18)
#define UART_IBRD (UART_OFFSET + 0x24)
#define UART_FBRD (UART_OFFSET + 0x28)
#define UART_LCRH (UART_OFFSET + 0x2C)
#define UART_CR (UART_OFFSET + 0x30)
#define UART_IMSC (UART_OFFSET + 0x38)


#endif  /*_P_MINI_UART_H */
