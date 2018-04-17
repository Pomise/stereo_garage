#include <SPI.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include "Init.h"


#define SS_PIN 10
#define RST_PIN 5

void MFRC522_Init();
bool Check_Card();
byte * Get_CardID();
void Stop_Check();
