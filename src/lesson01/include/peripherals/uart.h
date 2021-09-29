#ifndef	_P_UART_H
#define	_P_UART_H

#include "peripherals/base.h"

#define UART_OFFEST 0x00201000

#define UART_DR   (PBASE + UART_OFFEST +0x00)
#define UART_FR (PBASE + UART_OFFEST + 0x18)
#define UART_IBRD (PBASE +UART_OFFEST + 0x24)
#define UART_FBRD (PBASE +UART_OFFEST + 0x28)
#define UART_LCRH (PBASE +UART_OFFEST + 0x2C)
#define UART_CR (PBASE + UART_OFFEST + 0x30)
#define UART_IMSC (PBASE +UART_OFFEST + 0x38)


#endif  /*_P_MINI_UART_H */
