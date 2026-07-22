# Real-Time HCHO Measurement & Monitoring System (Role: Co-Contributor)

This repository contains an independent extracurricular project developed by a two-student team during our Electrical and Computer Engineering (ECE) studies at the Vietnamese-German University (VGU). I worked as a co-contributor alongside **Lê Huỳnh Văn Hóa**, under the supervision of **Hồ Hữu Khánh An** and the academic guidance of **Professor Võ Bích Hiển**.

## 🖥️ About the Project

This project is a portable embedded and IoT system designed to measure **formaldehyde (HCHO)** concentration and support long-term indoor environmental monitoring.

The final prototype uses a **Sensirion SFA30** sensor and an **ESP32-WROOM-32U** to collect HCHO data, display the current concentration locally in parts per billion (ppb), timestamp and save readings to a microSD card, and upload measurements to a ThingSpeak dashboard for remote observation.

The electronics were soldered onto a prototyping board and installed inside a custom transparent enclosure. Ventilation openings and intake/exhaust fans were included to maintain airflow around the sensor while protecting the electronics.

## 👥 My Contribution

As one of the project's two student contributors, I participated in:

* Designing and assembling the embedded measurement system.
* Integrating the ESP32 with the HCHO sensor, OLED display, RTC, and microSD module.
* Developing and optimizing the Arduino/C++ firmware.
* Implementing local data logging and ThingSpeak cloud monitoring.
* Testing, troubleshooting, documenting, and improving the prototype across multiple development stages.

## 🛠️ Hardware & Build Process

* **Microcontroller:** ESP32-WROOM-32U.
* **HCHO Sensor:** Sensirion SFA30 formaldehyde sensor connected through I2C.
* **Local Display:** SH1106 128 × 64 OLED for HCHO concentration, date, time, and connection-status icons.
* **Timekeeping:** DS3231 real-time clock for timestamping measurements.
* **Local Storage:** MicroSD card module for backup logging in CSV format.
* **Power:** Portable 5 V power-bank supply during prototype testing.
* **Construction:** Soldered prototyping board housed in a custom ventilated transparent enclosure.

### Final Wiring

| Component | ESP32 Connection |
|---|---|
| SFA30 VCC / GND | 3.3 V / GND |
| SFA30 SDA / SCL | GPIO21 / GPIO22 |
| SFA30 SEL | GND |
| DS3231 SDA / SCL | GPIO21 / GPIO22 |
| SH1106 SDA / SCL | GPIO21 / GPIO22 |
| MicroSD MISO / MOSI | GPIO19 / GPIO23 |
| MicroSD SCK / CS | GPIO18 / GPIO5 |

## 💻 Software & Data Processing

* **Language and Environment:** Arduino C/C++ using the Arduino IDE and ESP32 board support.
* **Sensor Processing:** Reads HCHO concentration from the Sensirion SFA30 and converts the output for display in ppb.
* **Dual-Core Operation:** Uses ESP32 FreeRTOS tasks to separate local measurement operations from Wi-Fi and cloud communication.
* **Local Task:** Reads the sensor, updates the OLED, retrieves RTC timestamps, and records a new measurement to `log.csv` approximately every two seconds.
* **Cloud Task:** Maintains the Wi-Fi connection and uploads HCHO readings to ThingSpeak approximately every 15 seconds.
* **Connection Recovery:** Automatically retries the Wi-Fi connection when the network becomes unavailable.
* **Main Libraries:** `SensirionI2CSfa3x`, `U8g2`, `RTClib`, `ThingSpeak`, `WiFi`, `SD`, `SPI`, and `Wire`.

* Source Code: [View the Formaldehyde System Repository](https://github.com/donguyen0701/Formaldehyde)

## 🔄 Development Progression

### Stage 1 — Proof of Concept

The first prototype used a temporary low-cost gas sensor, an SPI TFT display, a DS3231 RTC, and Adafruit IO.

This stage verified analog sensor acquisition, local time display, and remote cloud visualization.

* [Watch First-Stage Hardware Demo](HCHO%20demo%281%29%20First%20stage.mp4)
* [Watch First-Stage Cloud Demo](HCHO%20demo%282%29%20First%20stage.mp4)

### Final Prototype — Integrated Monitoring System

The system was upgraded to include:

* A Sensirion SFA30 formaldehyde sensor.
* A compact I2C OLED display.
* ThingSpeak real-time cloud monitoring.
* Reliable microSD backup storage.
* Optimized dual-core firmware.
* A soldered circuit board.
* A ventilated protective enclosure.

These changes reduced cable clutter and improved the system's portability, maintainability, and data continuity.

## 📷 Prototype & Results

### Enclosure Concept

![Ventilated enclosure concept](Box.jpg)

### Final Enclosed Prototype

![Finished HCHO measurement system](Finished.jpg)

### Final Circuit Schematic

![Final HCHO measurement system schematic](Schematics.jpg)

### Soldered Electronics

![Soldered ESP32 HCHO measurement circuit](Soldered.jpg)

### Serial Monitoring & Local Logging

![ESP32 terminal output and SD-card logging](Terminal.jpg)

### ThingSpeak Cloud Dashboard

![ThingSpeak monitoring dashboard](Thingspeak.jpg)

The prototype successfully demonstrated the complete data path from sensor acquisition to local display, timestamped microSD storage, serial monitoring, and remote cloud visualization.

The recorded values were used for preliminary system evaluation rather than certified air-quality assessment.

## 🚀 How to Run

### Requirements

* Arduino IDE with ESP32 board support installed.
* The libraries listed in the software section.
* Assembled hardware following the final wiring table or project report.
* A formatted microSD card.
* A Wi-Fi network.
* A ThingSpeak channel with write access.

### Instructions

1. Clone or download the [source-code repository](https://github.com/donguyen0701/Formaldehyde).
2. Open `HCHO_MARK4/HCHO_MARK4.ino` in the Arduino IDE.
3. Keep all `.ino` files inside the `HCHO_MARK4` directory so that they compile together.
4. Install the required Arduino libraries.
5. Select the appropriate ESP32 board and serial port.
6. Replace the Wi-Fi SSID, Wi-Fi password, ThingSpeak channel number, and write API key with your own configuration.
7. Connect the hardware according to the final wiring table.
8. Insert the microSD card and upload the firmware to the ESP32.
9. Open the Serial Monitor at **115200 baud**.
10. Verify the sensor readings, SD-card logging, RTC time, Wi-Fi connection, and ThingSpeak updates.

> [!IMPORTANT]
> Never publish real Wi-Fi credentials or ThingSpeak write keys in the source code. Use placeholders or a separate untracked configuration file before making the repository public.

## 📄 Project Documents

* [Final Project Report — July 2024](HCHO%20MEASURE%20FINAL%20REPORT.pdf)
* [Initial Project Report](HCHO%20MEASURE%20PROJECT%20REPORT.pdf)
* [Project Progress Update — 18 June 2024](HCHO%2018-06-2024.pdf)

## ⚠️ Prototype Status & Limitations

This system is an engineering prototype that reached the preliminary laboratory-testing stage. It is **not a calibrated or certified safety instrument**.

The project reports identified several remaining limitations:

* Variation in the sensor output during early testing.
* Prototype-grade wiring and electronic connections.
* Limitations in the power-supply and power-distribution design.
* Dependence on Wi-Fi for real-time cloud updates.
* The need to compare measurements against a trusted reference instrument.

Further calibration, controlled laboratory testing, and electrical refinement would be required before the system could be considered for real-world safety applications.
