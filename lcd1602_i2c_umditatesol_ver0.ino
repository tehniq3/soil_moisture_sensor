// sketch scris de niq_ro (Nicu FLORICA)
// Craiova, 22.06.2016
// http://www.tehnic.go.ro
// http://nicuflorica.blogspot.ro/
// http://arduinotehniq.blogspot.com/
// http://www.arduinotehniq.com/

#include <Wire.h>                // folosire librarie pentru protocol i2c
#include <LiquidCrystal_I2C.h>   // folosire librarie pentru afisaj lcd1602 pe i2c

// afisaj 1602 pe i2c cu adresa 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

int citiredate;
int procentumiditate;
#define pinsenzor A1


void setup()
{
lcd.begin();  // initializare afisaj

lcd.backlight(); // aprindere fundal

lcd.setCursor(3, 0);   // pozitionare cursor pe colana a 4-a din stanga - sus
lcd.print("masurare"); // afisare text
lcd.setCursor(1, 1);   // mutare cursor pe coloana a 2-a din stanga - jos
lcd.print("umiditate sol"); // afisare text
delay(3000);           // temporizare 3 secunde
lcd.clear();           // stergere ecran 
}

void loop()
{
citiredate = analogRead(pinsenzor);                // citire valoare pe intrarea analogica
procentumiditate = map(citiredate, 1023,0,0,100);  // transformare date primare in procente

lcd.setCursor(0, 0);
lcd.print("Umiditate: ");
if (procentumiditate < 100) lcd.print(" ");
if (procentumiditate < 10) lcd.print(" ");
lcd.print(procentumiditate);
lcd.print("%");

delay(3000);	
}
