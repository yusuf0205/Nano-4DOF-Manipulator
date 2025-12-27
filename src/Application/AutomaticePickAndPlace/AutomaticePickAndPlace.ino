/*
 * 🦾 Yujai Bot - Automatic Pick & Place (Arduino Nano Version) by H Mohammed Yusuf
 * * Logic:
 * 1. Start at Home Position
 * 2. Move to Pick Location (Hover -> Lower)
 * 3. Grab Object
 * 4. Lift & Move to Place Location
 * 5. Drop Object
 * 6. Return Home
 * * Author: You (The Engineer)
 */

#include <Servo.h> // ✅ Changed back to Standard Servo library for Nano

// Create Servo Objects
Servo base;
Servo shoulder;
Servo elbow;
Servo gripper;

// --- ⚙️ PIN CONFIGURATION (Nano PWM Pins) ---
const int basePin = 3;      // Nano D3
const int shoulderPin = 5;  // Nano D5
const int elbowPin = 6;     // Nano D6
const int gripperPin = 9;   // Nano D9

// --- 📍 COORDINATES (Tune these values!) ---

// 1. HOME Position (Safe Resting State)
int homeBase = 90;
int homeShoulder = 90;
int homeElbow = 90;
int homeGripper = 0;   // 0 = Open

// 2. PICK Position (Where the object is)
int pickBase = 45;     // Rotate to the object
int pickShoulder = 60; // Reach forward
int pickElbow = 60;    // Lower arm
int pickGripper = 180; // 180 = Closed (Grab)

// 3. PLACE Position (Where to drop it)
int placeBase = 135;   // Rotate to other side
int placeShoulder = 60;
int placeElbow = 60;
int placeGripper = 0;  // Open to drop

// Speed Delay (Lower = Faster, Higher = Smoother)
int speedDelay = 30; 

void setup() {
  Serial.begin(9600);
  
  // Attach Servos
  base.attach(basePin);
  shoulder.attach(shoulderPin);
  elbow.attach(elbowPin);
  gripper.attach(gripperPin);

  Serial.println("🤖 Yujai Bot Initialized!");
  Serial.println("Moving to Home Position...");
  
  // Start at Home
  base.write(homeBase);
  shoulder.write(homeShoulder);
  elbow.write(homeElbow);
  gripper.write(homeGripper);
  
  delay(2000); // Wait for you to get ready
}

void loop() {
  Serial.println("--- Starting Cycle ---");

  // Step 1: Open Gripper & Go to Pick Approach (Hover)
  Serial.println("Moving to Pick...");
  smoothMove(base, pickBase);
  // Keep arm slightly up before diving down
  smoothMove(shoulder, pickShoulder + 20); 
  smoothMove(elbow, pickElbow + 20);
  smoothMove(gripper, 0); // Open Gripper
  delay(500);

  // Step 2: Dive Down
  Serial.println("Grabbing...");
  smoothMove(shoulder, pickShoulder);
  smoothMove(elbow, pickElbow);
  delay(500);

  // Step 3: GRAB!
  smoothMove(gripper, pickGripper); // Close
  delay(500); // Ensure grip is tight

  // Step 4: Lift Up (Important! Don't drag the object)
  Serial.println("Lifting...");
  smoothMove(shoulder, 110); // Lift shoulder high
  smoothMove(elbow, 90);
  delay(500);

  // Step 5: Move to Place Location
  Serial.println("Moving to Place...");
  smoothMove(base, placeBase);
  delay(500);

  // Step 6: Lower Arm to Drop
  Serial.println("Dropping...");
  smoothMove(shoulder, placeShoulder);
  smoothMove(elbow, placeElbow);
  delay(500);

  // Step 7: DROP!
  smoothMove(gripper, placeGripper); // Open
  delay(500);

  // Step 8: Lift & Return Home
  Serial.println("Returning Home...");
  smoothMove(shoulder, 110); // Lift first
  smoothMove(base, homeBase);
  smoothMove(elbow, homeElbow);
  
  Serial.println("Cycle Complete. Waiting...");
  delay(2000); // Wait 2 seconds before repeating
}

// --- 🧈 SMOOTH MOVEMENT FUNCTION ---
// Makes the robot look professional, not jerky
void smoothMove(Servo &servo, int targetAngle) {
  int currentAngle = servo.read();
  
  if (currentAngle < targetAngle) {
    for (int i = currentAngle; i <= targetAngle; i++) {
      servo.write(i);
      delay(speedDelay); // Speed control
    }
  } else {
    for (int i = currentAngle; i >= targetAngle; i--) {
      servo.write(i);
      delay(speedDelay);
    }
  }
}