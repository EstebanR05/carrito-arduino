# 🤖 Carrito Arduino

A project for building and programming an Arduino-based remote-controlled car.

---

## 📚 Table of Contents

- [✨ About](#-about)
- [🔧 Features](#-features)
- [🛠️ Hardware Requirements](#-hardware-requirements)
- [💾 Software & Libraries](#-software--libraries)
- [⚡ Installation & Usage](#-installation--usage)
- [📁 Project Structure](#-project-structure)
- [🤝 Contributing](#-contributing)
- [📝 License](#-license)

---

## ✨ About

This project contains code and resources to build a remote-controlled car using Arduino. It includes different control modes (automatic, manual, sensors) and is designed for learning and experimentation with robotics and embedded systems.

---

## 🔧 Features

- 🚗 Remote control via sensors or manual input
- 🤖 Automatic driving mode
- 📏 Obstacle detection (ultrasonic, inductive sensors)
- 💧 Humidity and environmental sensors
- 🛠️ Modular code for easy extension

---

## 🛠️ Hardware Requirements

- Arduino board (Uno, Mega, etc.)
- Motor driver (L298N or similar)
- DC motors and wheels
- Ultrasonic sensor (HC-SR04)
- Inductive sensor (optional)
- Humidity sensor (optional)
- Power supply (batteries)
- Jumper wires, breadboard, etc.

---

## 💾 Software & Libraries

- [Arduino IDE](https://www.arduino.cc/en/software)
- Standard Arduino libraries
- Additional libraries as needed for sensors

---

## ⚡ Installation & Usage

1. **Clone this repository:**
   ```sh
   git clone <your-repo-url>
   cd carrito-arduino
   ```

2. **Open the desired code in Arduino IDE:**
   - For automatic mode: `Automatic/automatico.cpp`
   - For manual/sensor modes: Check `Control/` subfolders

3. **Connect your Arduino and upload the code.**

4. **Assemble the hardware as described above.**

5. **Power on and enjoy your Arduino car!**

---

## 📁 Project Structure

```
carrito-arduino/
├── Automatic/
│   └── automatico.cpp
├── Control/
│   ├── just-tires/
│   │   └── <code>
│   ├── sensor-inductive/
│   │   └── <code>
│   └── ultrasonic-humidity/
│       └── <code>
├── README.md
```

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome! Please open an issue or pull request. 🙌

---

## 📝 License

This project is licensed under the MIT License.

---

> **Note:**  
> Replace `<your-repo-url>` with your actual repository URL.  
> You can add wiring diagrams, photos, or videos to make your README even more helpful!
