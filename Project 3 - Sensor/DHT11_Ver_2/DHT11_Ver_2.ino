#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4 // Pin data DHT11 (ubah sesuai wiring)
#define DHTTYPE DHT11 // Jenis sensor

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "NALA"; // Ganti dengan SSID WiFi kamu
const char* password = "TORAJATA"; // Ganti dengan password WiFi kamu

WebServer server(80);

void handleRoot() {
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
server.send(200, "text/html", "<h1>Gagal membaca sensor DHT11!</h1>");
return;
}

String html = "<!DOCTYPE html><html>";
html += "<head><meta http-equiv='refresh' content='3'/>"; // auto refresh tiap 3 detik
html += "<title>Monitoring Suhu & Kelembaban</title></head>";
html += "<body style='font-family: Arial; text-align:center;'>";
html += "<h1>ESP32 Monitoring Suhu & Kelembaban</h1>";
html += "<p><b>Suhu: </b>" + String(t) + " &deg;C</p>";
html += "<p><b>Kelembaban: </b>" + String(h) + " %</p>";
html += "</body></html>";

server.send(200, "text/html", html);
}

void setup() {
Serial.begin(115200);
dht.begin();

WiFi.begin(ssid, password);
Serial.print("Menghubungkan ke WiFi");
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nWiFi Terhubung!");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());

server.on("/", handleRoot);
server.begin();
Serial.println("Web server berjalan...");
}

void loop() {
server.handleClient();
}