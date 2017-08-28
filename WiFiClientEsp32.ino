/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

// #include <ESP8266WiFi.h> // uncomment for Esp8266
// #include <WiFi.h> // uncomment for Esp32

#include <PubSubClient.h>
#include <DHT.h>
#include <Streaming.h>

#define DHTPIN 21    // what digital pin dht11 is connected to
#define DHTTYPE DHT22   // DHT 22

DHT dht(DHTPIN, DHTTYPE);

// configure the following values as neccesary
const char* ssid = "xxx";
const char* password = "xxx";
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* mqtt_topic = "mysensors/esp32/dht22_01";

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(115200);
    delay(10);
    
    dht.begin();

    // We start by connecting to a WiFi network

    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    //WiFi.config(ip, dns, gateway, subnet);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_server, 1883);
}

char tempStr[6];
char humidityStr[6];
char formatted_string[256];

float getTemperature() {
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return -100.0;
  }
  return t;
}

float getHumidity() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read humidity from DHT sensor!");
    return -100.0;
  }
  return h;
}

void publish_sensor_readings(){
    float temperature = getTemperature();
    float humidity = getHumidity();

    // return if reading was invalid
    if (temperature==-100.0){
      return;
    }

    // convert temperature to a string with two digits before the comma and 2 digits for precision
    dtostrf(temperature, 2, 2, tempStr);
    dtostrf(humidity, 2, 2, humidityStr);

    //format string
    snprintf(formatted_string, sizeof(formatted_string), "{\"temperature\":%s,\"humidity\":%s}", tempStr, humidityStr);
    
    // send temperature to the serial console
    Serial << "Sending result: " << formatted_string << endl;
    // send temperature to the MQTT topic
    client.publish(mqtt_topic, formatted_string);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client_2jo3f28", mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 500 ms");
      // Wait 5 seconds before retrying
      delay(500);
    }
  }
}

void loop()
{
    delay(500);
    reconnect();
    publish_sensor_readings();
}

