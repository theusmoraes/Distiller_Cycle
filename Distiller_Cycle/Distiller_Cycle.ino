#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

OneWire pino(5);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
const int soneloidePin = 6; 
const int boia1Pin = 2; 
const int boia2Pin = 3; 

void setup() {
  pinMode (boia1Pin, INPUT);
  pinMode (boia2Pin, INPUT);
  pinMode (soneloidePin, OUTPUT);  
  barramento.begin();
  barramento.getAddress(sensor, 0);  
  lcd.begin (16,2);
}

void loop() {
  barramento.requestTemperatures(); 
  float temperatura = barramento.getTempC(sensor);
  int boia2_estado = digitalRead(boia2Pin);
  int boia1_estado = digitalRead(boia1Pin);
  if  (boia1_estado == HIGH){ 
    digitalWrite(soneloidePin,LOW); 
  }else{
    if (boia2_estado == LOW) {
      digitalWrite(soneloidePin,HIGH);
    }
  }
  lcd.setCursor (2,0);
  lcd.print("Temperatura");
  lcd.setCursor (5,1);
  lcd.print (temperatura);
  lcd.setCursor (10,1);
  lcd.print ("C");
  delay (250);
}
