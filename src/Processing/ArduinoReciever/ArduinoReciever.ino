#include <Servo.h>

Servo base, shoulder, elbow, gripper;

// PINS (Un setup padi)
const int basePin = 3;
const int shoulderPin = 5;
const int elbowPin = 6;
const int gripperPin = 9;

// Buffer for incoming data
String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(9600); // Communication speed
  
  base.attach(basePin);
  shoulder.attach(shoulderPin);
  elbow.attach(elbowPin);
  gripper.attach(gripperPin);
  
  // Home Position
  base.write(90);
  shoulder.write(90);
  elbow.write(90);
  gripper.write(0);
}

void loop() {
  if (stringComplete) {
    // Expected format: "90,45,120,10" (Base, Shoulder, Elbow, Gripper)
    parseAndMove(inputString);
    inputString = "";
    stringComplete = false;
  }
}

void parseAndMove(String data) {
  // Simple Parsing Logic
  int firstComma = data.indexOf(',');
  int secondComma = data.indexOf(',', firstComma + 1);
  int thirdComma = data.indexOf(',', secondComma + 1);
  
  if (firstComma > 0 && secondComma > 0 && thirdComma > 0) {
    int b = data.substring(0, firstComma).toInt();
    int s = data.substring(firstComma + 1, secondComma).toInt();
    int e = data.substring(secondComma + 1, thirdComma).toInt();
    int g = data.substring(thirdComma + 1).toInt();
    
    // Safety Limits
    b = constrain(b, 0, 180);
    s = constrain(s, 0, 180);
    e = constrain(e, 0, 180);
    g = constrain(g, 0, 180);
    
    // Move Servos
    base.write(b);
    shoulder.write(s);
    elbow.write(e);
    gripper.write(g);
  }
}

// Serial Interrupt (Reads data automatically)
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
}
