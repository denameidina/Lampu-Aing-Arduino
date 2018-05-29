#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "lampu-aing.firebaseio.com"
#define FIREBASE_AUTH "TDhwAGzKGCkJcwcBIqZV7SuGc5VmAmRBRpWfj6zR"
#define WIFI_SSID "bagoy hotspot"
#define WIFI_PASSWORD "galonasli69"

#define RELAY 2 // sama dengan pin D4

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //  Firebase.set("STATUS_LAMPU", 0);
}

int status_lampu = 0;

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
  }

  // set value
  status_lampu = Firebase.getInt("STATUS_LAMPU");
  if (status_lampu == 1) {
    //    Serial.println("OFF");
    digitalWrite(RELAY, HIGH);
  } else if (status_lampu == 2) {
    //    Serial.println("ON");
    digitalWrite(RELAY, LOW);
  }
  delay(200);
}
