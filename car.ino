#include <PID_v1.h>

const byte pinStandby = 9;

const byte pinLeft1 = 5;
const byte pinLeft2 = 6;

const byte pinRight1 = 7;
const byte pinRight2 = 8;

const byte pinLeftPWM = 1;
const byte pinRightPWM = 2;

const byte pinLeftLaser = 3;
const byte pinRightLaser = 4;


int leftPWM = 200;
int rightPWM = 200;

int leftLaserCounter = 0;
int rightLaserCounter = 0;

double countBlance, countDiff, pwmAdjustment;

PID blancePID(&countDiff, &pwmAdjustment, &countBlance, 2, 5, 1, DIRECT);

void leftLaserCount() {
  leftLaserCounter++;
}

void rightLaserCount() {
  rightLaserCounter++;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pinStandby, OUTPUT);
  pinMode(pinLeft1, OUTPUT);
  pinMode(pinLeft2, OUTPUT);
  pinMode(pinRight1, OUTPUT);
  pinMode(pinRight2, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);

  digitalWrite(pinStandby, HIGH);
  digitalWrite(pinLeft1, HIGH);
  digitalWrite(pinLeft2, LOW);
  digitalWrite(pinRight1, HIGH);
  digitalWrite(pinRight2, LOW);

  attachInterrupt(digitalPinToInterrupt(pinLeftLaser), leftLaserCount, RISING);
  attachInterrupt(digitalPinToInterrupt(pinRightLaser), rightLaserCount, RISING);

  //turn the PID on
  countBlance = 0;
  blancePID.SetOutputLimits(-50, 50);
  blancePID.SetMode(AUTOMATIC);
}

void loop() {
  // put your main code here, to run repeatedly:

  countDiff = leftLaserCounter - rightLaserCounter;
  blancePID.Compute();
  leftPWM = constrain(leftPWM-pwmAdjustment, 0, 255);
  rightPWM = constrain(rightPWM+pwmAdjustment, 0, 255);

  analogWrite(pinLeftPWM, leftPWM);
  analogWrite(pinRightPWM, rightPWM);

  delay(50);
}
