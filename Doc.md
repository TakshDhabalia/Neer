# Proof of Concept (POC) Documentation

**Introduction**
This document outlines the detailed steps for creating a server-client system using NodeMCU and ESP8266 microcontrollers. The system is designed to display data from an HC-SR04 sensor module on the server (NodeMCU) and transmit it to Thingspeak via Wi-Fi, using ESP-NOW for communication between the client and server.

**Objective**
The objective of this project is to establish a robust server-client architecture where:
- **NodeMCU acts as the server**, receiving and displaying data from an HC-SR04 sensor module.
- **ESP8266 acts as the client**, collecting sensor data and transmitting it to the server using ESP-NOW.
- Data from the server is sent via Wi-Fi to Thingspeak for storage and further processing through a MIT App Inventor API.

## Client Setup

### Components Used
- **HC-SR04T Ultrasonic Sensor**
  - *Connection Details:*
    - Trigger Pin (Trig): Connected to GPIO5 (D1) of ESP8266.
    - Echo Pin (Echo): Connected to GPIO4 (D2) of ESP8266.
    - VCC: Connected to 5V output of breadboard power supply.
    - GND: Connected to GND of breadboard power supply.
- **ESP8266 Microcontroller**
  - *Component Details:*
    - Used for data collection from HC-SR04 sensor and communication with the server.
    - Integrated with ESP-NOW protocol for direct communication with NodeMCU.
    - Powered by a power bank for mobility and flexibility in deployment.
- **Breadboard Power Supply**
  - *Component Details:*
    - Provides stable 5V power supply to the HC-SR04 sensor and ESP8266.
    - Ensures consistent operation of connected components.
- **Blank PCB**
  - *Component Details:*
    - Used for soldering and organizing connections in a compact form factor.
    - Facilitates customization and integration of additional components if needed.
- **Power Bank**
  - *Component Details:*
    - Supplies power to the ESP8266 for field deployment scenarios.
    - Enables portable operation without reliance on direct mains power.
- **LED Indicators**
  - *Component Details:*
    - Calibration LED: Connected to GPIO12 (D6) of ESP8266.
    - Constant Feed LED: Connected to GPIO13 (D7) of ESP8266.
    - Status LED: Connected to GPIO14 (D5) of ESP8266.
    - Communication LED: Connected to GPIO15 (D8) of ESP8266.
    - Provides visual feedback for system status, calibration process, and communication activity.
- **Calibration Button**
  - *Component Details:*
    - Connection: Connected to GPIO0 (D3) of ESP8266 with an internal pull-up resistor.
    - Controls the start and stop of the calibration process for accurate sensor readings.

### Roles and Responsibilities
- **HC-SR04T Ultrasonic Sensor**: Measures the distance to the water level in the tank.
- **ESP8266 Microcontroller**: Manages sensor data collection, LED status indications, and ESP-NOW communication with the server.
- **Breadboard Power Supply**: Provides stable 5V power to the sensor and ESP8266 for continuous operation.
- **Blank PCB**: Serves as a platform for organizing and connecting components securely.
- **Power Bank**: Supplies portable power for field deployment.
- **LED Indicators**: Visualize system states and communication activity.
- **Calibration Button**: Controls the calibration process for accurate sensor measurements.

**Client Working Details**
The ESP8266 microcontroller in the client setup plays a crucial role in gathering data from the HC-SR04T sensor and communicating it to the server (NodeMCU) using ESP-NOW protocol. Upon initialization, it sets up GPIO pins for sensor and LED control. The HC-SR04T sensor measures distances, and the microcontroller processes these measurements, triggering LEDs to indicate calibration status, constant feed, system status, and communication activity. The calibration button controls the start and stop of calibration processes, ensuring accurate sensor readings.

---

## Server Setup (NodeMCU)

### Components Used
- **NodeMCU (ESP8266)**
  - *Component Details:*
    - Acts as the server to receive data from the client (ESP8266).
    - Integrates with Wi-Fi for data transmission to Thingspeak and MIT App Inventor API.
    - Powered via USB cable for development and testing phases.
- **USB Cable**
  - *Component Details:*
    - Provides power and programming interface to the NodeMCU for setup and operation.
    - Ensures stable connectivity during development and initial deployment stages.
- **Power Supply (5V)**
  - *Component Details:*
    - Supplies continuous 5V power to NodeMCU for operation.
    - Ensures reliable functioning of the server in all operating conditions.

### Server Connections
- **NodeMCU (ESP8266):**
  - Wi-Fi Setup: Configured to connect to the local Wi-Fi network for internet access.
  - Thingspeak Integration: Sends sensor data to Thingspeak cloud platform for storage and visualization.
  - MIT App Inventor API: Facilitates further data processing and integration with external applications.

**Server Working Details**
The NodeMCU (ESP8266) serves as the central server in this setup, receiving real-time sensor data from the client (ESP8266) via ESP-NOW communication. It manages Wi-Fi connectivity for data transmission to the Thingspeak cloud platform, where sensor readings are stored and visualized. Additionally, the NodeMCU facilitates integration with the MIT App Inventor API for extended data processing capabilities. Powered via USB and equipped with robust 5V supply, the NodeMCU ensures continuous operation and reliable data handling across various deployment scenarios.

**Conclusion**
This detailed documentation provides a comprehensive guide to setting up and understanding the server-client system using NodeMCU and ESP8266 microcontrollers. It covers component details, connection diagrams, and functional roles of each component in the system. This documentation is intended to serve as a reference for senior professors and technical stakeholders, ensuring clarity and completeness in project understanding and implementation.
