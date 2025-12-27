🦾 The Resurrected Arm - 4DOF Robotic Arm (Arduino Nano)

"Hardware is hard, but we are harder." 🛠️

Welcome to The Resurrected Arm, a 4-Degree-Of-Freedom (DOF) robotic arm powered by an Arduino Nano. What started as a dead breakout board and a dream is now a fully calibrated, Inverse Kinematics-driven pick-and-place machine.

🌟 The Origin Story (The "Surgical Strike")

This project almost died on Day 1. The breakout board arrived with a factory defect—a nasty short circuit between 5V and GND.
Instead of tossing it, I performed a surgical strike with a paper cutter, removing two faulty SMD capacitors that were bridging the rails.
Result: The board resurrected, and the arm was born. 🧟‍♂️✨

🧠 Features

Inverse Kinematics (IK): Enter (x, y, z) coordinates, and the bot calculates the angles using Trigonometry.

Pose Recording: A manual "Teach Mode" to record safe action-figure poses.

Smooth Motion: Custom acceleration logic (no jerky servo movements).

Calibrated Hardware: Software offsets to correct physical servo misalignment.

Wiggle Protocol: A diagnostic tool to check for mechanical jams before operation.

⚡ Hardware Stack

Controller: Arduino Nano (ATmega328P)

Actuators: 4x SG90 Micro Servos

Power: LM2596 Buck Converter (5.2V Output)

Chassis: DIY Acrylic MeArm Clone

Input: Potentiometer (for calibration), Serial Monitor (for commands)

<img width="994" height="448" alt="image" src="https://github.com/user-attachments/assets/6bce190f-da53-4bb6-8525-179c8deafb58" />

⚠️ Power Note: The servos are powered externally via the Buck Converter. The Nano is back-powered via the 5V rail (Adapter Switch MUST be ON before operation).

📂 Project Structure

01_Diagnostics/ - Tools to check servo health (Wiggle Test).

02_Calibration/ - Pose Recorder & Hardware Offset tools.

03_Kinematics/ - The Inverse Kinematics calculator engine.

04_Applications/ - Pick & Place automation scripts.

🚀 How to Run

Clone this repo.

Open 01_Diagnostics/Joint_Wiggle_Test.ino to verify mechanical freedom.

Upload 02_Calibration/Pose_Recorder.ino to find your joint limits.

Update the L1/L2 lengths and Offsets in 03_Kinematics/IK_Calibrated.ino.

Watch the magic happen!

📸 Gallery

![04_Bot_Final_Build](https://github.com/user-attachments/assets/588aa9ac-64a6-46f4-85d5-253d050222b1)

Author: H Mohammed Yusuf
Built with Caffeine, Debugging, and a Multimeter. ⚡
