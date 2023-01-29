#define BLYNK_TEMPLATE_ID "TMPL3qL6DkZt"
#define BLYNK_DEVICE_NAME "coal mining"
//#define BLYNK_AUTH_TOKEN "t2bAh9AZ1yu2NLTcLZaczC7xL9kW7zw_"
//
//char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "Funking7";
//char pass[] = "12345678";

#define DHTTYPE DHT11
#define methane A0
#define rain 4
#define buzz 15

int a,b;

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG

#include "DHT.h"
#include "BlynkEdgent.h"

//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

DHT dht(5, DHTTYPE);

void setup() {
  Serial.begin(9600);
  BlynkEdgent.begin();
  dht.begin();
  
  pinMode(methane,INPUT);
  pinMode(rain,INPUT);
  pinMode(buzz,OUTPUT);
  Serial.println(F("DHTxx test!"));
}

void loop() {
  delay(2000);
  BlynkEdgent.run();
//  Blynk.run();

  sens();
if (b<1 || a>250){
  digitalWrite(buzz,HIGH);
  delay(1000);
  digitalWrite(buzz,LOW);
  delay(1000);
}
}

void sens(){
  a = analogRead(methane);
  b = digitalRead(rain);
  
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%     Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C    "));
//  Serial.print(f);
//  Serial.print(F("°F         "));
//  Serial.print("metane level:  ");
//  Serial.print(a);
//  Serial.print("    Rain state  ");
//  Serial.println(b);

Blynk.virtualWrite(V0,h);
Blynk.virtualWrite(V1,t);
Blynk.virtualWrite(V2,a);
Blynk.virtualWrite(V3,b);
delay(500);

if (t>35){
  digitalWrite(buzz,HIGH);
  delay(1000);
  digitalWrite(buzz,LOW);
  delay(3000);
  }
}
