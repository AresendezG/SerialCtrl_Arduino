/*
  Serial Port Ctrl 
  Example based on Arduino examples 
*/

#include <String.h>

const String UserMessage = "Enter your Command: >"; // Message for the COM user 
const String ErrorMessage = "ERROR: Wrong Sintax \n";
String inputString = "";         // a String to hold incoming data
String cmd = ""; // String to hold the command in the Input String 
String port = "";
String operation = "";
String remain = "";

int cmdIndex;
                // D12 D2 D3 D4 D5 D6 D7 D8 D9 D10 D11     
char GPIOs [11] = {12, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Arduino Nano GPIO's

void setup() {

  // Set all GPIO Pins as INPUT_PULLUP 

    for (int i=0; i<11; i++) {
      pinMode(GPIOs[i], INPUT_PULLUP);
    }

  //Enable built In LED ctrl 
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize serial:
  Serial.begin(19200);
  inputString.reserve(200);
  remain.reserve(100);
  cmd.reserve(50);
  port.reserve(50);
  operation.reserve(50);
  Serial.println(UserMessage);
  Serial.setTimeout(500); // This timeout might not be important? 

}


int matchPattern(String inStr, String *beforeStr, String *afterStr, char chrToFind){
    int index;
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
  
  // Read a String from the Serial Port 
  inputString = Serial.readString();
  if (inputString != ""){
    // Find the command 
     cmdIndex =  matchPattern(inputString, &cmd, &remain,' ');
        if(cmdIndex >0)
        { 
          Serial.print("Echo the received Command: ");
          Serial.print(cmd);
          Serial.print("\n"); //Echo the received command

            if (cmd.equalsIgnoreCase("led")){
                
                if (remain.equalsIgnoreCase("on\n") || remain.equalsIgnoreCase("off\n")) // This one checks if the operation Option is valid
                {
                    Serial.print("Set LED to:");
                    //Serial.print(cmd);
                    Serial.println(remain);
                    digitalWrite(LED_BUILTIN, strToBol(remain));
                    //Serial.println("Enter Command >");
                }
                else // Wrong Operation Mode 
                {
                  Serial.println(ErrorMessage);
                }
            }
            else if(cmd.equalsIgnoreCase("read")){ // Read the Status of a Port

               cmdIndex = matchPattern(remain, &port, &operation, ' '); // Will find Selected port and Selected Operation
               int PortNum = port.toInt();

               if (PortNum > 0 && PortNum < 11) { // Only if Pin# Is correct, 
                    Serial.print("Port: ");
                    Serial.print(port); 
                    // Verify the Digital Read 
                    bool PinStatus = digitalRead(GPIOs[PortNum]);
                  
                  if (PinStatus == true){
                    Serial.print(" is HIGH \n");
                  } 
                  else
                  {
                    Serial.print(" is LOW \n");
                  }
               
               }
               else { // Wrong Port number, Return Error Flag
                  Serial.print("You Selected Port#: ");
                  Serial.print(port);
                  Serial.print("\n");
                  Serial.println("ERROR: Wrong Port Number, Pick 1 to 10 \n");
               }


            }
            
            else if(cmd.equalsIgnoreCase("set")){ // Set a port into ON or OFF state  
                cmdIndex = matchPattern(remain, &port, &operation, ' '); // Will find Selected port and Selected Operation
               //   Serial.print("Index for Port: ");                
               //   Serial.print(cmdIndex);
               //   Serial.print("\n");
                /* Parse the Input String: */
                Serial.print("Command: ");
                Serial.print(cmd);
                Serial.print("\t Port: ");
                Serial.print(port);

                int portNumeric = port.toInt();

                Serial.print("\t Operation: ");
                Serial.print(operation);
                Serial.println("");

                  if ((operation.substring(0,1)).equalsIgnoreCase("on")){

                  }
                  else if ((operation.substring(0,2)).equalsIgnoreCase("off")) {
                      // Default 
                  }
                  else {
                    Serial.println(ErrorMessage);
                  }
            }

            else {
              Serial.println(cmd); //Echo back cmd
            }
        }
        else
        {
          Serial.println(ErrorMessage);
        }
        
    //Serial.println(cmd); //Echo back
    inputString=""; //Reset InputStr variable to pick a new instruction 
    Serial.println(UserMessage); 
    delay(200);
    
  }
  else {
    // Serial.println("Enter your command >");
  }

}
