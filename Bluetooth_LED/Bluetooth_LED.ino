#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

const int ledPin = 16;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_LED");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char data = SerialBT.read();

    if (data == '1') {
      digitalWrite(ledPin, HIGH);
    } 
    else if (data == '0') {
      digitalWrite(ledPin, LOW);
    }
  }
}