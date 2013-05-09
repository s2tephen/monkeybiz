#include "Servo.h"
#include "Skyscraper.h"
#include "Pitches.h"

// mux control pins
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;

int controlPin[] = {s0, s1, s2, s3};

int SIG_pin = 0;

int muxChannel[16][4]={
  {0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1}  //channel 15
};

// towers
Skyscraper tower1(1, 5, 6);
Skyscraper tower2(2, 3, 4);

Skyscraper towers[] = { tower1, tower2 }; // array containing all towers

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
  
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  
  Serial.begin(9600);
  
  tower1.initSkyscraper();
  tower2.initSkyscraper();
  
  // TODO: Starting sound
  // playSound(startMelody, startDurations);
  TIME_LIMIT = 60000 + millis(); // one minute from initialization
}

// Main loop.
void loop() {
  Serial.println("running...");
  
  for (int i = 0; i < 4; i++) {
    Serial.print(i);
    Serial.println(": read");
    readMux(i);
    Serial.print(i);
    resetReader(7);
  }
  
//  if (tower1.getSerial().available())
//    Serial.write("tower1: "+tower1.getSerial().read());
//  if (tower2.getSerial().available())
//    Serial.write("tower2: "+tower2.getSerial().read());
//  
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

void readMux(int channel) {
  String id = "";
  char val;
  int counter = 0; // breaks while loop when counter > 10

  // loop through the 4 sig
  for (int i = 0; i < 4; i++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  
  // read the value at the SIG pin
  while (Serial.available()) {
    if (counter > 20 || id.length() == 12) {
      break;
    }
    else {
      Serial.print(channel);
      Serial.println(": while");
      
      val = Serial.read();
      if (isalnum(val)) id.concat(val);
      
      counter++;
    }
  }
   
  Serial.print(channel);
  Serial.print(": ");
  Serial.println(id);
}

void resetReader(int pin){
  Serial.println(": reset");
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
  delay(150);
}

void gameOver() {
  // TODO: Ending sound
  Serial.println("game over");
  tower1.resetColor();
  tower2.resetColor();
  while(1) { } // infinite empty loop
}
