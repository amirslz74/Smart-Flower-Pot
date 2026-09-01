# Firmware Guide

The Arduino firmware serves a SPIFFS dashboard, reads a DHT11 on GPIO 32, and controls relays on GPIO 14 and GPIO 4.

## Setup

Install the ESP32 Arduino core, DHT library, ESPAsyncWebServer, its asynchronous TCP dependency, and a compatible SPIFFS uploader. Copy `secrets.example.h` to `secrets.h` and replace the example values:

```cpp
#pragma once
#define WIFI_SSID "your-network-name"
#define WIFI_PASSWORD "your-network-password"
```

Adjust the static IP, gateway, DNS, NTP offset, sensor type, and GPIO assignments. Upload `data/` to SPIFFS, flash `SmartFlowerPot.ino`, then open the serial monitor at 115200 baud.

## Limitations

- Relay endpoints have no authentication.
- Network settings are installation-specific.
- Automatic irrigation policy is not implemented.
- Relay startup state should be made explicit for the connected loads.

Do not expose the server directly to the internet; use a trusted, isolated IoT network.
