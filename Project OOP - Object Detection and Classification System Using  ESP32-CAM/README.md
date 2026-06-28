# Object Detection & Classification System (Role: Hardware Coordinator and Co-Coder)

This repository contains my university project, developed as part of my Electrical and Computer Engineering (ECE) studies at the Vietnamese-German University (VGU) for the Object-Oriented Programming subject.

## 🖥️ About the Project

This project is an edge-based inventory tracking solution that seamlessly combines AI and embedded systems. We built a real-time object detection and classification pipeline that identifies various electronic components. The backend implements a robust C++ Object-Oriented Programming (OOP) structure to handle complex storage management, dynamic inventory updates, and checkout functionalities.

## 🛠️ Tools & Build Process

* **Hardware Assembly:** Built using an ESP32-CAM module for real-time edge vision processing.
* **Software & AI:** Model trained and deployed via Edge Impulse. The backend architecture is written entirely in C++ utilizing Linux `termios.h` for seamless serial communication between the microcontroller and the database.
* Here is our demonstration video for this project:
** Object detection demo: https://drive.google.com/file/d/1eHbygeopQmX8abPkYGOJ_PLn9WdN20Hd/view?usp=sharing
** Program OOP demo: https://drive.google.com/file/d/1KJbYxlfLJotT-9fmg-7zanbYw1GJIC-2/view?usp=sharing
## 🚀 How to Run

**Requirements:**
* Linux-based operating system
* Arduino IDE program

**Instructions:**
1. Download the included library and put it in your Arduino folder.
2. With the Edge Impulse library setup, upload the ESP-Cam program to the device.
3. Get the Communication port of the ESP-Cam (e.g., `/dev/ttyACM0`) and assign it to the `portName` variable in the `getComp` function inside `communicator.cpp`.
4. Add the files to a project manager app or compile directly via terminal.
