
void Sequence_1()
{
  CentreToFront(4000, 8000);

  FrontToCentre(4000, 10);
}


void Sequence_2()
{
  CentreToFront(2000, 1000);

  FrontBottomBack(2000, 1000);
  BackBottomFront(2000, 1000);
  FrontBottomBack(2000, 1000);
  BackBottomFront(2000, 1000);

  FrontToCentre(2000, 10);
}

void Sequence_3()
{
  CentreToFront(4000, 1000);

  FrontBottomBack(4000, 1000);
  BackBottomFront(4000, 1000);
  FrontBottomBack(4000, 1000);
  BackBottomFront(4000, 1000);

  FrontToCentre(4000, 10);
}

void Sequence_4()
{
  CentreToSide(2000, 1000);
  
  MoveServos(FRONT[0], FRONT[1], FRONT[2], 2000);
  delay(1000);
  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], 2000);
  delay(1000);
  MoveServos(SIDE[0], SIDE[1], SIDE[2], 2000);

  SideToCentre(2000, 1000);
}

void Sequence_5()
{
  CentreToFront(8000, 2000);

  FrontBottomBack(8000, 2000);
  BackBottomFront(8000, 2000);
  FrontBottomBack(8000, 2000);
  BackBottomFront(8000, 2000);

  FrontToCentre(8000, 10);
}

void Sequence_6()
{
  CentreToBack(4000, 8000);


  BackToCentre(4000, 10);
}


void Sequence_7()
{
   CentreToSide(4000, 8000);
   SideToCentre(4000, 10);
}


void Sequence_8()
{
  CentreToFront(2000, 8000);

  FrontBottomBack(10000, 8000);
  BackBottomFront(10000, 8000);
  FrontBottomBack(10000, 8000);
  BackBottomFront(10000, 8000);

  FrontToCentre(2000, 10);
}

void Sequence_8A()
{
  CentreToFront(1000, 4000);

  FrontBottomBack(5000, 4000);
  BackBottomFront(5000, 4000);
  FrontBottomBack(5000, 4000);
  BackBottomFront(5000, 4000);

  FrontToCentre(1000, 10);
}

void Sequence_9()
{
  CentreToFront(1000, 500);

  FrontBottomBack(1000, 500);
  BackBottomFront(1000, 500);
  FrontBottomBack(1000, 500);
  BackBottomFront(1000, 500);

  FrontToCentre(1000, 10);
}

void Sequence_10()
{
  CentreToFront(1000, 500);

  FrontBottomBack(1000, 500);
  
  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], 1000);
  delay(500);
  MoveServos(SIDE[0], SIDE[1], SIDE[2], 1000);
  delay(500);

  MoveServos(FRONT[0], FRONT[1], FRONT[2], 1000);
  delay(500);

  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], 1000);
  delay(500);
  MoveServos(SIDE[0], SIDE[1], SIDE[2], 1000);
  delay(500);

  
  MoveServos(BACK[0], BACK[1], BACK[2], 1000);
  delay(500);
  BackBottomFront(1000, 500);

  FrontToCentre(1000, 10);
}

void Sequence_11()
{
  CentreToFront(2000, 500);

  FrontBottomBack(2000, 500);
  
  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], 2000);
  delay(500);
  MoveServos(SIDE[0], SIDE[1], SIDE[2], 2000);
  delay(500);

  MoveServos(FRONT[0], FRONT[1], FRONT[2], 2000);
  delay(500);

  MoveServos(BOTTOM[0], BOTTOM[1], BOTTOM[2], 2000);
  delay(500);
  MoveServos(SIDE[0], SIDE[1], SIDE[2], 2000);
  delay(500);

  
  MoveServos(BACK[0], BACK[1], BACK[2], 2000);
  delay(500);
  BackBottomFront(2000, 500);

  FrontToCentre(2000, 10);
}

