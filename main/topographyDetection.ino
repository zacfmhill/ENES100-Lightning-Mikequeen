/*************************************************
   Code for detecting topography orientation
 *************************************************/

// Reads the topography and returns the corresponding value based on the limit switches. 
 int readTopography(){
  if(analogRead(A11) <  1000  && analogRead(A10) > 1020){
          Serial.println("A");

      return TOP_A;
    }
    if(analogRead(A11) >  1000  && analogRead(A10) < 1000){
            Serial.println("B");

      return TOP_B;
    }
    if(analogRead(A11) < 1000  && analogRead(A10) < 1000){
      Serial.println("C");
      return TOP_C;
    }
    return 1; 
  
 }