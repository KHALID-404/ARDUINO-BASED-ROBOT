#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Wi-Fi credentials
const char* ssid = "Amirul khokon";
const char* password = "MARIAISL";

// Request URL and Host
const char* host = "bulksmsbd.net";
const int httpsPort = 443;  // HTTPS port

// API endpoint path
String apiPath = "/api/smsapi?api_key=MfN9WKhYONb6U4fPwvTC&type=text&number=01782669241&senderid=8809617618859&message=TestSMS";

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  
  // Set insecure for HTTPS (skip certificate verification)
  client.setInsecure();
}

void loop() {
  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed!");
    return;
  }

  // Construct HTTP GET request
  String request = "GET " + apiPath + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n";

  // Send the request
  client.print(request);
  Serial.println("Request sent. Awaiting response...");

  // Read the response
  while (client.connected() || client.available()) {
    if (client.available()) {
      String response = client.readString();
      Serial.println("Response:");
      Serial.println(response);
      break;
    }
  }

  client.stop();
  Serial.println("Disconnected from server.");
  
  // Wait 30 seconds before sending the next request
  delay(30000);
}
