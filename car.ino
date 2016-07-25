#include <PID_v1.h>

// pins
const byte pinLeftLaser = 2;
const byte pinRightLaser = 3;

const byte pinLeftPWM = 5;
const byte pinLeft2 = 6;
const byte pinLeft1 = 7;
const byte pinStandby = 8;
const byte pinRight1 = 9;
const byte pinRight2 = 10;
const byte pinRightPWM = 11;

const double dDelay = 50;

// global variables
double leftPWM = 50;
double rightPWM = 50;
double lCounter = 0;
double rCounter = 0;
double lastLCounter = 0;
double lastRCounter = 0;
double lSpeed = 0;
double rSpeed = 0;

double lrSetpoint, speedSetpoint, speedDiff, speedAvg, lrPWMAdj, speedPWMAdj;

PID lrPID(&speedDiff, &lrPWMAdj, &lrSetpoint, 0.05, 0, 0.05, DIRECT);
//PID lrPID(&speedDiff, &lrPWMAdj, &lrSetpoint, 3, 0.5, 0.28, DIRECT);
//PID lrPID(&speedDiff, &lrPWMAdj, &lrSetpoint, 0.5, 0, 0.06, DIRECT);
//PID lrPID(&speedDiff, &lrPWMAdj, &lrSetpoint, 0.02, 0, 0.001, DIRECT);
//PID lrPID(&speedDiff, &lrPWMAdj, &lrSetpoint, 0.05, 0, 0.015, DIRECT);

PID speedPID(&speedAvg, &speedPWMAdj, &speedSetpoint, 0, 0, 0, REVERSE);

void lCount() {
  lCounter++;
}

void rCount() {
  rCounter++;
}

void computeSpeed() {
  lSpeed = (lCounter - lastLCounter) / dDelay * (1000 / dDelay);
  lastLCounter = lCounter;
  rSpeed = (rCounter - lastRCounter) / dDelay * (1000 / dDelay);
  lastRCounter = rCounter;

  speedDiff = lSpeed - rSpeed;
  speedAvg = (lSpeed + rSpeed) / 2;
}

void reset() {
  leftPWM = 0;
  rightPWM = 0;
  lastLCounter = 0;
  lastRCounter = 0;
  lCounter = 0;
  rCounter = 0;

  lrSetpoint = 0;
  lrPID.SetMode(MANUAL);
  lrPID.SetMode(AUTOMATIC);
  speedPID.SetMode(MANUAL);
  speedPID.SetMode(AUTOMATIC);
}

void forward() {
  digitalWrite(pinLeft1, HIGH);
  digitalWrite(pinLeft2, LOW);
  digitalWrite(pinRight1, HIGH);
  digitalWrite(pinRight2, LOW);
}

void stop() {
  digitalWrite(pinLeft1, LOW);
  digitalWrite(pinLeft2, LOW);
  digitalWrite(pinRight1, LOW);
  digitalWrite(pinRight2, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.println("diff adj left right");
  
  // put your setup code here, to run once:
  pinMode(pinStandby, OUTPUT);
  pinMode(pinLeft1, OUTPUT);
  pinMode(pinLeft2, OUTPUT);
  pinMode(pinRight1, OUTPUT);
  pinMode(pinRight2, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);
  
  pinMode(pinLeftLaser, INPUT);
  pinMode(pinRightLaser, INPUT);

  digitalWrite(pinStandby, HIGH);

  attachInterrupt(digitalPinToInterrupt(pinLeftLaser), lCount, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinRightLaser), rCount, CHANGE);
  
  analogWrite(pinLeftPWM, leftPWM);
  analogWrite(pinRightPWM, rightPWM);

  stop();
  reset();

  //turn the PID on
  lrPID.SetOutputLimits(-10, 10);
  lrPID.SetMode(AUTOMATIC);
  lrPID.SetSampleTime(dDelay);
}

//void loop() {
//}

void loop() {
  // put your main code here, to run repeatedly:

  forward();
  /*
   * switch (state) {
   *   case FORWARD:
   *     forward();
   *     break;
   *   case STOP: 
   *   default:
   *     stop();
   *     reset();
   * }
   */

  computeSpeed();
  Serial.print(speedDiff);

  lrPID.Compute();
  Serial.print(" ");
  Serial.print(lrPWMAdj);

  /*
   * speedPID.Compute();
   * Serial.print(" ");
   * Serial.print(speedPWMAdj);
   */

  leftPWM = constrain(leftPWM+lrPWMAdj+speedPWMAdj, 0, 255);
  Serial.print(" ");
  Serial.print(leftPWM);

  rightPWM = constrain(rightPWM-lrPWMAdj+speedPWMAdj, 0, 255);
  Serial.print(" ");
  Serial.println(rightPWM);

  analogWrite(pinLeftPWM, leftPWM);
  analogWrite(pinRightPWM, rightPWM);

  delay(dDelay);
}
