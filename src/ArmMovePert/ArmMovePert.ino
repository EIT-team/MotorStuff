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
float FRONT[3] = { 108, 70, 140 }; //114, 70, 140
float FRONT_INTER[3] = {106, 70, 137};
float MIDDLE[3] = { 100, 70, 130 }; //102 58 144
float BOTTOM[3] = { 100, 58, 150}; // 99 50 168
float SIDE[3] = { 100, 80, 150 };
float TOP_HIGH[3] = { 104, 124, 100 };
float TOP_SIDE[3] = { 65, 124, 100 }; // 104 135 110
float HOME[3] = { 98, 120, 90 };

float START[3] = {160, 130, 100};
float MOUNT[3] = {120, 135, 110};
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

  //delay(5000);

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


/*
 * ###############################
 * ###############################
 * ###############################
 */

  Sequence_9();

  //Sequence_11();
  
  //Sequence_8A();
  
 // CentreToFront(1000, 500);

//  delay(60000);

 //FrontToCentre(1000, 500);

  

/*
 * ###############################
 * ###############################
 * ###############################
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


