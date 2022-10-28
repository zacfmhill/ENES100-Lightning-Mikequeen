/*************************************************
   Code for navigating around the arena
 *************************************************/

//constant for line follower
int lineFollowLimit = 100; 
int locChangeLimit = 0.01

/*** Vision System Location Detection ***/ 
void updateCurrentLocation() {
  while (!Enes100.updateLocation()) {
    // OSV's location was not found
  }
  Enes100.updateLocation();
  lastLocation[0] = currentLocation[0];
  lastLocation[1] = currentLocation[1];
  lastLocation[2] = currentLocation[2];
  currentLocation[0] = Enes100.location.x;
  currentLocation[1] = Enes100.location.y;
  currentLocation[2] = Enes100.location.theta;
}

void printCurrentLocation() {
  Enes100.print("Current Location: [");
  Enes100.print(currentLocation[0]);
  Enes100.print(", ");
  Enes100.print(currentLocation[1]);
  Enes100.print(", ");
  Enes100.print(currentLocation[2]);
  Enes100.println("]");
}

void printLastLocation() {
  Enes100.print("Last Location: [");
  Enes100.print(lastLocation[0]);
  Enes100.print(", ");
  Enes100.print(lastLocation[1]);
  Enes100.print(", ");
  Enes100.print(lastLocation[2]);
  Enes100.println("]");
}

bool checkLocationChange() {
  if (abs(lastLocation[0] - currentLocation[0]) < locChangeLimit && abs(lastLocation[0] - currentLocation[0]) < locChangeLimit) {
    return false;
  }
  return true;
}

/*** Ultrasonic ***/
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
void followLine(){
  //left side reads line
  if(analogRead(leftLineSensor) < lineFollowLimit){
    rightMotorForward(125);
    leftMotorForward(50);
  }
  //right side reads line
  else if(analogRead(rightLineSensor) < lineFollowLimit){
    leftMotorForward(125);
    rightMotorForward(50);

  }
  //nothing reads line
  else{
    driveForward(125);
  }
}

void findLine(){

}

double calculateDesiredAngle(){
	double deltaX = goalLocation[0]- currentLocation[0];
	double deltaY = goalLocation[1]- currentLocation[1];
	double angle = atan2f(deltaY,deltaX);
	return angle;
}

void turnToAngleLeft(double desiredAngle){
	// Enes100.print("desired Anlge: ");
	// Enes100.println(desiredAngle);
	// Enes100.print("Current Angle: ");
	// Enes100.println(currentLocation[2]);
	while(currentLocation[2] <= desiredAngle - 0.01 || currentLocation[2] >= desiredAngle +0.01){
		turnLeft(125);
		// Enes100.print("Current Angle: ");
		// Enes100.println(currentLocation[2]);
		updateCurrentLocation();
	}
}
void turnToAngleRight(double desiredAngle){
	Enes100.print("desired Anlge: ");
	Enes100.println(desiredAngle);
	Enes100.print("Current Angle: ");
	Enes100.println(currentLocation[2]);
	while(currentLocation[2] <= desiredAngle - 0.01 || currentLocation[2] >= desiredAngle +0.01){
		turnRight(125);
		Enes100.print("Current Angle: ");
		Enes100.println(currentLocation[2]);
		updateCurrentLocation();
	}
}

void moveToGoalLocation(){
	updateCurrentLocation();
	// printCurrentLocation();
	// Enes100.println("Goal Location:");
	// Enes100.println(goalLocation[0]);
	// Enes100.println(goalLocation[1]);
	turnToAngleLeft(calculateDesiredAngle());
	stopMotors();
	delay(100);
	driveForward(255);
	updateCurrentLocation();
	double deltaX = abs(currentLocation[0] - goalLocation[0]);
	double deltaY = abs(currentLocation[1] - goalLocation[1]);
	while(deltaX > 0.1 || deltaY > 0.1){
		updateCurrentLocation();
		deltaX = abs(currentLocation[0] - goalLocation[0]);
		deltaY = abs(currentLocation[1] - goalLocation[1]);
	  driveForward(255);
	}
	stopMotors();
	
}

