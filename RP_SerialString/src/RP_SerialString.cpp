

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "RP_SerialString.h"

/* 	###########################################################################
*	constructor
*/
RP_SerialString::RP_SerialString() {
    
}

/* 	###########################################################################
*	call if you expect a new String within timeout
*/
void RP_SerialString::renew(String &string){
  getData = true;
  found_delim = false;
  stateVal = 0;
  string = "";
  ms_start = millis();
}

/* 	###########################################################################
*	xxx
*/
void RP_SerialString::settimeout(uint32_t newtime){
  timeout = newtime;
}

void RP_SerialString::setdelim(char newdelim){
  delim = newdelim;
}

void RP_SerialString::rst_timeout(void){
  ms_start = millis();
}


/* 	###########################################################################
*	call frequently in main loop
*/
int RP_SerialString::read(String &string){
  char c;
  
  if(getData == true){
    if(Serial.available() > 0){
      c = Serial.read();
      if(c != delim){
        string += c;
      }
      else{
        found_delim = true;
      }
    }
  }
  else{
    if(Serial.available() > 0){
      c = Serial.read();
    }
  }
  
  if(found_delim == true){
    getData = false;
    stateVal = 1;
  }
  
  if(millis() - ms_start > timeout){
    getData = false;
    string = "Timeout";
    stateVal = -1;
  }
  
  return stateVal;
  
}

