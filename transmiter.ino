// Transciever

#include <SPI.h>
#include <LoRa.h>

#define NSS 2
#define RST 13
#define DI0 12

const int potPin = 4; // Pin potentiometer

//sended data
String stringData = "Hello, LoRa!";
String ledStatus = "1";

void setup() {
  Serial.begin(115200);

  LoRa.setPins(NSS, RST, DI0);

  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Initializing Successful!");
}

void loop() {
  // Read potentiometer value
  int potValue = analogRead(potPin);

  Serial.print("PotValue:");
  Serial.println(potValue);

  //combine all variable and send into one data
  String data = ledStatus + '#' + String(potValue) + '#' + stringData;
  
  Serial.println(data);

  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();    

  delay(1000); // Delay to avoid sending data too quickly
}
