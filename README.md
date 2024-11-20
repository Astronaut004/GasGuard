# GasGuard: Smart Gas Leakage Detection System

GasGuard is an IoT-based gas leakage detection system designed to monitor and alert users about potential gas leaks in residential or industrial environments. The system uses multiple gas sensors (MQ2, MQ4, MQ9), and an ESP32 microcontroller to detect various gases and send SMS alerts. The system also uploads gas concentration data to ThingSpeak for remote monitoring and analytics.

## Table of Contents

- [Introduction](#introduction)
- [Technology Stack](#technology-stack)
- [Key Features](#key-features)
- [Components](#components)
- [Code Overview](#code-overview)
- [Usage](#usage)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Introduction

GasGuard is an innovative IoT-based solution to detect gas leaks and provide real-time alerts to prevent accidents. By utilizing gas sensors, WiFi communication, SMS alerts, and cloud storage (ThingSpeak), GasGuard enables users to monitor gas concentrations continuously and receive immediate notifications when thresholds are crossed.

## Technology Stack

- **Microcontroller**: ESP32
- **Gas Sensors**: MQ-2, MQ-4, MQ-9
- **Cloud**: ThingSpeak for data visualization and analysis
- **SMS Alert**: GSM Module (SIM900A or SIM800L)
- **Programming Language**: Arduino IDE (C/C++)

## Key Features

- Multi-gas detection: LPG, Methane, CO, Propane, Hydrogen, CNG, and Smoke.
- Real-time SMS alert system to notify users of gas leaks.
- Data logging and remote monitoring via ThingSpeak.
- Threshold-based triggering for gas concentrations.
- LED indicators and buzzer for local alerts.

## Components

- **ESP32 Microcontroller**: Handles the main processing and WiFi communication.
- **MQ-2, MQ-4, MQ-9 Sensors**: Used to detect various gases.
- **GSM Module (SIM900A or SIM800L)**: Used for sending SMS alerts.
- **Buzzer and LEDs**: For immediate local visual and audio alerts.
- **WiFi**: For cloud communication to ThingSpeak.
- **Power Supply**: 5V DC for the ESP32 and other components.

## Code Overview

The code is designed to read sensor data from the gas sensors (MQ-2, MQ-4, MQ-9), calculate the gas concentrations, compare them to predefined thresholds, and alert the user if a gas leak is detected. The system also uploads the sensor data to ThingSpeak for real-time monitoring.

### Key Functions:
- **calculateMQ2()**, **calculateMQ4()**, **calculateMQ9()**: Functions to calculate the concentration of specific gases.
- **checkAndAlert()**: Function to check if the gas concentration exceeds the threshold and trigger the alert.
- **sendSMS()**: Sends SMS messages to a predefined number.
- **WiFi & HTTP Client**: Uploads data to ThingSpeak.

## Usage

1. Set up your ESP32 and sensors according to the wiring diagram.
2. Replace the Wi-Fi credentials (`ssid`, `password`) and ThingSpeak API key in the code.
3. Upload the code to the ESP32 using the Arduino IDE.
4. Connect the system to a power supply.
5. The system will start detecting gas concentrations, triggering alerts, and uploading data to ThingSpeak.

## Installation

1. **Install the necessary libraries in Arduino IDE**:
   - `WiFi.h`
   - `HTTPClient.h`
   
2. **Set up ThingSpeak**:
   - Create an account on ThingSpeak and create a new channel.
   - Use the channel's API key in the code.

3. **Upload the Code**:
   - Connect your ESP32 to your computer.
   - Select the correct board and port in Arduino IDE.
   - Upload the provided code.

## Contributing

Feel free to fork the repository, submit issues, or create pull requests to contribute improvements or report bugs.

### Contact
For any questions or inquiries, reach out to me via email at [ac4548817@gmail.com].
