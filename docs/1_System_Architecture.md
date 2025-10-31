# 1. System Architecture Overview

The RockShield AI system is an end-to-end IoT solution for landslide risk prediction.

## Workflow

1.  [cite_start]**Data Acquisition (ESP32):** The ESP32 collects real-time data from onboard sensors (Temperature, Soil Moisture, Vibration, Humidity) every 15 seconds[cite: 2, 3].
2.  [cite_start]**ML Inference (Cloud API):** The ESP32 sends a JSON payload of critical sensor readings to the **ML Server** (`mlServer`) via HTTP POST[cite: 20].
3.  [cite_start]**Risk Prediction & Alert:** The ML Server runs the Random Forest model and returns a prediction (e.g., "High Risk," "Landslide Event") and associated probabilities[cite: 25]. [cite_start]If the risk is high (Landslide Event probability > 0.8), the ESP32 triggers a local buzzer alarm[cite: 27].
4.  [cite_start]**Data Logging (ThingSpeak):** The ESP32 sends the raw sensor data to the **ThingSpeak** IoT platform for storage and visualization[cite: 31, 32].

## Components
* **Edge Device:** ESP32 running `RockShield_AI.ino`.
* **ML Endpoint:** Hosted server running the Random Forest classifier (e.g., Django REST API).
* **IoT Platform:** ThingSpeak for real-time data logging and charting.