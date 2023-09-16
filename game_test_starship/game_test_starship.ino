#include "Keyboard.h"

void setup() {
  // put your setup code here, to run once:
   Keyboard.begin();
   pinMode(6, INPUT_PULLUP);
   pinMode(7, INPUT_PULLUP);
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(6 ) == LOW) {
    Keyboard.write('q');
    delay(100);
    Serial.print('q');
    Keyboard.releaseAll();
  }
  if(digitalRead(7 ) == LOW ) {
    Keyboard.write('e');
    delay(100);
    Serial.print('e');
    Keyboard.releaseAll();
  }
}
