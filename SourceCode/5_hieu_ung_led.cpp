#include <Arduino.h>
#include <stdio.h>
#define NUM_LED 12
int ledPins[] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, A4};
const int buttonPin = A5;
const int buzzerPin = A0;

int currentEffect = 0;
int previousButtonState = LOW;
unsigned long previousMillis = 0;
const long interval = 300;
uint8_t  indexStart = 0;
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}
uint16_t ledStates_1[] = {
0x0555,
0x0AAA,
};
uint16_t ledStates_2[] = {
 0x0000,
 0x0001,
0x0003,
0x0007,
0x000F,
0x001F,
0x003F,
0x007F,
0x00FF,
0x01FF,
0x03FF,
0x07FF,
0x0FFF,
0x0FFE,
0x0FFC,
0x0FF8,
0x0FF0,
0x0FE0,
0x0FC0,
0x0F80,
0x0F00,
0x0E00,
0x0C00,
0x0800,
0x0000,
};
uint16_t ledStates_3[] = {
 0x0000,
0x0001,
0x0000,
0x0002,
0x0000,
0x0004,
0x0000,
0x0008,
0x0000,
0x0010,
0x0000,
0x0020,
0x0000,
0x0040,
0x0000,
0x0080,
0x0000,
0x0100,
0x0000,
0x0200,
0x0000,
0x0400,
0x0000,
0x0800,
0x0000,

};
uint16_t ledStates_4[] = {
0x003F,
0x0FC0,
};

uint16_t ledStates_5[] = {
0x0249,
0x0492,
0x0924,
};
void displayLed(uint16_t data)
{
    for (int j = 0; j < NUM_LED; j++) 
    {
      int ledState = (data >> j) & 0x01; 
      digitalWrite(ledPins[(NUM_LED - 1) -j], ledState);
    }
}

void EffectLed(uint16_t * dataInput, uint16_t size, uint16_t delayTime)
{
    unsigned static long getTime = millis();
  if(millis() - getTime > delayTime)
   {
      if(indexStart >= size)
      {
        indexStart = 0;
      }
      displayLed(dataInput[indexStart]);
      Serial.print(dataInput[indexStart]);
      indexStart++;
      getTime = millis();
   }   
}

void effect1() {
 EffectLed(ledStates_1 , sizeof(ledStates_1)/ sizeof(ledStates_1[0]),100);
}

void effect2() {
   EffectLed(ledStates_2 , sizeof(ledStates_2)/ sizeof(ledStates_2[0]),50);
}

void effect3() {
EffectLed(ledStates_3 , sizeof(ledStates_3)/ sizeof(ledStates_3[0]),50); 
}

void effect4() {
  EffectLed(ledStates_4 , sizeof(ledStates_4)/ sizeof(ledStates_4[0]),100); 
  }

void effect5() {
   EffectLed(ledStates_5 , sizeof(ledStates_5)/ sizeof(ledStates_5[0]),100); 
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState != previousButtonState) {
    if (buttonState == LOW) {
      currentEffect = (currentEffect + 1) % 5;
      indexStart = 0;
      tone(buzzerPin,1000*(currentEffect*2+ 2));
    }
    delay(50); // Debounce
    noTone(buzzerPin);
  }
  previousButtonState = buttonState;
    switch (currentEffect) {
    case 0:
     // Serial.print("Start 1 \r\n");
      effect1();
      break;
    case 1:
      effect2();
      break;
    case 2:
      effect3();
      break;
    case 3:
      effect4();
      break;
    case 4:
      effect5();
      break;
}

}