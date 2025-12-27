/*
 * Robotic Arm - Precision Calibrator Tool
 * * HOW TO USE:
 * 1. Connect Potentiometer to Pin A0.
 * 2. Upload Code & Open Serial Monitor.
 * 3. Type a character to select a servo:
 * 'b' = Base      (Pin 3)
 * 's' = Shoulder  (Pin 5)
 * 'e' = Elbow     (Pin 6)
 * 'g' = Gripper   (Pin 9)
 * 4. Turn the Pot to move that servo.
 * 5. Note down the angle shown on screen!
 * Author H Mohammed Yusuf
 */

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
  base.write(0);
  shoulder.write(0);
  elbow.write(90);
  gripper.write(0);

  Serial.println("=== SERVO CALIBRATOR READY ===");
  Serial.println("Type 'b' for Base");
  Serial.println("Type 's' for Shoulder");
  Serial.println("Type 'e' for Elbow");
  Serial.println("Type 'g' for Gripper");
  Serial.println("Turn the Potentiometer to move!");
}

void loop() {
  // 1. Check for User Input (Servo Selection)
  if (Serial.available() > 0) {
    char input = Serial.read();
    // Only accept valid keys
    if (input == 'b' || input == 's' || input == 'e' || input == 'g') {
      activeServo = input;
      Serial.print(">>> SELECTED: ");
      if (activeServo == 'b') Serial.println("BASE");
      if (activeServo == 's') Serial.println("SHOULDER");
      if (activeServo == 'e') Serial.println("ELBOW");
      if (activeServo == 'g') Serial.println("GRIPPER");
    }
  }

  // 2. Read Potentiometer
  int potValue = analogRead(potPin);
  int angle = map(potValue, 0, 1023, 0, 180);

  // 3. Move the Selected Servo
  switch (activeServo) {
    case 'b':
      base.write(angle);
      break;
    case 's':
      shoulder.write(angle);
      break;
    case 'e':
      elbow.write(angle);
      break;
    case 'g':
      gripper.write(angle);
      break;
    default:
      break;
  }

  // 4. Print Data (Only if changed to avoid spam)
  if (abs(angle - currentAngle) > 1) {
    Serial.print("Active: ");
    Serial.print(activeServo);
    Serial.print(" | Angle: ");
    Serial.println(angle);
    currentAngle = angle;
    delay(50); // Small delay for stability
  }
}