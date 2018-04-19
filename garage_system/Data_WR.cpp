#include "Data_WR.h"
#include "EEPROM.h"
/*******************************数据结构*****************************************
车位（0~29）：每个车位用一个字节存储，最高位用于标识是否为空车位，其余用于存放车位编号。
旋转车库当前车位编号：每个用一个字节存储，记录各个车库当时靠前的车位编号，用于计算需要旋转车库需要经过几次限位开关。
卡号：用四个字节存储，记录每个车位存车用户的卡号
********************************定义变量***************************************/
uchar Table[Car_Num];
uchar UID_Data[UID_Size];

/********************************读取函数*****************************************/

uchar * Read_Table(){                     
	for(uchar i=0;i<Car_Num;i++){
		Table[i] = EEPROM.read(i);
	}
	return Table;
}

uchar *Read_UID(uchar port){
	for(uchar i=0;i<UID_Size;i++){
		UID_Data[i] = EEPROM.read(Car_Num+Park_Num+port*UID_Size+i);
	}
	return UID_Data;
}

uchar Read_Current(uchar Garage){
	return EEPROM.read(Car_Num+Garage);
}

/***************************************写入数据*********************************************/
void Write_Data(uchar port,uchar *UID){
	if(port < Car_Num){
		EEPROM.write(port,port|0x80);
		for(uchar i=0;i<UID_Size;i++)
			EEPROM.write(Car_Num+Park_Num+port*UID_Size+i,UID[i]);
	}
	Read_Table();
}

void Write_Clear(uchar port){
	EEPROM.write(port,port&0x7F);
	Read_Table();
}


void Write_Current(uchar port){
	uchar Garage;
	if(port<Car_Num){
		Garage = port/Garage_Volume;
		EEPROM.write(Car_Num+Garage,port);
		return true;
	}
	return false;
}
