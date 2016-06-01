

const int FWD_PIN = 5;
const int REV_PIN = 6;

int PWM_VAL=255;


void setup() {
  pinMode(FWD_PIN,OUTPUT);
  pinMode(REV_PIN,OUTPUT);
  Serial.begin(115200);

Serial.println("Motor H-Bridge Test");

}

void loop() {

    analogWrite(FWD_PIN,PWM_VAL);
    analogWrite(REV_PIN,0);
    delay(1000);
    analogWrite(FWD_PIN,0);
    analogWrite(REV_PIN,PWM_VAL);
    delay(1000);

  

}
