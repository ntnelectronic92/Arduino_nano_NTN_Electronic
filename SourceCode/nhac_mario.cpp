#include <Arduino.h>
#include <stdio.h>
//NTN.ELECTRONIC 2023 CREATOR YOUTUBE
// Định nghĩa chân buzzer
#define BUZZER_PIN A1
uint8_t ledPins[] = {12,11,10,9,8,7,6,5};
uint16_t numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

uint8_t ledStates[] = {
 0x01,
0x03,
0x07,
0x0F,
0x1F,
0x3F,
0x7F,
0xFF,
};
#define NOTE_E6 1319
#define NOTE_G6 1568
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_D7 2349
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_G7 3136
#define NOTE_A7 3520

uint16_t melody[] = {
    NOTE_E7, NOTE_E7, 0, NOTE_E7,
    0, NOTE_C7, NOTE_E7, 0,
    NOTE_G7, 0, 0,  0,
    NOTE_G6, 0, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0
};

// Hằng số để đại diện cho các khoảng thời gian giữa các nốt nhạc
#define NOTE_DURATION 100

// Hàm phát một nốt nhạc
void playNote(uint16_t note, uint16_t duration) {
  tone(BUZZER_PIN, note, duration);
  delay(duration);
  noTone(BUZZER_PIN);
}
void displayLed(uint8_t effectIndex)
{
    byte hexCode = ledStates[effectIndex];
    // Bật sáng các chân LED dựa trên mã hex
    for (uint8_t j = 0; j < numLeds; j++) 
    {
      uint8_t ledState = (hexCode >> j) & 0x01;  // Kiểm tra bit tại vị trí j
      // Bật hoặc tắt chân LED tương ứng
      digitalWrite(ledPins[(numLeds - 1) - j], ledState);
    }

}

// Hàm chơi bản nhạc Mario
void playMarioTheme() {
  uint16_t noteCount = sizeof(melody) / sizeof(melody[0]);
  for (uint16_t i = 0; i < noteCount; i++) {
    if (melody[i] == 0) {
      delay(NOTE_DURATION);
    } else {
      uint8_t ledIndex = map(melody[i],NOTE_E6, NOTE_A7, 0, (long)(numLeds -1));
      Serial.print("Led index = ");
      Serial.print(ledIndex);
      Serial.println();
      displayLed(ledIndex);
      playNote(melody[i], NOTE_DURATION);
    }
    delay(NOTE_DURATION / 2);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  for (uint8_t i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  playMarioTheme();
  delay(2000); 
}
