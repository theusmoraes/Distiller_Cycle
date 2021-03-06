#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

OneWire pino(5);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
const int soneloidePin = 6; 
const int soneloideRua = 6; 
const int SuperiorEnvia = 2; 
const int InferiorEvia = 3; 
const int InferiorArmazena =  4;
const int BombaArmazena = 7;
int tempoFinalEnvia = 300;
int tempoFinalResfriaBomba = 400;
int tempoFinalResfriaSoneloide = 400;
long tempoAtual;
long tempoInicial;
int cont=0;

void setup() {
  pinMode (SuperiorEnvia, INPUT);
  pinMode (InferiorEvia, INPUT);
  pinMode (soneloidePin, OUTPUT);  
  pinMode (soneloideRua, OUTPUT);  
  pinMode (InferiorArmazena, INPUT);
  barramento.begin();
  
  barramento.getAddress(sensor, 0);  
  lcd.begin (16,2);
}

void loop() {
  
  barramento.requestTemperatures(); 
  float temperatura = barramento.getTempC(sensor);
  int InferiorEvia_estado = digitalRead(InferiorEvia);
  int SuperiorEnvia_estado = digitalRead(SuperiorEnvia);
  int InferiorArmazena_estado = digitalRead(InferiorArmazena);
  tempoAtual = millis()/1000; //Atualizando sempre o tempo atual
    if (InferiorEvia_estado == LOW) {//Se a boia inferior do enviar estiver low ligar soneloide
      digitalWrite(soneloidePin,HIGH);
      if (cont == 0){                // Se for a primeira vez que entrou nesse ciclo registra o tempo inicial que começou
        long TempoInicial = millis()/1000;
      }
      
      cont = 1;
      
      
    }else{
      if (soneloidePin == HIGH && tempoAtual - tempoInicial >= tempoFinalEnvia) { //Se a senloide tiver ligada e o tempo final ser alcançado, desliga soneloide liga bomba para re encher o armazena
        digitalWrite(soneloidePin,LOW);
        cont = 0; 
        digitalWrite(BombaArmazena,HIGH);
        tempoInicial = millis()/1000;
      }
    }
    if (BombaArmazena == HIGH && InferiorArmazena == LOW){ //Se bomba armazena estiver ligada e a agua estiver abaixo da boia liga solenoide rua
      digitalWrite(BombaArmazena,LOW);
      digitalWrite(soneloideRua,HIGH);
    }
    if (soneloideRua == HIGH && tempoAtual - tempoInicial >= tempoFinalResfriaSoneloide){ //A soneloide estando ligada ira desligar quando o tempo final ser alcançado
      digitalWrite(soneloideRua,LOW);
    }
    
  
  lcd.setCursor (2,0);
  lcd.print("Temperatura");
  lcd.setCursor (5,1);
  lcd.print (temperatura);
  lcd.setCursor (10,1);
  lcd.print ("C");
  delay (250);
}

