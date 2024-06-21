# Smart Medibox

## Project Overview

The Smart Medibox is an innovative device designed to help users manage their medication schedules effectively while monitoring environmental conditions. This device uses an ESP32 microcontroller and integrates several components including an OLED display, a DHT22 temperature and humidity sensor, push buttons for user input, LEDs for visual alerts, and a buzzer for auditory alerts.

## Features

1. **Medication Reminders**:
   - Set up to three alarms to remind users to take their medication.
   - Alarms are configurable via push buttons and displayed on the OLED screen.
   - A buzzer plays a melody and a red LED lights up when it's time to take medication.

2. **Environmental Monitoring**:
   - Continuously monitors temperature and humidity using a DHT22 sensor.
   - Alerts the user with a yellow LED if the temperature or humidity levels go outside predefined boundaries.

3. **User Interface**:
   - OLED display shows current time, alarm settings, and environmental readings.
   - Push buttons allow users to navigate the menu, set alarms, and adjust temperature and humidity thresholds.

4. **Time Synchronization**:
   - Automatically synchronizes time using Wi-Fi and an NTP server.
   - Allows the user to set the time zone offset for accurate local time display.

## Components

- **ESP32 Microcontroller**: The brain of the project, responsible for managing all functionalities.
- **OLED Display (128x64)**: Used to display time, alarms, and menu options.
- **DHT22 Sensor**: Measures temperature and humidity.
- **Buzzer**: Plays a melody to alert the user when it's time to take medication.
- **LEDs**: 
  - Red LED for medication time alerts.
  - Yellow LED for temperature and humidity warnings.
- **Push Buttons**:
  - OK/Menu button for selecting options.
  - UP and DOWN buttons for navigation.
  - CANCEL button to stop alarms or exit menus.

## How It Works

### Initial Setup

1. **Power On**: When powered on, the medibox initializes the OLED display, DHT22 sensor, and connects to a Wi-Fi network.
2. **Display Welcome Message**: The OLED screen displays a welcome message.

### Setting Alarms

1. **Enter Menu**: Press the OK/Menu button to enter the menu.
2. **Navigate Menu**: Use the UP and DOWN buttons to navigate through menu options.
3. **Set Alarms**: Select the option to set an alarm and use the UP and DOWN buttons to adjust the hours and minutes. Confirm by pressing the OK button.

### Monitoring Environment

1. **Continuous Monitoring**: The DHT22 sensor continuously monitors the temperature and humidity.
2. **Warning Alerts**: If the readings exceed the preset boundaries, the yellow LED lights up and a warning message is displayed on the OLED screen.

### Taking Medication

1. **Alarm Trigger**: At the set alarm time, the buzzer plays a melody and the red LED lights up.
2. **Stop Alarm**: Press the CANCEL button to stop the alarm and reset the reminder.

## Circuit Diagram

The project circuit diagram is created using Wokwi and includes connections for all components:
- ESP32
- OLED Display
- DHT22 Sensor
- Buzzer
- LEDs
- Push Buttons
- Resistors

Refer to the `diagram.json` file for detailed connections.

## Code Overview

The project code is implemented in `esp32-arduino.ino`, which includes:

- Initialization of all components.
- Wi-Fi connection and time synchronization.
- Functions for setting alarms, monitoring environmental conditions, and handling user input.
- Logic to manage alarms and provide alerts.

## Getting Started

1. **Clone the Repository**:
   ```
   git clone <https://github.com/LasiduDilshan/Medibox-Project-for-Embedded-Systems-Module>
   cd smart-medibox
   ```

2. **Upload the Code**:
   - Open the `esp32-arduino.ino` file in the Arduino IDE.
   - Select the appropriate board and port.
   - Upload the code to the ESP32.

3. **Assemble the Hardware**:
   - Connect the components as per the circuit diagram in `diagram.json`.

4. **Power On**:
   - Power on the device and wait for the initial setup to complete.
   - Set the time zone and alarms as needed.

Even we can try it in wokwi platform.

## Conclusion

The Smart Medibox is a practical and user-friendly device designed to help users manage their medication schedules effectively while keeping track of environmental conditions. With its intuitive interface and reliable alerts, it ensures users never miss their medication and stay informed about their surroundings.
