/*
 * RP 22.03.2022
 * code and library running, tested with Arduino Uno
 * reading serial received data into a string 
 * - with timeout, once, time settable
 * - without timeout, call function for resetting time
 * - call the trim-function to trim the string (see string.trim())
 * - reserve() a among of bytes to avoid memmory fragmentation
 */

#include "src/RP_SerialString.h"


const uint32_t s_baud = 115200;             //serial baud
String mystr;                               //empty input string

RP_SerialString SerialStr;                  //serialStr object


void setup(){
  
  Serial.begin(s_baud);
  Serial.print("Software: RP_SerialString");
  mystr.reserve(96);
  
  SerialStr.settimeout(6000);               //set timeout in ms, default is 5000
  SerialStr.setdelim('\r');                 //set CR as delim, default is NL
  SerialStr.renew(mystr);                   //empty string and start receiving sequence, timeout countdown starts

  SerialStr.rst_timeout();                  //call to reset timeout countdown, still listen to serial input
}

void loop(){
  
  int i;
  i = SerialStr.read(mystr);                //call frequently in main-loop
                                            //returns 0: in progress, no valid data
  if(i == 1){                               //returns 1: string received
    Serial.println(mystr);                  //print it 
    mystr.trim();                           //cut spaces etc.
    Serial.println(mystr);                  //print it
    SerialStr.renew(mystr);                 //start listening for a new string
  }
  else if(i == -1){                         //returns -1: timeout, string now contains "Timeout";
    Serial.println(mystr);
    SerialStr.renew(mystr);                 //start listening for a new string
  }

  static uint32_t ms;
  if(millis() - ms > 1000){
    ms = millis();
    Serial.println("loop");
  }
  


}
