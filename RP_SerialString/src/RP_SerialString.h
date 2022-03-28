/*
 * RP_SerialString.h
 *
 * Created on: 26.03.2022
 * Author: Ralf
 */

#ifndef RP_SerialString_H_
#define RP_SerialString_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class RP_SerialString{
  public:
  RP_SerialString();                            //constructor
  void settimeout(uint32_t newtime);            //call to change default timeout
  void setdelim(char newdelim);                 //call to change default delim
  void renew(String &string);                   //call to read a new string from Serial
  int read(String &string);                     //call frequently in main
  void rst_timeout(void);                       //call to reset timeout
  
  
  private:
  uint32_t timeout = 5000;                      //timeout for waiting serial data
  uint32_t ms_start;
  char delim = '\n';                            //String is complete if delim is found \n = new line; \r = CR
  bool found_delim = false;                     //true if delim char was found
  bool getData = false;                         //true if new string should be received
  int stateVal = -1;                            //-1->timeout; 0->progress; 1->data valid
  
};





#endif