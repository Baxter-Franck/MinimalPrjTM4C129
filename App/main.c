/***************************************************
 *  Include section
 ***************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "tm4c1294kcpdt.h"
#include "sysctl.h"
#include "gpio.h"
#include "hw_memmap.h"
#include "pin_map.h"
#include "uartstdio.h"
#include "ioexp.h"
#include "ddi_uart.h"

#define CLEAR_LOG(...) UARTprintf("\33\143")
#define LOG(...) UARTprintf("[MAIN] ");UARTprintf(__VA_ARGS__);UARTprintf("\n",0)

void Ddi_uart_Init(void);
void sleep(int sec);
void msleep(int msec);

uint32_t HR_Sys_Clock_Freq;
uint32_t i=0; 

//*****************************************************************************
//                              MAIN
//*****************************************************************************
int main(void)
{
	
	i=0;
    // Setup the system clock to run at 80 Mhz from PLL with crystal reference
    HR_Sys_Clock_Freq = SysCtlClockFreqSet( 
            SYSCTL_OSC_MAIN |
            SYSCTL_USE_PLL  |
            SYSCTL_XTAL_25MHZ |
            SYSCTL_CFG_VCO_480 ,
            80000000
    );

    Ddi_uart_Init();            // init uart driver
	Ddi_ioexp_Init();

	CLEAR_LOG();
    LOG( " ******************************** Main Start ******************************** %d", __LINE__);
    LOG("Start execution");

    while(1)
    {
		i++;
		(i%2==0)?on_off(true):on_off(false);
        LOG("Led => %d",i%2);
		msleep(500);
		
		if(i==100)
			i=0;
    }
}

void sleep(int sec)
{
	int oneSec = HR_Sys_Clock_Freq/3;
	SysCtlDelay(sec * oneSec);
}

void msleep(int msec)
{
	int oneSec = HR_Sys_Clock_Freq/3000;
	SysCtlDelay(msec * oneSec);
}

