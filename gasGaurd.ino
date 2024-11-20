#include <WiFi.h>
#include <HTTPClient.h>

// WiFi Credentials
const char* ssid = "project";
const char* password = "project007";

// ThingSpeak API
const char* server = "http://api.thingspeak.com/update";
String apiKey = "H8WP6AJFT410LCQ9";

// GSM Module Pins
#define RXD2 16 // Connect to TX of GSM Module
#define TXD2 17 // Connect to RX of GSM Module

// MQ Sensor Pins
const int mq2Pin = 34;
const int mq4Pin = 35;
const int mq9Pin = 32;

// LED Pins
const int mq2LED = 25;
const int mq4LED = 26;
const int mq9LED = 27;

// Buzzer Pin
const int buzzerPin = 14;

// Threshold Values
const int mq2Threshold = 3000;
const int mq4Threshold = 3000;
const int mq9Threshold = 3000;

// Constants for Calculations
float mq2RL = 10.0; // Load resistance in kOhms
float mq4RL = 20.0;
float mq9RL = 10.0;