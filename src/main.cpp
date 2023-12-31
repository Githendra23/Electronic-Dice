#include <Arduino.h>

uint8_t firstLedPin = 0;
uint8_t lastLedPin = 3;
uint8_t switchPin = 4;
uint8_t ledPin;
uint8_t number;

void setup() {
  initPins();
  initRandomSerie();
  //Serial.begin(9600);
}

void loop() {
  if(isSequenceTriggered() == 1) {
    displayDiceFace(transcodeNumber(number));
    number = generateNewFaceNumber();
    delay(1000);
  }
}

void initPins() {
  for(ledPin = firstLedPin; ledPin <= lastLedPin; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
}

byte transcodeNumber(uint8_t diceFace) {
  switch(diceFace) {
    case 1: return (0b1000);
    case 2: return (0b0001);
    case 3: return (0b1001);
    case 4: return (0b0101);
    case 5: return (0b1101);
    case 6: return (0b0111);
  }
}

void displayDiceFace(byte pinByte) {
  for(ledPin = 0; ledPin <= 3; ledPin++) {
    digitalWrite(ledPin, bitRead(pinByte, ledPin));
  }
}

void initRandomSerie() {
  number = random(1, 7);

}

int generateNewFaceNumber() {
  static int previousDisplayedNumber = number;
  number = random(1, 7);
  while(true) {
    if(number == previousDisplayedNumber) {
      return random(1, 7);
    }
    else return number;
  }
}

bool isSequenceTriggered() {
  static int previousSwitchLevel = LOW;
  static int currentSwitchLevel = LOW;

  previousSwitchLevel = currentSwitchLevel;
  currentSwitchLevel = digitalRead(switchPin);

  if(previousSwitchLevel == LOW && currentSwitchLevel == HIGH) {
    return 1;
  }
  else return 0;
}