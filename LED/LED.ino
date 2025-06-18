#include <dummy.h>

#define LED_PIN D1 // GPIO5

String inputString = "";
bool stringComplete = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start OFF
  Serial.begin(115200);       // ESP8266 default baud rate
  Serial.println("Type ON or OFF to control the LED/Relay");
}

void loop() {
  if (stringComplete) {
    inputString.trim(); // Remove whitespace

    if (inputString.equalsIgnoreCase("ON")) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED is ON");
    } else if (inputString.equalsIgnoreCase("OFF")) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED is OFF");
    } else {
      Serial.println("Invalid command. Type ON or OFF.");
    }

    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
