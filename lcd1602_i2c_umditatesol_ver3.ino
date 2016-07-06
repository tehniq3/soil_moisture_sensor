// sketch scris de niq_ro (Nicu FLORICA), Craiova, 22.06.2016
// versiune pentru udare, 27.06.2016
// versiune indicate timp scurs de la ultima udare, 02.07.2016
// versiune pentru 4 zone de control, 06.07.2016
// http://www.tehnic.go.ro
// http://nicuflorica.blogspot.ro/
// http://arduinotehniq.blogspot.com/
// http://www.arduinotehniq.com/

#include <Wire.h>                // folosire librarie pentru protocol i2c
#include <LiquidCrystal_I2C.h>   // folosire librarie pentru afisaj lcd1602 pe i2c

// afisaj 1602 pe i2c cu adresa 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

int citiredate1, citiredate2, citiredate3, citiredate4;
int procentumiditate1, procentumiditate2, procentumiditate3, procentumiditate4;
#define pinsenzor1 A0             // senzorul de masura se conecteaza la pinul definit
#define pinsenzor2 A1
#define pinsenzor3 A2
#define pinsenzor4 A3
#define alimentaresenzor1 6      // senzorul nu va fi alimentat permanent pt. evitare efect de coroziune (electroliza)
#define pinreleu1 7              // comanda releului care poate porni o pompa se conecteaza la pinul definit
#define alimentaresenzor2 8
#define pinreleu2 9
#define alimentaresenzor3 10
#define pinreleu3 11
#define alimentaresenzor4 12
#define pinreleu4 13





byte pragudare;                  // variabila pentru prag pornire pompa (0..100%)
unsigned long pauzamare;         // variabila pentru timp intre citiri (in ms) cand pamantul este umed;
unsigned int pauzamica;          // variabila pentru timp intre citiri (in ms) cand pamantul este uscat;

unsigned long tpudare1, tpudare2, tpudare3, tpudare4;
unsigned long tpactual;
unsigned long tptrecut1, tptrecut2, tptrecut3, tptrecut4;
int tpminute1, tpminute2, tpminute3, tpminute4;
int tpore1, tpore2, tpore3, tpore4;


void setup()
{
pinMode(alimentaresenzor1, OUTPUT); // definim pinul ca iesire
pinMode(alimentaresenzor2, OUTPUT);
pinMode(alimentaresenzor3, OUTPUT);
pinMode(alimentaresenzor4, OUTPUT);
pinMode(pinreleu1, OUTPUT);         // definim pinul ca iesire
pinMode(pinreleu2, OUTPUT);
pinMode(pinreleu3, OUTPUT);
pinMode(pinreleu4, OUTPUT);

digitalWrite(alimentaresenzor1, LOW); // pinul ramane in 0 logic
digitalWrite(alimentaresenzor2, LOW);
digitalWrite(alimentaresenzor3, LOW);
digitalWrite(alimentaresenzor4, LOW);
digitalWrite(pinreleu1, LOW);         // pinul ramane in 0 logic
digitalWrite(pinreleu2, LOW);
digitalWrite(pinreleu3, LOW);
digitalWrite(pinreleu4, LOW);
  
lcd.begin();  // initializare afisaj
lcd.backlight(); // aprindere fundal

lcd.setCursor(1, 0);   // pozitionare cursor pe colana a 4-a din stanga - sus
lcd.print("sistem udare"); // afisare text
lcd.setCursor(1, 1);   // mutare cursor pe coloana a 2-a din stanga - jos
lcd.print("sol in 4 zone"); // afisare text
delay(3000);           // temporizare 3 secunde
lcd.clear();           // stergere ecran 

pragudare = 25;        // prag alimentare pompa in % (25%)
//pauzamare = 300000;    // timp in ms (300000 -> 300sec -> 5 minute)
pauzamare = 5000;
pauzamica = 3000;      // timp in ms (5000 -> 5sec)

tpudare1 = 0;
tpudare2 = 0;
tpudare3 = 0;
tpudare4 = 0;
tpactual = 0;
tptrecut1 = 0;
tptrecut2 = 0;
tptrecut3 = 0;
tptrecut4 = 0;
tpminute1 = 0;
tpminute2 = 0;
tpminute3 = 0;
tpminute4 = 0;
tpore1 = 0;
tpore2 = 0;
tpore3 = 0;
tpore4 = 0;
}

