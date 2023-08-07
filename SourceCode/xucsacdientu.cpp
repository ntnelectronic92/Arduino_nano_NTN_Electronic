// Định nghĩa thư viện và chân kết nối buzzer và LED
#include <Arduino.h>
#include<Tone.h>
// Code được tạo từ phần mềm của NTN.ELECTRONIC
// Youtube Channel: https://www.youtube.com/@ntn.electronic92
// Gmail: ntn.electronic92@gmail.com
// Phone: 0934.026.250
// Khai báo các chân LED

int ledPins[] = {12,11,10,9,8,7,6,5,4,3};
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const int buttonPin = A5; // Chân kết nối nút nhấn
const int buzzerPin = A0; // Chân kết nối buzzer
bool flagStart = 0;
///Button Bebounce
const int DEBOUNCE_DELAY = 50;   // the debounce time; increase if the output flickers
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin
unsigned long lastDebounceTime = 0;  // 
 long timeRandom = 0;
int ledStates[] = {
0x0002,
0x0048,
0x004A,
0x00B4,
0x00B6,
0x00FC,

};

void buttonHandle()
{
   currentState = digitalRead(buttonPin);

  if (currentState != lastFlickerableState) {
    lastDebounceTime = millis();
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (lastSteadyState == HIGH && currentState == LOW)
    {
       Serial.println("The button is pressed");
    }
    else if (lastSteadyState == LOW && currentState == HIGH)
     {
       Serial.println("The button is released");
       flagStart = 1;
       timeRandom =  millis()    ;
     }    
    lastSteadyState = currentState;
  }
}
void setup() 
{
  // Khởi tạo các chân LED là đầu ra
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP); // Nút nhấn được kéo lên cấp nguồn
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(115200);
   randomSeed(analogRead(A1));
}
void handle(uint8_t ledNumber)
{
    uint16_t hexCode = ledStates[ledNumber];
    for (int j = 0; j < numLeds; j++)
    {
       uint16_t ledState = (hexCode >> j) & 0x01; 
       digitalWrite(ledPins[(numLeds - 1) -j], ledState);
      
    }
}
void loop() {
  buttonHandle();
  if(millis() - timeRandom > 3000)
  {
    flagStart = 0;
  }
  if(flagStart)
  {
    uint8_t randomNumber = random(6);
    handle(randomNumber);
    tone(buzzerPin,800 * randomNumber);
    delay(70);
    noTone(buzzerPin);
  }
}


