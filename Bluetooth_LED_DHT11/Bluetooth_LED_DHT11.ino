#include "BluetoothSerial.h"
#include "DHT.h"

BluetoothSerial SerialBT;

#define DHTPIN 4
#define DHTTYPE DHT11
#define LED_PIN 16

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_DHT_LED");

  pinMode(LED_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  // Baca data sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Kirim data ke Bluetooth
  SerialBT.print("Temp: ");
  SerialBT.print(temp);
  SerialBT.print(" C | Humidity: ");
  SerialBT.print(hum);
  SerialBT.println(" %");

  // Kontrol LED dari Bluetooth
  if (SerialBT.available()) {
    char data = SerialBT.read();

    if (data == '1') {
      digitalWrite(LED_PIN, HIGH);
    } else if (data == '0') {
      digitalWrite(LED_PIN, LOW);
    }
  }

  delay(2000);
}