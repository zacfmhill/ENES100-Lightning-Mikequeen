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
int currentStage = 1; 
int last; 
int check;

/*************************************************
  Node Setup
 *************************************************/
double nodeA[2] = {1,0.5};
double nodeB[2] = {1,1};
double nodeC[2] = {1,1.5};
double nodeD[2] = {1.9,0.5};
double nodeE[2] = {1.9,1};
double nodeF[2] = {1.9,1.5};
double nodeG[2] = {3,0.5};
double nodeH[2] = {3,1};
double nodeI[2] = {3,1.5};
double nodeJ[2] = {3.9,1.5};





void setup() {
   Serial.begin(9600);
    // *****  Set Pin Modes  ***** //
      // Ultrasonic
    pinMode(pingPin, OUTPUT);
    pinMode(echoPin, INPUT);
      // Motors
    pinMode(leftMotorsIN1, OUTPUT);
    pinMode(rightMotorsIN1, OUTPUT);
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
    pinMode(leftLimitSwitch, INPUT);
    pinMode(rightLimitSwitch, INPUT);
      //fan
    pinMode(fanMotorsIN1, OUTPUT);




    // Initialize Enes100 library
    // Team Name, Mission Type, Marker ID, TX Pin, RX Pin
    
    
    
    Enes100.begin("Lightning Mikequeen", FIRE, MarkerID, TXPin, RXPin);
    
    goalLocation[0] = Enes100.missionSite.x;
  	goalLocation[1] = Enes100.missionSite.y;
}

