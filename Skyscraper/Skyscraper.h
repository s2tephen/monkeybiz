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
// color - this skyscraper's current color
//
// Skyscraper - skyscraper constructor
// initSkyscraper - initializes the skyscraper for gameplay
// readRFID - detects an incoming RFID
// getColor - gets current color
// setColor - sets current color
// turnServo - turns the servo
// clean - strips non-alphanumeric characters from a string
class Skyscraper {
  private:
    int _id;
    int _rfidPin;
    int _servoPin;
    Servo _servo;
    int _red;
    int _blue;
    String _color;
    void turnServo();
    String clean(String s);
  public:
    Skyscraper(int id, int rfidPin, int servoPin, int red, int blue);
    void initSkyscraper();
    int readRFID();
    String getColor();
    void setColor(String color);
};

#endif
