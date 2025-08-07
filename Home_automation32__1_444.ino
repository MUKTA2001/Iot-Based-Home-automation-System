#define BLYNK_TEMPLATE_ID "TMPL68Jbuv9mi"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "_sKnut_jC4t2YYpRTpvsomfDkG3WXJB-"

// Enable Serial Monitor debug output
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk Auth Token
char auth[] = "_sKnut_jC4t2YYpRTpvsomfDkG3WXJB-";

// WiFi credentials
char ssid[] = "realme 8";         // Replace with your WiFi SSID
char pass[] = "trishita3838#";     // Replace with your WiFi password

// Timer object
BlynkTimer timer;

// GPIO pins for buttons
#define button1_pin 26
#define button2_pin 25
#define button3_pin 33
#define button4_pin 32

// GPIO pins for relays
#define relay1_pin 13
#define relay2_pin 12
#define relay3_pin 14
#define relay4_pin 27

// Relay states
int relay1_state = 0;
int relay2_state = 0;
int relay3_state = 0;
int relay4_state = 0;

// Virtual pins for Blynk
#define button1_vpin    V1
#define button2_vpin    V2
#define button3_vpin    V3
#define button4_vpin    V4

// Sync state on Blynk connection
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  Blynk.syncVirtual(button2_vpin);
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button4_vpin);
}

// Virtual button press from Blynk app
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}

BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}

BLYNK_WRITE(button3_vpin) {
  relay3_state = param.asInt();
  digitalWrite(relay3_pin, relay3_state);
}

BLYNK_WRITE(button4_vpin) {
  relay4_state = param.asInt();
  digitalWrite(relay4_pin, relay4_state);
}

void setup() {
  // Debug monitor
  Serial.begin(115200);

  // Set button pins as INPUT_PULLUP
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(button3_pin, INPUT_PULLUP);
  pinMode(button4_pin, INPUT_PULLUP);

  // Set relay pins as OUTPUT
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay4_pin, OUTPUT);

  // Initialize relays to OFF (HIGH = relay off for active LOW modules)
  digitalWrite(relay1_pin, HIGH);
  digitalWrite(relay2_pin, HIGH);
  digitalWrite(relay3_pin, HIGH);
  digitalWrite(relay4_pin, HIGH);

  // Connect to WiFi and Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
  listen_push_buttons(); // Listen for physical button presses
}

// Listen for button presses and toggle corresponding relay
void listen_push_buttons() {
  if (digitalRead(button1_pin) == LOW) {
    delay(200); // Debounce
    control_relay(1);
    Blynk.virtualWrite(button1_vpin, relay1_state);
  } else if (digitalRead(button2_pin) == LOW) {
    delay(200);
    control_relay(2);
    Blynk.virtualWrite(button2_vpin, relay2_state);
  } else if (digitalRead(button3_pin) == LOW) {
    delay(200);
    control_relay(3);
    Blynk.virtualWrite(button3_vpin, relay3_state);
  } else if (digitalRead(button4_pin) == LOW) {
    delay(200);
    control_relay(4);
    Blynk.virtualWrite(button4_vpin, relay4_state);
  }
}

// Function to toggle relay state
void control_relay(int relay) {
  switch (relay) {
    case 1:
      relay1_state = !relay1_state;
      digitalWrite(relay1_pin, relay1_state);
      Serial.print("Relay 1 State: "); Serial.println(relay1_state);
      break;
    case 2:
      relay2_state = !relay2_state;
      digitalWrite(relay2_pin, relay2_state);
      Serial.print("Relay 2 State: "); Serial.println(relay2_state);
      break;
    case 3:
      relay3_state = !relay3_state;
      digitalWrite(relay3_pin, relay3_state);
      Serial.print("Relay 3 State: "); Serial.println(relay3_state);
      break;
    case 4:
      relay4_state = !relay4_state;
      digitalWrite(relay4_pin, relay4_state);
      Serial.print("Relay 4 State: "); Serial.println(relay4_state);
      break;
  }
}