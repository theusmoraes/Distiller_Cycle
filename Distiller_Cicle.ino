const int soneloidePin = 6; // Definir qual é a porta no arduino da Valvula Soneloide
const int boia1Pin = 2; // Definir qual é a Porta do sensor de nivel d'agua
const int boia2Pin = 3; // Definir qual é a Porta do sensor de nivel d'agua


void setup() {
  
  // Setando a entrada ou saido do pino
  pinMode (boia1Pin, INPUT);
  pinMode (boia2Pin, INPUT);
  pinMode (soneloidePin, OUTPUT);  
}

void loop() {
  //Aqui estou botando o valor que a boia esta gerando numa variavel, sendo HIGH, a boia cheia d'água e LOW, a boia vazia.
  int boia2_estado = digitalRead(boia2Pin);
  int boia1_estado = digitalRead(boia1Pin);
  //Nesta parte, primeiramente se a primeira boia estiver "LOW" significa que precisa encher o recipiente, ja se a boia 2 tiver "HIGH" precisa parar de encher
  if  (boia1_estado == LOW){ 
    digitalWrite(soneloidePin,HIGH); 
  }else{
  if (boia2_estado == HIGH) {
    digitalWrite(soneloidePin,LOW);
  }
  }
}
