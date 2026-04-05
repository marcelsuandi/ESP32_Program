#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// BMP280
Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(115200);

  // Inisialisasi I2C
  Wire.begin(21, 22);

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal ditemukan");
    while (1);
  }

  // Inisialisasi BMP280
  if (!bmp.begin(0x76)) {  
    Serial.println("BMP280 tidak ditemukan!");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // hPa

  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Tekanan: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Monitoring BMP280");

  display.setTextSize(2);
  display.setCursor(0,20);
  display.print(temperature);
  display.println(" C");

  display.setTextSize(1);
  display.setCursor(0,50);
  display.print("Pressure: ");
  display.print(pressure);
  display.println(" hPa");

  display.display();

  delay(2000);
}