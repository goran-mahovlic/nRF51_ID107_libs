#include "SmartOled.h"
#include "KX022.h"

KX022 acc(acc);

#define RESET 30
#define DC 0
#define CS 29

#define VIBRATE 7

#define BUTTON 4
int counter = 0;

SmartOled my_oled(RESET, DC, CS); // pin_rst, pin_dc, pin_cs)

const int CLOCK_SPEED = 1000;

// Use these variables to set the initial time
int hours = (__TIME__[0] -'0') *10 +( __TIME__[1] -'0') ;
int minutes = (__TIME__[3] -'0') *10 +( __TIME__[4] -'0') ;
int seconds = (__TIME__[7] -'0') *10 +( __TIME__[7] -'0') ;
unsigned long lastUpdate = 0;

void updateTime()
{
  seconds++;  // Increment seconds
  if (seconds >= 60)  // If seconds overflows (>=60)
  {
    seconds = 0;  // Set seconds back to 0
    minutes++;    // Increment minutes
    if (minutes >= 60)  // If minutes overflows (>=60)
    {
      minutes = 0;  // Set minutes back to 0
      hours++;      // Increment hours
      if (hours >= 12)  // If hours overflows (>=12)
      {
        hours = 0;  // Set hours back to 0
      }
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  my_oled.init(0, 8000000);
  my_oled.clear(PAGE);
  my_oled.setCursor(0,0);
  my_oled.puts("Smarty V2");
  my_oled.setCursor(0,10);
  my_oled.puts("Radiona");
  my_oled.display();
  pinMode(VIBRATE,OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  delay(10000);
  Serial.begin(9600);
  Serial.println("Serial OK");
  acc.init();
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(VIBRATE,!digitalRead(BUTTON));
char txtBuf[9];

//Acc is currently not working for some reason ...

 Serial.println("Acc");
 delay(1000);
 Serial.println((float)(acc.getAccel(0)),2);
 delay(1000);
 Serial.println((float)(acc.getAccel(1)),2); 
 delay(1000);
  Serial.println((float)(acc.getAccel(2)),2); 

  // Check if we need to update seconds, minutes, hours:
  if (lastUpdate + CLOCK_SPEED < millis())
  {
    lastUpdate = millis();
  
    updateTime();  // Add a second, update minutes/hours if necessary:

    my_oled.clear(PAGE);  // Clear the frame buffer

    sprintf(txtBuf,"%02d:%02d:%02d",hours,minutes,seconds);

    my_oled.setCursor(5,12);
    my_oled.puts(txtBuf);

    my_oled.display(); // Draw the memory buffer
  }

}
