/*
 * Uses custom letters and functions to drive 4 8x8 Led matrix
 * displays.
 *
 * Created by Yvan Ramirez, December 30, 2019
 *
 */


#ifdef __cplusplus
extern "C" {
#endif

//SPI CS PIN
#define CS_PIN 53

//Number of 8x8 screens
#define SCREEN_NUMBER 4

//Defines for the shift
#define UP 0
#define DOWN 1

//Defines for the animations
#define START 0
#define EXTRABALL 1
#define MULTIBALL 2
#define GAMEOVER 3

static const uint8_t CH[][5] =
{
  {B000, B000, B000, B000, B000},      // SPACE
  {B010, B010, B010, B000, B010}, // !
  {B101, B101, B000, B000, B000}, // "
  {B101, B111, B101, B111, B101}, // #
  {B000, B111, B111, B111, B000}, // $
  {B101, B001, B010, B100, B101}, // %
  {B010, B101, B010, B101, B111}, // &
  {B010, B010, B000, B000, B000}, // '
  {B011, B100, B100, B100, B011}, // (
  {B110, B001, B001, B001, B110}, // )
  {B101, B010, B101, B000, B000}, // *
  {B000, B010, B111, B010, B000}, // +
  {B000, B000, B000, B010, B100}, // ,
  {B000, B000, B111, B000, B000}, // -
  {B000, B000, B000, B000, B010}, // .
  {B001, B001, B010, B010, B100}, // /
  {B010, B101, B101, B101, B010}, // 0
  {B010, B110, B010, B010, B111}, // 1
  {B110, B001, B010, B100, B111}, // 2
  {B110, B001, B110, B001, B110}, // 3
  {B101, B101, B111, B001, B001}, // 4
  {B111, B100, B110, B001, B110}, // 5
  {B111, B100, B111, B101, B111}, // 6
  {B111, B001, B010, B100, B100}, // 7
  {B111, B101, B111, B101, B111}, // 8
  {B111, B101, B111, B001, B001}, // 9
  {B000, B010, B000, B010, B000}, // :
  {B000, B010, B000, B010, B100}, // ;
  {B001, B010, B100, B010, B001}, // <
  {B000, B111, B000, B111, B000}, // =
  {B100, B010, B001, B010, B100}, // >
  {B110, B001, B010, B000, B010}, // ?
  {B110, B001, B111, B101, B110}, // @
  {B010, B101, B111, B101, B101}, // A
  {B110, B101, B110, B101, B110}, // B
  {B111, B100, B100, B100, B111}, // C
  {B110, B101, B101, B101, B110}, // D
  {B111, B100, B110, B100, B111}, // E
  {B111, B100, B110, B100, B100}, // F
  {B111, B100, B111, B101, B110}, // G
  {B101, B101, B111, B101, B101}, // H
  {B111, B010, B010, B010, B111}, // I
  {B111, B010, B010, B010, B110}, // J
  {B101, B101, B110, B101, B101}, // K
  {B100, B100, B100, B100, B111}, // L
  {B101, B111, B111, B101, B101}, // M
  {B110, B101, B101, B101, B101}, // N
  {B111, B101, B101, B101, B111}, // O
  {B111, B101, B111, B100, B100}, // P
  {B111, B101, B101, B110, B001}, // Q
  {B110, B101, B110, B101, B101}, // R
  {B111, B100, B111, B001, B111}, // S
  {B111, B010, B010, B010, B010}, // T
  {B101, B101, B101, B101, B111}, // U
  {B101, B101, B101, B101, B010}, // V
  {B101, B101, B111, B111, B101}, // W
  {B101, B101, B010, B101, B101}, // X
  {B101, B101, B010, B010, B010}, // Y
  {B111, B001, B010, B100, B111}, // Z
  {B111, B100, B100, B100, B111}, // [
  {B101, B101, B010, B111, B010}, // ¥
  {B111, B001, B001, B001, B111}, // ]
  {B010, B101, B000, B000, B000}, // ^
  {B000, B000, B000, B000, B111}, // _
  {B100, B010, B000, B000, B000}, // `
  {B010, B101, B101, B101, B011}, // a
  {B100, B100, B110, B101, B110}, // b
  {B011, B100, B100, B100, B011}, // c
  {B001, B001, B011, B101, B011}, // d
  {B010, B101, B111, B100, B011}, // e
  {B110, B100, B110, B100, B100}, // f
  {B010, B101, B011, B001, B110}, // g
  {B100, B100, B110, B101, B101}, // h
  {B010, B000, B010, B010, B010}, // i
  {B001, B000, B001, B101, B010}, // j
  {B100, B101, B110, B111, B101}, // k
  {B010, B010, B010, B010, B010}, // l
  {B101, B111, B111, B101, B101}, // m
  {B100, B110, B101, B101, B101}, // n
  {B010, B101, B101, B101, B010}, // o
  {B110, B101, B110, B100, B100}, // p
  {B011, B101, B011, B001, B001}, // q
  {B100, B111, B101, B100, B100}, // r
  {B011, B100, B010, B001, B110}, // s
  {B100, B110, B100, B101, B010}, // t
  {B101, B101, B101, B101, B011}, // u
  {B101, B101, B101, B101, B010}, // v
  {B101, B101, B111, B111, B101}, // w
  {B101, B101, B010, B101, B101}, // x
  {B101, B101, B011, B001, B010}, // y
  {B110, B001, B010, B100, B011}, // z
  {B011, B010, B100, B010, B011}, // {
  {B000, B010, B010, B010, B000}, // |
  {B110, B010, B001, B010, B110}, // }
};

void writeSPI(uint8_t address, uint8_t value);

void initScreen();
void clearScreen();
void sendScreen();
void invertColors();

void saveChar(uint8_t character);
void saveString(uint8_t *characters);

void shift(int direc);
void score(int points);
void animation(int type);


#ifdef __cplusplus
}
#endif
