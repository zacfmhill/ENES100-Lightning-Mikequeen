/*************************************************
   Code for putting out candles
 *************************************************/

// Turns on the fans. 
 void turnOnFan(){
   digitalWrite(fanPin,HIGH);
 }

// Turns off the fans. 
 void turnOffFan(){
   digitalWrite(fanPin,LOW);
 }

// Returns true if all flames out, false if flames still present. 
 bool putOutFlames(){
   int startNum = getNumCandles();
   turnOnFan();
   delay(10000);
   turnOffFan();
   int endNum = getNumCandles();
   if(endNum < startNum){
     Serial.print("PUT OUT ");
     Serial.print(startNum-endNum);
     Serial.println(" CANDLES!!");
   }else{
     Serial.println("DID NOT PUT OUT CANDLES!!");
   }
   if(endNum > 0 ){
     return false; 
   }
   return true; 
 }