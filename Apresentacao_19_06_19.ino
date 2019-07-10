#include <AccelStepper.h>

int velocidade_motor = 1200; 
long int aceleracao_motor = 32000;
volatile float counter = 0; //This variable will increase or decrease depending on the rotation of encoder, volatile variables might change at any time, and thus the compiler must reload the variable whenever you reference it, rather than relying upon a copy it might have in a processor register

//Definicao pino ENABLE
int pino_enable = 10;

//Definicao pinos STEP e DIR
AccelStepper motor1(1,7,4);

 int val; 
 int encoder0PinA = 2;
 int encoder0PinB = 3;
 long encoder0Pos = 0;
 int encoder0PinALast = LOW;
 int n = LOW;
 float angulo = 0;

//MOTOR >> DRIVER AZUL - AMARELO, VERMELHO - PRETO. VERDE - VERDE, PRETO - AZUL
//Controle
float e_atual = 0;
float e_anterior1 = 0;
float e_anterior2 = 0;
float u_atual = 0;
float u_anterior1 = 0;
float u_anterior2 = 0;
float ref = 0;
float y = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(pino_enable, OUTPUT);
  //Configuracoes iniciais motor de passo
  motor1.setMaxSpeed(velocidade_motor*2);
  motor1.setSpeed(velocidade_motor);
  motor1.setAcceleration(aceleracao_motor);

  pinMode  (encoder0PinA,INPUT_PULLUP);
  pinMode (encoder0PinB,INPUT_PULLUP);

  digitalWrite(pino_enable, HIGH);
  delay(1000);}

  void loop() {
    n = digitalRead(encoder0PinA);
   if ((encoder0PinALast == LOW) && (n == HIGH)) {
     if (digitalRead(encoder0PinB) == LOW) {
       encoder0Pos--;
     } else {
       encoder0Pos++;
     }
     //Serial.println (encoder0Pos);
   } 
   encoder0PinALast = n;

   if(encoder0Pos > 800){
      encoder0Pos = encoder0Pos-800;}

      if(encoder0Pos < -800){
      encoder0Pos = encoder0Pos+800;}

      angulo = encoder0Pos*0.45;
    
    if (angulo > 180) {
      angulo = angulo - 360;}
    else {
      angulo = angulo;}

    e_atual = ref - angulo;
    u_atual = 82.421*(e_atual-1.619*e_anterior1+0.6556*e_anterior2)+1.788*u_anterior1-0.7877*u_anterior2; // CONTROLE PARA APRIMEIRA MASSA COM TS=0.05
    //u_atual = 78.713*(e_atual-1.619*e_anterior1+0.6555*e_anterior2)+1.788*u_anterior1-0.7877*u_anterior2; // CONTROLE PARA A MASSA DE 62,08G (3 MOEDAS DE 0,50 E 1 MOEDA DE 1,00)

    /*##########SATURAÇÃO##########*/
    if (u_atual > velocidade_motor){
      u_atual = velocidade_motor;}
    
    if (u_atual < -velocidade_motor){
      u_atual = -velocidade_motor;}
    
    e_anterior2 = e_anterior1;
    e_anterior1 = e_atual;
    u_anterior2 = u_anterior1;
    u_anterior1 = u_atual;

    motor1.setSpeed(-u_atual);
  
    //Serial.print (angulo);
    //Serial.print (" - ");
    //Serial.println (u_atual);

    /*##########MOTOR##########*/
    //Desabilita o movimento se == HIGH
    digitalWrite(pino_enable, LOW);

    motor1.runSpeed();

    //Comando para acionar o motor no sentido especificado
    motor1.run(); 
    }//Fim loop
    

