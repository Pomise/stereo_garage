#include "Move_Control.h"
#include "Plan.h"
#include <Servo.h>
#include <Arduino.h>

Servo myservo;
int pos = 0;

/***********************初始化运动控制************************************/
void Move_Init(){
  Disk_Init();
  Disk_Pause(4);          //暂停所有的圆盘车库
  Step_Init();
  Fixture_Init();
  Fixture_Relax();        //夹具放松。
  void Servo_Init();

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


void Disk_Move(uchar port,uchar Dir){
  switch (port){
    case 1:
      digitalWrite(Disk1_motor_1,Dir);
      digitalWrite(Disk1_motor_2,!Dir);
      break;
    case 2:
      digitalWrite(Disk2_motor_1,Dir);
      digitalWrite(Disk2_motor_2,!Dir);
      break;
    case 3:
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
  digitalWrite(Fixture_Motor_1,Fixture_DIR);
  digitalWrite(Fixture_Motor_2,!Fixture_DIR);
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
  uchar n = 0;
  uchar Limit_Need = port-Judge_Current(Garage);
  uchar Limit_Num = 0;
  uchar Limit_Flag =  Limit_Invert_Mask;
  bool  Step_OK = false;
  bool  Ratate_OK = false;

  digitalWrite(DIR_PIN,DIR_DIREC);
  Disk_Move(Garage ,1);
  if(Limit_Need == 0)
    Ratate_OK = true;

  while(1){
    if(!Step_OK){
      if(Can_Up(Garage)){
        Move_Step();
      }
      else
        Step_OK = true;
    }
    if(!Ratate_OK){
      if(Read_Disk_Limit(Garage) == Limit_Flag){
        Limit_Flag = !Limit_Flag;
        n++;
        if(n == 2){
          n = 0;
          Limit_Num ++;
          if(Limit_Need == Limit_Num)
            Ratate_OK = true;
        }
      }

    }
    else
      Disk_Pause(Garage);
    if(Step_OK && Ratate_OK)
      break;
    delayMicroseconds(Speed);
  }
  Disk_Pause(Garage);
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
