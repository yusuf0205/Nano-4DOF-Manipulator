/*
 * 🎯 Yujai Bot - Single Joint Test by H Mohammed Yusuf
 * * GOAL: Test ONLY ONE servo to fix mechanical jams.
 * * * HOW TO USE:
 * 1. Change 'targetPin' below to the pin you want to test (3, 5, 6, or 9).
 * 2. Upload.
 * 3. Watch ONLY that joint.
 * 4. If it hums/stalls, LOOSEN the screw gently until it moves freely.
 */

#include <Servo.h>

Servo myServo;

// 👇👇👇 CHANGE THIS NUMBER (3, 5, 6, or 9) 👇👇👇
const int targetPin = 5; 
// 👆👆👆 CHANGE THIS NUMBER 👆👆👆

void setup() {
  Serial.begin(9600);
  
  Serial.print("🎯 Targeting Servo on Pin: ");
  Serial.println(targetPin);
  
  myServo.attach(targetPin);
  
  Serial.println("Moving to Center (90)...");
  myServo.write(90);
  delay(2000); // Wait for you to touch the screw
}

void loop() {
  Serial.println("🔄 Wiggling...");
  
  // Gentle Wiggle (70 to 110 degrees)
  // Not full range, just enough to check tightness
  
  // Go Left
  for (int pos = 90; pos >= 60; pos--) {
    myServo.write(pos);
    delay(20); // Slow movement
  }
  
  delay(500); // Pause
  
  // Go Right
  for (int pos = 60; pos <= 120; pos++) {
    myServo.write(pos);
    delay(20);
  }
  
  delay(500); // Pause

  // Return Center
  for (int pos = 120; pos >= 90; pos--) {
    myServo.write(pos);
    delay(20);
  }
  
  Serial.println("⏸️ Pausing... Adjust Screw NOW if needed!");
  delay(2000); // 2 Seconds break for you to adjust
}