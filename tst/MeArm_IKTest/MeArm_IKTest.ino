/* meArm IK test - York Hackspace May 2014
   Test applying Nick Moriarty's Inverse Kinematics solver
   to Phenoptix' meArm robot arm, to walk a specified path.

   Pins:
   Arduino    Base   Shoulder  Elbow    Gripper
      GND    Brown     Brown   Brown     Brown
       5V      Red       Red     Red       Red
       11    Yellow
       10             Yellow
        9                     Yellow
        6                               Yellow
*/
#include "meArm.h"
#include <Servo.h>

int basePin = 7;
int shoulderPin = 2;
int elbowPin = 4;
int gripperPin = 8;

meArm arm(
  180, 12, -pi / 2, pi / 2,
  160, 61, pi / 4, 122 * pi / 180,
  55, 110, 0, -40* pi / 180,
  35, 90, pi / 2, 0
);

void setup() {
  Serial.begin(115200);
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);

}

void loop() {

  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    float X = Serial.parseInt();
    // do it again:
    float Y = Serial.parseInt();
    // do it again:
    float Z = Serial.parseInt();

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {
      Serial.print("Moving motor to ");
      Serial.print(X);
      Serial.print(",");
      Serial.print(Y);
      Serial.print(",");
      Serial.println(Z);
      arm.gotoPoint(X,Y,Z);
      

    }
  }



 
  
}



bool goifreach(float x, float y, float z)
{
  if (arm.isReachable(x, y, z))
  {
    arm.gotoPoint(x,y,z);
  }
  else
  {
    Serial.println("CANT REACH!!!");
  }
}



