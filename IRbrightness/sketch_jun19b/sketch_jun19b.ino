int IR_PIN = D2;
int LED_PIN = D4;

unsigned long gestureStart = 0;
bool gestureInProgress = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
}

void loop() {
  int irData = digitalRead(IR_PIN);

  if (irData == 0) { // Object detected
    if (!gestureInProgress) {
      gestureStart = millis();
      gestureInProgress = true;
      Serial.println("Object detected...");
    }

    // Calculate how long object has been present
    unsigned long duration = millis() - gestureStart;

    // Map duration to PWM range (0–255), maxing out at 5 seconds (5000 ms)
    int brightness = map(min(duration, 5000UL), 0, 5000, 0, 255);

    analogWrite(LED_PIN, brightness);
    Serial.print("Duration: ");
    Serial.print(duration);
    Serial.print(" ms | Brightness: ");
    Serial.println(brightness);

  } else { // No object
    gestureInProgress = false;
    analogWrite(LED_PIN, 0); // Turn off LED
  }

  delay(50);
}
