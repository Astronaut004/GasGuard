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

void setup() {
  Serial.begin(115200);       // Debugging serial
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // UART2 for GSM communication

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Pin Modes
  pinMode(mq2LED, OUTPUT);
  pinMode(mq4LED, OUTPUT);
  pinMode(mq9LED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  int mq2Value = analogRead(mq2Pin);
  int mq4Value = analogRead(mq4Pin);
  int mq9Value = analogRead(mq9Pin);

  // Calculate Gas Concentrations
  float mq2Concentration[5];
  calculateMQ2(mq2Value, mq2Concentration);

  float mq4Concentration[2];
  calculateMQ4(mq4Value, mq4Concentration);

  float mq9Concentration[2];
  calculateMQ9(mq9Value, mq9Concentration);

  Serial.println("MQ2 Concentrations:");
  Serial.print("LPG: "); Serial.println(mq2Concentration[0]);
  Serial.print("Propane: "); Serial.println(mq2Concentration[1]);
  Serial.print("Hydrogen: "); Serial.println(mq2Concentration[2]);
  Serial.print("Smoke: "); Serial.println(mq2Concentration[3]);
  Serial.print("Methane (MQ2): "); Serial.println(mq2Concentration[4]);

  Serial.println("MQ4 Concentrations:");
  Serial.print("Methane (MQ4): "); Serial.println(mq4Concentration[0]);
  Serial.print("CNG: "); Serial.println(mq4Concentration[1]);

  Serial.println("MQ9 Concentrations:");
  Serial.print("CO: "); Serial.println(mq9Concentration[0]);
  Serial.print("Methane (MQ9): "); Serial.println(mq9Concentration[1]);


  // Compose SMS Message
  String alertMessage = "";
  bool alert = false;

  if (checkAndAlert(mq2Value, mq2Threshold, mq2LED, "MQ2")) {
    alert = true;
    alertMessage += "MQ2 Alert (LPG, Propane, Hydrogen, Smoke, Methane)\n";
  }
  if (checkAndAlert(mq4Value, mq4Threshold, mq4LED, "MQ4")) {
    alert = true;
    alertMessage += "MQ4 Alert (Methane, CNG)\n";
  }
  if (checkAndAlert(mq9Value, mq9Threshold, mq9LED, "MQ9")) {
    alert = true;
    alertMessage += "MQ9 Alert (CO, Methane)\n";
  }

  if (alert) {
    digitalWrite(buzzerPin, HIGH);
    sendSMS(alertMessage);
    delay(2000); // Buzzer duration
    digitalWrite(buzzerPin, LOW);
  }

  // Upload Data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey +
                 "&field1=" + String(mq2Concentration[0]) + // LPG
                 "&field2=" + String(mq2Concentration[1]) + // Propane
                 "&field3=" + String(mq2Concentration[2]) + // Hydrogen
                 "&field4=" + String(mq2Concentration[3]) + // Smoke
                 "&field5=" + String(mq2Concentration[4]) + // Methane (MQ2)
                 "&field6=" + String(mq4Concentration[0]) + // Methane (MQ4)
                 "&field7=" + String(mq4Concentration[1]) + // CNG
                 "&field8=" + String(mq9Concentration[0]);  // CO
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) 
    {
      Serial.println("Data sent to ThingSpeak");
    } 
    else 
    {
      Serial.println("Error in ThingSpeak communication");
    }
    http.end();
  } 
  else 
  {
    Serial.println("WiFi Disconnected");
  }

  delay(5000); // Adjust for ThingSpeak upload rate
}