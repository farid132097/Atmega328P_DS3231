#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"
#include "i2c.h"
#include "rtc.h"

int main(void){

  DDRD  |= (1<<4);
  PORTD &=~(1<<4);
  
  RTC_Init();
  debug_init();
  debug_tx_text_nl("Debug Started");
  
  //arguments hr,min,sec, 12h/24h, Am/Pm
  //12H:1, 24H:0
  //PM :1, AM :0
  //RTC_Set_Time_With_Format(3, 36, 0, 1, 1);
  
  //arguments day,date,mon, year
  //RTC_Set_Date(3, 16, 1, 24);
  
  while(1){
    
    debug_tx_number_cm(RTC_Get_Year());
	debug_tx_number_cm(RTC_Get_Month());
	debug_tx_number_cm(RTC_Get_Date());
	debug_tx_number_cm(RTC_Get_Day());
	debug_tx_number_cm(RTC_Get_Hr());
	debug_tx_number_cm(RTC_Get_Min());
	debug_tx_number_sp(RTC_Get_Sec());

	if(RTC_Get_AmPm()){
	  debug_tx_text_nl("PM");
	}else{
	  debug_tx_text_nl("AM");
	}
	_delay_ms(500);
	
  }
}