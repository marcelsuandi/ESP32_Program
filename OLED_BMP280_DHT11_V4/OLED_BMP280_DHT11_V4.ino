#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// BMP280
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);

  dht.begin();

  // OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal");
    while(true);
  }

  // BMP280
  if (!bmp.begin(0x76)) {  
    Serial.println("BMP280 tidak ditemukan!");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {

  float hum = dht.readHumidity();
  float tempDHT = dht.readTemperature();
  float tempBMP = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0; // hPa

  if (isnan(hum) || isnan(tempDHT)) {
    Serial.println("Error baca DHT11");
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("Monitoring Udara");

  display.setCursor(0,12);
  display.print("DHT T: ");
  display.print(tempDHT);
  display.println(" C");

  display.setCursor(0,22);
  display.print("Hum  : ");
  display.print(hum);
  display.println(" %");

  display.setCursor(0,32);
  display.print("BMP T: ");
  display.print(tempBMP);
  display.println(" C");

  display.setCursor(0,42);
  display.print("Press: ");
  display.print(pressure);
  display.println(" hPa");

  display.display();

  delay(2000);
}