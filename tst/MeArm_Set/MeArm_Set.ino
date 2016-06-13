

#include <Servo.h>

Servo myservo0, myservo1, myservo2 ;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int posmin = 0;
int posmax = 181;

void setup() {
  Serial.begin(115200);
  myservo0.attach(7);  // attaches the servo on pin 11 to the servo object
  myservo1.attach(4);  // attaches the servo on pin 10 to the servo object
  myservo2.attach(2);  // attaches the servo on pin 9 to the servo object
  Serial.println("hello, this is a servo test");
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
      myservo0.write(X);
      myservo1.write(Y);
      myservo2.write(Z);


    }
  }

}

