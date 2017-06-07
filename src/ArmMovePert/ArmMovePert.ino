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

int IndicatorPin = 30;
int LEDPin = 10;


// above centre 104,135,80
// above side - needed to avoid mount on way out 70 135 110
// off to side 40,130,100

//potential target positions // old ones
float BACK[3] = { 85, 69, 139 };
float FRONT[3] = { 114, 70, 140 }; //121 65, 140 or 117 65,142
float FRONT_INTER[3] = {106, 70, 137};
float MIDDLE[3] = { 100, 70, 130 }; //102 58 144
float BOTTOM[3] = { 100, 58, 150}; // 99 50 168
float SIDE[3] = { 100, 80, 150 };
float TOP_HIGH[3] = { 104, 124, 100 };
float TOP_SIDE[3] = { 65, 124, 100 }; // 104 135 110
float HOME[3] = { 98, 120, 90 };

float START[3] = {40, 130, 100};
float MOUNT[3] = {70, 135, 110};
float ABOVECENTRE[3] = {95, 135, 80}; // 104 135 80

//global variables of current positions
float Base_cur = START[0];
float Left_cur = START[1];
float Right_cur = START[2];

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


  Serial.print("Profile delay : ");
  Serial.println(ProfileDelay);


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

  for (int i = 0; i < MoveSteps; i++) {

    cur_x = x0 + (stepdist_x) * i;
    cur_y = y0 + (stepdist_y) * i;
    cur_z = z0 + (stepdist_z) * i;
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






void setup() {
  // put your setup code here, to run once:
  pinMode(IndicatorPin, OUTPUT);
  digitalWrite(IndicatorPin, 0);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, 0);



  Serial.begin(115200);

  MakeCurveProfile();


  digitalWrite(IndicatorPin, 1);
  delay(1);
  digitalWrite(IndicatorPin, 0);

  delay(5000);

  digitalWrite(IndicatorPin, 1);
  delay(1);
  digitalWrite(IndicatorPin, 0);




  BaseServo.attach(BasePin);
  LeftServo.attach(LeftPin);
  RightServo.attach(RightPin);

  Serial.println("Hello");

  goNow(START[0], START[1], START[2]);

  StartToCentre(1000, 250);
  Serial.println("Lets move this stuff about");

  //CheckAllPos();

  digitalWrite(IndicatorPin, 1);
  delay(1);
  digitalWrite(IndicatorPin, 0);
  digitalWrite(LEDPin, 1);



  /*###################################################
     ###################################################
     ###################################################
  */


  Sequence_11();


  /*###################################################
     ###################################################
     ###################################################
  */


  digitalWrite(IndicatorPin, 1);
  delay(1);
  digitalWrite(IndicatorPin, 0);
  digitalWrite(LEDPin, 0);



  delay(1000);
  CentreToStart(1000, 250);


  BaseServo.detach();
  LeftServo.detach();
  RightServo.detach();




}

void loop() {
  // put your main code here, to run repeatedly:

}


