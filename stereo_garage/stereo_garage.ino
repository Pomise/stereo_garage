#include <HardwareSerial.h>
#include "Init.h"
#include "Move_Control.h"

void setup()
{
	//Do startup stuff here
	Serial.begin(19200);
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
	delay(200);
}

bool Chose_Front(){
	if(digitalRead(FRONT) == Limit_Invert_Mask)
		return true;
	return  false;
}

bool Chose_Back(){
	if(digitalRead(BACK) == Limit_Invert_Mask)
		return true;
	return  false;
}
