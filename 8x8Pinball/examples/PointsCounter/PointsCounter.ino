#include <8x8Pinball.h>

// This example test's the points counter.
// 
// Github Page
// https://github.com/Yvanox/Pinball-Matrix

int Button = 41;

void setup() 
{
  // 
  pinMode(Button, INPUT);  //BTN
  initScreen();
  clearScreen();
  score(0);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int val;
  val = digitalRead(Button);

    if(val == HIGH)
    {
      
    score(150);
    delay(200);
    
    }
  
}
