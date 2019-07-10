// Programa : Driver motor de passo A4988
// Autor : Arduino e Cia

#include <AccelStepper.h>

int velocidade_motor = 1000; 
long int aceleracao_motor = 32000;
bool aux = 0; 

// Definicao pino ENABLE
int pino_enable = 10;

// Definicao pinos STEP e DIR
AccelStepper motor1(1,7,4 );

void setup()
{
  //Serial.begin(9600);
  pinMode(pino_enable, OUTPUT);
  // Configuracoes iniciais motor de passo
  motor1.setMaxSpeed(velocidade_motor);
  motor1.setSpeed(velocidade_motor);
  motor1.setAcceleration(aceleracao_motor);

    digitalWrite(pino_enable, HIGH);
    delay(1000);
  
  //Serial.println("Digite 1, 2 ou 3 e clique em ENVIAR...");
}

void loop()  {
  //Desabilita o movimento
  digitalWrite(pino_enable, LOW);
  
  // Move o motor no sentido horario
  if (aux == 0 && motor1.isRunning() != 1){
    motor1.moveTo(400);
    aux = 1;
  }
  // Move o motor no sentido anti-horario
  if (aux == 1 && motor1.isRunning() != 1)
  {
    motor1.moveTo(-400);
    aux = 0;
  }
  // Comando para acionar o motor no sentido especificado
  motor1.run();
}  
