# 3. Hardware Wiring Diagram

This section details how to connect the sensors and peripherals to the ESP32 board.

## Component Connections
| Component                  | ESP32 Pin Name | Pin Type       | Purpose (Defined in RockShield_AI.ino)                            |
| :---                       | :---           | :---           | :---                                                              |
| **DHT11/DHT22 Data Pin**   | D2             | Digital I/O    | [cite_start]Temperature & Humidity Sensor (`DHTPIN`) [cite: 1]    |
| **Soil Moisture Data Pin** | D34            | Analog Input   | [cite_start]Raw soil water content (`SOIL_PIN`) [cite: 1]         |
| **Vibration Digital Out**  | D27            | Digital Input  | [cite_start]Ground movement detection (`VIBRATION_PIN`) [cite: 1] |
| **Buzzer Signal Pin**      | D25            | Digital Output | [cite_start]Local landslide alert (`BUZZER_PIN`) [cite: 1]        |

**Note:** Ensure all sensors have proper power (VCC) and ground (GND) connections. [cite_start]The soil moisture sensor reading requires an **Analog-to-Digital Converter (ADC)** pin, which is D34 on the ESP32[cite: 1].