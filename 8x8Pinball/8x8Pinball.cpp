/*
 * Uses custom made letters for pinball machine
 */

#include <SPI.h>
#include "Arduino.h"
#include "8x8Pinball.h"

//Variable used for the limit of characters on 4 8x8 displays
int limit = 0;

//Variable to store the sum of all the current points
int sum = 0;

uint8_t charBuff [SCREEN_NUMBER][5] =
{
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
};

uint8_t shiftBuff[4] =
{B00000000, B00000000, B00000000, B00000000};


uint8_t matrixBuffer[SCREEN_NUMBER][8] =
{
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // matrix_1
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // matrix_2
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // matrix_3
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // matrix_4

};

void writeSPI(uint8_t address, uint8_t value)
{

  digitalWrite(CS_PIN, LOW);
  SPI.transfer(address);      // Send address.
  SPI.transfer(value);        // Send the value.
  digitalWrite(CS_PIN, HIGH); // Finish transfer.

}

void initScreen()
{
  SPI.begin();

  pinMode(CS_PIN, OUTPUT);

  // Intiation of LED segment display.
  writeSPI(0x09, 0x00); //Decode mode -- no decode
  writeSPI(0x0A, 0x01);  //Intensity -- Low
  writeSPI(0x0B, 0x07);  //Scan Limit -- 0-7
  writeSPI(0x0C, 0x01);    //Shutdown -- no
  writeSPI(0x0F, 0x00);  //Display Test -- Yes

  writeSPI(0x01, 0X00);  //00000000
  writeSPI(0x02, 0X00);  //00000000
  writeSPI(0x03, 0X00);  //00000000
  writeSPI(0x04, 0X00);  //00000000
  writeSPI(0x05, 0X00);  //00000000
  writeSPI(0x06, 0X00);  //00000000
  writeSPI(0x07, 0X00);  //00000000
  writeSPI(0x08, 0X00);  //00000000

  delay(20);

}

void clearScreen()
{
  int index;
  for (index = 0; index < 8; index++)
  {
    matrixBuffer[0][index] = B00000000;
    matrixBuffer[1][index] = B00000000;
    matrixBuffer[2][index] = B00000000;
    matrixBuffer[3][index] = B00000000;
  }
  sendScreen();
  delay(50);
}

void sendScreen()
{
  int row;

  for (row = 0; row < 8; row++)
  {
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(row + 1);    // Send address.
    SPI.transfer(matrixBuffer[0][row]);        // Send the value.
    SPI.transfer(row + 1);    // Send address.
    SPI.transfer(matrixBuffer[1][row]);        // Send the value.
    SPI.transfer(row + 1);    // Send address.
    SPI.transfer(matrixBuffer[2][row]);        // Send the value.
    SPI.transfer(row + 1);    // Send address.
    SPI.transfer(matrixBuffer[3][row]);        // Send the value.
    digitalWrite(CS_PIN, HIGH); // Finish transfer.
  }
  limit = 0;
}

void invertColors()
{
  int index;
  for (index = 0; index < 8; index++)
  {
    matrixBuffer[0][index] = matrixBuffer[0][index] ^ B11111111;
    matrixBuffer[1][index] = matrixBuffer[1][index] ^ B11111111;
    matrixBuffer[2][index] = matrixBuffer[2][index] ^ B11111111;
    matrixBuffer[3][index] = matrixBuffer[3][index] ^ B11111111;
  }
}

void saveChar(uint8_t character)
{
  uint16_t index = 0;

  if (limit <= 8)
  {

    switch (limit)
    {
      case 0:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[0][index] = CH[character - 0x20][index];
          matrixBuffer[0][index] = (matrixBuffer[0][index] <<= 5);
          charBuff[0][index] = matrixBuffer[0][index];
        }
        break;
      case 1:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[0][index] = CH[character - 0x20][index];
          matrixBuffer[0][index] = (matrixBuffer[0][index] <<= 1);
          matrixBuffer[0][index] = matrixBuffer[0][index] + charBuff[0][index];
        }
        break;
      case 2:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[1][index] = CH[character - 0x20][index];
          matrixBuffer[1][index] = (matrixBuffer[1][index] <<= 5);
          charBuff[1][index] = matrixBuffer[1][index];
        }
        break;
      case 3:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[1][index] = CH[character - 0x20][index];
          matrixBuffer[1][index] = (matrixBuffer[1][index] <<= 1);
          matrixBuffer[1][index] = matrixBuffer[1][index] + charBuff[1][index];
        }
        break;
      case 4:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[2][index] = CH[character - 0x20][index];
          matrixBuffer[2][index] = (matrixBuffer[2][index] <<= 5);
          charBuff[2][index] = matrixBuffer[2][index];
        }
        break;
      case 5:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[2][index] = CH[character - 0x20][index];
          matrixBuffer[2][index] = (matrixBuffer[2][index] <<= 1);
          matrixBuffer[2][index] = matrixBuffer[2][index] + charBuff[2][index];
        }
        break;
      case 6:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[3][index] = CH[character - 0x20][index];
          matrixBuffer[3][index] = (matrixBuffer[3][index] <<= 5);
          charBuff[3][index] = matrixBuffer[3][index];
        }
        break;
      case 7:
        for (index = 0; index < 5; index++)
        {
          matrixBuffer[3][index] = CH[character - 0x20][index];
          matrixBuffer[3][index] = (matrixBuffer[3][index] <<= 1);
          matrixBuffer[3][index] = matrixBuffer[3][index] + charBuff[3][index];
        }
        break;
    }

    //Fill whats left on the buffers with 0s (Erase this and the flip of colors stops working from 6th row to 8th)
    for (index = 5; index < 8; index++)
    {
      matrixBuffer[0][index] = B00000000;
      matrixBuffer[1][index] = B00000000;
      matrixBuffer[2][index] = B00000000;
      matrixBuffer[3][index] = B00000000;
    }

    limit ++;

  }
  else
  {
    limit = 0;
  }
}

