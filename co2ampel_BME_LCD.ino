#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Seeed_BME280.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

BME280 bme280;

int ROT=6;
int GELB=7;
int GRUN=8;

int SensorPin = 11; 
int Messbereich = 5000;
unsigned long ZeitMikrosekunden; 
unsigned long ZeitMillisekunden; 

int PPM = 0; 
float Prozent=0; 


void setup() 
{
lcd.init();
lcd.backlight  ();
Serial.begin(9600);
if(!bme280.init())
{
Serial.println("FEHLER!");
}
  pinMode(SensorPin, INPUT); 
  Serial.begin(9600); 
  pinMode(ROT, OUTPUT);
  pinMode(GELB, OUTPUT);
  pinMode(GRUN, OUTPUT);
}

void loop() 
{  
   float Druck;
  float Pascal;
  double Bar;  
ZeitMikrosekunden = pulseIn(SensorPin, HIGH, 2000000);
ZeitMillisekunden = ZeitMikrosekunden/1000;
float Prozent = ZeitMillisekunden / 1004.0;
PPM = Messbereich * Prozent;
Serial.print("CO2 Anteil in der Luft in PPM: ");
Serial.println(PPM);
if (PPM <800 ) 
{ 
digitalWrite(GRUN, HIGH); 
digitalWrite(GELB, LOW); 
digitalWrite(ROT, LOW); 
}
if (PPM >=800 && PPM <=1000)
{ 
digitalWrite(GRUN, HIGH); 
digitalWrite(GELB, HIGH); 
digitalWrite(ROT, LOW); 
}
if (PPM >1000 && PPM <=1400)
{
digitalWrite(GRUN, LOW); 
digitalWrite(GELB, HIGH); 
digitalWrite(ROT, LOW); 
}
if (PPM >1400)
{ 
digitalWrite(GRUN, LOW); 
digitalWrite(GELB, LOW); 
digitalWrite(ROT, HIGH);
delay(1000);
digitalWrite(ROT, LOW); 
delay(1000);
digitalWrite(ROT, HIGH);
delay(1000);
digitalWrite(ROT, LOW); 
delay(1000);
digitalWrite(ROT, HIGH);
delay(1000);
digitalWrite(ROT, LOW); 
delay(1000);
}

 Serial.print("Temperatur : ");   
          Serial.print(bme280.getTemperature());
          Serial.println("C");
 
          
          Serial.print("  Druck : ");
          Pascal = bme280.getPressure(); 
          Bar = (Pascal/100000); 
          Serial.print(Bar); 
          Serial.println(" Bar");
          
          Serial.print("Feuchtigkeit : "); 
          Serial.print(bme280.getHumidity());
          Serial.println("%");
          Serial.println(" ");
          
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp.");
  lcd.setCursor(8,0);
  lcd.print( bme280.getTemperature() );
  lcd.setCursor(14,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("CO2");
  lcd.setCursor(8,1);
  lcd.print( PPM );
  lcd.setCursor(13,1);
  lcd.print("ppm");

delay(3000);
}
