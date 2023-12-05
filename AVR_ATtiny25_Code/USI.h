#ifndef DBG_PUTCHAR_H
#define DBG_PUTCHAR_H

#define F_CPU 1000000UL

#include <stdint.h>
#include <util/delay.h>

/* User setting -> Whether to enable the software UART */
#define DBG_UART_ENABLE		1

/* User setting -> Output pin the software UART */
#define DBG_UART_TX_PORT	PORTB
#define DBG_UART_TX_DDR		DDRB
#define DBG_UART_TX_PIN		PB0

/* User setting -> Software UART baudrate. */
#define DBG_UART_BAUDRATE	9600


/* ---- DO NOT TOUCH BELOW THIS LINE ---- */

#if DBG_UART_ENABLE

/**
 * @brief Debug software UART initialization.
 */
#define tx_init()	do { \
		DBG_UART_TX_PORT |= (1<<DBG_UART_TX_PIN); \
		DBG_UART_TX_DDR |= (1<<DBG_UART_TX_PIN); \
	} while(0)

/**
 * @brief Software UART routine for transmitting debug information. 
 *
 * @warning This routine blocks all interrupts until all 10 bits  ( 1 START +
 * 8 DATA + 1 STOP) are transmitted. This would be about 1ms with 9600bps.
 *
 * @note Calculation for the number of CPU cycles, executed for one bit time:
 * F_CPU/BAUDRATE = (3*1+2) + (2*1 + (NDLY-1)*4 + 2+1) + 6*1
 * NDLY - time required for transfer
 * 
 * (NDLY-1)*4 = F_CPU/BAUDRATE - 16
 * NDLY = (F_CPU/BAUDRATE-16)/4+1
 */
extern void putchar(uint8_t c);
extern void out_device(char *s);
#else
  #define tx_init()		
  #define putchar(A)		((void)(A))
#endif	/* DBG_UART_ENABLE */

#endif	/* DBG_PUTCHAR_H */

