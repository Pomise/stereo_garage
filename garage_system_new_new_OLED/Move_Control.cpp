#include "Move_Control.h"
#include "Plan.h"
#include <Servo.h>
#include <Arduino.h>
#include <math.h>

Servo myservo;
int pos = 0;

/***********************初始化运动控制************************************/
void Move_Init(){
  Enable_Init();           //L298N使能
  Disk_Init();
  Disk_Pause(4);          //暂停所有的圆盘车库
  Step_Init();
  Fixture_Init();
  Servo_Init();
  Key_Init();
}
void Site_Reset(){
  Fixture_Relax();
  Move_Down();
  Fixture_Back();
  //Disk_Rest();
}

void Key_Init(){
  pinMode(Key_Pin,INPUT);

  digitalWrite(Key_Pin,HIGH);
}
void Enable_Init(){
  pinMode(Fixture_Enable,OUTPUT);
  pinMode(Disk1_Enable,OUTPUT);
  pinMode(Disk2_Enable,OUTPUT);
  pinMode(Disk3_Enable,OUTPUT);

  digitalWrite(Fixture_Enable,HIGH);
  digitalWrite(Disk1_Enable,HIGH);
  digitalWrite(Disk2_Enable,HIGH);
  digitalWrite(Disk3_Enable,HIGH);
}
void Disk_Init(){
  pinMode(Disk1_motor_1,OUTPUT);
  pinMode(Disk1_motor_2,OUTPUT);
  pinMode(Disk1_limit,INPUT);
  pinMode(Disk1_limit,LOW);

  pinMode(Disk2_motor_1,OUTPUT);
  pinMode(Disk2_motor_2,OUTPUT);
  pinMode(Disk2_limit,INPUT);
  pinMode(Disk2_limit,LOW);

  pinMode(Disk3_motor_1,OUTPUT);
  pinMode(Disk3_motor_2,OUTPUT);
  pinMode(Disk3_limit,INPUT);
  pinMode(Disk3_limit,LOW);
}

void Step_Init(){
  pinMode(STEP_PIN,OUTPUT);
  pinMode(DIR_PIN,OUTPUT);
  pinMode(ENABLE_PIN,OUTPUT);
  pinMode(Step_Limit_Max,INPUT);
  pinMode(Step_Limit_Second,INPUT);
  pinMode(Step_Limit_First,INPUT);
  pinMode(Step_Limit_Min,INPUT);

  digitalWrite(Step_Limit_Min,LOW);
  digitalWrite(Step_Limit_First,LOW);
  digitalWrite(Step_Limit_Second,LOW);
  digitalWrite(Step_Limit_Max,LOW);

  digitalWrite(STEP_PIN,LOW);
  digitalWrite(ENABLE_PIN,LOW);
}

void Fixture_Init(){                       //夹具动力元件初始化。
  pinMode(Fixture_Motor_1,OUTPUT);
  pinMode(Fixture_Motor_2,OUTPUT);
  pinMode(Fixture_Front_Limit,INPUT);
  pinMode(Fixture_Back_Limit,INPUT);

  digitalWrite(Fixture_Front_Limit,LOW);
  digitalWrite(Fixture_Back_Limit,LOW);
}

void Servo_Init(){                        //舵机运动初始化。
  pinMode(Servo_PIN,OUTPUT);
}

/**********************定义圆盘电机运动***********************************/

void Disk_Rest(){
  for(uchar i=0;i<Park_Num;i++){
    Disk_Move(i,HIGH);
    while(Read_Disk_Limit(i) == !Disk_Limit_Mask){
      delay(2);
    }
    Disk_Pause(i);
  }
  Disk_Pause(3);
}

void Disk_Move(uchar port,uchar Dir){
  switch (port){
    case 0:
      digitalWrite(Disk1_motor_1,Dir);
      digitalWrite(Disk1_motor_2,!Dir);
      break;
    case 1:
      digitalWrite(Disk2_motor_1,Dir);
      digitalWrite(Disk2_motor_2,!Dir);
      break;
    case 2:
      digitalWrite(Disk3_motor_1,Dir);
      digitalWrite(Disk3_motor_2,!Dir);
      break;
  }
}

