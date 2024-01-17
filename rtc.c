#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "rtc.h"

#define ENABLE_ERROR_HANDLER

uint8_t RTC_Error=0;


//edit below functions for compatibility with other devices//

uint8_t RTC_Read(uint8_t addr){
  return I2C_Read_Register(addr);
}

void RTC_Write(uint8_t addr, uint8_t data){
  I2C_Write_Register(addr,data);
}

/////////////////////////////////////////////////////////////






void RTC_Init(void){
  I2C_Init();  
}

void RTC_Set_24H(void){
  RTC_Write(0x02,0b00000000);
}

void RTC_Set_12H_AM(void){
  RTC_Write(0x02,0b01000000);
}

void RTC_Set_12H_PM(void){
  RTC_Write(0x02,0b01100000);
}


void RTC_Set_Time(uint8_t hr, uint8_t min, uint8_t sec){
  uint8_t tmp0=0,tmp1=0,tmp2=0, error=0;
  uint8_t hr_reg=0, min_reg=0, sec_reg=0;
  
  //write sec
  tmp1=sec/10;
  tmp2=sec%10;
  if(sec<=59){
    sec_reg=(tmp1<<4)|tmp2;
  }else{
    error=0x01;
  }
  
  //write min
  tmp1=min/10;
  tmp2=min%10;
  if(min<=59){
    min_reg=(tmp1<<4)|tmp2;
  }else{
    error=0x02;
  }
  
  //write hour
  tmp0=RTC_Read(0x02);
  tmp0&=0x60;
  tmp1=hr/10;
  tmp2=hr%10;
  if(tmp0 & (1<<6)){          //12H
    if(hr<=12){
	  hr_reg=tmp0|(tmp1<<4)|tmp2;
	}else{
	  error=0x03;
	}
  }else{                      //24H 
    tmp0&=0x40;
	hr_reg=(tmp1<<4)|tmp2;
  }
  
  
  if(error==0){
    RTC_Write(0x02,hr_reg);
	RTC_Write(0x01,min_reg);
	RTC_Write(0x00,sec_reg);
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
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


void RTC_Set_Date(uint8_t day, uint8_t date, uint8_t mon, uint16_t year){
  uint8_t tmp0=0,tmp1=0, error=0;
  uint8_t day_reg=0, date_reg=0, mon_reg=0, year_reg=0;
  
  //write day
  if( (day>=1) && (day<=7) ){
	day_reg=day;
  }else{
    error=0x04;
  }
  
  //write date
  tmp0  = date/10;
  tmp0<<=4;
  tmp1  = date%10;
  tmp1 |= tmp0;
  if( ((mon==1)||(mon==3)||(mon==5)||(mon==7)||(mon==8)||(mon==10)||(mon==12)) && ((date>=1) && (date<=31)) ){
    date_reg=tmp1;
  }
  else if( ((mon==4)||(mon==6)||(mon==9)||(mon==11)) && ((date>=1) && (date<=30)) ){
    date_reg=tmp1;
  }
  else if( mon==2 ){
    if(year%4==0){                  //leap year
      if((date>=1) && (date<=29)){
        date_reg=tmp1;
	  }else{
	    error=0x05;
	  }
    }else{
      if((date>=1) && (date<=28)){
	    date_reg=tmp1;
	  }else{
	    error=0x05;
	  }
    }
  }
  else{   //Month->out of range
    error=0x05;
  }
  
  if( (mon>=1) && (mon<=12) ){
    tmp0  = mon/10;
    tmp0<<=4;
    tmp1  = mon%10;
    tmp1 |= tmp0;
	date_reg = tmp1;
  }else{
    error=0x06;
  }
  
  //write year
  if(year<=9999){
    if(year>99){
      year/=100;
    }
    tmp0 = date/10;
	tmp0<<=4;
    tmp1 = date%10;
	tmp1|= tmp0;
	tmp1 = year_reg;
  }else{
    error=0x07;
  }
  
  
  if(error==0){
    RTC_Write(0x06,year_reg);
	RTC_Write(0x05,mon_reg);
	RTC_Write(0x04,date_reg);
    RTC_Write(0x03,day_reg);
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
}
  

  
uint8_t RTC_Get_AmPm(void){  //0:AM, 1:PM
  uint8_t tmp0=I2C_Read_Register(0x02);
  if(tmp0 & (1<<5)){
    return 1;
  }else{
    return 0;
  }
}



uint8_t RTC_Get_Sec(void){
  uint8_t tmp0=0, sec=0, error=0;
  tmp0=RTC_Read(0x00);
  sec = ((tmp0 & 0x70)>>4);
  sec*= 10;
  sec+= (tmp0 & 0x0F);
  if(sec>59){
    error=0x11;
	sec=0;
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
  return sec;
}


uint8_t RTC_Get_Min(void){
  uint8_t tmp0=0, min=0, error=0;
  tmp0=RTC_Read(0x01);
  min = ((tmp0 & 0x70)>>4);
  min*= 10;
  min+= (tmp0 & 0x0F);
  if(min>59){
    error=0x12;
	min=0;
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
  return min;
}


uint8_t RTC_Get_Hr(void){
  uint8_t tmp0=0, hr=0, error=0;
  tmp0=RTC_Read(0x02);
  if(tmp0 & (1<<6)){           //12H
    hr = ((tmp0 & (1<<4))>>4);
	hr*= 10;
	hr+= (tmp0 & 0x0F);
  }else{                       //24H
    hr = (tmp0 & 0x30)>>4;
    hr*= 10;
	hr+= (tmp0 & 0x0F);
  }
  if((tmp0 & 0x40) && (hr>12)){
    error=0x13;
	hr=0;
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
  return hr;
}


uint8_t RTC_Get_Day(void){
  uint8_t tmp0=0, day=0, error=0;
  tmp0=RTC_Read(0x03);
  day = (tmp0 & 0x07);
  if((day<1) && (day>7)){
    error=0x14;
	day=0;
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
  return day;
}


uint8_t RTC_Get_Date(void){
  uint8_t tmp0=0, date=0, error=0;
  tmp0=RTC_Read(0x04);
  date = ((tmp0 & 0x30)>>4);
  date*= 10;
  date+= (tmp0 & 0x0F);
  if((date<1) && (date>31)){
    error=0x15;
	date=0;
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
  return date;
}


uint8_t RTC_Get_Month(void){
  uint8_t tmp0=0, mon=0, error=0;
  tmp0=RTC_Read(0x05);
  mon = ((tmp0 & 0x10)>>4);
  mon*= 10;
  mon+= (tmp0 & 0x0F);
  if((mon<1) && (mon>12)){
    error=0x16;
	mon=0;
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
  return mon;
}

uint8_t RTC_Get_Year(void){
  uint8_t tmp0=0, year=0, error=0;
  tmp0=RTC_Read(0x06);
  year = ((tmp0 & 0xF0)>>4);
  year*= 10;
  year+= (tmp0 & 0x0F);
  if(year>99){
    error=0x17;
	year=0;
  }
  
  #ifdef ENABLE_ERROR_HANDLER
  RTC_Error=error;
  #endif
  
  return year;
}



uint8_t RTC_Get_Error(void){
  uint8_t error=0;
  #ifdef ENABLE_ERROR_HANDLER
  error=RTC_Error;
  #endif
  return error;
}