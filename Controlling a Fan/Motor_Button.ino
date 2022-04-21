//EECE 4520-201: Micro 2: Lab 3: Prof. Wang
//Renin Kingsly Jose
//Johnny Nhem
//Alex Skinner
//4/21/22


#include <SoftwareSerial.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "DS3231.h"
#include "DS1307RTC.h"
#include "TimeLib.h"
#include <LiquidCrystal.h>

DS3231 Currclock;

const int ENABLE = 5; //enable on pin 5
const int DIRA = 3; //clock-wise spin on pin 3
const int DIRB = 4; //counterclock-wise spin on pin 4
const int buttonApin = 9; //button A
const int buttonBpin = 8; //button B

LiquidCrystal lcd(7, 2, 10, 11, 12, 13);
  bool Twelve = true;
  bool PM = false;
  
void setup() 
{
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Fan:Med: Off");
}

void loop() 
{
  //First, Refresh the current time: (Heres hoping this all runs within 1 second!)
  lcd.setCursor(0, 1);
  lcd.print(String(Currclock.getHour(Twelve,PM))+":"+String(Currclock.getMinute())); 

  //Then, Update the motor based on the current buttons
  if (digitalRead(buttonApin) == LOW) //if button A is pressed, fan turn clock-wise
  {
    digitalWrite(ENABLE,HIGH); //turn enable ON
    digitalWrite(DIRA,HIGH); //make fan spin clock-wise
    digitalWrite(DIRB,LOW); //turn counterclock-wise OFF
    analogWrite(ENABLE,180); //turn enable OFF
    lcd.begin(16, 2);
    lcd.print("Fan:Med:Clk wise");
  }
  if (digitalRead(buttonBpin) == LOW) //if buton B is pressed, fan turn counterclock-wise
  {
    digitalWrite(ENABLE,HIGH); //turn enable ON
    digitalWrite(DIRA,LOW); //turn clock-wise OFF
    digitalWrite(DIRB,HIGH); //make fan spin counterclock-wise
    analogWrite(ENABLE,180); //turn enable OFF
    lcd.begin(16, 2);
    lcd.print("Fan:Med:C-C wise");
  }

  //RTC Clock Code
  
 /* 
 if(Currclock.getSecond() == 30){
    digitalWrite(DIRA, HIGH); //Enable the Motor off completely
    digitalWrite(DIRB, LOW);
    lcd.setCursor(16, 2);
    lcd.print("Fan:Med: Clk wise"); 
  }
  if(Currclock.getSecond() == 30){
    digitalWrite(DIRA, LOW); //Enable the Motor off completely
    digitalWrite(DIRB, LOW);
    lcd.setCursor(16, 2);
    lcd.print("Fan:Med: Off"); 
  }
*/
  
}
