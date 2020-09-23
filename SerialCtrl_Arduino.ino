/*
  Serial Port Ctrl 
  Example based on Arduino examples 
*/

#include <String.h>

String inputString = "";         // a String to hold incoming data
String cmd = "";
String remain = "";
String operation = "";
uint8_t cmdIndex;

void setup() {
  //Enable built In LED ctrl 
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize serial:
  Serial.begin(19200);
  inputString.reserve(200);
  remain.reserve(100);
  cmd.reserve(50);
  Serial.println("Enter your command: > ");
  Serial.setTimeout(2500); // This timeout might not be important? 

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

//In this function, it will convert certain types of strings into TRUE or FALSE values
bool strToBol(String inStr){
  if (inStr.equalsIgnoreCase("on") || inStr.equalsIgnoreCase("on\n"))
    return true;
  else
    return false;
}


void loop() {
  

  // Read a string from the serial Port 
  inputString = Serial.readString();
  if (inputString != ""){
    
    // find the command 
     cmdIndex =  matchPattern(inputString, &cmd, &remain,' ');

        if(cmdIndex >0)
        { 
          Serial.println("command found: ");
            if (cmd.compareTo("led")){
                
                if (remain.equalsIgnoreCase("on\n") || remain.equalsIgnoreCase("off\n")) // This one checks if the sintax is valid
                {
                    digitalWrite(LED_BUILTIN, strToBol(cmd));
                }
                else
                {
                  Serial.println("Wrong Sintax! ");
                }
                

            }
            else if(cmd.compareTo("read")){

            }
            
            else if(cmd.compareTo("set")){

            }

            else {
              Serial.println(cmd); //Echo back cmd
            }
        }
        else
        {
          Serial.println("Wrong Sintax");
        }
        
    //Serial.println(cmd); //Echo back
    inputString=""; //Reset InputStr variable to pick a new instruction 
    delay(200);

  }
  else {
    Serial.println("Enter your command >");
  }

}



