const int trigLeft = D1;
const int echoLeft = D2;

const int trigRight = D5;
const int echoRight = D6;

const int threshold = 10;

void setup() {
  Serial.begin(9600);

  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
}

void loop() {
  long distanceLeft = getDistanceCM(trigLeft, echoLeft);
  long distanceRight = getDistanceCM(trigRight, echoRight);

  Serial.print("Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" cm | Right Distance: ");
  Serial.print(distanceRight);
  Serial.println(" cm");


  if (distanceLeft < threshold) {
    Serial.println("⚠️ Obstacle on the LEFT!");
  }
  if (distanceRight < threshold) {
    Serial.println("⚠️ Obstacle on the RIGHT!");
  }

  delay(1000);
}

long getDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}
