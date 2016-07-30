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

// defaults
const double dDelay = 200;
const byte countStep = 40;
const int defaultPWM = 60;
const double defaultSpeed = 50;

// global variables
int lCounter = 0;
int rCounter = 0;
unsigned long lTimePoints[countStep] = {0};
unsigned long rTimePoints[countStep] = {0};
double lSpeed;
double rSpeed;
double lrPWMAdjSum = 0;
double speedPWMAdjSum = 0;
int leftPWM = 0;
int rightPWM = 0;
double lrSetpoint, speedSetpoint, speedDiff, speedAvg, lrPWMAdj, speedPWMAdj;
PID lrPID(&speedDiff, &lrPWMAdj, &lrSetpoint, 0.025, 0.00, 0.00, DIRECT);
PID speedPID(&speedAvg, &speedPWMAdj, &speedSetpoint, 0.05, 0, 0, DIRECT);

void lCount() {
  unsigned long now = millis();
  lTimePoints[lCounter % countStep] = now;
  unsigned long last = lTimePoints[(lCounter+1) % countStep];
  if (last != 0) {
    lSpeed = countStep * (1000 / double(now - last));
  }
  /* Serial.println(lSpeed); */

  lCounter++;
}

void rCount() {
  unsigned long now = millis();
  rTimePoints[rCounter % countStep] = now;
  unsigned long last = rTimePoints[(rCounter+1) % countStep];
  if (last != 0) {
    rSpeed = countStep * (1000 / double(now - last));
  }
  /* Serial.println(rSpeed); */

  rCounter++;
}

void computePIDInput() {
  speedDiff = lSpeed - rSpeed;
  speedAvg = (lSpeed + rSpeed) / 2;
}

void reset() {
  lCounter = 0;
  rCounter = 0;
  leftPWM = defaultPWM;
  rightPWM = defaultPWM;
  lSpeed = defaultSpeed;
  rSpeed = defaultSpeed;
  for (int i = 0; i < countStep; i++) {
    lTimePoints[i] = 0;
  }
  for (int i = 0; i < countStep; i++) {
    rTimePoints[i] = 0;
  }

  lrSetpoint = 0;
  lrPID.SetMode(MANUAL);
  lrPID.SetMode(AUTOMATIC);

  speedSetpoint = defaultSpeed;
  speedPID.SetMode(MANUAL);
  speedPID.SetMode(AUTOMATIC);
}

void updatePWM() {
  computePIDInput();
  Serial.print(speedDiff);
  /*
   * Serial.print(" ");
   * Serial.print(speedAvg);
   */

  lrPID.Compute();
  Serial.print(" ");
  Serial.print(lrPWMAdj);
  lrPWMAdjSum += lrPWMAdj;
  Serial.print(" ");
  Serial.print(lrPWMAdjSum);

  speedPID.Compute();
  Serial.print(" ");
  Serial.print(speedPWMAdj);
  speedPWMAdjSum += speedPWMAdj;

  leftPWM = constrain(defaultPWM+int(lrPWMAdjSum)+int(speedPWMAdjSum), 0, 255);
  Serial.print(" ");
  Serial.print(leftPWM);

  rightPWM = constrain(defaultPWM-int(lrPWMAdjSum)+int(speedPWMAdjSum), 0, 255);
  Serial.print(" ");
  Serial.println(rightPWM);

  analogWrite(pinLeftPWM, leftPWM);
  analogWrite(pinRightPWM, rightPWM);

  delay(dDelay);
}

void forward() {
  digitalWrite(pinLeft1, HIGH);
  digitalWrite(pinLeft2, LOW);
  digitalWrite(pinRight1, HIGH);
  digitalWrite(pinRight2, LOW);

  updatePWM();
}

void backward() {
  digitalWrite(pinLeft1, LOW);
  digitalWrite(pinLeft2, HIGH);
  digitalWrite(pinRight1, LOW);
  digitalWrite(pinRight2, HIGH);

  updatePWM();
}

void turnLeft() {
  digitalWrite(pinLeft1, LOW);
  digitalWrite(pinLeft2, HIGH);
  digitalWrite(pinRight1, HIGH);
  digitalWrite(pinRight2, LOW);

  updatePWM();
}

void turnRight() {
  digitalWrite(pinLeft1, HIGH);
  digitalWrite(pinLeft2, LOW);
  digitalWrite(pinRight1, LOW);
  digitalWrite(pinRight2, HIGH);

  updatePWM();
}

void stop() {
  digitalWrite(pinLeft1, LOW);
  digitalWrite(pinLeft2, LOW);
  digitalWrite(pinRight1, LOW);
  digitalWrite(pinRight2, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.println("diff adj adjsum left right");
  
  // put your setup code here, to run once:
  pinMode(pinStandby, OUTPUT);
  pinMode(pinLeft1, OUTPUT);
  pinMode(pinLeft2, OUTPUT);
  pinMode(pinRight1, OUTPUT);
  pinMode(pinRight2, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  pinMode(pinLeftLaser, INPUT);
  pinMode(pinRightLaser, INPUT);

  digitalWrite(pinStandby, HIGH);

  attachInterrupt(digitalPinToInterrupt(pinLeftLaser), lCount, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinRightLaser), rCount, CHANGE);
  
  analogWrite(pinLeftPWM, leftPWM);
  analogWrite(pinRightPWM, rightPWM);


  //turn the PID on
  lrPID.SetOutputLimits(-255, 255);
  lrPID.SetMode(AUTOMATIC);
  lrPID.SetSampleTime(dDelay);

  speedPID.SetOutputLimits(-255, 255);
  speedPID.SetMode(AUTOMATIC);
  speedPID.SetSampleTime(dDelay);

  stop();
  reset();
}

void loop() {
  int outA0 = digitalRead(A0);
  int outA1 = digitalRead(A1);
  int outA2 = digitalRead(A2);
  int outA3 = digitalRead(A3);

  // forward
  if (outA0 == HIGH && outA1 == LOW && outA2 == LOW && outA3 == LOW) {
    forward();
  } else if (outA0 == LOW && outA1 == HIGH && outA2 == LOW && outA3 == LOW) {
    backward();
  } else if (outA0 == LOW && outA1 == LOW && outA2 == HIGH && outA3 == LOW) {
    turnLeft();
  } else if (outA0 == LOW && outA1 == LOW && outA2 == LOW && outA3 == HIGH) {
    turnRight();
  } else {
    stop();
    reset();
  }
}
