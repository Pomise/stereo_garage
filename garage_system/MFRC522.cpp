#include "MFRC522.h"
 
MFRC522 mfrc522; // Instance of the class
MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

void MFRC522_Init(){
  mfrc522.PCD_Init(SS_PIN,RST_PIN);   //Init MFRC522
}

bool Check_Card(){
  if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){  
    return true;
  }
  return false;
}

byte * Get_CardID(){
  return mfrc522.uid.uidByte;
}

void Stop_Check(){
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}



