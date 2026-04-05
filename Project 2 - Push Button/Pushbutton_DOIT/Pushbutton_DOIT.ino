const int button1Pin = 4;   // push button 1
const int button2Pin = 15;  // push button 2

const int ledPin = 5;       // LED biasa

// RGB LED
const int redPin = 16;
const int greenPin = 17;
const int bluePin = 18;

// variabel button
int button1State = 0;
int button2State = 0;

int lastButton2State = 0;
int pressCount = 0;

void setup() {

  Serial.begin(115200);

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(ledPin, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {

  // =========================
  // PUSH BUTTON 1 (LED biasa)
  // =========================

  button1State = digitalRead(button1Pin);

  if (button1State == HIGH) {
    digitalWrite(ledPin, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW);
  }

  // =========================
  // PUSH BUTTON 2 (LED RGB)
  // =========================

  button2State = digitalRead(button2Pin);

  if (button2State == HIGH && lastButton2State == LOW) {

    pressCount++;
    delay(200); // debounce sederhana

    if (pressCount > 3) {
      pressCount = 0;
    }

    Serial.print("RGB Mode: ");
    Serial.println(pressCount);
  }

  lastButton2State = button2State;

  if (pressCount == 1) {

    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);

  }

  else if (pressCount == 2) {

    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);

  }

  else if (pressCount == 3) {

    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);

  }

  else {

    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);

  }

}