

void     RTC_Init(void);
void     RTC_Set_24H(void);
void     RTC_Set_12H_AM(void);
void     RTC_Set_12H_PM(void);
void     RTC_Set_Time(uint8_t hr, uint8_t min, uint8_t sec);
void     RTC_Set_Time_With_Format(uint8_t hr, uint8_t min, uint8_t sec, uint8_t hr_con, uint8_t AmPm);
uint8_t  RTC_Get_AmPm(void);
uint8_t  RTC_Get_Hr(void);
uint8_t  RTC_Get_Min(void);
uint8_t  RTC_Get_Sec(void);
uint8_t  RTC_Get_Error(void);