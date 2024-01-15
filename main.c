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
  
  //RTC_Set_12H_AM();
  //RTC_Set_Time(11,59,30);
  
  while(1){
    
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