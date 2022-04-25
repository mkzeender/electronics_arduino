
// This sketch uses a HW-627 motor driver to control two motors
  float sensitivity = .1;
  int sensorCutoff = 300;
  
  float derivativespeed = 200;
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
  allDirections();
  delay(10);
}

void allDirections() {
  int speed_ = 170;
  
  int left = analogRead(leftSensor);
  int right = analogRead(rightSensor);
  int center = analogRead(middleSensor);

  bool centerer = center < sensorCutoff;
  bool lefter = left < sensorCutoff;
  bool righter = right < sensorCutoff;

  if (lefter and righter) {
    goDirectionSpeed(0, 0.6 * speed_, 0.6 * speed_);
    
  }
  else if (lefter and centerer) {
    // slight right
    goDirectionSpeed(0, speed_ * 0.7, speed_*0.9);
    lastDirectionLeft = 1;
  }
  else if (lefter) {
    goDirectionSpeed(0, constrain(derivativespeed, speed_ * 0.5, speed_*0.9), speed_);
    lastDirectionLeft = 1;
  }
  else if (righter and centerer) {
    goDirectionSpeed(0, speed_*0.9, speed_ * 0.7);
    lastDirectionLeft = 2;
    derivativespeed = 0;
  }
  else if (righter) {
    goDirectionSpeed(0, speed_, constrain(derivativespeed, speed_ * 0.5, speed_*0.9));
    lastDirectionLeft = 2;
  }
  else if (centerer) {
    goDirectionSpeed(0, speed_, speed_);
    derivativespeed = 0;
  }
  else if (lastDirectionLeft == 1) {
    derivativespeed += 1;
    goDirectionSpeed(0, constrain(derivativespeed, 0, speed_*0.4), speed_ * 0.7);
    
  }
  else if (lastDirectionLeft == 2) {
    derivativespeed += 1;
    goDirectionSpeed(0, speed_ * 0.7, constrain(derivativespeed, 0, speed_*0.4));
    
  }
  
}

void dynamicSpeed() {
  
  int left = analogRead(leftSensor);
  int right = analogRead(rightSensor);
  int center = analogRead(middleSensor);

  int direction_;
  if (center < (sensorCutoff + 300)) {
    derivativespeed = derivativespeed + sensitivity * dv * (sensorCutoff - center);
    derivativespeed = constrain(derivativespeed, 127, 255);

    // pick which side of the line to follow
    int direction_;
    if (lastDirectionLeft == 1) {
      direction_ = sensorCutoff - center;
    }
    else {
      direction_ = center - sensorCutoff;
    }
    //goDirectionSpeed(direction_, derivativespeed, derivativespeed);
  }
  
  if ((left < sensorCutoff) and (right < sensorCutoff)) {
    
    direction_ = 0; // for both lines seen at same time
  }
  else if (left < sensorCutoff) { // keep track of last known side that we saw the line
    //turnLeft();
    lastDirectionLeft = 1;
    direction_ = -50;
  }
  else if (right < sensorCutoff) {
    //turnRight();
    //goDirectionSpeed(sensorCutoff - center, derivativespeed, derivativespeed);
    direction_ = 50;
    lastDirectionLeft = 2;
  }

  else if (lastDirectionLeft == 1) {
    // we know we are right of the line
    //turnLeft();
    direction_ = -2000;
  }
  else if (lastDirectionLeft == 2) {
    // we know we are left of the line
    //turnRight();
    direction_ = 2000;
  }

  
  goDirectionSpeed(direction_, derivativespeed, derivativespeed);
  
 
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
  
  