void saveString(uint8_t *characters)
{
  while (*characters)
  {
    saveChar(*characters++);
  }
}

void shift(int direction)
{

  if (direction == 0)
  {
    int index;

    shiftBuff[0] = matrixBuffer[0][0];
    shiftBuff[1] = matrixBuffer[1][0];
    shiftBuff[2] = matrixBuffer[2][0];
    shiftBuff[3] = matrixBuffer[3][0];

    for (index = 0; index < 7; index++)
    {
      matrixBuffer[0][index] = matrixBuffer[0][index + 1];
      matrixBuffer[1][index] = matrixBuffer[1][index + 1];
      matrixBuffer[2][index] = matrixBuffer[2][index + 1];
      matrixBuffer[3][index] = matrixBuffer[3][index + 1];
    }

    matrixBuffer[0][7] = shiftBuff[0];
    matrixBuffer[1][7] = shiftBuff[1];
    matrixBuffer[2][7] = shiftBuff[2];
    matrixBuffer[3][7] = shiftBuff[3];
  }

  if (direction == 1)
  {
    int index;

    shiftBuff[0] = matrixBuffer[0][7];
    shiftBuff[1] = matrixBuffer[1][7];
    shiftBuff[2] = matrixBuffer[2][7];
    shiftBuff[3] = matrixBuffer[3][7];

    for (index = 7; index > 0; index--)
    {
      matrixBuffer[0][index] = matrixBuffer[0][index - 1];
      matrixBuffer[1][index] = matrixBuffer[1][index - 1];
      matrixBuffer[2][index] = matrixBuffer[2][index - 1];
      matrixBuffer[3][index] = matrixBuffer[3][index - 1];
    }

    matrixBuffer[0][0] = shiftBuff[0];
    matrixBuffer[1][0] = shiftBuff[1];
    matrixBuffer[2][0] = shiftBuff[2];
    matrixBuffer[3][0] = shiftBuff[3];
  }

}

void score(int points)
{
  char pt[5];

  sum = points + sum;

  sprintf(pt, "%d", sum);

  saveString("PT:");
  sendScreen();
  limit = 3;
  saveString(pt);
  shift(DOWN);
  sendScreen();
}

void animation(int type)
{
  int i;
  switch (type)
  {
    case 0:
    clearScreen();
    saveString("P       ");
    shift(DOWN);
    sendScreen();
    delay(100);
    saveString("PI      ");
    shift(DOWN);
    sendScreen();
    delay(100);
    saveString("PIN     ");
    shift(DOWN);
    sendScreen();
    delay(100);
    saveString("PINB    ");
    shift(DOWN);
    sendScreen();
    delay(100);
    saveString("PINBA   ");
    shift(DOWN);
    sendScreen();
    delay(100);
    saveString("PINBAL  ");
    shift(DOWN);
    sendScreen();
    delay(100);
    saveString("PINBALL ");
    shift(DOWN);
    sendScreen();
    delay(100);
    saveString("PINBALL$");
    shift(DOWN);
    sendScreen();
    delay(150);

    for(i=0;i<12;i++)
    {
    invertColors();
    sendScreen();
    delay(80);
    }
    break;

    case 1:
    clearScreen();
    saveString(" EXTRA");
    shift(DOWN);
    sendScreen();
    delay(700);
    saveString(" BALL $");
    shift(DOWN);
    sendScreen();
    delay(200);
    saveString(" BALL  ");
    shift(DOWN);
    sendScreen();
    delay(200);
    saveString(" BALL $");
    shift(DOWN);
    sendScreen();
    delay(200);
    saveString(" BALL  ");
    shift(DOWN);
    sendScreen();
    delay(200);
    saveString(" BALL $");
    shift(DOWN);
    sendScreen();
    delay(200);
    break;

    case 2:
    for(i=0;i<6;i++)
    {
    saveString("MULTI   ");
    shift(DOWN);
    sendScreen();
    delay(180);
    saveString("    BALL");
    shift(DOWN);
    sendScreen();
    delay(180);
    }
    break;

    case 3:
    clearScreen();
    for(i=0;i<6;i++)
    {
    saveString("  YOU");
    shift(DOWN);
    sendScreen();
    delay(150);
    saveString("   YOU");
    shift(DOWN);
    sendScreen();
    delay(150);
    }

    saveString("  LOSE");
    shift(DOWN);
    sendScreen();

    for(i=0;i<12;i++)
    {
      invertColors();
      sendScreen();
      delay(80);
    }
    break;
  }
}
