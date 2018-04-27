#include "MFRC522.h"

/* * -----------------------------------------------------------------------------------------
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



