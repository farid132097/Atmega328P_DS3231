

////////////Added for compatibility with other devices////////
uint8_t  RTC_Read(uint8_t addr);
void     RTC_Write(uint8_t addr, uint8_t data);
//////////////////////////////////////////////////////////////

void     RTC_Init(void);
void     RTC_Set_24H(void);
void     RTC_Set_12H_AM(void);
void     RTC_Set_12H_PM(void);

////////////RTC set functions//////////////////////////////
void     RTC_Set_Time(uint8_t hr, uint8_t min, uint8_t sec);
void     RTC_Set_Time_With_Format(uint8_t hr, uint8_t min, uint8_t sec, uint8_t hr_con, uint8_t AmPm);
void     RTC_Set_Date(uint8_t day, uint8_t date, uint8_t mon, uint16_t year);

////////////RTC get functions//////////////////////////////
uint8_t  RTC_Get_AmPm(void);
uint8_t  RTC_Get_Sec(void);
uint8_t  RTC_Get_Min(void);
uint8_t  RTC_Get_Hr(void);
uint8_t  RTC_Get_Day(void);
uint8_t  RTC_Get_Date(void);
uint8_t  RTC_Get_Month(void);
uint8_t  RTC_Get_Year(void);
uint8_t  RTC_Get_Error(void);


/*

Error Code Conventions

-----------------------------------------------------------------------
1st digit of Hex Error code represents error type, Read/Write Error

0x -> Write Errors
1x -> Read Errors

-----------------------------------------------------------------------
2nd digit of Hex Error code represents error in specific operation

x1 -> Second read/write error
x2 -> Minute read/write error
x3 -> Hour read/write error
x4 -> Day read/write error
x5 -> Date read/write error
x6 -> Month read/write error
x7 -> Year read/write error
-----------------------------------------------------------------------

*/










