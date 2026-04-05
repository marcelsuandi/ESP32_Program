const int touchPin = 4;
const int irPin = 17;
const int ldrPin = 18;   // DO
const int ledPin = 16;

int touchValue;
int irState;
int ldrState;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {

  touchValue = touchRead(touchPin);
  irState = digitalRead(irPin);
  ldrState = digitalRead(ldrPin);

  Serial.print("Touch: ");
  Serial.print(touchValue);
  Serial.print(" | IR: ");
  Serial.print(irState);
  Serial.print(" | LDR: ");
  Serial.println(ldrState);

  // asumsi: LOW = aktif (gelap / ada objek)
  if (touchValue < 800 || irState == LOW || ldrState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW);
  }

  delay(20);
}