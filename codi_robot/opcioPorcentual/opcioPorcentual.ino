#include <QTRSensors.h>

/* Calcul porcentual de motor. Dividim la potencia a cada roda porcentualmente depenent de la distancia a la linea, si una gira al 70%
la altra girara al 30%. Aixo amb la velocitat base definida. 

Ex: Si posicio = 3500, la dreta gira amb velocitat |(3500/5000)*(200*2) = 280 amb constrain -> 255|
i la esquerra amb velocitat |400 - 280 = 120| Aixo moura el robot cap a la dreta.  */

//Definicio variables i constants

QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

int E1 = 6, M1 = 7, E2 = 5, M2 = 4; //M1 = Motor dreta, M2 = MotorEsquerra

const int vel_base = 180; //Velocitat robot

int vel_esq = 0, vel_dret = 0; // Definir velocitats de entrada

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
void setup(){
  //Definir pins
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //Configurar sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){9,8,3,2,1,10},SensorCount);

  //Duracio de 20 segons per calibrar.
  for(uint16_t i = 0; i < 400; i++){
    qtr.calibrate();
  }

  Serial.begin(9600);
  //Valors calibracio minims
  Serial.println("minimos");
  for(uint8_t i = 0; i < SensorCount; i++){
    Serial.println(qtr.calibrationOn.minimum[i]);
  }

  Serial.println();
  //Valors calibracio maxims
  Serial.println("maximos");
  for(uint8_t i = 0; i < SensorCount; i++){
    Serial.println(qtr.calibrationOn.maximum[i]);
  }
  Serial.println();
  delay(1000);
}

void loop() {
  //Definir la posicio relativa a la linea 
  uint16_t posicion = qtr.readLineBlack(sensorValues);
  double percentatge = posicion/5000.00;
  
  //Calcul velocitat de cada roda basat amb percentatges
  vel_dret = percentatge * (vel_base * 2); 
  vel_esq = (vel_base * 2) - vel_dret;

  Serial.println(posicion);
  Serial.println(vel_dret);
  Serial.println(vel_esq);
  Serial.println();
  Serial.println();

  //Escriure el valor de velocitat pels motors
  analogWrite(E1, constrain(vel_dret,0,vel_base));  
  analogWrite(E2, constrain(vel_esq,0,vel_base));

  //Cantidad que es pausa abans de calcular una altre velocitat
  delay(2);
}