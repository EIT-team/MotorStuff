

#include <Servo.h>

const int StepNum = 50;
const float pi = 3.14159265359;

float CurveProfile[StepNum] = { 0 };

float pi_inv = 0.318309886183791;

float pi_oversteps = pi / float(StepNum);

int min_pw =       544;     // the shortest pulse sent to a servo  
int max_pw   =   2400;     // the longest pulse sent to a servo 

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

	int calcval = map(90, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);


	Serial.print("From Calc :");
	Serial.println(calcval);








}

void loop() {
  // put your main code here, to run repeatedly:

}

