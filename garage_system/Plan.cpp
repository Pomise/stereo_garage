#include "Plan.h"
#include "Data_WR.h"

/******************************定义变量*********************************/
uchar * Park_Table ;
uchar Current_Port[Park_Num];
/********************************************************************/

uchar Empty_Num(){                         //判断空车位数量
  uchar n=0;
  for(uchar i=0;i<Car_Num;i++){
    if ((Park_Table[i] & 0x80) == 0)
      n++;
  }
  return n;
}

void Clear_Prot(ucar port){
  Write_clear(port);
}


bool Judge_Can(){                       //判断能否存车
  for(uchar i=0;i<Car_Num;i++){
    if(Park_Table[i]&0x80 == 0)
      return true;
  }
  return false;
}

uchar Judge_Port(){
  for(uchar i=0;i<Car_Num;i++){
    if(Park_Table[i]&0x80 == 0)
      break;
  }
  return Park_Table[i]&0x7F;
}

uchar Judge_Current(ucahr Garage){
  return Read_Current(Garage);
}


/**判断是存车还是取车（返回一个数字<Car_Num则是取车，数字为车位号）*******************************/ 

uchar Juge_UID(uchar * ID){
  uchar *Temp_ID;
  uchar i;
  for(i=0;i<Car_Num;i++){
    if(Park_Table[i]&0x80 == 1){
      Temp_ID = Read_UID(i)
      for(uchar j=0;j< UID_Size;j++){
        if(Temp_ID[j] == ID[j]){
          if (j == UID_Size-1)
            return Park_Table[i]&0x7F;
        }
        else
          break;
      }
    }
  }
  return i;                      //i此时的值等于CarNum.
}