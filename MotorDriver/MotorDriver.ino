
// This sketch uses a HW-627 motor driver to control two motors
 
  int leftFor = 6;//left motor forward
  int leftRev = 9;//left motor reverse
  int rightFor = 3;//right motor forward
  int rightRev = 5;//right motor reverse
  int enabledrive = 22;  //  drive enabled (HIGH) or disabled (LOW)
  
void setup()
{

pinMode (leftFor, OUTPUT);
pinMode (leftRev, OUTPUT);

pinMode (rightFor, OUTPUT);
pinMode (rightRev, OUTPUT);

pinMode (enabledrive, OUTPUT);

digitalWrite (enabledrive, HIGH);   // allows the car to drive


}


void loop() 
{
  
  turnLeft();
  //delay (500);
  //turnRight();
  delay (500);
  goStraight();
  delay (500);
 
//  goBack();
//  delay (5000);
//  goFast();
//  delay (5000);
// goBackfast();
//  delay(5000);
  
  
}


void turnLeft()
{
  digitalWrite (leftRev, LOW); //makes sure the motor does not rotate reverse
  analogWrite (leftFor, 100); //using PWM allows for an adjustable speed

  digitalWrite(rightRev, LOW);
  digitalWrite(rightFor, LOW);
  return;
}


void turnRight()
{
  digitalWrite (rightRev, LOW); //makes sure the motor does not rotate reverse
  analogWrite (rightFor, 100); //using PWM allows for an adjustable speed 

  digitalWrite(leftRev, LOW);
  digitalWrite(leftFor, LOW);
  return;
}
  
void goStraight()
{

  digitalWrite (rightRev, LOW); //makes sure the motor does not rotate reverse
  digitalWrite (leftRev, LOW); //makes sure the motor does not rotate reverse
  analogWrite (rightFor, 210); //using PWM allows for an adjustable speed 
  analogWrite (leftFor, 255); //for both left and right motors
  return;
}

void goBack()
{

  analogWrite  (rightRev, 200); 
  analogWrite (leftRev, 200); 
  digitalWrite (rightFor, LOW); 
  digitalWrite (leftFor, LOW); 
  return;
}

void goFast()
{
  

  digitalWrite (rightRev, LOW); //makes sure the motor does not rotate reverse
 digitalWrite (leftRev, LOW); //makes sure the motor does not rotate reverse
  analogWrite (rightFor, 255); //using PWM allows for an adjustable speed 
  analogWrite (leftFor, 255); //for both left and right motors
  return;
}
  
void goBackfast()
{
 
  analogWrite  (rightRev, 200); 
  analogWrite (leftRev, 200); 
  digitalWrite (rightFor, LOW); 
  digitalWrite (leftFor, LOW); 
  return;
}
  
  
