class UltrasonicSensor {
  private:
    int trigPin;
    int echoPin;

  public:
    UltrasonicSensor(int trig, int echo) {
      trigPin = trig;
      echoPin = echo;
    }

    void begin() {
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    long getDistanceCM() {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      long duration = pulseIn(echoPin, HIGH);
      return duration * 0.034 / 2;
    }
};

// Create an instance
UltrasonicSensor distanceSensor(D5, D6);  // Use actual pin numbers

void setup() {
  Serial.begin(9600);
  distanceSensor.begin();  // Initialize pins
}

void loop() {
  long distance = distanceSensor.getDistanceCM();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}