#include <WiFi.h>

const char* routerSSID = "YourNetworkSSID";
const char* routerPassword = "YourNetworkPassword";

const char* apSSID = "ESP32-AP";
const char* apPassword = "SecurePassword123!";

const int buttonPin = 0; // Adjust this pin number based on your setup
bool apEnabled = false; // Track the state of the Access Point

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP); // Configure button pin as input with pull-up resistor

  // Initially, make sure the AP is off
  WiFi.softAPdisconnect(true);
  Serial.println("Waiting for button press to toggle AP...");
}

void loop() {
  static bool lastButtonState = HIGH; // Last button state
  bool currentButtonState = digitalRead(buttonPin);

  // Check if the button state has changed
  if (currentButtonState != lastButtonState) {
    if (currentButtonState == LOW) { // Button is pressed
      if (!apEnabled) {
        // Start Access Point with WPA2 security
        WiFi.softAP(apSSID, apPassword, 1, 0, 8);
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

        Serial.println("AP and STA configured. Devices connected to the AP should have internet access.");
        apEnabled = true;
      }
    } else { // Button is not pressed
      if (apEnabled) {
        // Stop Access Point
        WiFi.softAPdisconnect(true);
        Serial.println("Access Point stopped.");
        
        // Disconnect from the existing Wi-Fi network
        WiFi.disconnect(true);
        Serial.println("Disconnected from Wi-Fi network.");
        
        apEnabled = false;
      }
    }
  }

  lastButtonState = currentButtonState; // Update last button state
  delay(100); // Debounce delay
}
