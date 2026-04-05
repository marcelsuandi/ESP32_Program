const int touchPin = 4;
const int irPin = 17;
const int ldrPin = 34;   // AO (Analog)
const int ledPin = 16;

int touchValue;
int irState;
int ldrValue;

// threshold cahaya (atur sesuai kondisi)
int ldrThreshold = 1500;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
}

void loop() {

  touchValue = touchRead(touchPin);
  irState = digitalRead(irPin);
  ldrValue = analogRead(ldrPin);

  Serial.print("Touch: ");
  Serial.print(touchValue);
  Serial.print(" | IR: ");
  Serial.print(irState);
  Serial.print(" | LDR: ");
  Serial.println(ldrValue);

  // logika: sentuh ATAU objek ATAU gelap
  if (touchValue < 800 || irState == LOW || ldrValue > ldrThreshold) {
    digitalWrite(ledPin, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW);
  }

  delay(2);
}