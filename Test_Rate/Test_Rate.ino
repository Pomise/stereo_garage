 #include <HardwareSerial.h>
#include "Init.h"
#include "Plan.h"
#include "MFRC522.h"
#include "Move_Control.h"
#include "Data_WR.h"

/*******************定义相应的变量************************/
byte* CardID;
byte PARK;
/********************************************************/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  Serial.print("Start:\n");
  Clear();
  Move_Init();
  Plan_Init();
}

void loop() {
  while(1){
    PARK = Car_Num;                             //初始化数据，Car_Num大于最大车位编号
    MFRC522_Init();                            //打开IC卡检测
    while(1){
      Serial.print(Empty_Num());           //输出空车数量.
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
      delay(300);
    }
    PARK = Juge_UID(CardID);
    if(PARK == Car_Num){        //表示要存车
      Serial.print("Let Car\n");
      if(Judge_Can()){              //表示可以存车，开始存车运动.
        PARK = Judge_Port();          //获取应该停入的停车位。
        Serial.print(PARK);
        Record_Car_Data(PARK,CardID);      //写入存车数据,并更新停车列表
        //Fixture_Clamp();                   //夹具夹紧车.
        //Serial.print("Clamp Fixture\n");
        Move_Up(PARK);               //平台向上运动，同时相应的车库圆盘旋转。
        Serial.print("Move UP\n");
        Record_Garage_Current(PARK);         //记录车库当前停车位变化.整个存车过程完成。
//        Fixture_Front();             //当平台和车库运动完成后夹具将车送往车位。
//        Serial.print("Fixture Front\n");
//        Fixture_Relax();             //放松夹具。
//        Serial.print("Fixture Relax\n");
//        Fixture_Back();                 //夹具返回.
//        Serial.print("Fixture Back\n");
//        Move_Down();                    //完成放车运动.
//        Serial.print("Move Down\n");
      }
      else
        Serial.print("NO PARK_PORT");
    }
    else{                   //表示要取车,当前PARK既是需要取车的车位.
      Serial.print("Get Car\n");
      Clear_Port(PARK);
      Serial.print("Clear_Port\n");
      Move_Up(PARK);
      Serial.print("Move_UP OK\n");
//      Fixture_Front();
//      Serial.print("Fixture Front\n");
//      Fixture_Clamp();
//      Serial.print("Fixture_Clamp\n");
//      Fixture_Back();
//      Serial.print("Fixture back\n");
//      Move_Down();
//      Serial.print("Move Down\n");
//      Fixture_Relax();
        Record_Garage_Current(PARK);
    }
    delay(1000); 
  }

}
}
