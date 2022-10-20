#include <Enes100.h>
#include <math.h>

double lastLocation[3];
double currentLocation[3];
double goalLocation[2];

void setup() {
    // Initialize Enes100 library
    // Team Name, Mission Type, Marker ID, TX Pin, RX Pin
    Enes100.begin("It's Lit", FIRE, 3, 10, 11);

}

void loop() {
    updateCurrentLocation();
    printCurrentLocation();
	  printLastLocation();
    
}
