/*
Into Robotics
*/
 
#include <Servo.h>  //add '<' and '>' before and after servo.h

const int servoPinLeft = 6;
const int servoPinRight = 9;
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8; // Echo Pin of Ultrasonic Sensor
const int speakerPin = 3;

bool seen = true;
String wrd = "";
int character = 0;

Servo servoLeft;
Servo servoRight;

int leftServo (char letter);
int rightServo (char letter);
String input ();
//char letter;
void textToBraile();

void setup()
{
  Serial.begin(9600);
  servoLeft.attach(servoPinLeft);
  servoRight.attach(servoPinRight);
  pinMode(speakerPin, OUTPUT);
  servoLeft.write(leftServo(' '));
  servoRight.write(rightServo(' '));
}

void loop()
{ 
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);

  if (character == wrd.length()) {
    character = 0;
    wrd = input();
    seen = true;
  } else if (cm < 15) {
    seen = true;
    Serial.println("Read.");
  } else if (cm >= 15 && seen) {
    seen = false;
    textToBraille(wrd.charAt(character++));
  }
}

void textToBraille(char letter) {
  servoLeft.write(leftServo(letter));
  delay(500);
  servoRight.write(rightServo(letter));
  delay(100);
  digitalWrite(speakerPin, HIGH);
  delay(100);
  digitalWrite(speakerPin, LOW);
  Serial.println("done");
}

String input() {
  Serial.println("Enter a word");
  
  while(!Serial.available()) {
    // wait for input
  }

  return Serial.readStringUntil(10);
}

int leftServo (char letter) {
  int servoAngle = 0;
  
  if (letter == 'a' || letter == 'c' || letter == 'd' || letter == 'e') {
    servoAngle = 30;
  } else if (letter == 'b' || letter == 'f' || letter == 'g' || letter == 'h') {
    servoAngle = 60;
  } else if (letter == 'i' || letter == 'j' || letter == 'w') {
    servoAngle = 90;
  } else if (letter == 'k' || letter == 'm' || letter == 'n' || letter == 'o' || letter == 'u' || letter == 'x' || letter == 'y' || letter == 'z') {
    servoAngle = 120;
  } else if (letter == 'l' || letter == 'p' || letter == 'q' || letter == 'r' || letter == 'v') {
    servoAngle = 150;
  } else if (letter == 's' || letter == 't') {
    servoAngle = 180;
  } else if (letter == ' ') {
    servoAngle = 0;
  }

  return servoAngle;
}

int rightServo (char letter) {
  int servoAngle = 250;
  
  if (letter == 'a' || letter == 'b' || letter == 'k' || letter == 'l') {
    servoAngle = 0;
  } else if (letter == 'c' || letter == 'f' || letter == 'i' || letter == 'm' || letter == 'p' || letter == 's') {
    servoAngle = 30;
  } else if (letter == 'd' || letter == 'g' || letter == 'j' || letter == 'n' || letter == 'q' || letter == 't') {
    servoAngle = 60;
  } else if (letter == 'e' || letter == 'h' || letter == 'o' || letter == 'r') {
    servoAngle = 90;
  } else if (letter == 'u' || letter == 'v' || letter == ' ' || letter == 'x') {
    servoAngle = 120;
  } else if (letter == 'w' || letter == 'y') {
    servoAngle = 150;
  } else if (letter == 'z') {
    servoAngle = 180;
  }

  return servoAngle;
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
