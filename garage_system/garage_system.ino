#include <Init.h>

/*******************定义相应的变量************************/
byte* CardID;
/********************************************************/
void setup() {
  // put your setup code here, to run once:
  Disk_Init();
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
}

void loop() {
  while(1){
    MFRC522_Init();                            //打开IC卡检测。
    while(1){                               
      if(Check_Card()){
        CardID=Get_CardID();
        Stop_Check;
        for(char i=0;i<UID_Size;i++){
          Serial.print(CardID[i] < 0x10 ? " 0" : " ");
          Serial.print(CardID[i],HEX);
        }
        break;
      }
      delay(100);
    }

    
  }

}
