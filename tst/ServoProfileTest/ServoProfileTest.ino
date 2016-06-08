#include <Servo.h>

const int StepNum = 50;
const float pi = 3.14159265359;

float CurveProfile[StepNum] = { 0 };

float pi_inv = 0.318309886183791;

float pi_oversteps = pi / float(StepNum);

const int min_us =       544;     // the shortest pulse sent to a servo
const int max_us   =   2400;     // the longest pulse sent to a servo

const int min_angle = 0;
const int max_angle = 180;

//value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  float curStep = 0;
  for (int iStep = 0; iStep < StepNum; iStep++)
  {
    curStep = float(iStep);
    CurveProfile[iStep] = pi_inv * ((pi_oversteps * iStep) - (cos((pi_oversteps * iStep)) * sin((pi_oversteps * iStep))));
    //Serial.print(CurveProfile[iStep],5);
    //Serial.print(",");
  }

  myServo.attach(2);
  myServo.write(90);
  int val = myServo.readMicroseconds();
  Serial.print("From Library :");
  Serial.println(val);

  int calcval = map(90, 0, 180, min_us, max_us);

  Serial.print("From Calc :");
  Serial.println(calcval);

  calcval = MapToMicros( 90.0);

  Serial.print("From NewCalc :");
  Serial.println(calcval);

float target_angle = 45;
   for (int iStep = 0; iStep < StepNum; iStep++)
   {
    Serial.print(target_angle * CurveProfile[iStep],5);
    Serial.print(",");
   }
Serial.println("");
   for (int iStep = 0; iStep < StepNum; iStep++)
   {
    Serial.print(MapToMicros(target_angle * CurveProfile[iStep]),5);
    Serial.print(",");
   }


  
}

void loop() {
  // put your main code here, to run repeatedly:

}

int MapToMicros(float x)
{
  // convert the required angle to uS for higher accuracy
  int valout = ( x - min_angle) * (max_us - min_us) / (max_angle - min_angle) + min_us;
  return valout;
}



