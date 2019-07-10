 #include <AccelStepper.h>
int velocidade_motor = 1000; 
int aceleracao_motor = 32000;
bool aux = 0; 

int temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder

// Definicao pino ENABLE
int pino_enable = 10;

// Definicao pinos STEP e DIR
AccelStepper motor1(1,7,4 );
 
 int val; 
 int encoder0PinA = 2;
 int encoder0PinB = 3;
 int encoder0Pos = 0;
 int encoder0PinALast = LOW;
 int n = LOW;
 int fimcurso_direita = 11;
 int fimcurso_esquerda = 12;

 void setup() {
  Serial.begin(9600);
  pinMode(pino_enable, OUTPUT);
  // Configuracoes iniciais motor de passo
  motor1.setMaxSpeed(velocidade_motor);
  motor1.setSpeed(velocidade_motor);
  motor1.setAcceleration(aceleracao_motor);

  pinMode(fimcurso_direita, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA
  pinMode(fimcurso_esquerda, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA

  
  pinMode  (encoder0PinA,INPUT_PULLUP);
  pinMode (encoder0PinB,INPUT_PULLUP);

  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);
  
   
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
  
  Serial.begin (115200);
 } 

 void loop() { 

  /*##########ENCODER##########*/
  /* n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
     } else {
       encoder0Pos++;
     }
     Serial.print(encoder0Pos);
     Serial.print('\n');
   } 
   encoder0PinALast = n;
*/

 // Send the value of counter
  if( counter != temp ){
 // Serial.println (counter);
  temp = counter;
  }
  Serial.println (counter);


  /*##########MOTOR##########*/
  //Desabilita o movimento
  digitalWrite(pino_enable, HIGH);
  
  // Move o motor no sentido horario
  if (aux == 0 && motor1.isRunning() != 1){
    motor1.moveTo(200);
    aux = 1;
  }
  // Move o motor no sentido anti-horario
  if (aux == 1 && motor1.isRunning() != 1)
  {
    motor1.moveTo(-200);
    aux = 0;
  }
  // Comando para acionar o motor no sentido especificado
  motor1.run();  
 } 



   void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(3)==LOW) {
  counter++;
  }else{
  counter--;
  }
  }
   
  void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
  counter--;
  }else{
  counter++;
  }
  }
