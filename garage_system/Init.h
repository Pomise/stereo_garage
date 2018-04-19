typedef unsigned char byte;
#define uchar unsigned char
/*******************************NFC卡引脚定义*************************************/
#define SS_PIN 10
#define RST_PIN 5
/* -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */
/*******************************电机引脚定义位************************************/
#define   Disk1_motor_1  3
#define   Disk1_motor_2  4
#define   Disk2_motor_1  3
#define   Disk2_motor_2  4
#define   Disk3_motor_1  5
#define   Disk3_motor_2  6

#define   STEP_PIN      22
#define   DIR_PIN       23
#define   ENABLE_PIN    24
#define   DIR_DIREC      LOW          //用于步进电机置方向
#define   Speed         500
/******************************限位开关引脚定义位*********************************/
#define   Limit_Invert_Mask  HIGH
#define   Disk1_limit   25                     //直流电机的限位开关引脚要连续定义,且要用数字引脚
#define   Disk2_limit   26
#define   Disk3_limit   27
#define   Step_Limit_Max  28
#define   Step_Limit_Min  29
#define   Fixture_Front_Limit   30
#define   Fixture_Back_Limit    31
/*****************************夹具电机舵机引脚定位******************************/
#define   Fixture_Motor_1  32
#define   Fixture_Motor_2  33
#define   Servo_PIN       9                  //需要一个能输出PWM的引脚。
#define   Servo_Clamp_angle     180
#define   Servo_Relax_angle    0
#define   Fixture_DIR      LOW


/*****************************车库数据定义位************************************/
#define   Car_Num   10
#define   Park_Num  1
#define   Garage_Volume  Car_Num/Park_Num
#define   UID_Size     4
