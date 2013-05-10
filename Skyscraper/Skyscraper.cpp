#include "Arduino.h"
#include "Skyscraper.h"

int NUM_RINGS = 2; // number of rings per team

// RFID values go here.
String red[] = { 
  String("4500B8FA5453"),
  String("4500B8A1A0FC") };
String blue[] = { 
  String("3F001EDAA05B"),
  String("4C0034E07DE5") };

// Skyscraper constructor.
Skyscraper::Skyscraper(int id, int rfidPin, int servoPin, int red, int blue) {
  _id = id;
  _rfidPin = rfidPin;
  _servoPin = servoPin;
  _red = red;
  _blue = blue;
}

// Initializes the skyscraper for gameplay.
void Skyscraper::initSkyscraper() {
  Serial.println("Initializing Tower "+String(_id));
  _servo.attach(_servoPin);
  _servo.write(90);
  analogWrite(_red, 0);
  analogWrite(_blue, 0);
}

// Detects an incoming RFID.
void Skyscraper::readRFID() {
  Serial.println("Tower "+String(_id)+":");

  String rfid = ""; // stores RFID string
  char val = 0; // stores incoming character
  int counter = 0;  // breaks loop if no RFID

  // reset readers
  for (int i = 3; i < 8; i++) {
    if (i == _rfidPin) {
      Serial.println("  digitalWrite("+String(i)+", HIGH);");
      digitalWrite(i, HIGH);
    }
    else {
      Serial.println("  digitalWrite("+String(i)+", LOW);");
      digitalWrite(i, LOW);
    }
  }
  delay(200);

  // read the serial port
  while (Serial.available()) {
    if (counter > 20 || rfid.length() == 12) {
      break;
    }
    else {
      val = Serial.read();
      if (isalnum(val)) rfid.concat(val);
      counter++;
    }
  }

  Serial.println("  rfid:"+rfid);
  
  // check color
  for (int i = 0; i < NUM_RINGS; i++) {
    if (rfid == clean(red[i])) {
      Serial.println("  detected red!");
      analogWrite(_red, 255); 
      analogWrite(_blue, 0); 
      turnServo();
    }
    else if (rfid == clean(blue[i])) {
      Serial.println("  detected blue!");
      analogWrite(_red, 0);
      analogWrite(_blue, 255);
      turnServo();
    }
  }
}

// Turns the servo.
void Skyscraper::turnServo() {
  _servo.write(210);
  delay(1000);
  _servo.write(90);
}

// Clears all colors.
void Skyscraper::resetColor() {
  analogWrite(_red, 0);
  analogWrite(_blue, 0);
}

// Strips non-alphanumeric characters from a string.
String Skyscraper::clean(String s) {
  String cleanedString = "";
  char chars[s.length()+1];
  s.toCharArray(chars,s.length()+1);
  for (int i = 0; i < s.length(); i++) {
    if (isdigit(chars[i]) || isalpha(chars[i])) {
      cleanedString.concat(chars[i]);
    }
  }
  return cleanedString;
}
