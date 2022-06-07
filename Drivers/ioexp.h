#ifndef __DDI_IOEXP_H__
#define __DDI_IOEXP_H__ 

#include <stdint.h>
#include "defines_HR.h"

#define PORT_PINS_I2C_IOEXP_BASE			GPIO_PORTG_BASE
#define PORT_PINS_I2C_IOEXP_PERIPH			SYSCTL_PERIPH_GPIOG
#define PORT_I2C_IOEXP_PERIPH				SYSCTL_PERIPH_I2C1

#define PIN_SCL_IOEXP						GPIO_PIN_0
#define PIN_SDA_IOEXP						GPIO_PIN_1

#define PIN_SCL_IOEXP_CONFIG	 			GPIO_PG0_I2C1SCL //Alternate function of a GPIO pin PG0
#define PIN_SDA_IOEXP_CONFIG	 			GPIO_PG1_I2C1SDA //Alternate function of a GPIO pin PG1

#define PORT_IN_NI2C_INT_IOEXP				GPIO_PORTL_BASE										
#define PIN_IN_NI2C_INT_IOEXP				GPIO_PIN_2							
#define	PORT_NI2C1_INT_PERIPH				SYSCTL_PERIPH_GPIOL

#define ADDR_IO_EXP_1	0x24 //Addr for TCA9535PWR	A0=0, A1=0, A2=1
#define PORT0_IN	0x00
#define PORT1_OUT	0x03
#define CONF_PORT0 	0x06
#define CONF_PORT1 	0x07

typedef union _IOExp_Model_STS_t
{
	uint8_t data;
	
	struct
	{
		uint8_t error_HW : 1;
		uint8_t unused : 7;
	}bits;
}IOExp_Model_STS_t;

typedef union _IOExp_Data_t
{
	struct
	{
		uint8_t Data_in : 8;
		uint8_t Data_out : 8;
	}blocks;
	
	struct
	{
		uint8_t in_Siderail_FT_Right : 1,   ///<
			in_Siderail_FT_Left : 1,        ///<
			in_Siderail_HD_Right : 1,       ///<
			in_Siderail_HD_Left: 1,         ///<
			in_plus_sw : 1,                 ///<
			in_minus_sw : 1,                ///<
			in_cal_sw : 1,                  ///<
			in_5V_SC_error : 1;             ///< scale power error ( 1 no error / 0 error active )
		
		uint8_t out_LD_BEAM1 : 1,
			out_LD_BEAM2 : 1,
			out_LD_BEAM3 : 1,
			out_LD_BEAM4 : 1,
			out_YELLOW_LED_ON : 1,
			out_RED_LED_ON : 1,
			out_GREEN_LED_ON : 1,
			out_5V_SC_EN : 1;
	}bits;
}IOExp_Data_t;

void Ddi_ioexp_Init(void);
uint8_t Ddi_i2c_SendI2C_IOEXP(uint8_t slave_addr, uint32_t  valToSend, uint8_t reg);
//extern uint8_t Ddi_i2c_ReceiveI2C_IOEXP(uint32_t * PData, uint32_t slave_addr, uint8_t reg);
//uint8_t Ddi_i2c_read1byte(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData);
void on_off(bool b);

extern IOExp_Data_t IoExp_Data;
extern IOExp_Model_STS_t IOExp_Model_STS;
#endif
