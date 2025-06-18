#include <DHT.h>
#include <ESP8266WiFi.h>

#define DHTPIN D4         // DHT11 data pin connected to GPIO2 (D4 on NodeMCU)
#define DHTTYPE DHT11     // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(2000);  // Sensor reading delay

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Temperature in Celsius

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
}
