#include <QTRSensors.h>
int E1 = 6;
int M1 = 7;
int E2 = 5;
int M2 = 4;
void avanzar(){
  analogWrite(E1, 255); // difèrencia de 5 
  analogWrite(E2, 255);
}

void blink(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
void setup()
{
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {

   //avanzar();

}