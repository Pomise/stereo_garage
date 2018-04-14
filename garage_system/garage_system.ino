#include <HardwareSerial.h>

void setup() {
  // put your setup code here, to run once:
  Disk_Init();
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:

  Disk1_Move(1,1);

}
