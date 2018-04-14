/**********************定义圆盘电机运动***********************************/
void Disk_Init(){
  pinMode(Disk1_motor_1,OUTPUT);
  pinMode(Disk1_motor_2,OUTPUT);
  pinMode(Disk1_limit,INPUT);
}

void Disk1_Move(uchar Caar_port,uchar Dir){
    digitalWrite(Disk1_motor_1,Dir);
    digitalWrite(Disk1_motor_2,!Dir);
    digitalWrite(Disk1_limit,HIGH);
    while(1){
      if (digitalRead(Disk1_limit)){
        digitalWrite(Disk1_motor_1,HIGH);
        digitalWrite(Disk1_motor_2,HIGH);
        while(digitalRead(Disk1_limit));
        break;
      }
      delay(10);
    }
    digitalWrite(Disk1_motor_1,HIGH);
    digitalWrite(Disk1_motor_2,HIGH);
}

