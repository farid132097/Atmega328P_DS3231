

#define  I2C_SCL_DDR  DDRC
#define  I2C_SCL_PORT PORTC
#define  I2C_SCL_PIN  PINC
#define  I2C_SCL_bp   5

#define  I2C_SDA_DDR  DDRC
#define  I2C_SDA_PORT PORTC
#define  I2C_SDA_PIN  PINC
#define  I2C_SDA_bp   4                      

void     I2C_Struct_Init(void);
void     I2C_Half_Bit_Delay(void);
void     I2C_Bit_Delay(void);
void     I2C_Guard_Delay(void);

void     I2C_SCL_Set_DD(uint8_t state);
void     I2C_SCL_Set_Output_LL(uint8_t state);
void     I2C_SCL_Set_Output(uint8_t state);
uint8_t  I2C_SCL_Get_State(void);

void     I2C_SDA_Set_DD(uint8_t state);
void     I2C_SDA_Set_Output_LL(uint8_t state);
void     I2C_SDA_Set_Output(uint8_t state);
uint8_t  I2C_SDA_Get_State(void);

void     I2C_SCL_Reset_State(void);
void     I2C_SDA_Reset_State(void);
void     I2C_GPIO_Init(void);

void     I2C_Start(void);
void     I2C_Stop(void);
void     I2C_Data_Send(uint8_t data);
uint8_t  I2C_Data_Receive(void);
void     I2C_Set_Ack(void);
void     I2C_Set_Nack(void);
uint8_t  I2C_Get_Ack(void);

uint8_t  I2C_Send_Device_Address(uint8_t address);
uint8_t  I2C_Get_Device_Address(void);

uint8_t  I2C_Read_Register(uint8_t reg);
void     I2C_Write_Register(uint8_t reg, uint8_t val);
void     I2C_Init(void);
