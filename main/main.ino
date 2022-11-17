#include <Enes100.h>
#include <math.h>
//#include <Tank.h>
#include "OSVpins.h"
/*************************************************
  Constants
 *************************************************/
#define MarkerID 524
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
int currentStage = 2; 
int last; 
int check;


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
    //pinMode(leftLimitSwitch, INPUT);
    //pinMode(rightLimitSwitch, INPUT);
      //Line Folowers
    pinMode(leftLineSensor, INPUT); 
    pinMode(rightLineSensor, INPUT); 
      //fan
    pinMode(fanMotorsIN1, OUTPUT);
    pinMode(fanMotorsIN2, OUTPUT);
    pinMode(FENA, OUTPUT);
    pinMode(A15, INPUT);
    pinMode(A14, INPUT);



    // Initialize Enes100 library
    // Team Name, Mission Type, Marker ID, TX Pin, RX Pin
    
    
    
    //Enes100.begin("Lightning Mikequeen", FIRE, MarkerID, 51, 50);
    
    goalLocation[0] = Enes100.missionSite.x;
  	goalLocation[1] = Enes100.missionSite.y;
}

void loop() {
  driveForward(255);


  // while(1){
  //   delay(1000);
  //   Serial.println(readTopography());

  // }

  // while(1){
  // delay(100);
  // if(Enes100.ping()){
  //   Serial.println("Connected");
  //   updateCurrentLocation();
  //   printCurrentLocation();
  //   Enes100.println("DELAY BEFORE TURN");
  //   delay(5000);
  //   moveToGoalLocation();
  //   Serial.println("COMPLETED");
  // }
  // else{
  //   Serial.println("Failed");
  // }
  // }

  Serial.println("YES");
  // Control which step in mission
  switch(currentStage){
    case Find_Line_Stage:
      findLine();
      currentStage++;
    break;
    case Line_Follow_Stage:
      //follow line 
      followLine();
      // stop when limit switch hits
    // if(digitalRead(leftLimitSwitch)== HIGH || digitalRead(rightLimitSwitch) == HIGH){
    //   currentStage++;
    // }
    //currentStage++;
    break;
    case Detect_Topography_Stage:
    Serial.println("TOSDOINDONDONO");
      stopMotors();
      driveForward(255);
      delay(1000);
      last = readTopography();  
      stopMotors();
      delay(1000);
      driveBackward(125);
      delay(500);
      stopMotors();
      driveForward(255);
      delay(1000);
      check = readTopography();
      if (last == check){
        Serial.println("TOPO:");
       Serial.println(check);
        Enes100.mission(TOPOGRAPHY, check);
      } else{
        driveBackward(125);
      delay(250);
      stopMotors();
      driveForward(255);
      delay(500);
      check = readTopography();
      Serial.println("TOPO:");
      Serial.println(check);
      //Enes100.mission(TOPOGRAPHY, check);
      }
      stopMotors();
      Serial.println("DONE");
    while(1);
   // currentStage++;
    break;
    case Detect_Num_Flames_Stage:
      int numCandles = getNumCandles(); 
      Enes100.mission(NUM_CANDLES, numCandles);
      currentStage++;
    break;
    case Blow_Out_Candles_Stage:
      int counter = 0; 
      //trys 4 times then gives up 
      while(counter < 4){
        bool checker = putOutFlames(); 
        if(checker){
          counter = 4; 
        }
      counter++; 
    }
    currentStage++;
    break;
    case Navigate_To_End_Stage:
    // statements
    break;
  }

    
}