void loop()
{
digitalWrite(alimentaresenzor1, HIGH); // pinul de alimentare senzor in 1 logic
delay(1000);  
citiredate1 = analogRead(pinsenzor1);                // citire valoare pe intrarea analogica
procentumiditate1 = map(citiredate1, 1023,0,0,100);  // transformare date primare in procente
digitalWrite(alimentaresenzor1, LOW); // pinul de alimentare senzor in 0 logic

lcd.setCursor(0, 0);
lcd.print("Umiditate1: ");
if (procentumiditate1 < 100) lcd.print(" ");
if (procentumiditate1 < 10) lcd.print(" ");
lcd.print(procentumiditate1);
lcd.print("%");

if (procentumiditate1 < pragudare) // daca pamantul e prea uscat
{
digitalWrite(pinreleu1, HIGH);     // se comanda releul pentru a actiona o pompa   
lcd.setCursor(0, 1);
lcd.print("Pompa 1 pornita ! ");
tpudare1 = millis();               // se memoreaza timpul cand se uda
delay(pauzamica);	          // pauza intre cititi
}
else                              // daca pamantul este suficient de umed
{
digitalWrite(pinreleu1, LOW);      // releul este in repaus
lcd.setCursor(0, 1);
//lcd.print("Pompa oprita !  ");
lcd.print("P1opr.de:");
tpactual = millis();

tptrecut1 = tpactual - tpudare1;
tptrecut1 = tptrecut1/60000;       // transformare in minute
tpore1 = tptrecut1/60;
tpminute1 = tptrecut1 - 60*tpore1;
if (tpore1<100) lcd.print(" ");
if (tpore1<10) lcd.print(" ");
lcd.print(tpore1);
lcd.print("h");
if (tpminute1<10) lcd.print("0");
lcd.print(tpminute1);
lcd.print("' ");
delay(pauzamare);                 // pauza mare intre citiri cand pamantul este umed
}

// senzor 2
digitalWrite(alimentaresenzor2, HIGH); // pinul de alimentare senzor in 1 logic
delay(1000);  
citiredate2 = analogRead(pinsenzor2);                // citire valoare pe intrarea analogica
procentumiditate2 = map(citiredate2, 1023,0,0,100);  // transformare date primare in procente
digitalWrite(alimentaresenzor2, LOW); // pinul de alimentare senzor in 0 logic

lcd.setCursor(0, 0);
lcd.print("Umiditate2: ");
if (procentumiditate2 < 100) lcd.print(" ");
if (procentumiditate2 < 10) lcd.print(" ");
lcd.print(procentumiditate2);
lcd.print("%");

if (procentumiditate2 < pragudare) // daca pamantul e prea uscat
{
digitalWrite(pinreleu2, HIGH);     // se comanda releul pentru a actiona o pompa   
lcd.setCursor(0, 1);
lcd.print("Pompa 2 pornita ! ");
tpudare2 = millis();               // se memoreaza timpul cand se uda
delay(pauzamica);	          // pauza intre cititi
}
else                              // daca pamantul este suficient de umed
{
digitalWrite(pinreleu2, LOW);      // releul este in repaus
lcd.setCursor(0, 1);
//lcd.print("Pompa oprita !  ");
lcd.print("P2opr.de:");
tpactual = millis();

tptrecut2 = tpactual - tpudare2;
tptrecut2 = tptrecut2/60000;       // transformare in minute
tpore2 = tptrecut2/60;
tpminute2 = tptrecut2 - 60*tpore2;
if (tpore2<100) lcd.print(" ");
if (tpore2<10) lcd.print(" ");
lcd.print(tpore2);
lcd.print("h");
if (tpminute2<10) lcd.print("0");
lcd.print(tpminute2);
lcd.print("' ");
delay(pauzamare);                 // pauza mare intre citiri cand pamantul este umed
}

// senzor 3
digitalWrite(alimentaresenzor3, HIGH); // pinul de alimentare senzor in 1 logic
delay(1000);  
citiredate3 = analogRead(pinsenzor3);                // citire valoare pe intrarea analogica
procentumiditate3 = map(citiredate3, 1023,0,0,100);  // transformare date primare in procente
digitalWrite(alimentaresenzor3, LOW); // pinul de alimentare senzor in 0 logic

lcd.setCursor(0, 0);
lcd.print("Umiditate3: ");
if (procentumiditate3 < 100) lcd.print(" ");
if (procentumiditate3 < 10) lcd.print(" ");
lcd.print(procentumiditate3);
lcd.print("%");

if (procentumiditate3 < pragudare) // daca pamantul e prea uscat
{
digitalWrite(pinreleu3, HIGH);     // se comanda releul pentru a actiona o pompa   
lcd.setCursor(0, 1);
lcd.print("Pompa 3 pornita ! ");
tpudare3 = millis();               // se memoreaza timpul cand se uda
delay(pauzamica);	          // pauza intre cititi
}
else                              // daca pamantul este suficient de umed
{
digitalWrite(pinreleu3, LOW);      // releul este in repaus
lcd.setCursor(0, 1);
//lcd.print("Pompa oprita !  ");
lcd.print("P3opr.de:");
tpactual = millis();

tptrecut3 = tpactual - tpudare3;
tptrecut3 = tptrecut3/60000;       // transformare in minute
tpore3 = tptrecut3/60;
tpminute3 = tptrecut3 - 60*tpore3;
if (tpore3<100) lcd.print(" ");
if (tpore3<10) lcd.print(" ");
lcd.print(tpore3);
lcd.print("h");
if (tpminute3<10) lcd.print("0");
lcd.print(tpminute3);
lcd.print("' ");
delay(pauzamare);                 // pauza mare intre citiri cand pamantul este umed
}

// senzor 4
digitalWrite(alimentaresenzor4, HIGH); // pinul de alimentare senzor in 1 logic
delay(1000);  
citiredate4 = analogRead(pinsenzor4);                // citire valoare pe intrarea analogica
procentumiditate4 = map(citiredate4, 1023,0,0,100);  // transformare date primare in procente
digitalWrite(alimentaresenzor4, LOW); // pinul de alimentare senzor in 0 logic

lcd.setCursor(0, 0);
lcd.print("Umiditate4: ");
if (procentumiditate4 < 100) lcd.print(" ");
if (procentumiditate4 < 10) lcd.print(" ");
lcd.print(procentumiditate4);
lcd.print("%");

if (procentumiditate4 < pragudare) // daca pamantul e prea uscat
{
digitalWrite(pinreleu4, HIGH);     // se comanda releul pentru a actiona o pompa   
lcd.setCursor(0, 1);
lcd.print("Pompa 4 pornita ! ");
tpudare4 = millis();               // se memoreaza timpul cand se uda
delay(pauzamica);	          // pauza intre cititi
}
else                              // daca pamantul este suficient de umed
{
digitalWrite(pinreleu4, LOW);      // releul este in repaus
lcd.setCursor(0, 1);
//lcd.print("Pompa oprita !  ");
lcd.print("P4opr.de:");
tpactual = millis();

tptrecut4 = tpactual - tpudare4;
tptrecut4 = tptrecut4/60000;       // transformare in minute
tpore4 = tptrecut4/60;
tpminute4 = tptrecut4 - 60*tpore4;
if (tpore4<100) lcd.print(" ");
if (tpore4<10) lcd.print(" ");
lcd.print(tpore4);
lcd.print("h");
if (tpminute4<10) lcd.print("0");
lcd.print(tpminute4);
lcd.print("' ");
delay(pauzamare);                 // pauza mare intre citiri cand pamantul este umed
}


//delay(pauzamica);	          // pauza intre cititi
}
