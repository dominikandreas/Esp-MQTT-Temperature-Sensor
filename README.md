# Esp32MqttTempSensor
Arduino Code to post readings of a DHT22 sensor to a mqtt broker over WiFi using an Esp32

## Prerequisites:
- Esp8266 Arduino for the Board Manager (Arduino IDE): https://github.com/esp8266/Arduino
- MQTT PubSubClient: https://github.com/knolleary/pubsubclient
- DHT Sensor library: https://github.com/adafruit/DHT-sensor-library
- Streaming library for serial console logs: https://github.com/geneReeves/ArduinoStreaming or http://arduiniana.org/Streaming/Streaming5.zip

If you're using a public MQTT broker, modify the client id (needs to be unique)
