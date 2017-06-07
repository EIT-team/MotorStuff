void CheckAllPos()
{
  CentreToFront(2000, 1000);
  FrontToCentre(2000, 10);

  CentreToBack(2000, 1000);
  BackToCentre(2000, 10);

  CentreToSide(2000, 1000);
  SideToCentre(2000, 10);

  CentreToMiddle(2000, 1000);
  MiddleToCentre(2000, 10);

  CentreToBottom(2000, 1000);
  BottomToCentre(2000, 10);
}

void StartToCentre(int Duration, int Pause)
{
  delay(Pause);
  Serial.println("Start");
  MoveServos(START[0], START[1], START[2], Duration);
  delay(Pause);
  Serial.println("Avoiding Mount");
  MoveServos(MOUNT[0], MOUNT[1], MOUNT[2], Duration);
  delay(Pause);
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);
}


void CentreToStart(int Duration, int Pause)
{
  delay(Pause);
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);
  delay(Pause);
  Serial.println("Avoiding Mount");
  MoveServos(MOUNT[0], MOUNT[1], MOUNT[2], Duration);
  delay(Pause);
  Serial.println("Start");
  MoveServos(START[0], START[1], START[2], Duration);
}

void CentreToFront(int Duration, int Pause)
{
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], 20);

  MoveServos(FRONT_INTER[0], FRONT_INTER[1], FRONT_INTER[2], Duration/2);


  Serial.println("To The front");
  MoveServos(FRONT[0], FRONT[1], FRONT[2], Duration/2);
  delay(Pause);
}

void FrontToCentre(int Duration, int Pause)
{
  Serial.println("To The front");
  //MoveServos(FRONT[0], FRONT[1], FRONT[2], 20);

  //MoveServos(FRONT_INTER[0], FRONT_INTER[1], FRONT_INTER[2], 20);

  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);
  delay(Pause);

}

void CentreToBack(int Duration, int Pause)
{
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);

  Serial.println("To the Back");
  MoveServos(BACK[0], BACK[1], BACK[2], Duration);
  delay(Pause);
}

void BackToCentre(int Duration, int Pause)
{
  Serial.println("To The back");
  MoveServos(BACK[0], BACK[1], BACK[2], Duration);

  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);
  delay(Pause);

}

void CentreToSide(int Duration, int Pause)
{
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);

  Serial.println("To the Side");
  MoveServos(SIDE[0], SIDE[1], SIDE[2], Duration);
  delay(Pause);
}

void SideToCentre(int Duration, int Pause)
{
  Serial.println("To The side");
  MoveServos(SIDE[0], SIDE[1], SIDE[2], Duration);
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);
  delay(Pause);
}

void CentreToMiddle(int Duration, int Pause)
{
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);

  Serial.println("To the middle");
  MoveServos(MIDDLE[0], MIDDLE[1], MIDDLE[2], Duration);
  delay(Pause);
}

void MiddleToCentre(int Duration, int Pause)
{
  Serial.println("To the middle");
  MoveServos(MIDDLE[0], MIDDLE[1], MIDDLE[2], Duration);
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);
  delay(Pause);
}

void CentreToBottom(int Duration, int Pause)
{
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);

  Serial.println("To the bottom");
  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], Duration);
  delay(Pause);
}

void BottomToCentre(int Duration, int Pause)
{
  Serial.println("To The bottom");
  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], Duration);
  Serial.println("Above the centre");
  MoveServos(ABOVECENTRE[0], ABOVECENTRE[1], ABOVECENTRE[2], Duration);
  delay(Pause);
}

void FrontToBack(int Duration, int Pause)
{
  MoveServos(FRONT[0], FRONT[1], FRONT[2], 10);
  MoveServos(BACK[0], BACK[1], BACK[2], Duration);
  delay(Pause);
}

void BackToFront(int Duration, int Pause)
{
  MoveServos(BACK[0], BACK[1], BACK[2], 10);
  MoveServos(FRONT[0], FRONT[1], FRONT[2], Duration);
  delay(Pause);
}

//tee hee
void FrontBottomBack(int Duration, int Pause)
{
  MoveServos(FRONT[0], FRONT[1], FRONT[2], 10);
  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], Duration / 2);
  MoveServos(BACK[0], BACK[1], BACK[2], Duration / 2);
  delay(Pause);
}

void BackBottomFront(int Duration, int Pause)
{
  MoveServos(BACK[0], BACK[1], BACK[2], 10);
  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], Duration / 2);
  MoveServos(FRONT[0], FRONT[1], FRONT[2], Duration / 2);
  delay(Pause);
}

