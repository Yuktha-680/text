#include <ESP8266WiFi.h>

// Wi-Fi credentials
const char* ssid = "Mayathilokke venam ketto";
const char* password = "********";

// Create a server on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  Serial.println();
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connected
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // listen for incoming clients

  if (client) {
    Serial.println("New Client connected.");
    String request = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\n') {
          // End of HTTP request header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html><head><title>NodeMCU</title></head><body>");
          client.println("<h1>Hello, World</h1>");
          client.println("</body></html>");
          break;
        }
      }
    }

    // Give the web browser time to receive the data
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
