#include "Servo.h"
#include "Skyscraper.h"
#include "Pitches.h"

// TODO: set correct pin #'s
// id, rfid, servo, red, blue
Skyscraper tower1(1, 3, 0, 0, 0);
Skyscraper tower2(2, 4, 0, 0, 0);
Skyscraper tower3(3, 5, 0, 0, 0);
Skyscraper tower4(4, 6, 0, 0, 0);
Skyscraper tower5(5, 7, 0, 0, 0);

Skyscraper towers[] = { tower1, tower2, tower3, tower4, tower5 }; // array containing all towers

// game parameters
int TIME_LIMIT;
int red;
int blue;
int AUDIO_PIN = 0; // TODO: set pin #

// audio
int startMelody[] = {
  NOTE_C4, NOTE_G4, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
int startDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4 };
int endMelody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F3, NOTE_D3, NOTE_C3 };
int endDurations[] = {
  8, 8, 8, 8, 4, 4, 2 };
int drawMelody[] = {
  NOTE_AS3, NOTE_A3, NOTE_GS3, NOTE_G3, NOTE_FS3, NOTE_F3 };
int drawDurations[] = {
  4, 4, 4, 4, 4 };
int scoreMelody[] = {
  NOTE_C3, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4 };
int scoreDurations[] = {
  4, 8, 8, 8, 4 };

// Sets up the game logic.
void setup() {
  Serial.println("setting up...");
  
  Serial.begin(9600);
  
  for (int i = 3; i < 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  for (int i = 0; i < 5; i++) {
    towers[i].initSkyscraper();
  }
  
  playSound(startMelody, startDurations, 8);
  TIME_LIMIT = 60000 + millis(); // one minute from initialization
}

// Main loop.
void loop() {
  Serial.println("running...");
  red = 0;
  blue = 0;
  
  for (int i = 0; i < 5; i++) {
    if(towers[i].readRFID() == 1) {
      playSound(scoreMelody, scoreDurations, 5);
    }
    if (towers[i].getColor() == "red") {
      red++; 
    }
    else if (towers[i].getColor() == "blue") {
      blue++;
    }
  }
  
  if (millis() > TIME_LIMIT || red == 5 || blue == 5) { // victory conditions: time, monopoly
    gameOver();
  }
}

void playSound(int melody[], int noteDurations[], int length) {
  for (int i = 0; i < length ; i++) {
    int noteDuration = 1000/noteDurations[i];
    tone(AUDIO_PIN, melody[i], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(AUDIO_PIN);
  }
}

void gameOver() {
  Serial.println("game over");
  
  if (red > blue) { // red wins
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 5; j++) {
        towers[j].setColor("red");
        delay(200);
        towers[j].setColor("none");
        delay(200);
      }
    }
    playSound(endMelody, endDurations, 7);
  }
  else if (blue > red) { // blue wins
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 5; j++) {
        towers[j].setColor("red");
        delay(200);
        towers[j].setColor("none");
        delay(200);
      }
    }
    playSound(endMelody, endDurations, 7);
  }
  else { // nobody wins
    String colors[] = { tower1.getColor(), tower2.getColor(), tower3.getColor(), tower4.getColor(), tower5.getColor() };
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 5; j++) {
        towers[j].setColor(colors[j]);
        delay(200);
        towers[j].setColor("none");
        delay(200);
      }
    }
    playSound(drawMelody, drawDurations, 6);
  }
  
  while(1) { } // infinite empty loop
}
