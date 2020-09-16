/*
  Serial Port Ctrl 
  Example based on Arduino examples 
*/


String inputString = "";         // a String to hold incoming data
String cmd = "";
String operation = "";
bool stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(19200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  cmd.reserve(20);
}

void loop() {
  
  stringComplete = false;
  // print the string when a newline arrives:

  if (stringComplete) {
   // getCommand();

 //   if (

  }
}


//Find string up to the first empty space  
void splitString(char toFind){

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

        }

        iterator++;
    } while (currentChar != toFind && iterator < inputStrSize && iterator < cmdStrSize );


}

// Read Serial Event same as Arduino Example 
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
