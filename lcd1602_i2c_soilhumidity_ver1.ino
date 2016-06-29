// sketch writed by niq_ro (Nicu FLORICA), Craiova, 22.06.2016
// version for control soil humidity (moisture) uding reley for water pump
// http://www.tehnic.go.ro
// http://nicuflorica.blogspot.ro/
// http://arduinotehniq.blogspot.com/
// http://www.arduinotehniq.com/


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int citiredate;          
int procentumiditate;
#define pinsenzor A1             // pin for sensor
#define alimentaresenzor 12      // pin for power sensor
#define pinreleu 13              // pin for relay
byte pragudare;                  // threshold for begin wattering (0..100%)
unsigned long pauzamare;         // time between reading (in ms) when soil is wet
unsigned int pauzamica;          // time between reading (in ms) when soil is dry

void setup()
{
pinMode(alimentaresenzor, OUTPUT); // digital pin is now output for power the sensor
pinMode(pinreleu, OUTPUT);         // digital pin is now output for control relay

digitalWrite(alimentaresenzor, LOW); // power sensor is off
digitalWrite(pinreleu, LOW);         // reley is off
  
// initialize the LCD
lcd.begin();

// Turn on the blacklight and print a message.
lcd.backlight();

lcd.setCursor(1, 0);
lcd.print("Soil moisture");
lcd.setCursor(1, 1);
lcd.print("control system");
delay(3000);
lcd.clear();

pragudare = 25;        // threshold for begin wattering process % (25%)
//pauzamare = 300000;    // time in ms (300000 -> 300sec -> 5 minute)
pauzamare = 10000;
pauzamica = 5000;      // timp in ms (5000 -> 5sec)
}

void loop()
{
digitalWrite(alimentaresenzor, HIGH); // sensor is powered
delay(1000);  
  
citiredate = analogRead(pinsenzor);
procentumiditate = map(citiredate, 1023,0,0,100);
digitalWrite(alimentaresenzor, LOW); // sensor is disconnect from power system


lcd.setCursor(0, 0);
lcd.print("Humidity: ");
if (procentumiditate < 100) lcd.print(" ");
if (procentumiditate < 10) lcd.print(" ");
lcd.print(procentumiditate);
lcd.print("%");

if (procentumiditate < pragudare) // if soil is too dry
{
digitalWrite(pinreleu, HIGH);     // relay is powered for begin the watering
lcd.setCursor(0, 1);
lcd.print("Pump is ON !  ");
}
else                              // if soil is wet
{
digitalWrite(pinreleu, LOW);      // relay is off (wattering pump is off)
lcd.setCursor(0, 1);
lcd.print("Pump is OFF ! ");
delay(pauzamare);                 // time between reading is more than usual (when pump is on)
}

delay(pauzamica);	          
}
