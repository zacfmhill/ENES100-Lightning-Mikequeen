/*************************************************
   Code for navigating around the arena
 *************************************************/

//constant for line follower
int lineFollowLimitLeft = 745; 
int lineFollowLimitRight = 870;
int locChangeLimit = 0.1;

// Updates the stored last location and stored current location of the OSV to the current OSV location based on the vision system
void updateCurrentLocation() {
  while (!Enes100.updateLocation()) {
     // OSV's location was not found
    Enes100.println("404 not found!");
    Serial.println("404!!");
  }
  lastLocation[0] = currentLocation[0];
  lastLocation[1] = currentLocation[1];
  lastLocation[2] = currentLocation[2];
  currentLocation[0] = Enes100.location.x;
  currentLocation[1] = Enes100.location.y;
  currentLocation[2] = Enes100.location.theta;
}

// Prints the stored current location of the OSV
void printCurrentLocation() {
  Enes100.print("Current Location: [");
  Enes100.print(currentLocation[0]);
  Enes100.print(", ");
  Enes100.print(currentLocation[1]);
  Enes100.print(", ");
  Enes100.print(currentLocation[2]);
  Enes100.println("]");
}

// Prints the stored last location of the OSV
void printLastLocation() {
  Enes100.print("Last Location: [");
  Enes100.print(lastLocation[0]);
  Enes100.print(", ");
  Enes100.print(lastLocation[1]);
  Enes100.print(", ");
  Enes100.print(lastLocation[2]);
  Enes100.println("]");
}

// Checks if the OSV location has changed from the current and last stored locations and returns true or false
bool checkLocationChange() {
  if (abs(lastLocation[0] - currentLocation[0]) < locChangeLimit && abs(lastLocation[1] - currentLocation[1]) < locChangeLimit) {
    return false;
  }
  return true;
}

/*** Ultrasonic ***/
// Returns the distance of an object from the front of the OSV in cm using the ultrasonic
long getUltrasonicDistance(){
  long duration; 
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  long cm = duration * 0.034 / 2;

  return cm;
}
/*** Line Follower ***/ 

// Sets movement for following the line using photoresistors once. (Needs to be included in a loop!!)
void followLine(){
  //left side reads line
  if(analogRead(leftLineSensor) > lineFollowLimitLeft){
    rightMotorForward(255);
    stopLeftMotor();
  }
  //right side reads line
  else if(analogRead(rightLineSensor) > lineFollowLimitRight){
    leftMotorForward(255);
    stopRightMotor();

  }
  //nothing reads line
  else{
    leftMotorForward(255);
    stopRightMotor();
  }
}

// Has the OSV turn to find the line to follow. 
void findLine(){
// Make OSV turn 
while(analogRead(rightLineSensor) < lineFollowLimitRight){
turnLeft(255);
}
// Once sensor reads 0 (off the line) continue turning
// Once sensor reads 1 (on line) stop turning
stopMotors();
}

// returns the desired angle between the current location and our goal location. 
double calculateDesiredAngle(){
  updateCurrentLocation();
	double deltaX = goalLocation[0]- currentLocation[0];
	double deltaY = goalLocation[1]- currentLocation[1];
	double angle = atan2f(deltaY,deltaX);
	return angle;
}

// Turns left to a given desired angle based on the vision system. 
void turnToAngleLeft(double desiredAngle){
  Serial.print("desired Anlge: ");
	Serial.println(desiredAngle);
	Serial.print("Current Angle: ");
	Serial.println(currentLocation[2]);
  Enes100.print("Goal Location: ");
  Enes100.print(goalLocation[0]);
  Enes100.print(", ");
  Enes100.print(goalLocation[1]);
	Enes100.print("desired Anlge: ");
	Enes100.println(desiredAngle);
	Enes100.print("Current Angle: ");
	Enes100.println(currentLocation[2]);
	while(currentLocation[2] <= desiredAngle - 0.03 || currentLocation[2] >= desiredAngle +0.03){
		turnLeft(125);
		Serial.print("desired Anlge: ");
	  Serial.println(desiredAngle);
	  Serial.print("Current Angle: ");
	  Serial.println(currentLocation[2]);
    Enes100.print("desired Anlge: ");
	  Enes100.print(desiredAngle);
	  Enes100.print(" Current Angle: ");
	  Enes100.println(currentLocation[2]);
		updateCurrentLocation();
	}
  stopMotors();
}

// Turns right to a given desired angle based on the vision system. 
void turnToAngleRight(double desiredAngle){
	Enes100.print("desired Anlge: ");
	Enes100.println(desiredAngle);
	Enes100.print("Current Angle: ");
	Enes100.println(currentLocation[2]);
	while(currentLocation[2] <= desiredAngle - 0.01 || currentLocation[2] >= desiredAngle +0.01){
		turnRight(100);
		Enes100.print("Current Angle: ");
		Enes100.println(currentLocation[2]);
		updateCurrentLocation();
	}
}

// Moves to the location stored in goalLocation
void moveToGoalLocation(){
	updateCurrentLocation();
	printCurrentLocation();
	Enes100.println("Goal Location:");
	Enes100.println(goalLocation[0]);
	Enes100.println(goalLocation[1]);
	
  //**updated turning**// -- Marco
  if(calculateDesiredAngle<0){ //goal angle is below us
    if(Enes100.location.theta<(pi/2) && Enes100.location.theta>(-pi)/2){ //idk if pi is the constant name
      turnToAngleRight(calculateDesiredAngle()); //turn right
    }
    else if(Enes100.location.theta>(pi/2) && Enes100.location.theta<(-pi)/2){
      turnToAngleLeft(calculateDesiredAngle()); //turn left
    }
    else if(Enes100.location.theta == calculateDesiredAngle()){ //probably not accurate??
      break; //don't turn
    }
  }
  else{ //goal angle is above us
    if(Enes100.location.theta<(pi/2) && Enes100.location.theta>(-pi)/2){ //idk if pi is the constant name
      turnToAngleLeft(calculateDesiredAngle()); //turn left
    }
    else if(Enes100.location.theta>(pi/2) && Enes100.location.theta<(-pi)/2){
      turnToAngleRight(calculateDesiredAngle()); //turn right
    }
    else if(Enes100.location.theta == calculateDesiredAngle()){ //probably not accurate??
      break; //don't turn
    }
  }

	stopMotors();
	delay(1000);
	driveBackward(255);
	updateCurrentLocation();
	double deltaX = abs(currentLocation[0] - goalLocation[0]);
	double deltaY = abs(currentLocation[1] - goalLocation[1]);
	while(deltaX > 0.2 || deltaY > 0.2){
    Enes100.print("Goal Location: ");
	  Enes100.print(goalLocation[0]);
    Enes100.print(", ");
	  Enes100.println(goalLocation[1]);
    Enes100.print("Goal Location: ");
	  Enes100.print(goalLocation[0]);
    Enes100.print(", ");
	  Enes100.println(goalLocation[1]);
		updateCurrentLocation();
		deltaX = abs(currentLocation[0] - goalLocation[0]);
		deltaY = abs(currentLocation[1] - goalLocation[1]);
	  driveBackward(255);
	}
	stopMotors();
	
}

