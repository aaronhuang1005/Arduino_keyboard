#include "Keyboard.h"

bool status_check = false;

void setup() {
  // put your setup code here, to run once:
   Keyboard.begin();
   pinMode(6, INPUT_PULLUP);
   pinMode(7, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(6 ) == LOW) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_DELETE);
    delay(100);
    Keyboard.releaseAll();
    delay(200);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('k');
    Keyboard.releaseAll();
    status_check = true;
  }
  if(digitalRead(7 ) == LOW && status_check) {
    Keyboard.write(' ');
    delay(100);
    Keyboard.write(KEY_KP_9);
    Keyboard.write(KEY_KP_8);
    Keyboard.write(KEY_KP_0);
    Keyboard.write(KEY_KP_0);
    Keyboard.write(KEY_KP_4);
    Keyboard.write(KEY_KP_9);
    Keyboard.releaseAll();
    delay(200);
    status_check = !(status_check);
  }
}
