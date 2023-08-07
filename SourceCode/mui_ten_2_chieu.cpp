#include <Arduino.h>
#include <stdio.h>
// Code được tạo từ phần mềm của NTN.ELECTRONIC
// Youtube Channel: https://www.youtube.com/@ntn.electronic0205
// Gmail: ntn.electronic92@gmail.com
// Phone: 0934.026.250
// Khai báo các chân LED

#define NUM_LED 16
int ledPins[] = {12,11,10,9,8,7,6,5,4,3,2,13,A0,A1,A2,A3};
const int buttonPin = A5;

int currentEffect = 0;
int previousButtonState = LOW;
unsigned long previousMillis = 0;
const long interval = 300;
uint8_t  indexStart = 0;

uint16_t ledStates_1[] = {
0x0000,
0x0180,
0x0240,
0x0420,
0x0810,
0x1008,
0x2004,
0x4002,
0x8001,
};
uint16_t ledStates_2[] = {

0x0000,
0x0100,
0x0000,
0x0200,
0x0000,
0x0400,
0x0000,
0x0800,
0x0000,
0x1000,
0x0000,
0x2000,
0x0000,
0x4000,
0x0000,
0x8000,
//////
0x0000,
0x0100,
0x0000,
0x0200,
0x0000,
0x0400,
0x0000,
0x0800,
0x0000,
0x1000,
0x0000,
0x2000,
0x0000,
0x4000,
0x0000,
0x8000,
//////
0x0000,
0x0100,
0x0000,
0x0200,
0x0000,
0x0400,
0x0000,
0x0800,
0x0000,
0x1000,
0x0000,
0x2000,
0x0000,
0x4000,
0x0000,
0x8000,
/////
0x0000,
0x0100,
0x0000,
0x0200,
0x0000,
0x0400,
0x0000,
0x0800,
0x0000,
0x1000,
0x0000,
0x2000,
0x0000,
0x4000,
0x0000,
0x8000,
///////
0x0000,
0x0080,
0x0000,
0x0040,
0x0000,
0x0020,
0x0000,
0x0010,
0x0000,
0x0008,
0x0000,
0x0004,
0x0000,
0x0002,
0x0000,
0x0001,
//////
0x0000,
0x0080,
0x0000,
0x0040,
0x0000,
0x0020,
0x0000,
0x0010,
0x0000,
0x0008,
0x0000,
0x0004,
0x0000,
0x0002,
0x0000,
0x0001,
//////
0x0000,
0x0080,
0x0000,
0x0040,
0x0000,
0x0020,
0x0000,
0x0010,
0x0000,
0x0008,
0x0000,
0x0004,
0x0000,
0x0002,
0x0000,
0x0001,
//////
0x0000,
0x0080,
0x0000,
0x0040,
0x0000,
0x0020,
0x0000,
0x0010,
0x0000,
0x0008,
0x0000,
0x0004,
0x0000,
0x0002,
0x0000,
0x0001,
};
uint16_t ledStates_3[] = {
0x1188,
0x2244,
0x4422,
0x8811,
};
uint16_t ledStates_4[] = {
0x1100,
0x2200,
0x4400,
0x8800,
};
uint16_t ledStates_5[] = {
0x0088,
0x0044,
0x0022,
0x0011,
};
uint16_t ledStates_6[] = {
0xFF00,
0x0000,
0x00FF,
0x0000,
};
uint16_t ledStates_7[] = {
0x1100,
0x2200,
0x4400,
0x8800,
0x0088,
0x0044,
0x0022,
0x0011,
};
uint16_t ledStates_8[] = {
0x0100,
0x0200,
0x0400,
0x0800,
0x1000,
0x2000,
0x4000,
0x8000,
0x0080,
0x0040,
0x0020,
0x0010,
0x0008,
0x0004,
0x0002,
0x0001,
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
EffectLed(ledStates_3 , sizeof(ledStates_3)/ sizeof(ledStates_3[0]),100); 
}
void effect4() {
  EffectLed(ledStates_4 , sizeof(ledStates_4)/ sizeof(ledStates_4[0]),100); 
}
void effect5() {
   EffectLed(ledStates_5 , sizeof(ledStates_5)/ sizeof(ledStates_5[0]),100); 
}
void effect6() {
   EffectLed(ledStates_6 , sizeof(ledStates_6)/ sizeof(ledStates_6[0]),100); 
}
void effect7() {
   EffectLed(ledStates_7 , sizeof(ledStates_7)/ sizeof(ledStates_7[0]),100); 
}
void effect8() {
   EffectLed(ledStates_8 , sizeof(ledStates_8)/ sizeof(ledStates_8[0]),100); 
}

void setup() { // Chạy một lần duy nhất khi hệ thống khởi động.
  Serial.begin(115200);
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
}
void loop() {// Sẽ lặp đi lặp lại mãi mãi đến khi tắt nguồn.
  int buttonState = digitalRead(buttonPin);

  if (buttonState != previousButtonState) {
    if (buttonState == LOW) {
      currentEffect = (currentEffect + 1) % 9;
      indexStart = 0;
    }
    delay(50); // Debounce
  }
  previousButtonState = buttonState;
    switch (currentEffect) {
    case 0:
      break;
    case 1:
      effect1();
      break;
    case 2:
      effect2();
      break;
    case 3:
      effect3();
      break;
    case 4:
      effect4();
      break;
    case 5:
      effect5();
      break;
    case 6:
      effect6();
      break;
    case 7:
      effect7();
      break;
    case 8:
      effect8();
      break;
  }
 
}