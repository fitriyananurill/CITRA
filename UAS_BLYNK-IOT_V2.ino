#define BLYNK_TEMPLATE_ID "TMPL6YpvklLjd"
#define BLYNK_TEMPLATE_NAME "UAS EMBEDDED"
#define BLYNK_AUTH_TOKEN "MYV3bCh0ZtDW16jlzyih_vQpJvL3_QAp"

#include <WiFi.h>
#include <WiFiClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

char ssid[] = "put you wifi name here";
char pass[] = "put you wifi password here";

#define ONE_WIRE_BUS 15
#define RELAY_LAMP 12 // Relay untuk lampu
#define RELAY_FAN 13   // Relay untuk kipas
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define VPIN_TEMP V3 // Virtual pin untuk suhu
#define VPIN_LAMP V1 // Virtual pin untuk kontrol lampu
#define VPIN_FAN V2  // Virtual pin untuk kontrol kipas

void setup() {
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");
  
  sensors.begin();
  pinMode(RELAY_LAMP, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  
  // Awal kondisi relay mati
  digitalWrite(RELAY_LAMP, LOW);
  digitalWrite(RELAY_FAN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  sensors.requestTemperatures();
  
  float tempC = sensors.getTempCByIndex(0);
  if (tempC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperature: ");
    Serial.println(tempC);
    Blynk.virtualWrite(VPIN_TEMP, tempC);
    
    if (tempC < 32.0) {
      // Lampu hidup, kipas mati
      digitalWrite(RELAY_LAMP, LOW);  // Lampu hidup
      digitalWrite(RELAY_FAN, HIGH); // Kipas mati
      Serial.println("Lampu: ON, Kipas: OFF");
      Blynk.virtualWrite(VPIN_LAMP, "ON");
      Blynk.virtualWrite(VPIN_FAN, "OFF");
    } else if (tempC >= 32.0 && tempC <= 35.0) {
      // Semua mati
      digitalWrite(RELAY_LAMP, HIGH); // Lampu mati
      digitalWrite(RELAY_FAN, HIGH);  // Kipas mati
      Serial.println("Lampu: OFF, Kipas: OFF");
      Blynk.virtualWrite(VPIN_LAMP, "OFF");
      Blynk.virtualWrite(VPIN_FAN, "OFF");
    } else if (tempC > 35.0) {
      // Lampu mati, kipas hidup
      digitalWrite(RELAY_LAMP, HIGH); // Lampu mati
      digitalWrite(RELAY_FAN, LOW);  // Kipas hidup
      Serial.println("Lampu: OFF, Kipas: ON");
      Blynk.virtualWrite(VPIN_LAMP, "OFF");
      Blynk.virtualWrite(VPIN_FAN, "ON");
    }
  } else {
    Serial.println("Error: Could not read temperature data");
  }
  
  delay(3000); // Delay 3 detik untuk pembacaan berikutnya
}
