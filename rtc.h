

void     RTC_Init(void);
void     RTC_Set_24H_AM(void);
void     RTC_Set_12H_AM(void);
void     RTC_Set_12H_PM(void);
void     RTC_Set_Time(uint8_t hr, uint8_t min, uint8_t sec);
uint8_t  RTC_Get_AmPm(void);
uint8_t  RTC_Get_Hr(void);
uint8_t  RTC_Get_Min(void);
uint8_t  RTC_Get_Sec(void);