# Esp32MqttTempSensor
Arduino Code to post readings of a DHT22 sensor to a mqtt broker over WiFi using an Esp32

## Prerequisites:
- Wifi (install using Board Manager of Arduino IDE):
  - For Esp8266: https://github.com/esp8266/Arduino
  - For Esp32: https://github.com/espressif/arduino-esp32
- MQTT PubSubClient: https://github.com/knolleary/pubsubclient
- DHT Sensor library: https://github.com/adafruit/DHT-sensor-library
- Streaming library for serial console logs: https://github.com/geneReeves/ArduinoStreaming or http://arduiniana.org/Streaming/Streaming5.zip

Furthermore, you'll need to edit the sources and adapt the following lines as necessary:
```c
// #include <ESP8266WiFi.h> // uncomment for Esp8266
// #include <WiFi.h> // uncomment for Esp32
```

If you're using a public MQTT broker, modify the client id (needs to be unique)
