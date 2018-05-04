#include "Init.h"
#include "Servo.h"

void Move_Init();
void Disk_Init();
void Step_Init();
void Fixture_Init();
void Servo_Init();
void Enable_Init();
void Key_Init();
void Site_Reset();
void Disk_Rest();
bool KEY_Scan();

void Disk_Move(uchar port,uchar Dir);
void Disk_Pause(uchar Garage);
uchar Read_Disk_Limit(uchar Garage);
void Move_Step();
bool Can_Up(uchar Garage);
bool Can_Down();

void Platform_Ratate(uchar port);
void Platform_Rest(uchar port);

void Fixture_Clamp();
void Fixture_Relax();
void Fixture_Pause();
void Fixture_Front();
void Fixture_Back();

void Move_Up(uchar port);
void Move_Down();
