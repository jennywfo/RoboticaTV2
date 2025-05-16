#include <QTRSensors.h>
/* Opcio de control propocional, integral i derivatiu (Aquesta es la opcio del profe).
    Aixo funciona controlant el error pasat, el presente i el futur.
*/

//Definicio variables i constants

QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

int E1 = 6, M1 = 7, E2 = 5, M2 = 4; //Pins al Arduino. M1 = Motor dreta, M2 = MotorEsquerra

const int vel_base = 220, centre = 2500; //Velocitat robot i valor quan el robot esta centrat amb la linea, centre = 2500

int vel_motor, vel_esq = 0, vel_dret = 0; // Definir velocitats de entrada

int error = 0, ultimError = 0;
double kp = 0., ki = 0.01, kd = 0.25; //kp: Com de bruscs son els girs | ki: Aumenta el gir si el error es persistent | kd: Limita la velocitat del gir
int integral = 0, derivatiu = 0;

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
  uint16_t posicion = qtr.readLineBlack(sensorValues);

  // Calcul dels errors
  error = centre - posicion; //Diferencia entre el centre i la posicio actual
  integral += error; 
  derivatiu = error - ultimError; 
  ultimError = error;

  //Calcul de velocitats
  vel_motor = kp * error + ki * integral + kd * derivatiu; 
  vel_dret = vel_base - vel_motor;
  vel_esq = vel_base + vel_motor;

  Serial.println(posicion);
  Serial.println(vel_dret);
  Serial.println(vel_esq);
  Serial.println();
  Serial.println();

  //Escriure la velocitat de gir dels rodes
  analogWrite(E1, constrain(vel_dret,0,vel_base));  
  analogWrite(E2, constrain(vel_esq,0,vel_base));

  //Delay entre canvis de velocitats als rodes.
  delay(2);
}