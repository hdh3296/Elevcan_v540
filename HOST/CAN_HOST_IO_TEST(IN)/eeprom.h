

extern unsigned char  EEPROM_write_Ready(void);
extern unsigned char  EEPROM_write_Enable(void);
extern unsigned char  EEPROM_write_Disable(void);

/*
extern void startWriting( unsigned int Eep_Command );
extern void EraseEepromWard( unsigned int Eep_Addr );
extern void WriteDataEepromWard( unsigned int Eep_Addr ,unsigned int Eep_Data );
extern unsigned char  EEPROM_read_Wait(void);
*/

extern unsigned int   EEPROM_Read_Word(unsigned int Eep_Addr);
extern unsigned int   EEPROM_Write_Word(unsigned int Eep_Adr,unsigned int Eep_Data);

extern unsigned char EEPROM_Read_Byte(unsigned int Eep_Addr);
extern unsigned int  EEPROM_Write_Byte(unsigned int Eep_Adr,unsigned int Eep_Data);


