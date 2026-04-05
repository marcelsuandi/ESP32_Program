// the number of LED pin
const int ledPin = 16; // 16 coressponds to GPIO16

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
  // configure LED PWM functionalitties
  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    // changing the LED brigthness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brigthness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }
}
