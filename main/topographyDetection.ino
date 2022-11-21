/*************************************************
   Code for detecting topography orientation
 *************************************************/

// Reads the topography and returns the corresponding value based on the limit switches. 
 int readTopography(){
  if(digitalRead(leftLimitSwitch) == 0  && digitalRead(rightLimitSwitch) == 1){
          Serial.println("A");

      return TOP_A;
    }
    if(digitalRead(leftLimitSwitch) == 1  && digitalRead(rightLimitSwitch) == 0){
            Serial.println("B");

      return TOP_B;
    }
    if(digitalRead(leftLimitSwitch) == 0 && digitalRead(rightLimitSwitch) == 0){
      Serial.println("C");
      return TOP_C;
    }
    return 4; 
  
 }