#include "Init.h"


uchar* Read_Table();
uchar *Read_UID(uchar port);
uchar Read_Current(uchar Garage);
void Write_Data(uchar port,uchar *UID);
void Write_Clear(uchar port);
void Write_Current(uchar port);
void Clear();