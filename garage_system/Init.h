typedef unsigned char byte;
#define uchar unsigned char
/*******************************电机引脚定义位************************************/
#define   Disk1_motor_1  A0
#define   Disk1_motor_2  A1
#define   Disk2_motor_1  A2
#define   Disk2_motor_2  A3
#define   Disk3_motor_1  A4
#define   Disk3_motor_2  A5

#define   STEP_PIN      2
#define   DIR_PIN       3
#define   ENABLE_PIN    4
#define   DIR_DIREC      HIGH          //用于步进电机置方向
#define   Speed         1000
/******************************限位开关引脚定义位*********************************/
#define   Limit_Invert_Mask  HIGH
#define   Disk1_limit   9                     //直流电机的限位开关引脚要递增定义,且要用数字引脚
#define   Disk2_limit   10
#define   Disk3_limit   11
#define   Step_Limit_Max  12
#define   Step_Limit_Min  13
#define   Fixture_Front_Limit   16
#define   Fixture_Back_Limit    17
/*****************************夹具电机舵机引脚定位******************************/
#define   Fixture_Motor_1  14
#define   Fixture_Motor_2  15
#define   Servo_PIN       18                  //需要一个能输出PWM的引脚。
#define   Servo_Clamp_angle     180
#define   Servo_Relax_angle    0
#define   Fixture_DIR      HIGH


/*****************************车库数据定义位************************************/
#define   Car_Num   30
#define   Park_Num  3
#define   Garage_Volume  Car_Num/Park_Num
#define   UID_Size     4
