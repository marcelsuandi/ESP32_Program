const int touchPin = 4;      // Touch sensor
const int irPin = 17;        // IR sensor
const int ledPin = 16;       // LED

int touchValue;
int irState;

void setup() {

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
}

void loop() {

  touchValue = touchRead(touchPin);
  irState = digitalRead(irPin);

  Serial.print("Touch Value: ");
  Serial.print(touchValue);
  Serial.print(" | IR State: ");
  Serial.println(irState);

  if (touchValue < 800 || irState == LOW) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  delay(2);
}