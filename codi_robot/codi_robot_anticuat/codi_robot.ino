#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount =6;
uint16_t sensorValues[SensorCount];
int E1 = 6;
int M1 = 7; // dreta
int E2 = 5;
int M2 = 4; // esquerra
int vel_base = 180;
int vel_esq = 0;
int vel_dret = 0;
void avanzar(){
  analogWrite(E1, vel_dret); // difèrencia de 5 
  analogWrite(E2, vel_esq);
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

    // configurar sensors
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){9,8,3,2,1,10},SensorCount);

    // 2.5 ms RC read timeout (default)* 10 reads per calibrate() call
    // = mas o menos 25 ms per calibrate() call.
    // call calibrate() 400 times to make calibration take about 20 seconds
    for(uint16_t i =0; i <400;i++){
      qtr.calibrate();
    }
    Serial.begin(9600);
  
    Serial.println("minimos");
    for(uint8_t i = 0; i < SensorCount;i++){
       
         Serial.println(qtr.calibrationOn.minimum[i]);
       
    }

    Serial.println();
    Serial.println("maximos");
   for(uint8_t i = 0; i < SensorCount;i++){

         Serial.println(qtr.calibrationOn.maximum[i]);
       
    }
    Serial.println();
    Serial.println();
    
    delay(1000);


}
void loop() {
  
  uint16_t posicion = qtr.readLineBlack(sensorValues);
  // Calcula el error
  int error = 2500 - posicion;
  int vel_motor = error * 0.2;
  vel_dret = vel_base - vel_motor;
  vel_esq = vel_base + vel_motor;
  Serial.println(posicion);
  analogWrite(E1, constrain(vel_dret,0,255)); // difèrencia de 5 
  analogWrite(E2, constrain(vel_esq,0,255));
  delay(2);
  




}