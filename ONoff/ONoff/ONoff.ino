#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Galaxy M21 2021 Edition7759";          // 🔹 Enter your WiFi name
const char* password = "mzoh2193";  // 🔹 Enter your WiFi password

ESP8266WebServer server(80);   // Create a web server on port 80
bool ledState = false;         // Variable to track LED status

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; }
    button { padding: 10px 20px; font-size: 18px; margin: 10px; }
  </style>
  <script>
    function send(cmd) {
      fetch("/" + cmd).then(() => location.reload());
    }
  </script>
</head>
<body>
  <h1>NodeMCU LED Control</h1>
  <p>Status: <strong>%STATE%</strong></p>
  <button onclick="send('on')">Turn ON</button>
  <button onclick="send('off')">Turn OFF</button>
</body>
</html>
)rawliteral";

String makePage() {
  String page = PAGE;
  page.replace("%STATE%", ledState ? "LED is ON" : "LED is OFF");
  return page;
}

void handleRoot() {
  server.send(200, "text/html", makePage());
}

void handleOn() {
  ledState = true;
  digitalWrite(LED_BUILTIN, LOW);  // ON = LOW
  handleRoot();
}

void handleOff() {
  ledState = false;
  digitalWrite(LED_BUILTIN, HIGH); // OFF = HIGH
  handleRoot();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // Start with LED OFF

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! Visit: http://");
  Serial.println(WiFi.localIP());  // 🔹 This is your web address

  server.on("/", handleRoot);      // Load page
  server.on("/on", handleOn);      // Turn ON
  server.on("/off", handleOff);    // Turn OFF
  server.begin();
}

void loop() {
  server.handleClient();           // Keeps web server running
}