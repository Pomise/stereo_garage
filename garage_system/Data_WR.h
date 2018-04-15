#include "Init.h"
#include "EEPROM.h"


uchar* Read_Table();
bool Judge_Can();
uchar Judge_Port();
bool Write_Port(uchar port,uchar *UID);
bool Write_Current(uchar port);
