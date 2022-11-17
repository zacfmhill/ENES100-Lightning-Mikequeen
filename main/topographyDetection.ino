/*************************************************
   Code for detecting topography orientation
 *************************************************/

// Reads the topography and returns the corresponding value based on the limit switches. 
 int readTopography(){
  if(analogRead(A15) <  1023  && analogRead(A14) == 1023){
          Serial.println("A");

      return TOP_A;
    }
    if(analogRead(A15) ==  1023  && analogRead(A14) < 1023){
            Serial.println("B");

      return TOP_B;
    }
    if(analogRead(A15) < 1023  && analogRead(A14) < 1023){
      Serial.println("C");
      return TOP_C;
    }
  
 }