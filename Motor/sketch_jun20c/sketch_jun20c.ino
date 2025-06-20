#include <DHT.h>

#define DHTPIN 2          // GPIO2 (D4)
#define DHTTYPE DHT11
#define SOIL_PIN A0       // Analog pin
#define RELAY_PIN 5       // GPIO5 (D1)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Pump OFF
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  float temp = dht.readTemperature();
  int soilRaw = analogRead(SOIL_PIN);

  // Convert raw value to percentage (wet = 100%, dry = 0%)
  int soilPercent = map(soilRaw, 644, 343, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100); // Clamp between 0–100%

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Soil Moisture: ");
  Serial.print(soilPercent);
  Serial.println(" %");

  // Trigger pump if soil moisture < 30% or temperature > 36°C
  if (soilPercent < 30 || temp > 36) {
    digitalWrite(RELAY_PIN, LOW); // Pump ON
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Pump OFF
  }

  delay(2000);
}