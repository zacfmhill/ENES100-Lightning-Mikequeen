#include <Enes100.h>
#include <math.h>
//#include <Tank.h>
#include "OSVpins.h"
/*************************************************
  Constants
 *************************************************/
#define MarkerID 213
#define Find_Line_Stage 0
#define Line_Follow_Stage 1
#define Detect_Topography_Stage 2
#define Detect_Num_Flames_Stage 3
#define Blow_Out_Candles_Stage 4
#define Navigate_To_End_Stage 5 


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
int currentStage = 0; 



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
   Enes100.begin("Lightning Mikequeen", FIRE, MarkerID, TXPin, RXPin);
    //driveForward(255);
}

void loop() {
   
  // Control which step in mission
  switch(currentStage){
    case Find_Line_Stage:
      findLine();
      currentStage++;
    break;
    case Line_Follow_Stage:
      //follow line 
      // stop when limit switch hits
    
    //currentStage++;
    break;
    case Detect_Topography_Stage:
    // statements
    //currentStage++;
    break;
    case Detect_Num_Flames_Stage:
    // statements
    //currentStage++;
    break;
    case Blow_Out_Candles_Stage:
    // statements
    //currentStage++;
    break;
    case Navigate_To_End_Stage:
    // statements
    break;
  }

    
}
