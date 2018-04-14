/**********************定义圆盘电机运动***********************************/
void Disk_Init(){
  pinMode(Disk1_motor_1,OUTPUT);
  pinMode(Disk1_motor_2,OUTPUT);
  pinMode(Disk1_limit,INPUT);
  pinMode(Disk1_limit,HIGH);
}

void Disk_Move(uchar Car_port,uchar Dir){
  switch (Car_port){
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

void Disk_Pause(uchar Car_port){
  switch (Car_port){
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

/********************************平台运动********************************************/
void Platform_Ratate(uchar port){
  
}

void Platform_Rest(uchar port){
  
}
/********************************整体运动****************************************/
void Move_Up(uchar port){
  
}

