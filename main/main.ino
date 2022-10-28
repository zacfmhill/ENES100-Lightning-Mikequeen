#include <Enes100.h>
#include <math.h>
//#include <Tank.h>
#include "OSVpins.h"
/*************************************************
  Constants
 *************************************************/
#define MarkerID = 254; 
#define Line_Follow_Stage = 1; 
#define Detect_Topography_Stage = 2;
#define Detect_Num_Flames_Stage = 3; 
#define Blow_Out_Candles_Stage = 4; 
#define Navigate_To_End_Stage = 5; 

/*************************************************
  Analog Pin Definitions
 *************************************************/
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
int currentStage = 1; 



void setup() {
   Serial.begin(9600);
    // *****  Set Pin Modes  ***** //
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
    // Enes100.begin("Lightning Mikequeen", FIRE, MarkerID, TXPin, RXPin);
    
}

void loop() {
    // Get OSV current position and print it to the console
    // updateCurrentLocation();
    // printCurrentLocation();
	  // printLastLocation();
    //Serial.println(getUltrasonicDistance());

   // testing fan
    // Serial.println("ON");
    // digitalWrite(fanPin,HIGH);
    // delay(3000);
    // Serial.println("OFF");
    // digitalWrite(fanPin,LOW);
    // delay(3000);

    //testing ultrasonic
    // Serial.println(getUltrasonicDistance());
    // delay(100);

    //testing IR
    // Serial.print("Left IR Sensor: ");
    // Serial.println(analogRead(leftLineSensor));
    // Serial.print("Right IR Sensor: ");
    // Serial.println(analogRead(rightLineSensor));
    
    // ************ MS5 *************** // 
  // A) [10 Points] MOTION 
    // DriveForward(255);
  // (B) [15 Points] TURN 
    // turnToAngleRight(0);
    // delay(2000);
    // turnToAngleLeft(PI/2);
    // delay(2000);
    // turnToAngleRight(0);
    // delay(2000);
    // turnToAngleLeft(PI/2);
  //(C) [5 Points] WiFi COMMUNICATION
    //updateCurrentLocation();
    //delay(1000);
    //updateCurrentLocation();
    // if(checkLocationChange()){
    //   Enes100.println("LOCATION HAS CHANGED!!!!")
    // }else{
    //   Enes100.println("LOCATION HAS NOT CHANGED :(")
    // }
  //(D) [15 Points] MISSION SPECIFIC APPARATUS
    //turnOnFan();
    //delay(10000);
    //turnOffFan();


  // Control which step in mission
  // switch(currentStage){
  //   case Line_Follow_Stage:
  //   // statements
  //   //currentStage++;
  //   break;
  //   case Detect_Topography_Stage:
  //   // statements
  //   //currentStage++;
  //   break;
  //   case Detect_Num_Flames_Stage:
  //   // statements
  //   //currentStage++;
  //   break;
  //   case Blow_Out_Candles_Stage:
  //   // statements
  //   //currentStage++;
  //   break;
  //   case Navigate_To_End_Stage:
  //   // statements
  //   break;
  // }

    
}
