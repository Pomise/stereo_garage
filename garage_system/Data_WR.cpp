#include "Init.h"

/*******************************数据结构*****************************************/
车位（0~29）：每个车位用一个字节存储，最高位用于标识是否为空车位，其余用于存放车位编号。
旋转车库当前车位编号：每个用一个字节存储，记录各个车库当时靠前的车位编号，用于计算需要旋转车库需要经过几次限位开关。
卡号：用四个字节存储，记录每个车位存车用户的卡号
/********************************定义变量***************************************/
byte ParkPort_Table[Car_Num];

/********************************读取函数*****************************************/
byte * Read_Table(){                      //使用这个文件的函数要先调用这个函数
	for(uchar i=0;i<Car_Num;i++){
		ParkPort_Table[i] = EEPROM.read(i);
	}
	return ParkPort;
}

bool Judge_Can(){
	for(uchar i=0;i<Car_Num;i++){
		if(ParkPort_Table[i]&0x80 == 0)
			return true;
	}
	return false;
}

uchar Judge_Port(){
	uchar i=0;
	for(i=0;i<Car_Num;i++){
		if(ParkPort_Table[i]&0x80 == 0)
			break;
	}
	return i;
}

uchar Read_Current(uchar Garge){
	return EEPROM.read(Car_Num+Garage)
}

/***************************************写入数据*********************************************/
bool Write_Port(uchar port,byte *UID){
	if(port < Car_Num){
		EEPROM.write(port,port&0x80);
		for(uchar i=0;i<UID_Size;i++)
			EEPROM.write(Car_Num+Park_Num+port*UID_Size+i,UID[i]);
		return true;
	}
	return false;
}

bool Write_Current(uchar port){
	uchar Garage;
	if(port<Car_Num){
		Garage = port/Garage_Volume+1;
		EEPROM.write(Car_Num+Garge,port);
		return true;
	}
	return false;
}