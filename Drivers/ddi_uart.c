/***************************************************
 * Module name: ddi_siderail
 *
 * Copyright 2015 Hill-Rom
 * All Rights Reserved.
 *
 *  The information contained herein is confidential
 * property of Hill-Rom. The user, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Hill-Rom.
 *
 * First written on january 2015 by Jose Eslava.
 *
 * Module Description:
 * \brief		This module implements siderails controls driver interface
 */

#include "sysctl.h"                         // SysCtlPeripheralEnable
#include "pin_map.h"                        // GPIO_PC6_U5RX
#include "gpio.h"                           // GPIOPinConfigure
#include "hw_memmap.h"                      // GPIO_PORTC_BASE
#include "ddi_uart.h"

#define UART_DEBUG_BASE             UART5_BASE
#define	PORT_UART_DEBUG_PERIPH      SYSCTL_PERIPH_GPIOC

#define PORT_PINS_UART_DEBUG_BASE   GPIO_PORTC_BASE
#define PIN_RX_UART5                GPIO_PIN_6
#define PIN_TX_UART5                GPIO_PIN_7
#define PIN_RX_UART5_CONFIG         GPIO_PC6_U5RX 
#define PIN_TX_UART5_CONFIG         GPIO_PC7_U5TX
#define UART_BAUD_RATE              115200 //Default
//#define UART_BAUD_RATE              256000


void Ddi_uart_Init(void)
{			
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOC );
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_UART5 );
    GPIOPinConfigure ( PIN_RX_UART5_CONFIG );
    GPIOPinConfigure ( PIN_TX_UART5_CONFIG );
    GPIOPinTypeUART ( PORT_PINS_UART_DEBUG_BASE, PIN_RX_UART5 | PIN_TX_UART5 );

    UARTConfigSetExpClk ( UART_DEBUG_BASE,
                          HR_Sys_Clock_Freq,
                          UART_BAUD_RATE,
                          ( UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE ) );

    UARTEnable ( UART_DEBUG_BASE );
    UARTStdioConfig(5, UART_BAUD_RATE, HR_Sys_Clock_Freq);
}

/**
 * \file
 *
 *
 * !!File history
 *
||DATE||WRITTEN BY||COMMENT
|01/14/2015|J. Eslava|Initial version
 */

