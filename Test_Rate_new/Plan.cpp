#include "Plan.h"
#include "Data_WR.h"
#include "Arduino.h"
#include <math.h>

/******************************定义变量*********************************/
uchar * Park_Table ;
uchar Current_Port[Park_Num];
/********************************************************************/

void Plan_Init(){
  Park_Table = Read_Table();
}

void Record_Car_Data(uchar port,uchar *UID){
  Write_Data(port,UID);
}

void Record_Garage_Current(uchar Port){
  Write_Current(Port);
}

uchar Empty_Num(){                         //判断空车位数量
  uchar n=0;
  for(uchar i=0;i<Car_Num;i++){
    if ((Park_Table[i] & 0x80) == 0)
      n++;
  }
  return n;
}

void Clear_Port(uchar port){
  Write_Clear(port);
}

bool Judge_Can(){                       //判断能否存车
  uchar i;
  for(i=0;i<Car_Num;i++){
    if((Park_Table[i]&0x80)== 0){
      return true;
    }
  }
  Serial.print(i);
  return false;
}

uchar Judge_Port(){
  uchar i,Garage;
  uchar Current;
  uchar n = 0;
  uchar temp = 0;           //用于排序
  for(i=0;i<Car_Num;i++){
    if((Park_Table[i]&0x80) == 0)
      break;
  }
  Serial.print("Plan:\ni:");
  Serial.print(i);
  Garage = i/Garage_Volume;
  Current = Judge_Current(Garage);
  Serial.print(Current);
  if((Park_Table[Current]&0x80) == 0)
    return Park_Table[Current]&0x7F;
  for(i=1;i<=Garage_Volume/2;i++){
    temp = Current + i;
    if(temp >= Garage*Garage_Volume+Garage_Volume)
      temp = temp -Garage_Volume;
    if((Park_Table[temp]&0x80) == 0)
      return Park_Table[temp]&0x7F;

    temp = Current - i;
    if(temp < Garage*Garage_Volume)
      temp = temp + Garage_Volume;
    if((Park_Table[temp]&0x80) == 0)
      return Park_Table[temp]&0x7F;
  }
  return Park_Table[temp]&0x7F;        //用不到
}

uchar Judge_Current(uchar Garage){
  return Read_Current(Garage);
}

/**判断是存车还是取车（返回一个数字<Car_Num则是取车，数字为车位号）*******************************/ 

uchar Juge_UID(uchar * ID){
  uchar *Temp_ID;
  uchar i;
  for(i=0;i<Car_Num;i++){
    if((Park_Table[i]&0x80) == 0x80){
      Temp_ID = Read_UID(i);
      for(uchar j=0;j< UID_Size;j++){
        if(Temp_ID[j] == ID[j]){
          if (j == UID_Size-1){
            return (Park_Table[i]&0x7F);
          }
        }
        else
          break;
      }
    }
  }
  return i;                      //i此时的值等于CarNum.
}
