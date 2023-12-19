//receiver

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#define NSS 2
#define RST 13
#define DI0 12

const int ledPin = 2; // Pin LED internal ESP32

void setup(){
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  LoRa.setPins(NSS, RST, DI0);

  while (!LoRa.begin(433E6)){
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Initializing Successful!");
}

void loop(){
  int packetSize = LoRa.parsePacket();

  if (packetSize){
    String stringData = "";
    String led, pot, text;
    String newtext = " ";
    while (LoRa.available()){
      char receivedChar = (char)LoRa.read();
      stringData += receivedChar;
    }

    int pos1 = stringData.indexOf('#');

    if (pos1 != -1){
      String num1 = stringData.substring(0, pos1);
      if (!num1.isEmpty()){
        led = num1;
      }
      int pos2 = stringData.indexOf('#', pos1 + 1);

      if (pos2 != -1){
        String num2 = stringData.substring(pos1 + 1, pos2);
        pot = num2;

        String str = stringData.substring(pos2 + 1);
        text = str;

        Serial.print("Les Status: ");
        Serial.println(led);
        Serial.print("Potentio: ");
        Serial.println(pot);
        Serial.print("String: ");
        Serial.println(text);

        if (led == "0"){
          digitalWrite(ledPin, LOW);
        }
        else if (led == "1"){
          digitalWrite(ledPin, HIGH);
        }
      }
      else{
        Serial.println("Second '#' not found");
      }
    }
    else{
      Serial.println("First '#' not found");
    }

    delay(10);
  }
}