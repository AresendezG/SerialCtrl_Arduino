/*
  Serial Port Ctrl 
  Example based on Arduino examples 
*/

#include <String.h>

String inputString = "";         // a String to hold incoming data
String cmd = "";
String remain = "";
String operation = "";
bool stringComplete = false;  // whether the string is complete
uint8_t cmdIndex;

void setup() {
  // initialize serial:
  Serial.begin(19200);
  inputString.reserve(200);
  remain.reserve(100);
  cmd.reserve(50);
  Serial.println("Enter your command: > ");
  Serial.setTimeout(500);

}



// Read Serial Event same as Arduino Example 
void serialEvent() {

    if(Serial.available())
    {
        Serial.readBytesUntil('\n',&inputString[0], 120);
        stringComplete = true; 
    }

}

uint8_t matchPattern(String inStr, String *beforeStr, String *afterStr, char chrToFind){
  uint8_t index;

    index = inStr.indexOf(chrToFind);
      if (index > 0){
          *beforeStr = inStr.substring(0,index);
          *afterStr = inStr.substring(index+1);
          return index;
      }
      else
      {
        return -1; // Char not found in string
      }
      

}


void loop() {
  
  // print the string when a newline arrives:

  inputString = Serial.readString();
  if (inputString != ""){
    
    // find the command 

     cmdIndex =  matchPattern(inputString, &cmd, &remain,' ');

        if(cmdIndex >0)
        { 
          Serial.println("command found: ");
          Serial.println(cmd);
        }
        else
        {
          Serial.println("Wrong Sintax");
        }
        
    //Serial.println(cmd); //Echo back
    inputString=""; //Reset InputStr variable to pick a new instruction 
    delay(200);

  }


}



