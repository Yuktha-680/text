const int soilMoisturePin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(soilMoisturePin);

  // Map the raw value (dry: 1023, wet: 0) to percentage
  int moisturePercent = map(rawValue, 1023, 0, 0, 100);  // Reverse scale

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println(" %");

  delay(1000);
}