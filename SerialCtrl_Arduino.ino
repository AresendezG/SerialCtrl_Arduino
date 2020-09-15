/*
  Serial Port Ctrl 
  Example based on Arduino examples 
*/

String inputString = "";         // a String to hold incoming data
char * cmd[4];
String operation = "";
bool stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(19200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  
  stringComplete = false;
  // print the string when a newline arrives:

  if (stringComplete) {
    getCommand(inputString);

 //   if (

  }
}


//Find command type: READ, WRTE, HELP,  
void getCommand(String inputString){

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
