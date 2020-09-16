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

void setup() {
  // initialize serial:
  Serial.begin(19200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  remain.reserve(100);
  cmd.reserve(20);
}


void loop() {
  

  // print the string when a newline arrives:
  Serial.println("some data before go to if");
  delay(1500);

  Serial.println(inputString); // echo back the data to Serial console
  if (stringComplete) {
   stringComplete = false;
   //splitString(' '); //Find an emptySpace in the input String

   Serial.println("some data before go to if");

    if (inputString.equals("read")){
      Serial.print("some data");
      Serial.println("Read DIGITAL IO selected");

    } 
    else if (inputString.equalsIgnoreCase("set")){
      Serial.println("Set DIGITAL IO selected");
      //In here must go again to parse and select which port and which status

    }
    else if (inputString.equalsIgnoreCase("help")){
      Serial.println("Use SET [PORT #] [ON/OFF]");
      Serial.println("Use READ [PORT #] to verify the High / Low status");

      }
    else { // Default option 
      Serial.println("default option executed");
    }
  
    inputString = "";
  }
}


//Find string up to the first empty space  
void splitString(char toFind){
// Find splitString and define the charToFind

    int iterator = 0;
    int inputStrSize = 0;
    int cmdStrSize = 0;
    char currentChar = 0;
    cmd = ""; // Reset cmd string

    inputStrSize = inputString.length();
    cmdStrSize = cmd.length();

    do {
        currentChar = inputString.charAt(iterator);
        if (currentChar != toFind)
        {
            cmd.setCharAt(iterator,currentChar);
        }
        else {
            remain = inputString.substring(iterator,inputString.length());
            break;
        }
        iterator++;
    } while (currentChar != toFind && iterator < inputStrSize && iterator < cmdStrSize );


}

// Read Serial Event same as Arduino Example 
void serialEvent() {
  int iterator = 0;
  while(Serial.available() == true) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString.setCharAt(iterator, inChar);
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      break;
    }
    iterator++;
  }
  stringComplete = true; 
}
