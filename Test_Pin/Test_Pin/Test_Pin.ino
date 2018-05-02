#include "Init.h"
#define Pin_1 Disk2_limit
#define Pin_2 Disk1_motor_2
#define Pin_3 Disk1_Enable
#define Pin_4
#define Mode   INPUT
#define H_L    LOW

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Pin_1,Mode);
  pinMode(Pin_2,Mode);
  pinMode(Pin_3,Mode);

  digitalWrite(Pin_1,H_L);
  digitalWrite(Pin_2,HIGH);
  digitalWrite(Pin_3,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(Pin_1));
  Serial.print(digitalRead(Pin_2));
  Serial.print("\n");
  delay(2000);
  
}
