#include "Servo.h"
#include "Skyscraper.h"
#include "Pitches.h"

// towers
Skyscraper tower1(1, 3, 0, 0);
Skyscraper tower2(2, 4, 0, 0);
Skyscraper tower3(3, 5, 0, 0);
Skyscraper tower4(4, 6, 0, 0);
Skyscraper tower5(5, 7, 0, 0);

Skyscraper towers[] = { tower1, tower2, tower3, tower4, tower5 }; // array containing all towers

// game parameters
int TIME_LIMIT;

// music
int startMelody[] = {
  NOTE_C4, NOTE_G4,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4 };
int startDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4 };

// Sets up the game logic.
void setup() {
  Serial.println("setting up...");
  
  Serial.begin(9600);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  
  tower1.initSkyscraper();
  tower2.initSkyscraper();
  tower3.initSkyscraper();
  tower4.initSkyscraper();
  tower5.initSkyscraper();
  
  // TODO: Starting sound
  // playSound(startMelody, startDurations);
  TIME_LIMIT = 60000 + millis(); // one minute from initialization
}

// Main loop.
void loop() {
  Serial.println("running...");
  tower1.readRFID();
  tower2.readRFID();
  tower3.readRFID();
  tower4.readRFID();
  tower5.readRFID();
  
//  if (millis() > TIME_LIMIT) {
//    gameOver();
//  }

//void playSound(int melody[], int noteDurations[]) {
//  for (int i = 0; i < 8 ; i++) {
//    int noteDuration = 1000/noteDurations[i];
//    tone(8, melody[i], noteDuration);
//    int pauseBetweenNotes = noteDuration * 1.30;
//    delay(pauseBetweenNotes);
//    noTone(8);
//  }
}

void gameOver() {
  // TODO: Ending sound
  Serial.println("game over");
  tower1.resetColor();
  tower2.resetColor();
  while(1) { } // infinite empty loop
}
