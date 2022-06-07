/**

	*	HR900 Access Interface board
	*	\file Device driver interface header file for spi port
		\brief 

*/

#ifndef __DDI_UART_H__
#define __DDI_UART_H__

/**************************************************
* \name			 	void Ddi_uart_Init(void)
* \author			Tifaine Guyot
* \date				May 2017
* \brief			UART5  initialization
* \details		it initializes UART5 peripheral and microcontroller pins as follow:
	-	Clock frequency: 9.6Kbps.
	-	8 data bits, 1 stop bit, parity none
	-	Microcontroller pin configuration:
			o	Port C – pin 6: UART Rx.
			o	Port C – pin 7: UART Tx.
**************************************************/
void Ddi_uart_Init(void);

#endif // __DDI_UART_H__
