/*************************************************
   Functions for controlling drive base motors
 *************************************************/

// Turn Left Motors Forward at set PWM
void leftMotorForward(int PWM){
  digitalWrite(leftMotorsIN1, HIGH);
  analogWrite(ENA, PWM);
  
}

// Turn Left Motors Backward at set PWM
void leftMotorBackward(int PWM){
  digitalWrite(leftMotorsIN1, LOW);
  analogWrite(ENA, PWM);

}

// Turn Right Motors Forward at set PWM
void rightMotorForward(int PWM){
  digitalWrite(rightMotorsIN1, HIGH);
  analogWrite(ENB, PWM);
}

// Turn Right Motors Backward at set PWM
void rightMotorBackward(int PWM){
  digitalWrite(rightMotorsIN1, LOW);
  analogWrite(ENB, PWM);
}

// Turn OSV Counterclockwise at set PWM
void turnLeft(int PWM){
  rightMotorForward(PWM);
  leftMotorBackward(PWM);
}

// Turn OSV Clockwise at set PWM
void turnRight(int PWM){
  rightMotorBackward(PWM);
  leftMotorForward(PWM);
}

// Drive OSV Straight Forward at set PWM
void driveForward(int PWM){
  rightMotorForward(PWM);
  leftMotorForward(PWM);
}

// Drive OSV Straight Backward at set PWM
void driveBackward(int PWM){
  rightMotorBackward(PWM);
  leftMotorBackward(PWM);
}

// Stop the Left Motors
void stopLeftMotor(){
  digitalWrite(leftMotorsIN1, LOW);
  analogWrite(ENA, 0);
}

// Stop the Right Motors
void stopRightMotor(){
  digitalWrite(rightMotorsIN1, LOW);
  analogWrite(ENB, 0);
}

// Stop Both Motors
void stopMotors(){
  stopRightMotor();
  stopLeftMotor();
}