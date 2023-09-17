#include "Arduino.h"
//#include "AVR_Watchdog.h"
#include <EEPROM.h>
#include <TaHa.h> 
#include "BtnPinOnOff.h"

#define ROW1  3
#define ROW2  4
#define ROW3  5
#define ROW4  6
#define COL1  A1
#define COL2  A0



TaHa TaHa_10ms;

BtnPinOnOff  Pin1;
BtnPinOnOff  BtnPin[8];


void setup() 
{
  delay(2000);
  Serial.begin(9600); 
  Serial.println("btn_pin_on_off_test.ino  2023");

  BtnPin[0].Init(ROW1,'A');
  BtnPin[1].Init(ROW2,'B');
  BtnPin[2].Init(ROW3,'C');
  BtnPin[3].Init(ROW4,'D');
  BtnPin[4].Init(ROW1,'E');
  BtnPin[5].Init(ROW2,'F');
  BtnPin[6].Init(ROW3,'G');
  BtnPin[7].Init(ROW4,'H');


  pinMode(COL1,OUTPUT);
  pinMode(COL2,OUTPUT);
  TaHa_10ms.set_interval(10, RUN_RECURRING, run_10ms); 
}

void loop() {
    // put your main code here, to run repeatedly:
    TaHa_10ms.run();

    for( uint8_t i= 0; i<8; i++)
    {
        char c = BtnPin[i].Read();
        if (c != 0x00) 
        {
            if ((c & 0b10000000) == 0) 
                Serial.print("On ");
            else 
                Serial.print("Off ");
            Serial.println(c & 0b01111111);

        }

    }
}


void run_10ms()
{
    digitalWrite(COL1,LOW);
    digitalWrite(COL2,HIGH);

    for( uint8_t i= 0; i<4; i++)
    {
        BtnPin[i].Scan();

    }
    digitalWrite(COL1,HIGH);
    digitalWrite(COL2,LOW);

    for( uint8_t i= 4; i<8; i++)
    {
        BtnPin[i].Scan();

    }
}