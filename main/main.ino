#include <Enes100.h>
#include <math.h>
#include <OSVpins.h>
/*************************************************
  Analog Pin Definitions
 *************************************************/
const leftLineSensor = A0; 
const rightLineSensor = A1; 
const closeLeftTherm = A2; 
const closeRightTherm = A3; 
const farLeftTherm = A4;
const farRightTherm = A5;

// Location variables
double lastLocation[3];
double currentLocation[3];
double goalLocation[2];

void setup() {
    // Set Pin Modes
      // Ultrasonic
    pinMode(pingPin, OUTPUT);
    pinMode(echoPin, INPUT);
      // Motors
    pinMode(leftMotorsIN1, OUTPUT);
    pinMode(leftMotorsIN2, OUTPUT);
    pinMode(rightMotorsIN1, OUTPUT);
    pinMode(rightMotorsIN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
      // Servo
    pinMode(servoPin, OUTPUT);
      // Limit Switches
    pinMode(leftLimitSwitch, INPUT);
    pinMode(rightLimitSwitch, INPUT);


    // Initialize Enes100 library
    // Team Name, Mission Type, Marker ID, TX Pin, RX Pin
    Enes100.begin("It's Lit", FIRE, 3, 10, 11);
    
}

void loop() {
    // Get OSV current position and print it to the console
    updateCurrentLocation();
    printCurrentLocation();
	  printLastLocation();
    
}
