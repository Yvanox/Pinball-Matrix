#include "8x8Pinball.h"

// This example displays every tipe of animation for the
// pinball machine.
// 
// Github Page
// https://github.com/Yvanox/Pinball-Matrix

void setup() {
  // put your setup code here, to run once:
  initScreen();
  clearScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  animation(START);
  delay(500);
  animation(EXTRABALL);
  delay(500);
  animation(MULTIBALL);
  delay(500);
  animation(GAMEOVER);
  delay(500);
}
