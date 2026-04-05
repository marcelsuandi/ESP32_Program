#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED tidak ditemukan");
    for(;;);
  }
}

void loop() {
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 10);
  display.println("Monitoring Udara");

  display.setCursor(0, 30);
  display.print("Suhu: ");
  display.print(suhu);
  display.println(" C");

  display.setCursor(0, 45);
  display.print("Hum : ");
  display.print(kelembaban);
  display.println(" %");

  display.display();

  delay(2000);
}