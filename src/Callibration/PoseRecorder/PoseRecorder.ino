/*
 * 📸 Yujai Bot - Pose Recorder (The Action Figure Mode) by H Mohammed yusuf
 * * LOGIC:
 * Instead of finding individual limits, we find "Safe Combinations".
 * 1. Connect Potentiometer to A0.
 * 2. Upload & Open Serial Monitor.
 * 3. Select joint ('b', 's', 'e', 'g') and move it with Pot.
 * 4. Once the FULL ARM looks safe and ready, type 'p'.
 * 5. Copy the printed "Pose" values into your final code.
 */

#include <Servo.h>

Servo base, shoulder, elbow, gripper;

// Pins
const int basePin = 3;
const int shoulderPin = 5;
const int elbowPin = 6;
const int gripperPin = 9;
const int potPin = A0;

// Store Current Angles (Default Home)
int baseAngle = 90;
int shoulderAngle = 90;
int elbowAngle = 90;
int gripperAngle = 0;

char activeServo = 'n'; // 'n' = None

void setup() {
  Serial.begin(9600);
  
  base.attach(basePin);
  shoulder.attach(shoulderPin);
  elbow.attach(elbowPin);
  gripper.attach(gripperPin);
  
  // Move to initial home positions
  base.write(baseAngle);
  shoulder.write(shoulderAngle);
  elbow.write(elbowAngle);
  gripper.write(gripperAngle);

  Serial.println("=== 📸 POSE RECORDER READY ===");
  Serial.println("Commands:");
  Serial.println(" 'b' -> Control Base");
  Serial.println(" 's' -> Control Shoulder");
  Serial.println(" 'e' -> Control Elbow");
  Serial.println(" 'g' -> Control Gripper");
  Serial.println(" 'p' -> 📸 PRINT CURRENT POSE (Save this!)");
}

void loop() {
  // 1. Read Command
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    // Joint Selection
    if (input == 'b' || input == 's' || input == 'e' || input == 'g') {
      activeServo = input;
      Serial.print(">> Controlling: ");
      Serial.println(activeServo);
    }
    
    // Print Snapshot
    else if (input == 'p') {
      printPose();
    }
  }

  // 2. Read Potentiometer & Map
  int potVal = analogRead(potPin);
  // Map smoothly (Pot jitter reduction logic optional)
  int targetAngle = map(potVal, 0, 1023, 0, 180);

  // 3. Update ONLY the active servo variable
  switch (activeServo) {
    case 'b': baseAngle = targetAngle; base.write(baseAngle); break;
    case 's': shoulderAngle = targetAngle; shoulder.write(shoulderAngle); break;
    case 'e': elbowAngle = targetAngle; elbow.write(elbowAngle); break;
    case 'g': gripperAngle = targetAngle; gripper.write(gripperAngle); break;
  }
  
  delay(15); // Stability delay
}

// Function to print the code-ready values
void printPose() {
  Serial.println("\n--- 📸 SNAPSHOT SAVED ---");
  Serial.print("int base = "); Serial.print(baseAngle); Serial.println(";");
  Serial.print("int shoulder = "); Serial.print(shoulderAngle); Serial.println(";");
  Serial.print("int elbow = "); Serial.print(elbowAngle); Serial.println(";");
  Serial.print("int gripper = "); Serial.print(gripperAngle); Serial.println(";");
  Serial.println("-------------------------");
}