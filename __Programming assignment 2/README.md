# Smart Medibox - Node-RED Integration

## Project Overview

The Smart Medibox project has been enhanced with Node-RED integration to allow for remote monitoring and control via a Node-RED dashboard. Additionally, a Light Dependent Resistor (LDR) has been added to measure light intensity, which influences the servo motor's position for potential applications like adjusting light exposure.

## Features

1. **Remote Monitoring and Control**:
   - Monitor light intensity and temperature remotely via Node-RED dashboard.
   - Control the medibox features such as alarm settings and servo motor adjustments through MQTT messages.

2. **Light Intensity Measurement**:
   - Two LDR sensors (indoor and outdoor) to measure light intensity.
   - Servo motor adjusts its position based on the measured light intensity to control light exposure.

3. **Enhanced User Interface**:
   - Node-RED dashboard provides a user-friendly interface to view real-time data and control the device.
   - Components include gauges, charts, switches, sliders, and dropdowns for comprehensive control and monitoring.

4. **Scheduled Tasks**:
   - Ability to schedule tasks through the Node-RED dashboard.
   - Controls and monitors scheduled tasks via MQTT.

## Components

- **ESP32 Microcontroller**: The brain of the project, managing all functionalities.
- **OLED Display (128x64)**: Displays current time, alarms, and menu options.
- **DHT22 Sensor**: Measures temperature and humidity.
- **LDR Sensors**: Measures light intensity, influencing servo motor adjustments.
- **Buzzer**: Alerts the user for medication time.
- **Servo Motor**: Adjusts position based on light intensity.
- **LED**: Indicates various alerts.
- **Push Buttons**: Allows manual interaction with the device.
- **WiFi and MQTT**: Enables communication with Node-RED dashboard.

## Node-RED Dashboard

The Node-RED dashboard provides an intuitive interface for users to interact with the smart medibox. The dashboard includes:

1. **Light Intensity Monitoring**:
   - Gauge and chart display real-time light intensity readings from LDR sensors.
   - Text indicator shows which LDR (indoor or outdoor) has higher intensity.

2. **Temperature Monitoring**:
   - Gauge and chart display real-time temperature readings from the DHT22 sensor.

3. **Control Elements**:
   - **Main Switch**: Toggle the main power of the device.
   - **Scheduled Switch**: Enable or disable scheduled tasks.
   - **Date Picker**: Select a date for scheduling tasks.
   - **Time Input**: Input specific times for scheduling tasks.
   - **Sliders**: Adjust the minimum angle for the servo motor and the controlling factor for light intensity adjustment.
   - **Dropdown**: Select presets for medication types which adjust the minimum angle and controlling factor accordingly.

## Getting Started

### Hardware Setup

1. **Assemble the Components**:
   - Connect all components as per the circuit diagram provided in `diagram.json`.
   - Ensure the ESP32, OLED display, DHT22 sensor, LDR sensors, buzzer, servo motor, LEDs, and push buttons are properly connected.

2. **Upload the Code**:
   - Open the `sketch.ino` file in the Arduino IDE.
   - Select the appropriate board and port.
   - Upload the code to the ESP32.

### Node-RED Setup

1. **Install Node-RED**:
   - Ensure Node-RED is installed on your system. Follow the installation guide [here](https://nodered.org/docs/getting-started/).

2. **Import Flows**:
   - Open the Node-RED editor.
   - Import the flows from the `flows.json` file provided.
   - Deploy the flows.

3. **Configure MQTT Broker**:
   - Ensure the MQTT broker details are correctly configured in Node-RED.
   - The project uses `test.mosquitto.org` as the broker. Update the broker settings if using a different MQTT broker.

### Usage

1. **Monitor and Control via Dashboard**:
   - Access the Node-RED dashboard to view real-time data and control the device.
   - Use gauges and charts to monitor light intensity and temperature.
   - Use switches, sliders, and dropdowns to control various functionalities.

2. **Scheduled Tasks**:
   - Enable scheduled tasks via the schedule switch.
   - Set the date and time for tasks using the date picker and time input elements.

3. **Light Intensity Adjustment**:
   - The servo motor position adjusts automatically based on the LDR readings and the controlling factor set via the dashboard.

## Conclusion

The enhanced Smart Medibox with Node-RED integration provides a comprehensive solution for managing medication schedules, monitoring environmental conditions, and controlling device features remotely. The intuitive Node-RED dashboard ensures ease of use and flexibility for the user, making it a practical and effective tool for health management.
