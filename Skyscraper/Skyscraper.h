#ifndef Skyscraper_h
#define Skyscraper_h

#include "Arduino.h"
#include "Servo.h"

// Skyscraper class.
//
// id - the id of the skyscraper
// servo - the servo associated with this skyscraper
// servoPin - the output pin for the servo
// red - this skyscraper's red output pin
// blue - this skyscraper's blue output pin
// clean - strips non-alphanumeric characters from a string
//
// Skyscraper - skyscraper constructor
// initSkyscraper - initializes the skyscraper for gameplay
// readRFID - detects an incoming RFID
// resetColor - clears all colors
// turnServo - turns the servo
// clean - strips non-alphanumeric characters from a string
class Skyscraper {
  private:
    int _id;
    int _rfidPin;
    int _servoPin;
    Servo _servo;
    int _red;
    int _green;
    void turnServo();
    String clean(String s);
  public:
    Skyscraper(int id, int rfidPin, int servoPin, int red, int blue);
    void initSkyscraper();
    void readRFID();
    void resetColor();
};

#endif
