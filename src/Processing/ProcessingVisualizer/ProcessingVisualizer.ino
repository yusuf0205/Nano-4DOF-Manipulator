/*
  🦾 YUJAI BOT - DIGITAL TWIN 3D by H Mohammed Yusuf
  Run this in PROCESSING IDE (Not Arduino IDE!)
*/

import processing.serial.*;

Serial myPort;
float baseX = 90;
float shoulderY = 90;
float elbowY = 90;
float gripper = 0;

void setup() {
  size(800, 600, P3D); // 3D Window
  
  // CHANGE THIS TO YOUR COM PORT! (e.g., "COM5")
  // On Mac it looks like "/dev/tty..."
  // On Windows it is "COMx"
  String portName = "COM4"; 
  
  try {
    myPort = new Serial(this, portName, 9600);
  } catch (Exception e) {
    println("⚠️ Error: Check COM Port or connect Arduino!");
  }
  
  textSize(16);
}

void draw() {
  background(30); // Dark Grey Background
  lights(); // Add 3D Lighting
  
  // 1. Control Logic (Mouse Interaction)
  // Mouse X moves Base (Left-Right)
  // Mouse Y moves Shoulder (Up-Down)
  baseX = map(mouseX, 0, width, 0, 180);
  shoulderY = map(mouseY, 0, height, 180, 0); // Inverted for feel
  
  // Use Keyboard for Elbow (W/S) and Gripper (A/D)
  if (keyPressed) {
    if (key == 'w' || key == 'W') elbowY = constrain(elbowY + 1, 0, 180);
    if (key == 's' || key == 'S') elbowY = constrain(elbowY - 1, 0, 180);
    if (key == 'a' || key == 'A') gripper = constrain(gripper + 2, 0, 180);
    if (key == 'd' || key == 'D') gripper = constrain(gripper - 2, 0, 180);
  }

  // 2. Send Data to Arduino (Every 5 frames to avoid lag)
  if (frameCount % 5 == 0 && myPort != null) {
    String data = int(baseX) + "," + int(shoulderY) + "," + int(elbowY) + "," + int(gripper) + "\n";
    myPort.write(data);
  }

  // 3. DRAW THE 3D ROBOT
  pushMatrix();
  
  // Position the robot in center-bottom
  translate(width/2, height/2 + 100, -100);
  rotateX(radians(-20)); // Tilt camera slightly
  rotateY(radians(frameCount * 0.5)); // Auto-rotate view slowly (Cinematic!)

  // --- BASE ---
  fill(0, 255, 0); // Green
  box(100, 20, 100); // Base Plate
  
  rotateY(radians(baseX - 90)); // Rotate Base
  translate(0, -30, 0);
  fill(255, 0, 0); // Red Motor
  box(40, 40, 40); 
  
  // --- SHOULDER ---
  translate(0, -20, 0);
  rotateZ(radians(shoulderY - 90)); // Rotate Shoulder
  
  fill(255, 255, 0); // Yellow Arm
  translate(50, 0, 0); // Move along arm length
  box(100, 20, 20); // Draw Arm
  
  // --- ELBOW ---
  translate(50, 0, 0); // Move to end of arm
  rotateZ(radians(elbowY - 90)); // Rotate Elbow
  
  fill(0, 0, 255); // Blue Forearm
  translate(40, 0, 0);
  box(80, 15, 15);
  
  // --- GRIPPER ---
  translate(40, 0, 0);
  fill(255); // White Gripper
  
  pushMatrix();
  rotateX(radians(gripper)); // Open/Close animation logic (Fake visual)
  box(20, 5, 20);
  popMatrix();
  
  popMatrix();
  
  // 4. UI Overlay
  camera(); // Reset camera for text
  hint(DISABLE_DEPTH_TEST);
  fill(255);
  text("YUJAI BOT - DIGITAL TWIN", 20, 30);
  text("Base: " + int(baseX), 20, 60);
  text("Shoulder: " + int(shoulderY), 20, 80);
  text("Elbow (W/S): " + int(elbowY), 20, 100);
  text("Gripper (A/D): " + int(gripper), 20, 120);
  hint(ENABLE_DEPTH_TEST);
}