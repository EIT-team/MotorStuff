
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



