#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Your_WiFi";
const char* password = "Your_Password";

String apiKey = "5PX4PPTELVU5EHJY
";
const char* server = "api.thingspeak.com";

int ledPin = 5;

// Use ESP32 Hardware Serial 2 for HC-05
HardwareSerial BT(2);  // UART2

void setup() {
  Serial.begin(115200);
  BT.begin(9600, SERIAL_8N1, 16, 17); // RX, TX

  pinMode(ledPin, OUTPUT);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  WiFiClient client;

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=" + String(t);
    postStr += "&field2=" + String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();

  // Bluetooth control
  if (BT.available()) {
    char c = BT.read();

    if (c == '1') {
      digitalWrite(ledPin, HIGH);
      BT.println("LED ON");
    }
    if (c == '0') {
      digitalWrite(ledPin, LOW);
      BT.println("LED OFF");
    }
  }

  delay(15000);  // ThingSpeak update interval
}
