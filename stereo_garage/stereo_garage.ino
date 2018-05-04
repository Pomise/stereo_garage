#include <HardwareSerial.h>
#include "Init.h"
#include "Move_Control.h"

void setup()
{
	//Do startup stuff here
	Serial.begin(9600);
	Serial.println("start");
	Move_Init();
}

void loop()
{
	if(Chose_Front()){
    Serial.println("Move Front");
		Move_Front();
   Serial.println("Front Over");
	}
	if(Chose_Back()){
  Serial.println("Move Back");
		Move_Back();
    Serial.println("Back Over");
	}
	delay(10);
}

bool Chose_Front(){
	if(digitalRead(FRONT) == Key_Invert_Mask){
    delay(10);
    if(digitalRead(FRONT) == Key_Invert_Mask){
		  return true;
    }
	}
	return  false;
}

bool Chose_Back(){
	if(digitalRead(BACK) == Key_Invert_Mask){
		delay(10);
    if(digitalRead(BACK) == Key_Invert_Mask){
		  return true;
    }
	}
	return  false;
}