void loop() {
     //   updateCurrentLocation();


  // while(1){
  // driveForward(150);
  // }
  // while(1){
  //   Serial.println("FWD");
  //   driveForward(255);
  //   delay(3000);
  //   Serial.println("BWD");
  //   driveBackward(255);
  //   delay(3000);
  //   Serial.println("LFT");
  //   turnLeft(255);
  //   delay(3000);
  //   Serial.println("RGT");
  //   turnRight(255);
  //   delay(3000);
  //   Serial.println("STP");
  //   stopMotors();
  //   delay(3000);
  // }
  // while(!Enes100.ping());

  // while(1){
  //  delay(500);
  //  Serial.print("LEFT ");

  //  Serial.println(digitalRead(leftLimitSwitch));
   
    
  //    Serial.print("RIGHT ");
  //   Serial.println(digitalRead(rightLimitSwitch));

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

  // Control which step in mission
  switch(currentStage){
    case Find_Line_Stage:
      turnOffFan();
      findLine();
      currentStage++;
    break;
    case Line_Follow_Stage:
      turnOffFan();
      //follow line 
     // followLine();
     driveForward(150);
     delay(1000);
      // stop when limit switch hits
    if(digitalRead(leftLimitSwitch) == 0  || digitalRead(rightLimitSwitch) == 0){
      currentStage++;
    }
    //currentStage++;
    break;
    case Detect_Topography_Stage:
      stopMotors();
      delay(1000);
      driveForward(150);
      delay(1500);
      check = readTopography(); 
      stopMotors(); 
      Enes100.print("Topography Read: "); 
      Enes100.println(check);
      Enes100.mission(TOPOGRAPHY, check);
      Serial.println("DONE");
      currentStage++;
    break;
    case Detect_Num_Flames_Stage:
      currentStage++;
      break;
    //   int numCandles = getNumCandles(); 
    //   Enes100.mission(NUM_CANDLES, numCandles);
    //   currentStage++;
    // break;
    case Blow_Out_Candles_Stage:
      int counter = 0; 
      //trys 4 times then gives up 
      while(counter < 4){
        // bool checker = putOutFlames(); 
        // if(checker){
        //   counter = 4; 
        // }
        stopMotors();
        turnOnFan(255);
        delay(10000);
        turnOffFan();
        delay(5000);
      counter++; 
    }
    currentStage++;
    break;
    case Navigate_To_End_Stage:

				// Go to A
				goalLocation[0] = nodeA[0];
				goalLocation[1] = nodeA[1];
				Enes100.println("GOING TO A...");
				moveToGoalLocation();
				Enes100.println("MADE IT TO A");
				goalLocation[0] = nodeD[0];
				goalLocation[1] = nodeD[1];
				Enes100.println("GOING TO D");
				if(not moveToGoalLocation()){
					Enes100.println("DID NOT MAKE IT TO D");
					//DID NOT MAKE IT TO D. 
					// Back up 
					Tank.setRightMotorPWM(-255);
					Tank.setLeftMotorPWM(-255);
					delay(1000);
					Tank.setRightMotorPWM(0);
					Tank.setLeftMotorPWM(0);
					// Set goal to B 
					goalLocation[0] = nodeB[0];
					goalLocation[1] = nodeB[1];
					// Move to B 
					Enes100.println("GOING TO B");
					moveToGoalLocation();
					Enes100.println("MADE IT TO B");
					// Set goal to E
					goalLocation[0] = nodeE[0];
					goalLocation[1] = nodeE[1];
					Enes100.println("GOING TO E");
					if(not moveToGoalLocation()){
						Enes100.println("MADE IT TO E");
						// DID NOT MAKE IT TO E. 
						Tank.setRightMotorPWM(-255);
						Tank.setLeftMotorPWM(-255);
						delay(100);
						Tank.setRightMotorPWM(0);
						Tank.setLeftMotorPWM(0);
						// set goal to C. 
						goalLocation[0] = nodeC[0];
						goalLocation[1] = nodeC[1];
						//move to C
						Enes100.println("GOING TO C");
						moveToGoalLocation();
						Enes100.println("MADE IT TO C");
						// Set goal to F. 
						goalLocation[0] = nodeF[0];
						goalLocation[1] = nodeF[1];
						//move to F. 
						Enes100.println("GOING TO F");
						moveToGoalLocation();
						Enes100.println("MADE IT TO F");
						
						
					}
					// no matter what at this point it has reached the second row and so we move down to D. 
					// Go to D
					Enes100.println("GOING TO D");
					goalLocation[0] = nodeD[0];
					goalLocation[1] = nodeD[1];
					moveToGoalLocation();
					Enes100.println("MADE IT TO D");
				}
				goalLocation[0] = nodeG[0];
				goalLocation[1] = nodeG[1];
				moveToGoalLocation();
				if(not moveToGoalLocation()){
					//DID NOT MAKE IT TO G. 
					// Back up 
					Tank.setRightMotorPWM(-255);
					Tank.setLeftMotorPWM(-255);
					delay(100);
					Tank.setRightMotorPWM(0);
					Tank.setLeftMotorPWM(0);
					// Set goal to E 
					goalLocation[0] = nodeE[0];
					goalLocation[1] = nodeE[1];
					// Move to E 
					moveToGoalLocation();
					// Set goal to H
					goalLocation[0] = nodeH[0];
					goalLocation[1] = nodeH[1];
					if(not moveToGoalLocation()){
						// DID NOT MAKE IT TO H. 
						Tank.setRightMotorPWM(-255);
						Tank.setLeftMotorPWM(-255);
						delay(100);
						Tank.setRightMotorPWM(0);
						Tank.setLeftMotorPWM(0);
						// set goal to F. 
						goalLocation[0] = nodeF[0];
						goalLocation[1] = nodeF[1];
						//move to C
						moveToGoalLocation();
						// Set goal to I. 
						goalLocation[0] = nodeI[0];
						goalLocation[1] = nodeI[1];
						//move to I. 
						moveToGoalLocation();
						// move to J
						goalLocation[0] = nodeJ[0];
						goalLocation[1] = nodeJ[1];
						moveToGoalLocation();
						currentStage++;
						break;
					}
											// Set goal to I. 
						goalLocation[0] = nodeI[0];
						goalLocation[1] = nodeI[1];
						//move to I. 
						moveToGoalLocation();
						// move to J
						goalLocation[0] = nodeJ[0];
						goalLocation[1] = nodeJ[1];
						moveToGoalLocation();
						currentStage++;
						break;
					
				}
										// Set goal to I. 
						goalLocation[0] = nodeI[0];
						goalLocation[1] = nodeI[1];
						//move to I. 
						moveToGoalLocation();
						// move to J
						goalLocation[0] = nodeJ[0];
						goalLocation[1] = nodeJ[1];
						moveToGoalLocation();
						currentStage++;
						break;
				
			}
			currentStage++;
    break;
  }

    
}
