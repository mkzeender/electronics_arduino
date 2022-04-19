
// This sketch uses a HW-627 motor driver to control two motors
  int sensitivity = 0.1;
  int sensorCutoff = 300;
  int rightSensor = A0;
  int leftSensor = A1;
  
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
  
  int left = analogRead(leftSensor);
  int right = analogRead(rightSensor);

  int direction_ = right - left;
  
  if (left < sensorCutoff) {
    turnRight();
  }
  else if (right < sensorCutoff) {
    turnLeft();
  }
  else {
    goStraight();
  }
 
//  goBack();
//  delay (5000);
//  goFast();
//  delay (5000);
// goBackfast();
//  delay(5000);
}

void goDirection(int direction_) {
  int left = 105;
  int right = 127;
  if (direction_ <= 0) {
    left = left + direction_ * sensitivity;
    right = right + direction_ * sensitivity / 2;
  } else {
    right = right - direction_ * sensitivity;
    left = left + direction_ * sensitivity / 2;
  }
  left = clip(left);
  right = clip(right);
  
  digitalWrite (rightFor, right); //makes sure the right motor does not rotate forward
  digitalWrite (rightRev, LOW); //makes sure the right motor does not rotate reverse
  digitalWrite (leftRev, LOW); //makes sure the left motor does not rotate reverse
  analogWrite (leftFor, left); //using PWM allows for an adjustable speed
}

int clip(int input) {
  if (input > 255) {
    return 255;
  }
  if (input < 0) {
    return 0;
  }
  return input;
}

void turnLeft()
{
  digitalWrite (rightFor, LOW); //makes sure the right motor does not rotate forward
  digitalWrite (rightRev, LOW); //makes sure the right motor does not rotate reverse
  digitalWrite (leftRev, LOW); //makes sure the left motor does not rotate reverse
  analogWrite (leftFor, 100); //using PWM allows for an adjustable speed
  return;
}

void turnRight()
{
  digitalWrite (leftFor, LOW); //makes sure the left motor does not rotate forward
  digitalWrite (leftRev, LOW); //makes sure the left motor does not rotate reverse
  digitalWrite (rightRev, LOW); //makes sure the right motor does not rotate reverse
  analogWrite (rightFor, 100); //using PWM allows for an adjustable speed
  return;
}
  
void goStraight()
{

  digitalWrite (rightRev, LOW); //makes sure the motor does not rotate reverse
  digitalWrite (leftRev, LOW); //makes sure the motor does not rotate reverse
  analogWrite (rightFor, 105); //using PWM allows for an adjustable speed 
  analogWrite (leftFor, 127); //for both left and right motors
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
  
  
