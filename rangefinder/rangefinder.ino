/* This sketch uses a RCWL-1601 ultrasonic range finder 
 to measure distance
 */
 int sensorCutoff = 300;
 int rightSensor = A0;
 int leftSensor = A1;

 int leftFaceRightEye = 12;
 int leftFaceLeftEye = 13;

  int leftFor = 6;//left motor forward
  int leftRev = 9;//left motor reverse
  int rightFor = 3;//right motor forward
  int rightRev = 5;//right motor reverse
  int enabledrive = 22;  //  drive enabled (HIGH) or disabled (LOW)

#define trig 24   // trigger pin output
#define echo 26   // echo pin input

long duration;
long distance;


void setup() {
  // put your setup code here, to run once:

pinMode(leftFaceLeftEye, OUTPUT);
pinMode(leftFaceRightEye, OUTPUT);
//Serial.begin(9600);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);

digitalWrite(trig, LOW); 
delayMicroseconds(2);


pinMode (leftFor, OUTPUT);
pinMode (leftRev, OUTPUT);

pinMode (rightFor, OUTPUT);
pinMode (rightRev, OUTPUT);

pinMode (enabledrive, OUTPUT);

digitalWrite (enabledrive, HIGH);   // allows the car to drive

}

void loopaaa() {
  
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

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);

duration = pulseIn(echo, HIGH); // time in microseconds 
distance = (duration / 2) / 29.1;  

if (distance <= -1) { //CHANGE THIS
  goBack();
  delay(1000);
  turnLeft();
  delay(500);
  
  digitalWrite(leftFaceLeftEye, LOW);
  digitalWrite(leftFaceRightEye, LOW);
  
} else {
  
  int left = analogRead(leftSensor);
  int right = analogRead(rightSensor);
  if (left > sensorCutoff) {
    turnLeft();
  }
  else if (right > sensorCutoff) {
    turnRight();
  }
  else {
    goStraight();
  }
  
  digitalWrite(leftFaceLeftEye, HIGH);
  digitalWrite(leftFaceRightEye, HIGH);
}


delay(100);


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
  
  
