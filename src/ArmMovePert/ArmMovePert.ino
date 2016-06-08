
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
float BACK[3] = { 121,72,139 };
float FRONT[3] = { 81,69,139 };
float CENTRE[3] = { 102,57,144 };
float BOTTOM[3] = { 99,50,168 };
float SIDE[3] = { 98,86,155 };
float TOP_HIGH[3] = { 98,155,100 };
float TOP_SIDE[3] = { 65,124,100 };


float HOME[3] = { 98,130,77 };

//global variables of current positions
float x_cur = HOME[0];
float y_cur = HOME[1];
float z_cur = HOME[2];


//servo smoothing stuffs
int MoveSteps = 10;



int MoveDelay = 50;






void goNow(float x, float y, float z)
{
	BaseServo.write(x);
	LeftServo.write(y);
	RightServo.write(z);

	//updated globals of current pos
	x_cur = float(x);
	y_cur = float(y);
	z_cur = float(z);
}

void goSmooth(float x, float y, float z)
{
	//get baseline positions
	float x0 = x_cur;
	float y0 = y_cur;
	float z0 = z_cur;

	float dist

	Serial.print("distance is: ");
	Serial.print(dist);



	for (int i = 0; i<dist; i += MoveSteps) {
		goNow(x0 + (x - x0)*i / dist, y0 + (y - y0) * i / dist, z0 + (z - z0) * i / dist);
		delay(MoveDelay);
	}
	goNow(x, y, z);
	delay(MoveDelay);



}



void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);

	BaseServo.attach(BasePin);
	LeftServo.attach(LeftPin);
	RightServo.attach(RightPin);

	goNow(HOME[0], HOME[1], HOME[2]);

}

void loop() {
  // put your main code here, to run repeatedly:

}