void Disk_Pause(uchar Garage){
  switch (Garage){
    case 0:
      digitalWrite(Disk1_motor_1,Motor_Pause);
      digitalWrite(Disk1_motor_2,Motor_Pause);
      break;
    case 1:
      digitalWrite(Disk2_motor_1,Motor_Pause);
      digitalWrite(Disk2_motor_2,Motor_Pause);
      break;
    case 2:
      digitalWrite(Disk3_motor_1,Motor_Pause);
      digitalWrite(Disk3_motor_2,Motor_Pause);
      break;
    default:
      digitalWrite(Disk1_motor_1,Motor_Pause);
      digitalWrite(Disk1_motor_2,Motor_Pause);
      digitalWrite(Disk2_motor_1,Motor_Pause);
      digitalWrite(Disk2_motor_2,Motor_Pause);
      digitalWrite(Disk3_motor_1,Motor_Pause);
      digitalWrite(Disk3_motor_2,Motor_Pause);
      break;
  }
  
}

uchar Read_Disk_Limit(uchar Garage){
  switch (Garage){
    case 0:
      return digitalRead(Disk1_limit);
    case 1:
      return digitalRead(Disk2_limit);
    case 2:
      return digitalRead(Disk3_limit);
    case 3:
      return digitalRead(Disk1_limit);
  }
  return 0;
}
/*********************************步进电机运动***************************************/
void Move_Step(){
  digitalWrite(STEP_PIN,LOW);;
  delayMicroseconds(5);
  digitalWrite(STEP_PIN,HIGH);
}

bool Can_Up(uchar Garage){
  switch (Garage){
    case 0:
      if(digitalRead(Step_Limit_First) == Limit_Invert_Mask)
        return false;
      break;
    case 1:
      if(digitalRead(Step_Limit_Second)== Limit_Invert_Mask)
        return false;
        break;
    case 2:
      if(digitalRead(Step_Limit_Max) == Limit_Invert_Mask)
        return false;
      break;
  }
  return true;
}

bool Can_Down(){
  if(digitalRead(Step_Limit_Min) == Limit_Invert_Mask)
    return false;
  return true;
}
/**********************************按键检测******************************************/
bool KEY_Scan(){
  if(digitalRead(Key_Pin) == LOW){
    delay(50);
    if(digitalRead(Key_Pin) == LOW)
      return true;
  }
  while(digitalRead(Key_Pin) == LOW);
  return false;
}

/********************************平台运动********************************************/
void Platform_Ratate(uchar port){
  
}

void Platform_Rest(uchar port){
  
}
/*********************************夹具运动控制***************************************/
void Fixture_Clamp(){
  myservo.attach(Servo_PIN);
  for(;pos < Servo_Clamp_angle;pos++){
    myservo.write(pos);
    delay(10);
  }
  delay(1000);
}

void Fixture_Relax(){
  myservo.attach(Servo_PIN);
  for(;pos> Servo_Relax_angle;pos--){
    myservo.write(pos);
  }
  delay(1000);
}

void Fixture_Pause(){
  digitalWrite(Fixture_Motor_1,Motor_Pause);
  digitalWrite(Fixture_Motor_2,Motor_Pause);
}

void Fixture_Front(){
  digitalWrite(Fixture_Motor_1,HIGH);
  digitalWrite(Fixture_Motor_2,LOW);
  while(digitalRead(Fixture_Front_Limit) == !Limit_Invert_Mask){
    delay(10);
  }
  Fixture_Pause();
  delay(1000);
}

