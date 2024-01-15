#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "rtc.h"



void RTC_Init(void){
  I2C_Init();  
}

void RTC_Set_24H(void){
  I2C_Write_Register(0x02,0b00000000);
}

void RTC_Set_12H_AM(void){
  I2C_Write_Register(0x02,0b01000000);
}

void RTC_Set_12H_PM(void){
  I2C_Write_Register(0x02,0b01100000);
}

void RTC_Set_Time(uint8_t hr, uint8_t min, uint8_t sec){
  uint8_t tmp0=0,tmp1=0,tmp2=0, error=0;
  uint8_t hr_reg=0, min_reg=0, sec_reg=0;
  tmp0=I2C_Read_Register(0x02);
  tmp0&=0x60;
  tmp1=hr/10;
  tmp2=hr%10;
  if(tmp0 & (1<<6)){          //12H
    if(hr<=12){
	  hr_reg=tmp0|(tmp1<<4)|tmp2;
	}else{
	  error=0x01;
	}
  }else{                      //24H 
    tmp0&=0x40;
	hr_reg=(tmp1<<4)|tmp2;
  }
  
  tmp1=min/10;
  tmp2=min%10;
  if(min<=59){
    min_reg=(tmp1<<4)|tmp2;
  }else{
    error=0x02;
  }
  
  tmp1=sec/10;
  tmp2=sec%10;
  if(sec<=59){
    sec_reg=(tmp1<<4)|tmp2;
  }else{
    error=0x03;
  }
  
  if(error==0){
    I2C_Write_Register(0x02,hr_reg);
	I2C_Write_Register(0x01,min_reg);
	I2C_Write_Register(0x00,sec_reg);
  }
}

void RTC_Set_Time_With_Format(uint8_t hr, uint8_t min, uint8_t sec, uint8_t hr_con, uint8_t AmPm){
  if(hr_con==0){
    RTC_Set_24H();
  }else if(hr_con==1){
    if(AmPm==0){
	  RTC_Set_12H_AM();
	}else if(AmPm==1){
	  RTC_Set_12H_PM();
	}
  }
  RTC_Set_Time( hr, min, sec);
}
  
uint8_t RTC_Get_AmPm(void){  //0:AM, 1:PM
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
  if(tmp0 & (1<<6)){           //12H
    hr = ((tmp0 & (1<<4))>>4);
	hr*= 10;
	hr+= (tmp0 & 0x0F);
  }else{                       //24H
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