#include <WiFi.h>

const char* ssid = "NALA";
const char* password = "TORAJATA";

WiFiServer server(80);

int led1 = 4;
int led2 = 16;

String header;

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String currentLine = "";
    header = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {

            if (header.indexOf("GET /4/on") >= 0) {
              digitalWrite(led1, HIGH);
            } 
            else if (header.indexOf("GET /4/off") >= 0) {
              digitalWrite(led1, LOW);
            }

            if (header.indexOf("GET /16/on") >= 0) {
              digitalWrite(led2, HIGH);
            } 
            else if (header.indexOf("GET /16/off") >= 0) {
              digitalWrite(led2, LOW);
            }

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<html><body>");
            client.println("<h1>ESP32 Web Server</h1>");

            client.println("<p>GPIO 4</p>");
            client.println("<a href=\"/4/on\"><button>ON</button></a>");
            client.println("<a href=\"/4/off\"><button>OFF</button></a>");

            client.println("<p>GPIO 16</p>");
            client.println("<a href=\"/16/on\"><button>ON</button></a>");
            client.println("<a href=\"/16/off\"><button>OFF</button></a>");

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