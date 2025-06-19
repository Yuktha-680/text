int IR_PIN = D2; 
int LED_PIN = D4;

bool ledState = false;
unsigned long gestureStart = 0;
bool gestureInProgress = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int irData = digitalRead(IR_PIN);

  // Object appears
  if (irData == 0 && !gestureInProgress) {
    gestureInProgress = true;
    gestureStart = millis();  // Start timing
    Serial.println("Object detected...");
  }

  // Object disappears
  if (irData == 1 && gestureInProgress) {
    unsigned long gestureDuration = millis() - gestureStart;
    gestureInProgress = false;

    if (gestureDuration < 800) { // Adjust sensitivity here
      Serial.println("Gesture detected!");
      ledState = !ledState;  // Toggle LED
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    } else {
      Serial.println("Too slow — not a gesture.");
    }
  }

  delay(50); // Small delay for stability
}

