// sketch scris de niq_ro (Nicu FLORICA), Craiova, 22.06.2016
// versiune pentru udare, 27.06.2016
// versiune indicate timp scurs de la ultima udare, 02.07.2016
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
#define pinsenzor A1             // senzorul de masura se conecteaza la pinul definit
#define alimentaresenzor 12      // senzorul nu va fi alimentat permanent pt. evitare efect de coroziune (electroliza)
#define pinreleu 13              // comanda releului care poate porni o pompa se conecteaza la pinul definit
byte pragudare;                  // variabila pentru prag pornire pompa (0..100%)
unsigned long pauzamare;         // variabila pentru timp intre citiri (in ms) cand pamantul este umed;
unsigned int pauzamica;          // variabila pentru timp intre citiri (in ms) cand pamantul este uscat;

unsigned long tpudare;
unsigned long tpactual;
unsigned long tptrecut;
int tpminute;
int tpore;


void setup()
{
pinMode(alimentaresenzor, OUTPUT); // definim pinul ca iesire
pinMode(pinreleu, OUTPUT);         // definim pinul ca iesire

digitalWrite(alimentaresenzor, LOW); // pinul ramane in 0 logic
digitalWrite(pinreleu, LOW);         // pinul ramane in 0 logic
  
lcd.begin();  // initializare afisaj
lcd.backlight(); // aprindere fundal

lcd.setCursor(0, 0);   // pozitionare cursor pe colana a 4-a din stanga - sus
lcd.print("masurare/control"); // afisare text
lcd.setCursor(1, 1);   // mutare cursor pe coloana a 2-a din stanga - jos
lcd.print("umiditate sol"); // afisare text
delay(3000);           // temporizare 3 secunde
lcd.clear();           // stergere ecran 

pragudare = 25;        // prag alimentare pompa in % (25%)
//pauzamare = 300000;    // timp in ms (300000 -> 300sec -> 5 minute)
pauzamare = 30000;
pauzamica = 5000;      // timp in ms (5000 -> 5sec)

tpudare = 0;
tpactual = 0;
tptrecut = 0;
tpminute = 0;
tpore = 0;
}

void loop()
{
digitalWrite(alimentaresenzor, HIGH); // pinul de alimentare senzor in 1 logic
delay(1000);  
citiredate = analogRead(pinsenzor);                // citire valoare pe intrarea analogica
procentumiditate = map(citiredate, 1023,0,0,100);  // transformare date primare in procente
digitalWrite(alimentaresenzor, LOW); // pinul de alimentare senzor in 0 logic

lcd.setCursor(0, 0);
lcd.print("Umiditate: ");
if (procentumiditate < 100) lcd.print(" ");
if (procentumiditate < 10) lcd.print(" ");
lcd.print(procentumiditate);
lcd.print("%");

if (procentumiditate < pragudare) // daca pamantul e prea uscat
{
digitalWrite(pinreleu, HIGH);     // se comanda releul pentru a actiona o pompa   
lcd.setCursor(0, 1);
lcd.print("Pompa pornita ! ");
tpudare = millis();               // se memoreaza timpul cand se uda
}
else                              // daca pamantul este suficient de umed
{
digitalWrite(pinreleu, LOW);      // releul este in repaus
lcd.setCursor(0, 1);
//lcd.print("Pompa oprita !  ");
lcd.print("P.opr.de:");
tpactual = millis();

tptrecut = tpactual - tpudare;
tptrecut = tptrecut/60000;       // transformare in minute
tpore = tptrecut/60;
tpminute = tptrecut - 60*tpore;
if (tpore<100) lcd.print(" ");
if (tpore<10) lcd.print(" ");
lcd.print(tpore);
lcd.print("h");
if (tpminute<10) lcd.print(" ");
lcd.print(tpminute);
lcd.print("' ");

delay(pauzamare);                 // pauza mare intre citiri cand pamantul este umed
}

delay(pauzamica);	          // pauza intre cititi
}
