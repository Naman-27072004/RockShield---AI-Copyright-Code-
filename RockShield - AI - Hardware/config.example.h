// config.h
#ifndef CONFIG_H
#define CONFIG_H

// ------------------- WiFi Configuration -------------------
const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

// ------------------- Servers -------------------
const char *mlServer = "YOUR_API_ENDPOINT"; // ML API endpoint
const char *thingSpeakServer = "https://api.thingspeak.com/update";
String apiKey = "YOUR_API_KEY"; // ThingSpeak Write API Key

#endif
