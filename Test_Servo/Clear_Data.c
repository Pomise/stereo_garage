#include "Clear_Data.h"
#include "Init.h"
#include <EEPROM.h>

void Clear(){
	uchar i;

	for(i=0;i<Car_Num*Park_Num;i++){
		EEPROM.write(i,i);
	}
	for(;i<Car_Num*Park_Num+Park_Num;i++){
		EEPROM.write(i,0x00);
	}
}

