#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "rtc.h"



void RTC_Init(void){
  I2C_Init();  
}

void RTC_Set_24H_AM(void){
  I2C_Write_Register(0x02,0b00000000);
}

void RTC_Set_12H_AM(void){
  I2C_Write_Register(0x02,0b01000000);
}

void RTC_Set_12H_PM(void){
  I2C_Write_Register(0x02,0b01100000);
}

void RTC_Set_Time(uint8_t hr, uint8_t min, uint8_t sec){
  uint8_t tmp0=0,tmp1=0,tmp2=0;
  tmp0=I2C_Read_Register(0x02);
  tmp0&=0x60;
  tmp1=hr/10;
  tmp2=hr%10;
  if(tmp0 & (1<<6)){                    //12H Mode
    if(hr<=12){
	  I2C_Write_Register(0x02,tmp0|(tmp1<<4)|tmp2);
	}else{
	  //handle error
	}
  }else{                               //24H 
    tmp0&=0x40;
	I2C_Write_Register(0x02,(tmp1<<4)|tmp2);
  }
  
  tmp1=min/10;
  tmp2=min%10;
  if(min<=59){
    I2C_Write_Register(0x01,(tmp1<<4)|tmp2);
  }else{
    //handle error
  }
  
  tmp1=sec/10;
  tmp2=sec%10;
  if(sec<=59){
    I2C_Write_Register(0x00,(tmp1<<4)|tmp2);
  }else{
    //handle error
  }
}

uint8_t RTC_Get_AmPm(void){        //0:AM, 1:PM
  uint8_t tmp0=I2C_Read_Register(0x02);
  if(tmp0 & (1<<5)){
    return 1;
  }else{
    return 0;
  }
}

uint8_t RTC_Get_Hr(void){
  uint8_t tmp0=0, hr=0;
  tmp0=I2C_Read_Register(0x02);
  if(tmp0 & (1<<6)){               //12H
    hr = ((tmp0 & (1<<4))>>4);
	hr*= 10;
	hr+= (tmp0 & 0x0F);
  }else{                           //24H
    hr = (tmp0 & 0x30)>>4;
    hr*= 10;
	hr+= (tmp0 & 0x0F);
  }
  return hr;
}

uint8_t RTC_Get_Min(void){
  uint8_t tmp0=0, min=0;
  tmp0=I2C_Read_Register(0x01);
  min = ((tmp0 & 0x70)>>4);
  min*= 10;
  min+= (tmp0 & 0x0F);
  return min;
}

uint8_t RTC_Get_Sec(void){
  uint8_t tmp0=0, sec=0;
  tmp0=I2C_Read_Register(0x00);
  sec = ((tmp0 & 0x70)>>4);
  sec*= 10;
  sec+= (tmp0 & 0x0F);
  return sec;
}