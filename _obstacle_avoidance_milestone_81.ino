#include <Servo.h>

Servo servo;
const int trig = 6, echoPin = 7, servoPin = 8;
const int in1 = 2, in2 = 3, in3 = 4, in4 = 5;
const int ena = 9, enb = 10;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
  servo.write(90);

  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT); pinMode(enb, OUTPUT);
}

long getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void forward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(ena, 200); analogWrite(enb, 200);
}

void backward() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(ena, 200); analogWrite(enb, 200);
}

void turnRight() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(ena, 200); analogWrite(enb, 200);
}

void turnLeft() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(ena, 200); analogWrite(enb, 200);
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}

void loop() {
  long d = getDistance();
  
  if (d < 15) {
    stopMotors();
    delay(500);
    backward(); delay(1000);
    stopMotors(); delay(300);
    
    servo.write(45); delay(1000);
    long dRight = getDistance();
    
    servo.write(135); delay(1000);
    long dLeft = getDistance();
    
    servo.write(90); delay(500);
    
    if (dRight > dLeft) {
      turnRight(); delay(700);
    } else {
      turnLeft(); delay(700);
    }
    
    stopMotors(); delay(300);
  } else {
    forward();
  }
}



