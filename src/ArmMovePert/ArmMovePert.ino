#include <Servo.h>

Servo BaseServo;
Servo LeftServo;
Servo RightServo;

int BasePin = 7;
int LeftPin = 4;
int RightPin = 2;

int BaseMin = 12;
int BaseMax = 180;
int LeftMin = 20;
int LeftMax = 135;
int RightMin = 50;
int RightMax = 179;

//potential target positions
float BACK[3] = { 85,69,139 };
float FRONT[3] = { 121,65,140 };  // 81 69 139
float CENTRE[3] = { 102,58,144 };
float BOTTOM[3] = { 99,50,168 };
float SIDE[3] = { 104,82,150 };
float TOP_HIGH[3] = { 104,124,100 };
float TOP_SIDE[3] = { 65,124,100 };

float HOME[3] = { 98,120,90 };

//global variables of current positions
float Base_cur = HOME[0];
float Left_cur = HOME[1];
float Right_cur = HOME[2];

//servo smoothing stuffs
int MoveSteps = 10;
int MoveDelay = 50;

// sin profile stuff
const int StepNum = 180;
float CurveProfile[StepNum] = { 0 };
//int ProfileDelay = 5; 

//precalc for speed, in case we calc each loop
const float pi = 3.14159265359;
float pi_inv = 0.318309886183791;
float pi_oversteps = pi / float(StepNum);

const int min_us = 544;     // the shortest pulse sent to a servo
const int max_us = 2400;     // the longest pulse sent to a servo

const int min_angle = 0;
const int max_angle = 180;

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
		CurveProfile[iStep] = pi_inv * ((pi_oversteps * iStep) - (cos(pi_oversteps * iStep) * sin(pi_oversteps * iStep)));
		//Serial.print(CurveProfile[iStep],5);
		//Serial.print(",");
	}
}


int WriteServoBase(int curStep, float curAngle, float TrgAngle)
{
	int next_us = MapToMicros(curAngle + (CurveProfile[curStep] * (TrgAngle - curAngle)));
	BaseServo.writeMicroseconds(next_us);
	return next_us;

}

int WriteServoLeft(int curStep, float curAngle, float TrgAngle)
{
	int next_us = MapToMicros(curAngle + (CurveProfile[curStep] * (TrgAngle - curAngle)));
	LeftServo.writeMicroseconds(next_us);
	return next_us;

}

int WriteServoRight(int curStep, float curAngle, float TrgAngle)
{
	int next_us = MapToMicros(curAngle + (CurveProfile[curStep] * (TrgAngle - curAngle)));
	RightServo.writeMicroseconds(next_us);
	return next_us;

}


void MoveServos(float Target_angle_Base, float Target_angle_Left, float Target_angle_Right, int Duration)
{
	int cur_us_Base = 0;
	int cur_us_Left = 0;
	int cur_us_Right = 0;

	int ProfileDelay = (Duration * 1000) / StepNum; 

	/*
	Serial.print("Profile delay : ");
	Serial.println(ProfileDelay);
	*/
	
	for (int iStep = 0; iStep < StepNum; iStep++)
	{
		cur_us_Base = WriteServoBase(iStep, Base_cur, Target_angle_Base);
		cur_us_Left = WriteServoLeft(iStep, Left_cur, Target_angle_Left);
		cur_us_Right = WriteServoRight(iStep, Right_cur, Target_angle_Right);
		 /*
		Serial.print(cur_us_Base);
		Serial.print(",");
		Serial.print(cur_us_Left);
		Serial.print(",");
		Serial.print(cur_us_Right);
		Serial.println("");
		 */
		delayMicroseconds(ProfileDelay);
	}

	//Serial.println("");

	Base_cur = Target_angle_Base;
	Left_cur = Target_angle_Left;
	Right_cur = Target_angle_Right;

}



void goNow(float x, float y, float z)
{
	BaseServo.write(x);
	LeftServo.write(y);
	RightServo.write(z);

	//updated globals of current pos
	Base_cur = float(x);
	Left_cur = float(y);
	Right_cur = float(z);
}

void goSmooth(float x, float y, float z)
{
	//get baseline positions
	float x0 = Base_cur;
	float y0 = Left_cur;
	float z0 = Right_cur;

	float stepdist_x = (x - x0) / MoveSteps;
	float stepdist_y = (y - y0) / MoveSteps;
	float stepdist_z = (z - z0) / MoveSteps;

	float cur_x = 0;
	float cur_y = 0;
	float cur_z = 0;

	for (int i = 0; i<MoveSteps; i++) {

		cur_x = x0 + (stepdist_x)*i;
		cur_y = y0 + (stepdist_y)*i;
		cur_z = z0 + (stepdist_z)*i;
		goNow(cur_x, cur_y, cur_z);

		/*
		Serial.print(cur_x);
		Serial.print(",");
		Serial.print(cur_y);
		Serial.print(",");
		Serial.print(cur_z);
		Serial.println("");
		*/

		delay(MoveDelay);
	}

	goNow(x, y, z);
	
	/*
	Serial.print(x);
	Serial.print(",");
	Serial.print(y);
	Serial.print(",");
	Serial.print(z);
	Serial.println("");
	*/
	
	delay(MoveDelay);
}


void CheckAllPos(int Duration, int Pause)

{
	delay(Pause);
	Serial.println("Front");
	MoveServos(FRONT[0], FRONT[1], FRONT[2], Duration);
	delay(Pause);
	Serial.println("Back");
	MoveServos(BACK[0], BACK[1], BACK[2], Duration);
	delay(Pause);
	Serial.println("Centre");
	MoveServos(CENTRE[0], CENTRE[1], CENTRE[2], Duration);
	delay(Pause);
	Serial.println("Side");
	MoveServos(SIDE[0], SIDE[1], SIDE[2], Duration);
	delay(Pause);
	Serial.println("Bottom");
	MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], Duration);
	delay(Pause);
	Serial.println("Centre");
	MoveServos(CENTRE[0], CENTRE[1], CENTRE[2], Duration);
	delay(Pause);
	Serial.println("Home");
	MoveServos(HOME[0], HOME[1], HOME[2], Duration);
}




void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);

	MakeCurveProfile();

	BaseServo.attach(BasePin);
	LeftServo.attach(LeftPin);
	RightServo.attach(RightPin);

	Serial.println("Hello");

	goNow(HOME[0], HOME[1], HOME[2]);


	CheckAllPos(1000, 1000);


	BaseServo.detach();
	LeftServo.detach();
	RightServo.detach();




}

void loop() {
  // put your main code here, to run repeatedly:

}


