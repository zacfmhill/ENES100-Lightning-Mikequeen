/*************************************************
   Functions for detecting the number of lit candles
 *************************************************/

int VoCL, VoCR, VoFL, VoFR;
float R1 = 49000;
float logR2CL,logR2CR,logR2FL,logR2FR, R2, TCL, TCR, TFL, TFR;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int counts; 
const int tempFlame = 60; 
const int countTotal = 5; 

int getNumCandles(){
  counts = 0; 
  while(counts < countTotal ){
    // reads analog values
    VoCL = analogRead(closeLeftTherm);
    VoCR = analogRead(closeRightTherm);
    VoFL = analogRead(farLeftTherm);
    VoFR = analogRead(farRightTherm);
    // Calculates resistance changes 
    R2 = R1 * (1023.0 / (float)VoCL - 1.0);
    logR2CL = log(R2);
    R2 = R1 * (1023.0 / (float)VoCR - 1.0);
    logR2CR = log(R2);
    R2 = R1 * (1023.0 / (float)VoFL - 1.0);
    logR2FL = log(R2);
    R2 = R1 * (1023.0 / (float)VoFR - 1.0);
    logR2FR = log(R2);
    // calculates temps to F 
    TCL = (1.0 / (c1 + c2*logR2CL + c3*logR2CL*logR2CL*logR2CL));
    TCL = TCL - 273.15;
    TCL = (TCL * 9.0)/ 5.0 + 32.0; 

    TCR = (1.0 / (c1 + c2*logR2CR + c3*logR2CR*logR2CR*logR2CR));
    TCR = TCR - 273.15;
    TCR = (TCR * 9.0)/ 5.0 + 32.0; 

    TFL = (1.0 / (c1 + c2*logR2FL + c3*logR2FL*logR2FL*logR2FL));
    TFL = TFL - 273.15;
    TFL = (TFL * 9.0)/ 5.0 + 32.0; 

    TFR = (1.0 / (c1 + c2*logR2FR + c3*logR2FR*logR2FR*logR2FR));
    TFR = TFR - 273.15;
    TFR = (TFR * 9.0)/ 5.0 + 32.0; 
    // prints current temps
    Serial.print("TEMPS { CL: "); 
    Serial.print(TCL);
    Serial.print(" F, "); 
    Serial.print(" CR: "); 
    Serial.print(TCR);
    Serial.print(" F, "); 
    Serial.print(" FL: "); 
    Serial.print(TFL);
    Serial.print(" F, "); 
    Serial.print(" FR: "); 
    Serial.print(TFR);
    Serial.println(" F }"); 
    counts++; 
    delay(500);
  }
  // Checks each candle temp
  int totalNumCandles = 1; 
  if(TCL >= tempFlame){
    totalNumCandles++;
  }
  if(TCR >= tempFlame){
    totalNumCandles++;
  }
  if(TFL >= tempFlame){
    totalNumCandles++;
  }
  if(TFR >= tempFlame){
    totalNumCandles++;
  }
  return totalNumCandles; 
}