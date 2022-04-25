
// This sketch uses a HW-627 motor driver to control two motors
  float sensitivity = .1;
  int sensorCutoff = 300;
  
  int derivativespeed = 200;
  float dv = 0.01;

  int lastDirectionLeft = 0;
  
  int rightSensor = A0;
  int leftSensor = A1;
  int middleSensor = A2;
  
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

void loop() {
  dynamicSpeed();
  delay(10);
}

void dynamicSpeed() {
  
  int left = analogRead(leftSensor);
  int right = analogRead(rightSensor);
  int center = analogRead(middleSensor);

  
  if ((left < sensorCutoff) and (right < sensorCutoff)) {
    
    goStraight(); // for both lines seen at same time
  }
  else if (left < sensorCutoff) { // keep track of last known side that we saw the line
    turnLeft();
    lastDirectionLeft = 1;
  }
  else if (right < sensorCutoff) {
    turnRight();
    lastDirectionLeft = 2;
  }
  else if (center < sensorCutoff + 100) {
    derivativespeed = derivativespeed + sensitivity * dv * (sensorCutoff - center);
    derivativespeed = constrain(derivativespeed, 127, 255);
    goDirectionSpeed(sensorCutoff - center, derivativespeed, derivativespeed);
  }
  else if (lastDirectionLeft == 1) {
    // we know we are right of the line
    turnLeft();
  }
  else if (lastDirectionLeft == 2) {
    // we know we are left of the line
    turnRight();
  }

  
  goDirection(center-sensorCutoff);
  
 
//  goBack();
//  delay (5000);
//  goFast();
//  delay (5000);
// goBackfast();
//  delay(5000);
}

void goDirection(int direction_) {
  goDirectionSpeed(direction_, 140, 170);
}

void goDirectionSpeed(int direction_, int left, int right) {
  if (direction_ <= 0) {
    left = left + direction_ * sensitivity;
    //right = right + direction_ * sensitivity / 2;
  } else {
    right = right - direction_ * sensitivity;
    //left = left + direction_ * sensitivity / 2;
  }
  left = clip(left);
  right = clip(right);
  
  analogWrite (rightFor, right); //makes sure the right motor does not rotate forward
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

void goSpeed(int speed_)
{
  analogWrite (rightFor, speed_); //makes sure the right motor does not rotate forward
  digitalWrite (rightRev, LOW); //makes sure the right motor does not rotate reverse
  digitalWrite (leftRev, LOW); //makes sure the left motor does not rotate reverse
  analogWrite (leftFor, speed_); //using PWM allows for an adjustable speed
  return;
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
  
  
