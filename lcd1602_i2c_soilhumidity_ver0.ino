// sketch writed by niq_ro (Nicu FLORICA)
// Craiova, 22.06.2016
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
#define pinsenzor A1


void setup()
{
// initialize the LCD
lcd.begin();

// Turn on the blacklight and print a message.
lcd.backlight();

lcd.setCursor(1, 0);
lcd.print("Soil humidity");
lcd.setCursor(1, 1);
lcd.print("measure system");
delay(3000);
lcd.clear();


}

void loop()
{
citiredate = analogRead(pinsenzor);
procentumiditate = map(citiredate, 1023,0,0,100);

lcd.setCursor(0, 0);
lcd.print("Humidity: ");
if (procentumiditate < 100) lcd.print(" ");
if (procentumiditate < 10) lcd.print(" ");
lcd.print(procentumiditate);
lcd.print("%");

delay(3000);	
}
