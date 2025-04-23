# Smart Home Automation System

## Overview
This smart home automation system provides a comprehensive solution for monitoring and controlling various aspects of your home using IoT technology. Built with ESP8266 and the Blynk platform, it allows you to control your home appliances remotely via mobile or web interfaces.

[Watch Demo Video](https://www.youtube.com/watch?v=4yWa0fR5BLM)

## Features

### Remote Control
- Control lights and electric utilities from your smartphone
- Master light control
- Individual appliance control

### Security System
- Motion detection with PIR sensor
- Automatic alert notifications
- Visual and audio alarms (buzzer and LED alerts)
- Real-time security monitoring

### Environmental Monitoring
- Temperature and humidity tracking
- Gas leak detection
- Real-time environmental data dashboard

### Smart Water Management
- Water level monitoring in reservoir
- Dual operation modes:
  - **Automatic Mode**: Motor starts automatically when water reaches minimum threshold and stops at maximum level
  - **Manual Mode**: User-controlled motor operation
- Visual water level indicator on dashboard

### Energy Management
- Electricity usage monitoring
- Bill prediction based on utility usage time
- Energy consumption dashboard

## Hardware Components
- ESP8266 WiFi module
- DHT22 temperature and humidity sensor
- PIR motion sensor
- Ultrasonic sensor (for water level)
- Relay modules for controlling appliances
- LED indicators
- Buzzer for alerts
- Water pump motor

## Software Architecture
- Built on Blynk IoT platform
- Real-time monitoring and control
- Event-based notifications
- Timer-based sensing and actuation

## Installation & Setup

### Prerequisites
- Arduino IDE
- Blynk mobile app
- ESP8266 board support in Arduino IDE
- Required libraries:
  - ESP8266WiFi
  - BlynkSimpleEsp8266
  - DHT

### Configuration
1. Install the required libraries in Arduino IDE
2. Configure your WiFi credentials in the code
3. Set up your Blynk account and obtain Auth Token
4. Upload the code to ESP8266
5. Connect the hardware components according to the wiring diagram

### Blynk Dashboard Setup
The system uses the following virtual pins:
- V0: System ON/OFF
- V2: Temperature display
- V3: Humidity display
- V4: Distance sensor (water level)
- V5: Utilities monitoring
- V6: Water level percentage
- V7: Motor control
- V8: Automatic/Manual mode toggle
- V9: Master light control

## Circuit Diagram
(Add circuit diagram here)

## Future Enhancements
- Voice control integration
- Machine learning for predictive maintenance
- Solar power integration
- Additional sensor support
- Enhanced security features

## Troubleshooting
- Check WiFi connection if system is unresponsive
- Verify sensor connections if readings are inconsistent
- Ensure proper power supply to all components
- Reset the system if experiencing unexpected behavior

## Contributors
- MIRMD.TAHMIDKABIR

## License
This project is open-source and available under the MIT License. 