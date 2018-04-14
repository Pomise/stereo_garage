/**********************定义圆盘电机运动***********************************/
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
}
}

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

void Disk_Pause(uchar port){
  switch (port){
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
  if(digitalRead(Step_Limit_Max) == 0)
    return false;
  return true;
}

/********************************平台运动********************************************/
void Platform_Ratate(uchar port){
  
}

void Platform_Rest(uchar port){
  
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

  Disk_Move(port/Garage_Volume,1);
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
