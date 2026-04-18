#include <WiFi.h>
#include <DHT.h>

const char* ssid = "NALA";
const char* password = "TORAJATA";

WiFiServer server(80);

// LED
int led1 = 4;
int led2 = 16;

// DHT11
#define DHTPIN 17   
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float temperature;
float humidity;

String header;

bool led1State = false;
bool led2State = false;

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  dht.begin();

  Serial.println("\n==============================");
  Serial.println("ESP32 WiFi Connection");
  Serial.println("==============================");

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;

    if (counter > 20) {
      Serial.println("\n❌ Gagal connect! Cek WiFi");
      return;
    }
  }

  Serial.println("\n\n✅ WiFi Connected!");
  Serial.println("------------------------------");

  Serial.print("📡 SSID      : ");
  Serial.println(ssid);

  Serial.print("🌐 IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("📶 RSSI      : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  Serial.println("==============================\n");

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String currentLine = "";
    header = "";

    // 🔥 Baca DHT setiap ada request
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {

            // Kontrol LED
            if (header.indexOf("GET /4/on") >= 0) {
              led1State = true;
              digitalWrite(led1, HIGH);
            } 
            else if (header.indexOf("GET /4/off") >= 0) {
              led1State = false;
              digitalWrite(led1, LOW);
            }

            if (header.indexOf("GET /16/on") >= 0) {
              led2State = true;
              digitalWrite(led2, HIGH);
            } 
            else if (header.indexOf("GET /16/off") >= 0) {
              led2State = false;
              digitalWrite(led2, LOW);
            }

            // HANDLE ERROR SENSOR
            String tempStr = isnan(temperature) ? "Error" : String(temperature) + " °C";
            String humStr  = isnan(humidity) ? "Error" : String(humidity) + " %";

            // HTML
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");

            client.println("<style>");
            client.println("body { font-family: Arial; text-align: center; background: #f2f2f2; }");
            client.println(".card { background: white; padding: 20px; margin: 20px auto; width: 260px; border-radius: 15px; box-shadow: 0 4px 10px rgba(0,0,0,0.2);} ");
            client.println(".btn { padding: 12px 25px; font-size: 16px; margin: 5px; border: none; border-radius: 8px; color: white; cursor: pointer; }");
            client.println(".on { background-color: #4CAF50; }");
            client.println(".off { background-color: #f44336; }");
            client.println("</style>");
            client.println("</head>");

            client.println("<body>");
            client.println("<h2>ESP32 Web Server</h2>");

            // 🌡️ CARD SENSOR
            client.println("<div class=\"card\">");
            client.println("<h3>Sensor DHT11</h3>");
            client.println("<p>Suhu: " + tempStr + "</p>");
            client.println("<p>Kelembaban: " + humStr + "</p>");
            client.println("</div>");

            // 💡 LED 1
            client.println("<div class=\"card\">");
            client.println("<h3>GPIO 4</h3>");
            client.println("<p>Status: " + String(led1State ? "ON" : "OFF") + "</p>");
            client.println("<a href=\"/4/on\"><button class=\"btn on\">ON</button></a>");
            client.println("<a href=\"/4/off\"><button class=\"btn off\">OFF</button></a>");
            client.println("</div>");

            // 💡 LED 2
            client.println("<div class=\"card\">");
            client.println("<h3>GPIO 16</h3>");
            client.println("<p>Status: " + String(led2State ? "ON" : "OFF") + "</p>");
            client.println("<a href=\"/16/on\"><button class=\"btn on\">ON</button></a>");
            client.println("<a href=\"/16/off\"><button class=\"btn off\">OFF</button></a>");
            client.println("</div>");

            client.println("</body></html>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
}