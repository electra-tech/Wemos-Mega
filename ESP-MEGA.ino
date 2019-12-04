//include required library
#include <MemoryFree.h>
#include <EEPROM.h>
// define pin
#define LED 13

String inString;

void setup() {
  //assign global variables
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
}


void loop() {
}

//establishes serial port 3 communiation
void serialEvent3() {
  while (Serial3.available()) {

    char inChar = Serial3.read();

    Serial.write(inChar);

    inString += inChar;
    if (inChar == ']') {
      if (inString.indexOf("[on]") > 0) {
        digitalWrite(LED, HIGH);
      }

      if (inString.indexOf("[off]") > 0) {
        digitalWrite(LED, LOW);
      }




      inString = "";
    }
  }
}
