/*************************************************
   Code for detecting topography orientation
 *************************************************/

// Reads the topography and returns the corresponding value based on the limit switches. 
 int readTopography(){
  if(digitalRead(leftLimitSwitch)== HIGH && digitalRead(rightLimitSwitch) == LOW){
      return TOP_A;
    }
    if(digitalRead(leftLimitSwitch)== LOW && digitalRead(rightLimitSwitch) == HIGH){
      return TOP_B;
    }
    if(digitalRead(leftLimitSwitch)== HIGH && digitalRead(rightLimitSwitch) == HIGH){
      return TOP_C;
    }
 }