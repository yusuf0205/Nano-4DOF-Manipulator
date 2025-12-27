
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo gripper;

// Pins
const int basePin = 3;
const int shoulderPin = 5;
const int elbowPin = 6;
const int gripperPin = 9;
const int potPin = A0;

// Variables
char activeServo = 'n'; // 'n' for None initially
int currentAngle = 90;

void setup() {
  Serial.begin(9600);
  
  base.attach(basePin);
  shoulder.attach(shoulderPin);
  elbow.attach(elbowPin);
  gripper.attach(gripperPin);
  
  // Set all to Home initially to avoid crash
//  base.write(0);
//  shoulder.write(0);
  elbow.write(0);
 // gripper.write(0);

}


void loop() {
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);
  elbow.write(angle);

  // 4. Print Data (Only if changed to avoid spam)
  if (abs(angle - currentAngle) > 1) {
    Serial.print("Active: ");
    Serial.print(activeServo);+
    
    Serial.print(" | Angle: ");
    Serial.println(angle);
    currentAngle = angle;
    delay(50); // Small delay for stability
  }
}