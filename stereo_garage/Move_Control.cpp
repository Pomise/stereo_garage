#include "Move_Control.h"
#include "Init.h"
#include "Arduino.h"

void Move_Init(){
  pinMode(STEP_PIN,OUTPUT);
  pinMode(DIR_PIN,OUTPUT);
  pinMode(ENABLE_PIN,OUTPUT);
  pinMode(MAX_PIN,INPUT);
  pinMode(MIN_PIN,INPUT);
  pinMode(FRONT,INPUT);
  pinMode(BACK,INPUT);
  pinMode(Pause,INPUT);

  digitalWrite(MIN_PIN,HIGH);
  digitalWrite(MAX_PIN,HIGH);

  digitalWrite(STEP_PIN,LOW);
  digitalWrite(ENABLE_PIN,LOW);

  digitalWrite(FRONT,HIGH);
  digitalWrite(BACK,HIGH);
  digitalWrite(Pause,HIGH);
}

void Move_Step(){
  digitalWrite(STEP_PIN,LOW);;
  delayMicroseconds(5);
  digitalWrite(STEP_PIN,HIGH);
}

bool Can_Front(){
	if((digitalRead(MAX_PIN) == Limit_Invert_Mask)||(digitalRead(Pause) == Key_Invert_Mask))
		return false;
	return true;
}

bool Can_Back(){
	if((digitalRead(MIN_PIN) == Limit_Invert_Mask)||(digitalRead(Pause) == Key_Invert_Mask))
		return false;
	return true;
}

void Move_Front(){
  digitalWrite(DIR_PIN,DIR_Invert_Mask);
  while(1){
    if(!Can_Front()){
      break;
    }
      Move_Step();
      delayMicroseconds(Speed);
  }
}

void Move_Back(){
  digitalWrite(DIR_PIN,!DIR_Invert_Mask);
  while(1){
    if(!Can_Back()){
      break;
    }
    else{
      Move_Step();
      delayMicroseconds(Speed);
    }
  }
}
