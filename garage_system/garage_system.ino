#include <HardwareSerial.h>
#include "Init.h"
#include "Plan.h"
#include "MFRC522.h"
#include "Move_Control.h"

/*******************定义相应的变量************************/
byte* CardID;
byte* PARK;
/********************************************************/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  Move_Init();
  Plan_Init();
}

void loop() {
  while(1){
    PARK = Car_Num;                             //初始化数据，Car_Num大于最大车位编号
    MFRC522_Init();                            //打开IC卡检测
    while(1){                               
      if(Check_Card()){
        CardID=Get_CardID();
        Stop_Check;
        for(char i=0;i<UID_Size;i++){
          Serial.print(CardID[i] < 0x10 ? " 0" : " ");
          Serial.print(CardID[i],HEX);
        }
        break;
      }
      delay(100);
    }
    PARK = Juge_UID(CardID);
    if(PARK > Car_Num){        //表示要存车
      if(Judge_Can()){              //表示可以存车，开始存车运动.
        PARK = Judge_Port();          //获取应该停入的停车位。
        Record_Car_Data(PARK,CardID);      //写入存车数据,并更新停车列表
        Fixture_Clamp();                   //夹具夹紧车.
        Move_Up(PARK);               //平台向上运动，同时相应的车库圆盘旋转。
        Fixture_Front();             //当平台和车库运动完成后夹具将车送往车位。
        Fixture_Relax();             //放松夹具。
        Fixture_Back();                 //夹具返回.
        Move_Down();                    //完成放车运动.
        Record_Garage_Current(PARK);         //记录车库当前停车位变化.整个存车过程完成。
      }
      else
        Serial.print("NO PARK_PORT");
    }
    else{                   //表示要取车,当前PARK既是需要取车的车位.
      Clear_Port(PARK);
      Move_Up(PARK);
      Fixture_Front();
      Fixture_Clamp();
      Fixture_Back();
      Move_Down();
      Fixture_Relax();
      Record_Garage_Current(PARK);
    }
    delay(1000);
  }

}
