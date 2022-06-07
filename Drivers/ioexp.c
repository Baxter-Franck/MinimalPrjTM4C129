#include "ioexp.h"

#include <stdint.h>
#include <stdbool.h>
#include "defines_HR.h"
#include "sysctl.h"
#include "pin_map.h"
#include "gpio.h"
#include "hw_ssi.h"
#include "hw_i2c.h"
#include "hw_gpio.h"
#include "ssi.h"
#include "i2c.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "rom_map.h"
#include "rom.h"

IOExp_Data_t IoExp_Data;
IOExp_Model_STS_t IOExp_Model_STS;

void Ddi_ioexp_Init(void)
{		
    //Initialize the data structure
    IoExp_Data.blocks.Data_in = 0x00;
    IoExp_Data.blocks.Data_out = 0x00;
    IOExp_Model_STS.data = 0x00;
    SysCtlPeripheralEnable(PORT_PINS_I2C_IOEXP_PERIPH);
    GPIOPinConfigure(PIN_SCL_IOEXP_CONFIG);  //Configures the alternate function(I2C) of a GPIO pin.
    GPIOPinConfigure(PIN_SDA_IOEXP_CONFIG);	 //Configures the alternate function(I2C) of a GPIO pin.
    GPIOPinTypeI2CSCL(PORT_PINS_I2C_IOEXP_BASE, PIN_SCL_IOEXP);
    GPIOPinTypeI2C(PORT_PINS_I2C_IOEXP_BASE, PIN_SDA_IOEXP);
    SysCtlPeripheralEnable(PORT_I2C_IOEXP_PERIPH);
    I2CMasterInitExpClk(I2C1_BASE, HR_Sys_Clock_Freq, false);

    //clear I2C FIFOs
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;

    //Init Port0 to input
    Ddi_i2c_SendI2C_IOEXP((uint8_t)ADDR_IO_EXP_1, (uint8_t)0xFF, CONF_PORT0);
    SysCtlDelay(100);
    //Init Port1 to output
    Ddi_i2c_SendI2C_IOEXP((uint8_t)ADDR_IO_EXP_1, (uint8_t)0x00, CONF_PORT1);
    SysCtlDelay(100);
    //Init values to Port1
    Ddi_i2c_SendI2C_IOEXP((uint8_t)ADDR_IO_EXP_1, (uint8_t)0x8F, PORT1_OUT);	//Led OFF + 5V_SC_EN disable
    SysCtlDelay(100);
}

uint8_t Ddi_i2c_SendI2C_IOEXP(uint8_t slave_addr, uint32_t  valToSend, uint8_t reg)
{
    uint8_t success = TRUE;
    uint16_t timeOutI2C = 0;

    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);
    I2CMasterDataPut(I2C1_BASE, reg);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    timeOutI2C = 0;
    while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;
 
    I2CMasterDataPut(I2C1_BASE,(uint8_t)valToSend);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    timeOutI2C = 0;
    while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;
  
    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;
    return success;
}

void on_off(bool b)
{
	if(b)
	{
		   Ddi_i2c_SendI2C_IOEXP((uint8_t)ADDR_IO_EXP_1, (uint8_t)0x00, PORT1_OUT);	//Led OFF + 5V_SC_EN disable
	}else{
		   Ddi_i2c_SendI2C_IOEXP((uint8_t)ADDR_IO_EXP_1, (uint8_t)0xFF, PORT1_OUT);	//Led OFF + 5V_SC_EN disable
	}
	  SysCtlDelay(100);
}