void Fixture_Back(){
  digitalWrite(Fixture_Motor_1,!Fixture_DIR);
  digitalWrite(Fixture_Motor_2,Fixture_DIR);
  while(digitalRead(Fixture_Back_Limit) == !Limit_Invert_Mask){
    delay(10);
  }
  Fixture_Pause();
  delay(1000);
}
/********************************整体运动****************************************/
void Move_Up(uchar port){
  uchar Garage = port/Garage_Volume;
  int Limit_Need_P,Limit_Need_N,Limit_Need;                  //正向距离，反向距离，所取就近运动的需要光电变换一套的次数
  /*******************************************************************************************/
//  Limit_Need_P = port-Judge_Current(Garage);
//  Limit_Need_N = Judge_Current(Garage)-port+Garage_Volume;      //计算反向距离
//  if(Limit_Need_P!=0){                        //正向距离如果大于反向距离，则去反向距离
//    if(Limit_Need_P>0){
//      Limit_Need_N = Judge_Current(Garage)-port+Garage_Volume;
//        if(abs(Limit_Need_P)>abs(Limit_Need_N)){
//          Limit_Need = -abs(Limit_Need_N);
//        }
//        else Limit_Need = Limit_Need_P;
//    }
//    else{
//      Limit_Need_N = Judge_Current(Garage)-port-Garage_Volume;
//      if(abs(Limit_Need_P)>abs(Limit_Need_N)){
//        Limit_Need = abs(Limit_Need_N);
//      }
//      else Limit_Need = Limit_Need_P;
//    }
//  }
//  else
//     Limit_Need = 0;
  /***************************************************************/
   
  Limit_Need = port-Judge_Current(Garage);
  Serial.print("Limit_Need:");
  Serial.print(Limit_Need);
    

  // if(Limit_Need < 0)
  //   Limit_Need = Limit_Need + Garage_Volume;
  uchar Limit_Num = 0;
  uchar Limit_Flag;                     //使用前定义。
  bool  Step_OK = false;
  bool  Ratate_OK = false;

if(Limit_Need){                          //如果需要旋转车库圆盘.HIGH定义是正转（逆时针旋转）
    if(Limit_Need > 0){                                            //需要正向旋转。
      Limit_Num = Limit_Need*2;                                     //限位变换的次数。
      Serial.print("P:Limit_Num");
      Serial.print(Limit_Num);
//      Serial.print(Limit_Num);
      if(Read_Disk_Limit(Garage) == !Disk_Limit_Mask) {             //表示因为抖动车槽移位或者上次运动是反转当前车槽不在限位位置
        Limit_Num++;                                          //限位变换次数加一
//        Serial.print("limit +1");
      }
      Disk_Move(Garage,1);
      Limit_Flag = Read_Disk_Limit(Garage);
      for(uchar i=Limit_Num;i > 0;i--){
        while(1){       //知道限位状态发生变换跳出
          if(Read_Disk_Limit(Garage) == !Limit_Flag){
            delay(15);
            if(Read_Disk_Limit(Garage) == !Limit_Flag){
              break;
            }
          }
          delay(1);
        }
        Limit_Flag = !Limit_Flag;
      }
    }                                                         //完成正转运动

    if(Limit_Need < 0){                                       //需要逆向旋转
      Limit_Num = abs(Limit_Need)*2;                           //需要限位变换的次数
      if(Read_Disk_Limit(Garage) == Disk_Limit_Mask){        //因为抖动或者上次是正转
        Limit_Num++;                                         //限位变换次数加一
      }
      Disk_Move(Garage,0);
      Limit_Flag = Read_Disk_Limit(Garage);
      for(uchar i=Limit_Num;i > 0;i--){
        while(1){    //直到限位状态发生变换跳出
          if(Read_Disk_Limit(Garage) == !Limit_Flag){
            delay(15);
            if(Read_Disk_Limit(Garage) == !Limit_Flag)
              break;
          }
          delay(5);
        }
        Limit_Flag = !Limit_Flag;
      }
    }

  }
  Disk_Pause(Garage);                                //停止圆盘车库旋转。
  Ratate_OK = true;

  digitalWrite(DIR_PIN,DIR_DIREC);         //步进电机方向控制。
  while(1){
    if(!Step_OK){
      if(Can_Up(Garage)){
        Move_Step();
      }
      else
        Step_OK = true;
    }
    if(Step_OK)
      break;
    delayMicroseconds(Speed);
   }
}

void Move_Down(){
  digitalWrite(DIR_PIN,!DIR_DIREC);
  while(1){
    if(Can_Down())
      Move_Step();
    else
      break;
    delayMicroseconds(Speed);
  }

}
