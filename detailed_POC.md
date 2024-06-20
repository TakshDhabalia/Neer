# Proof of Concept (POC) Progress Documentation

This document outlines the steps for creating a server-client system where a NodeMCU acts as a server displaying data from an HC-SR04 sensor module. It also describes an alternative implementation using the MQTT protocol for real-time data transmission.

## Objective
To create a server-client system where a NodeMCU acts as a server displaying data from an HC-SR04 sensor module, and an alternative implementation using the MQTT protocol for real-time data transmission.

## Part 1: Server-Client System Using NodeMCU

### 1. Setting Up the Server (NodeMCU)

#### Components Required
- NodeMCU (ESP8266)
- USB cable
- Power supply (5V)

#### Steps
1. **Install Required Libraries**
   - Ensure you have the ESP8266 board package installed in your Arduino IDE.
   - Include the `ESP8266WiFi.h` library in your sketch.

2. **Writing the HTML in the Script**
   - Embed the HTML code within your Arduino sketch to create a web interface.
   - Example HTML can be as simple as buttons to display and control GPIO pins.

3. **Uploading the Script**
   - Connect your NodeMCU to your computer via USB.
   - Write and upload the sketch to the NodeMCU.

4. **Powering the NodeMCU**
   - Once uploaded, connect the NodeMCU to a 5V power supply.
   - The NodeMCU will connect to your Wi-Fi network and start the server.

5. **Accessing the Server**
   - Open a web browser and enter the IP address of the NodeMCU.
   - The web interface will be displayed, showing the status of GPIO pins and other data.

### 2. Setting Up the Client (HC-SR04 Sensor Module)

#### Components Required
- Another NodeMCU (ESP8266)
- HC-SR04 sensor
- Jumper wires

#### Steps
1. **Connect the Sensor**
   - Connect the HC-SR04 sensor to the NodeMCU. The typical connections are:
     - VCC to 5V
     - GND to GND
     - Trig to D1
     - Echo to D2

2. **Write the Sketch**
   - Write a sketch to read the distance measured by the HC-SR04 sensor.
   - Store the measured distance in a temporary variable.

3. **Publish Data to the Server**
   - Modify the client sketch to send the sensor data to the server (NodeMCU).
   - This can be done using HTTP requests (GET/POST) to update the data on the server.

## Alternative: Using MQTT Protocol

### 1. Introduction to MQTT
- **MQTT (Message Queuing Telemetry Transport)**
  - Lightweight messaging protocol.
  - Uses a broker to manage communication between clients.

### 2. Setting Up the Broker

#### Steps
1. **Choose an MQTT Broker**
   - Use a cloud-based broker like HiveMQ or another open cloud provider.
   - Sign up and set up a new MQTT broker instance.

### 3. Modifying the Server and Client Sketches

#### Steps
1. **Install MQTT Libraries**
   - Install PubSubClient library for MQTT communication in Arduino IDE.

2. **Configure the Server (NodeMCU)**
   - Write a sketch to connect to the MQTT broker.
   - Subscribe to relevant topics to receive data from the sensor client.

3. **Configure the Client (Sensor Module)**
   - Write a sketch to connect to the MQTT broker.
   - Publish sensor data to specific topics on the MQTT broker.

### 4. Setting Up the Android App

#### Steps
1. **Develop the App in Dart**
   - Use Flutter framework for developing the app.
   - Integrate MQTT client library to subscribe to topics and display real-time data.

## Summary of Steps

1. **Server-Client with NodeMCU**
   - Set up NodeMCU as a server with embedded HTML.
   - Use another NodeMCU to read sensor data and send it to the server.

2. **Using MQTT**
   - Set up an MQTT broker on the cloud.
   - Configure both NodeMCUs to connect to the broker.
   - Use an Android app to display data by subscribing to MQTT topics.
