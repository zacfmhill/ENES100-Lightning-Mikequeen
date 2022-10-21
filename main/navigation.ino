/*************************************************
   Code for navigating around the arena
 *************************************************/

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
  if (abs(lastLocation[0] - currentLocation[0]) < 0.001 && abs(lastLocation[0] - currentLocation[0]) < 0.001) {
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

  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration * 0.034 / 2; 
  return cm;
}