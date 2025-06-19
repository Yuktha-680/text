// ==== main.ino ====
int IR_PIN = D2;
int LED_PIN = D4;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  pinMode(IR_PIN,INPUT);
}

void loop() {
  int data = digitalRead(IR_PIN);
  if(data == 0){
    digitalWrite(LED_PIN,LOW);
  }
  else{
    digitalWrite(LED_PIN,HIGH);
  }
  delay(500);
}
