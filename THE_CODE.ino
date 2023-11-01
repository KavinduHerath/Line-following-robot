// IMPORT THE LINE SENSOR LIBRARY
#include <BeeLineSensorPro.h>

// DEFINE THE PINS
#define M1 4
#define M1pwm 5
#define M2 7
#define M2pwm 6

//CONSTRACTOR OF BEELINESENSORPRO
BeeLineSensorPro sensor = BeeLineSensorPro((unsigned char[]) {
  A0, A1, A2, A3, A4, A5, A6, A7
}, LINE_BLACK);

void setup()
{
  Serial.begin(115200);
  pinMode(M1, OUTPUT);
  pinMode(M1pwm, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M2pwm, OUTPUT);

  //CALIBRATE THE SENSOR
  for (int i = 0; i < 100; i++) {
    sensor.calibrate();
    Mdrive(-120,120);  
  }
  Mdrive(0,0);
  delay(100);

   for (int i = 0; i < 200; i++) {
    sensor.calibrate();
    Mdrive(120,-120);  
  }
  Mdrive(0,0);
  delay(100);

   for (int i = 0; i < 100; i++) {
    sensor.calibrate();
    Mdrive(-120,120);  
  }
  Mdrive(0,0);
  delay(1000);
}

float kP = 0.2;
float kD = 1;
int last_value;

void loop()
{
  int err = sensor.readSensor();
  //for (int i = 0; i < 8; i++) {
  //Serial.print(sensor.values[i]);
  //Serial.print('\t');
  // }
  Serial.println(err);
  int m1 = 120;
  int m2 = 120;
  int diff = err*kP+(err-last_value)*kD;

  last_value = err;

  Mdrive(m1+diff, m2-diff);

}

//CONSTRUCT THE Mdrive FUNCTION
void Mdrive(int m1, int m2)
{
  if (m1 > 0) {
    if (m1 > 255) {
      m1 = 255;
    }
    digitalWrite(M1, HIGH);
    analogWrite(M1pwm, 255 - m1);
  }
  else {
    if (m1 < -255) {
      m1 = -255;
    }
    digitalWrite(M1, LOW);
    analogWrite(M1pwm, m1 * -1);
  }

  if (m2 > 0) {
    if (m2 > 255) {
      m2 = 255;

    }
    digitalWrite(M2, HIGH);
    analogWrite(M2pwm, 255 - m2);
  }
  else {
    if (m2 < -255) {
      m2 = -255;
    }
    digitalWrite(M2, LOW);
    analogWrite(M2pwm, m2 * -1);
  }
}
