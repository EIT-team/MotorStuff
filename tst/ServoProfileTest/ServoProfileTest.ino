#include <Servo.h>

//array for holding step profile
const int StepNum = 180;
float CurveProfile[StepNum] = { 0 };

//precalc for speed, in case we calc each loop
const float pi = 3.14159265359;
float pi_inv = 0.318309886183791;
float pi_oversteps = pi / float(StepNum);

const int min_us = 544;     // the shortest pulse sent to a servo
const int max_us = 2400;     // the longest pulse sent to a servo

const int min_angle = 0;
const int max_angle = 180;

//value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());

Servo myServo;

const int servopin = 4;

float g_CurrentAngle = 70;

int MotorDelay = 5;


void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);

	Serial.println("Hello, this is a servo smooth profile test. THis will shiver the servo like a sonofabitch");

	MakeCurveProfile();

	myServo.attach(servopin);
	myServo.write(g_CurrentAngle);


	/*
	//calc checks - compare to matlab ideal ones
	int val = myServo.readMicroseconds();
	Serial.print("From Library :");
	Serial.println(val);

	int calcval = map(g_CurrentAngle, 0, 180, min_us, max_us);

	Serial.print("From Calc :");
	Serial.println(calcval);

	calcval = MapToMicros(g_CurrentAngle);

	Serial.print("From NewCalc :");
	Serial.println(calcval);

	float target_angle = g_CurrentAngle;
	for (int iStep = 0; iStep < StepNum; iStep++)
	{
		Serial.print(target_angle * CurveProfile[iStep], 5);
		Serial.print(",");
	}
	Serial.println("");


	for (int iStep = 0; iStep < StepNum; iStep++)
	{
		Serial.print(MapToMicros(target_angle * CurveProfile[iStep]));
		Serial.print(",");
	}

	*/


}

void loop() {
	// put your main code here, to run repeatedly:

	float SetPoint = 50;

	Serial.print("Current pos is : ");
	Serial.print(g_CurrentAngle);
	Serial.print(" . Moving to : ");
	Serial.println(SetPoint);

	MoveServo(SetPoint);

	delay(2000);

	SetPoint = 130;

	Serial.print("Current pos is : ");
	Serial.print(g_CurrentAngle);
	Serial.print(" . Moving to : ");
	Serial.println(SetPoint);

	MoveServo(SetPoint);

	delay(2000);

	SetPoint = 70;

	Serial.print("Current pos is : ");
	Serial.print(g_CurrentAngle);
	Serial.print(" . Moving to : ");
	Serial.println(SetPoint);

	MoveServo(SetPoint);

	delay(2000);


}

int MapToMicros(float x)
{

	// convert the required angle to uS for higher accuracy - this is how servo library does it 
	int valout = (x - min_angle) * (max_us - min_us) / (max_angle - min_angle) + min_us - 1;
	return valout;
}

void MakeCurveProfile()
{
	float curStep = 0;
	for (int iStep = 0; iStep < StepNum; iStep++)
	{
		curStep = float(iStep);
		CurveProfile[iStep] = pi_inv * ((pi_oversteps * iStep) - (cos((pi_oversteps * iStep)) * sin((pi_oversteps * iStep))));
		//Serial.print(CurveProfile[iStep],5);
		//Serial.print(",");
	}
}


void MoveServo(float Target_angle)
{
	int cur_us = 0;
	for (int iStep = 0; iStep < StepNum; iStep++)
	{
		cur_us = WriteServo(iStep, g_CurrentAngle, Target_angle);
		Serial.print(cur_us);
		Serial.print(",");
		delay(MotorDelay);
	}

	//Serial.println("");

	g_CurrentAngle = Target_angle;

}

int WriteServo(int curStep, float curAngle, float TrgAngle)
{
	int next_us = MapToMicros(curAngle + (CurveProfile[curStep] * (TrgAngle - curAngle)));
	myServo.writeMicroseconds(next_us);
	return next_us;

}

