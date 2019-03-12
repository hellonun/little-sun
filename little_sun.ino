//motor
#include <Stepper.h>
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;
int x = 1;
Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);

// switch function
int inPin = 2;
volatile byte state = LOW;
int reading;           // the current reading from the input pin
int bstate = 0;
int previous = LOW;

// 3 watt light
const int transistorPin = 3;

void setup() {
  //motor
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  motor.setSpeed(4);
  Serial.begin(9600);

  //switch and light
  pinMode(inPin, INPUT);
  pinMode(transistorPin, OUTPUT);
}

void loop() {
  //motor
  motor.step(1);

  // read switch state and turn on light
  reading = digitalRead(inPin);
  if (reading == HIGH && previous == LOW) {
    bstate = bstate + 1;
    bstate = bstate % 4;
  }
  if (bstate == 1) {
    analogWrite(transistorPin, 255);
  } else if (bstate == 2) {
    analogWrite(transistorPin, 150);
  } else if (bstate == 3) {
    analogWrite(transistorPin, 50);
  } else {
    analogWrite(transistorPin, 0);
  }
  previous = reading;
}
