#include "Init.h"

/******************************定义变量*********************************/
byte * Park_Table = Read_Table();
uchar Current_Port[Park_Num];
/********************************************************************/

void Data_Update(){
  Read_table();
}

uchar Empty_Num(){                         //判断空车位数量
  uchar n=0;
  for(uchar i=0;i<Car_Num;i++){
    if ((Park_Table[i] & 0x80) == 0)
      n++;
  }
  return n;
}

uchar Judge_Empty_Port(){                     //判断应该存放在哪个车位
  uchar i;
  for(i=0;i<Car_Num;i++){
    if((Park_Table[i] & 0x80) == 0)
      break;
  }
  return i;
}
/*************************************can_move*************************/ 

