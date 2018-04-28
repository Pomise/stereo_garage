#include "Init.h"
#define Pin_1 Fixture_Motor_1
#define Pin_2 Fixture_Motor_2
#define Mode   OUTPUT
#define H_L    LOW

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Pin_1,Mode);
  pinMode(Pin_2,Mode);

  digitalWrite(Pin_1,H_L);
  digitalWrite(Pin_2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(Pin_1));
  Serial.print(digitalRead(Pin_2));
  Serial.print("\n");
  delay(2000);
  
}
