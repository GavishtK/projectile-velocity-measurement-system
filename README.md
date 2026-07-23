# Projectile Velocity Measurement System (PVMS)

> **Development of an IoT-Based Projectile Velocity Measurement System**

![Project Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Language](https://img.shields.io/badge/Language-Arduino%20C++-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

## 📖 Overview

The Projectile Velocity Measurement System (PVMS) is an IoT-based embedded system designed to accurately measure the velocity of a projectile using the optical Time-of-Flight (ToF) principle.

The system utilizes two optical sensing gates connected to an ESP32 microcontroller. As a projectile passes through both gates, the ESP32 measures the elapsed time with microsecond precision and calculates the projectile's velocity. The measured velocity is displayed in real time on an OLED display.

This project was developed during a summer internship at **DRDO**. This repository contains only my original implementation and documentation intended for educational and portfolio purposes. No confidential or restricted information is included.

---

# ✨ Features

- High-speed projectile velocity measurement
- ESP32-based embedded system
- Optical Time-of-Flight measurement
- Microsecond precision using hardware interrupts
- Real-time OLED display
- Serial Monitor output
- Automatic timeout handling
- Low-cost implementation
- Compact and portable design

---

# ⚙ Hardware Used

| Component | Quantity |
|------------|----------|
| ESP32 DevKit V1 | 1 |
| OLED Display (SSD1306 128×64) | 1 |
| Laser Modules | 2 |
| Photodiodes | 2 |
| Breadboard | 1 |
| Jumper Wires | As required |
| USB Power Supply | 1 |

---

# 🛠 Software Used

- Arduino IDE
- ESP32 Board Package
- Adafruit SSD1306 Library
- Adafruit GFX Library
- Wire Library

---

# 🚀 Working Principle

The system consists of two optical gates placed at a known distance apart.

1. The first optical gate detects the projectile.
2. ESP32 starts a high-resolution timer.
3. The second optical gate detects the projectile.
4. ESP32 stops the timer.
5. Velocity is calculated using the Time-of-Flight equation:

\[
Velocity = \frac{Distance}{Time}
\]

The calculated velocity is then displayed on the OLED screen and printed to the Serial Monitor.

---

# 📂 Repository Structure

```
Projectile-Velocity-Measurement-System/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── src/
│   └── ProjectileVelocityMeasurement.ino
│
├── docs/
│   └── Final_Report.pdf
│
├── images/
│   ├── hardware_setup.jpg
│   ├── oled_display.jpg
│   └── flowchart.png
│
├── hardware/
│   ├── schematic/
│   ├── pcb/
│   └── enclosure/
│
└── results/
```

# 📊 Results

The developed prototype successfully measured projectile velocity using optical sensing gates with stable and repeatable measurements.

The system demonstrates:

- Reliable optical triggering
- Accurate microsecond timing
- Stable velocity calculations
- Real-time display on OLED

---

# 🔮 Future Improvements

- Custom PCB Design
- Rechargeable Battery System
- Wireless Data Logging
- Mobile Application
- Cloud Connectivity
- Protective Enclosure
- Improved Optical Alignment
- Calibration Software

---

# 👨‍💻 Author

**Gavisht Karkara**

B.Tech Electronics & Communication Engineering

Thapar Institute of Engineering and Technology

---

# 📜 License

This project is licensed under the MIT License.

---

# ⚠ Disclaimer

This project was developed during a summer internship at **DRDO**.

This repository contains only my own implementation, firmware, and documentation intended for educational and portfolio purposes. No confidential, proprietary, or restricted information has been included.

---

## ⭐ If you found this project useful, consider giving it a star!