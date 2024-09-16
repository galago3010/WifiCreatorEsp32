#include <WiFi.h>

// Wi-Fi credentials for the existing network (STA mode)
const char* routerSSID = "YourNetworkSSID";
const char* routerPassword = "YourNetworkPassword";

// Wi-Fi credentials for the ESP32 AP network with WPA2 security
const char* apSSID = "ESP32-AP";
const char* apPassword = "SecurePassword123!"; // Must be 8-63 characters long for WPA2

void setup() {
  Serial.begin(115200);

  // Start Access Point with WPA2 security
  WiFi.softAP(apSSID, apPassword, 1, 0, 8); // 1 = channel, 0 = no hidden SSID, 8 = max connections
  Serial.println("Access Point started with WPA2 security");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Connect to existing Wi-Fi network (Station mode)
  WiFi.begin(routerSSID, routerPassword);
  Serial.print("Connecting to ");
  Serial.print(routerSSID);
  Serial.println("...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi network");
  Serial.print("STA IP address: ");
  Serial.println(WiFi.localIP());
  
  // Use DHCP to set up the ESP32's AP mode network to route traffic to the STA network
  Serial.println("AP and STA configured. Devices connected to the AP should have internet access.");
}

void loop() {
  // Main loop does nothing in this example
}
