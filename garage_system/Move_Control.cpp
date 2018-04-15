#include "Move_Control.h"

Servo myservo;
int pos = 0;

/***********************初始化运动控制************************************/
void Move_Init(){
  Disk_Init();
  Disk_Pause(4);          //暂停所有的圆盘车库
  Step_Init();
  Fixture_Init();
  Fixture_Relax()        //夹具放松。

}

void Disk_Init(){
  pinMode(Disk1_motor_1,OUTPUT);
  pinMode(Disk1_motor_2,OUTPUT);
  pinMode(Disk1_limit,INPUT);
  pinMode(Disk1_limit,HIGH);

  pinMode(Disk2_motor_1,OUTPUT);
  pinMode(Disk2_motor_2,OUTPUT);
  pinMode(Disk2_limit,INPUT);
  pinMode(Disk2_limit,HIGH);

  pinMode(Disk3_motor_1,OUTPUT);
  pinMode(Disk3_motor_2,OUTPUT);
  pinMode(Disk3_limit,INPUT);
  pinMode(Disk3_limit,HIGH);
}

void Step_Init(){
  PinMode(STEP_PIN,OUTPUT);
  PinMode(DIR_PIN,OUTPUT);
  PinMode(ENABLE_PIN,OUTPUT);
  PinMode(Step_Limit_Max,INPUT);
  PinMode(Step_Limit_Min,INPUT);

  digitalWrite(Step_Limit_Min,HIGH);
  digitalWrite(Step_Limit_Max,HIGH);

  digitalWrite(STEP_PIN,LOW);
  digitalWrite(ENABLE_PIN,LOW);
}

void Fixture_Init(){                       //夹具动力元件初始化。
  PinMode(Fixture_Motor_1,OUTPUT);
  PinMode(Fixture_Motor_2,OUTPUT);
  PinMode(Fixture_Front_Limit,INPUT);
  PinMode(Fixtreu_Back_Limit,INPUT);

  digitalWrite(Fixture_Front_Limit,HIGH);
  digitalWrite(Fixtreu_Back_Limit,HIGH);
}

void Servo_Init(){                        //舵机运动初始化。
  PinMOde(Servo_PIN,OUTPUT);
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
    case 1:
      digitalWrite(Disk1_motor_1,HIGH);
      digitalWrite(Disk1_motor_2,HIGH);
      break;
    case 2:
      digitalWrite(Disk2_motor_1,HIGH);
      digitalWrite(Disk2_motor_2,HIGH);
      break;
    case 3:
      digitalWrite(Disk3_motor_1,HIGH);
      digitalWrite(Disk3_motor_2,HIGH);
      break;
    default:
      digitalWrite(Disk1_motor_1,HIGH);
      digitalWrite(Disk1_motor_2,HIGH);
      digitalWrite(Disk2_motor_1,HIGH);
      digitalWrite(Disk2_motor_2,HIGH);
      digitalWrite(Disk3_motor_1,HIGH);
      digitalWrite(Disk3_motor_2,HIGH);
      break;
  }
  
}
/*********************************步进电机运动***************************************/
void Move_Step(){
  digitalWrite(STEP_PIN,LOW);;
  delayMicroseconds(5);
  digitalWrite(STEP_PIN,HIGH);
}

bool Can_Up(){
  if(digitalRead(Step_Limit_Max) == 0)
    return false;
  return true;
}

bool Can_Down(){
  if(digitalRead(Step_Limit_Min) == 0)
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
  mysero.attach(Servo_PIN);
  for(;pos < Servo_Clamp_angle;pos++){
    myservo.write(pos);
    delay(10);
  }
}

void Fixture_Relax(){
  mysero.attach(Servo_PIN);
  for(;pos> Servo_Relax_angle;pos--){
    myservo.write(pos);
  }
}

void Fixture_Pause(){
  digitalWrite(Fixture_Motor_1,HIGH);
  digitalWrite(Fixture_Motor_2,HIGH);
}

void Fixture_Front(){
  digitalWrite(Fixture_Motor_1,Fixture_DIR);
  digitalWrite(Fixture_Motor_2,~Fixture_DIR);
  while(digitalRead(Fixture_Front_Limit) == LOW){
    delay(10);
  }
  Fixture_Pause();
}

void Fixture_Back(){
  digitalWrite(Fixture_Motor_1,~Fixture_DIR);
  digitalWrite(Fixture_Motor_2,Fixture_DIR);
  while(digitalRead(Fixture_Back_Limit) == LOW){
    delay(10);
  }
  Fixture_Pause();
}
/********************************整体运动****************************************/
void Move_Up(uchar port){
  uchar Garage = port/Garage_Volume;
  uchar n = 0;
  uchar Limit_Need = port-Read_Current(Garage);
  uchar Limit_Num = 0;
  uchar Limit_Flag =  0;
  bool  Step_OK = false;
  bool  Ratate_OK = false;

  digitalWrite(DIR_PIN,DIR_DIREC);
  Disk_Move(Garage ,1);

  while(1){
    if(!Step_OK){
      if(Can_Up()){
        Move_Step()
      }
      else
        Step_OK = true
    }
    if(!Ratate_OK){
      if(digitalRead(Disk1_limit+Garage) == Limit_Flag){
        Limit_Flag = ~Limit_Flag;
        n++;
        if(n == 2) = {
          n = 0;
          Limit_Num ++;
          if(Limit_Need == Limit_Num)
            Ratate_OK = 1;
        }
      }

    }
    else
      Disk_Pause(Garage);
    if(Step_OK && Ratate_OK)
      break;
    delayMicroseconds(1000);
  }
  Disk_Pause(Garage);
}

void Move_Down(){
  digitalWrite(DIR_PIN,~DIR_DIREC);
  while(1){
    if(Can_Down())
      Move_Step();
    else
      break;
    delayMicroseconds(1000);
  }

}
