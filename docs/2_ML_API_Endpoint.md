# 2. ML API Endpoint Reference

The ESP32 communicates with the deployed Machine Learning model via a single POST endpoint.

## Endpoint Details
* **URL:** `mlServer` constant in `config.h` (e.g., `http://voidpanel.com/predict/`)
* **Method:** `POST`
* **Content-Type:** `application/json`

## Request Body (Sent by ESP32)
| Key                | Type    | Description                                      |
| :---               | :---    | :---                                             |
| `temperature_C`    | Float   | Air temperature in Celsius.                      |
| `soil_moisture`    | Float   | Raw analog reading from soil moisture sensor.    |
| `vibration_peak_g` | Integer | Digital read from vibration sensor (0 or 1).     |
| `humidity`         | Float   | Air humidity (Optional, but available from DHT). |

## Success Response (200 OK)
The API is expected to return a JSON object with the risk assessment.

```json
{
    "prediction": "High Risk",
    "probabilities": {
        "Stable": 0.1874,
        "High Risk": 0.6624,
        "Landslide Event": 0.1500
    }
}