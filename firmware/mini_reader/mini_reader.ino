#define OLED_PWR1 5
#define OLED_PWR2 6
#define B_UP 3 //3      2
#define B_CENTER 4 //4  3
#define B_DOWN 2 //2    4


#define MODE_AMOUNT 3

#define SCREEN_SIZE_X 127
#define SCREEN_SIZE_Y 63
#define LETTER_SIZE_X 5
#define LETTER_SIZE_Y 8

#define ONE_SCREEN_LETTER_AMOUNT 148




#include <GyverOLED.h>
#include "EasyButton.h"
#include "Timer.h"
#include <EEPROM.h>
#include <directADC.h> 
#include <GyverPower.h>


EasyButton button_up(B_UP);
EasyButton button_center(B_CENTER);
EasyButton button_down(B_DOWN);
//GyverOLED<SSH1106_128x64, OLED_BUFFER> screen;
GyverOLED<SSD1306_128x64, OLED_BUFFER> screen;

#define FPSTR(pstr) (const __FlashStringHelper*)(pstr)

int8_t pointer = 0;

struct {
  uint8_t rightHand = true;
  uint8_t scale = 1;
  uint8_t brightness = 0;
  uint16_t internal_ref;
} settings;


uint8_t mode = 0; //main menuuint8_t mode = 0; //main menu

bool loadingFlag = false;

uint32_t eepromTimer;
bool eepromFlag;

Timer chargeTimer(7000);
uint8_t charge;

uint8_t chosenFile = 0;
char last_winner;
