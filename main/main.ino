#include <Enes100.h>
#include <math.h>
//#include <Tank.h>

/*************************************************
   Pin Definitions
 *************************************************/
 #define fanPin 10
 #define pingPin 12  // Trigger Pin of Ultrasonic Sensor
 #define echoPin 11  // Echo Pin of Ultrasonic Sensor
 //#define servoPin 10 
 #define leftMotorsIN1 13 
 #define leftMotorsIN2 12
 #define rightMotorsIN1 8
 #define rightMotorsIN2 7
 #define ENA 9 //Motor 1 PWM
 #define ENB 6 //Motor 2 PWM
 #define TXPin 5
 #define RXPin 3
 #define leftLimitSwitch 4
 #define rightLimitSwitch 2
const int leftLineSensor = A0; 
const int rightLineSensor = A1; 
const int closeLeftTherm = A2; 
const int closeRightTherm = A3; 
const int farLeftTherm = A4;
const int farRightTherm = A5;
/*************************************************
  Variable Setup
 *************************************************/
double lastLocation[3];
double currentLocation[3];
double goalLocation[2];

void setup() {
   Serial.begin(9600);
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
   // pinMode(servoPin, OUTPUT);
      // Limit Switches
    pinMode(leftLimitSwitch, INPUT);
    pinMode(rightLimitSwitch, INPUT);
      //Line Folowers
    pinMode(leftLineSensor, INPUT); 
    pinMode(rightLineSensor, INPUT); 
      //fan
    pinMode(fanPin, OUTPUT);



    // Initialize Enes100 library
    // Team Name, Mission Type, Marker ID, TX Pin, RX Pin
// Enes100.begin("It's Lit", FIRE, 3, 10, 11);
    
}

void loop() {
    // Get OSV current position and print it to the console
    // updateCurrentLocation();
    // printCurrentLocation();
	  // printLastLocation();
    //Serial.println(getUltrasonicDistance());
    // Serial.println("ON");
    // digitalWrite(fanPin,HIGH);
    // delay(1000);
    Serial.println("OFF");
    digitalWrite(fanPin,LOW);
    delay(1000);
    
}
