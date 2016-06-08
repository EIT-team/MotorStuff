

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int posmin =0;
int posmax = 181;

void setup() {
  Serial.begin(115200);
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
  Serial.println("hello, this is a servo test");
}

void loop() {



  while (Serial.available() > 0) {
    int c = Serial.parseInt();

    if (Serial.read() == '\n') {
      Serial.println(c);

      if (c < posmax && c > posmin)
      {
        pos = c;
        myservo.write(pos); 
        Serial.print("Setting Servo to : ");
        Serial.println(pos);

      }
      else
      {
        
          Serial.println("Out of Range");

      }


    }
  }

}

