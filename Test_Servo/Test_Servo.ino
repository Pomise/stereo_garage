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
  pinMode(Test_Pin,OUTPUT);
  digitalWrite(Test_Pin,HIGH);
}

void loop() {
  if (digitalRead(Test_Pin) == 0)
  {
    Fixture_Clamp();
    Serial.print("Clamp OK");
    Fixture_Front();
    Serial.print("Front OK");
    Fixture_Relax();
    delay(1000);
    Fixture_Back();
    delay(1000);
    /* code */
  }
}
