void main_menu() {
  screen.setScale(2);
  draw_menu();


  if (button_up.isClick()) {
    if (--pointer < 0) pointer = MODE_AMOUNT;

  }
  if (button_down.isClick()) {
    if (++pointer > MODE_AMOUNT) pointer = 0;

  }
  if (button_center.isClick()) {
    switchMode(pointer + 1);
  }

}

#define POINTER_X 3



void pipka() {
  screen.setScale(2);
  static uint8_t x = 0;
  static uint8_t y = 0;
  static uint8_t filled_counter = 0;
  static int8_t field[3][3] = //1 = X, -1 = O
  { {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  };

  if (loadingFlag) {
    loadingFlag = false;
    x = 0;
    y = 0;
    filled_counter = 0;
    for (uint8_t i = 0; i < 3; i++) {
      for (uint8_t j = 0; j < 3; j++) {
        field[i][j] = 0;
      }
    }

  }

  //draw field
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      screen.setCursorXY(i * SCREEN_SIZE_X / 3 + (SCREEN_SIZE_X / 6) - LETTER_SIZE_X , SCREEN_SIZE_Y / 3 * j + 3);
      switch (field[i][j]) {
        case -1:
          screen.print(F("O"));
          break;
        case 0:
          break;
        case 1:
          screen.print(F("X"));
          break;
      }
    }
  }

  // draw grid
  screen.fastLineV(SCREEN_SIZE_X / 3, 0, SCREEN_SIZE_Y, OLED_FILL);
  screen.fastLineV(SCREEN_SIZE_X / 3 * 2, 0, SCREEN_SIZE_Y, OLED_FILL);
  screen.fastLineH(SCREEN_SIZE_Y / 3, 0, SCREEN_SIZE_X, OLED_FILL);
  screen.fastLineH(SCREEN_SIZE_Y / 3 * 2, 0, SCREEN_SIZE_X, OLED_FILL);



  screen.circle(POINTER_X + (x * SCREEN_SIZE_X / 3), SCREEN_SIZE_Y / 3 * y + (SCREEN_SIZE_Y / 6), 1, OLED_FILL); // draw pointer
  screen.update();
  if (button_up.isClick()) {
    y = y == 2 ? y = 0 : y + 1;
  }
  if (button_down.isClick()) {
    x = x == 2 ? x = 0 : x + 1;
  }
  if (button_center.isClick()) {
    if (field[x][y] == 0) {
      field[x][y] = 1;
      filled_counter += 1;

      int8_t x_enemy = random(0, 3);
      int8_t y_enemy = random(0, 3);
      while (field[x_enemy][y_enemy] != 0 && filled_counter <= 8) {
        x_enemy = random(0, 3);
        y_enemy = random(0, 3);
      }
      screen.update();
      field[x_enemy][y_enemy] = -1;
      filled_counter += 1;
    }

    for (uint8_t i = 0; i < 8; i++) {
      if (field[get_x(pgm_read_byte(&win_conditions[i][0]))][get_y(pgm_read_byte(&win_conditions[i][0]))] == field[get_x(pgm_read_byte(&win_conditions[i][1]))][get_y(pgm_read_byte(&win_conditions[i][1]))] &&
          field[get_x(pgm_read_byte(&win_conditions[i][1]))][get_y(pgm_read_byte(&win_conditions[i][1]))] == field[get_x(pgm_read_byte(&win_conditions[i][2]))][get_y(pgm_read_byte(&win_conditions[i][2]))] &&
          field[get_x(pgm_read_byte(&win_conditions[i][0]))][get_y(pgm_read_byte(&win_conditions[i][0]))] != 0
         ) {

        last_winner = field[get_x(pgm_read_byte(&win_conditions[i][0]))][get_y(pgm_read_byte(&win_conditions[i][0]))] == -1 ? 'O' : 'X';
        switchMode(10);

      }
    }
  }
}

void winner() {
  static bool restartQ = true;

  if (loadingFlag){
    loadingFlag = false;
    restartQ = true;
  }
  
  screen.setScale(2);

  screen.home();
  screen.print(F("WINNER "));
  screen.println(last_winner);
  screen.print(F("Restart?"));
  screen.setCursorXY(LETTER_SIZE_X * 2, LETTER_SIZE_Y * 5);
  screen.print(F("Yes"));
  screen.setCursorXY(LETTER_SIZE_X * 17, LETTER_SIZE_Y * 5);
  screen.print(F("No"));

  if (restartQ) {
    screen.rect(LETTER_SIZE_X * 2 - 3, LETTER_SIZE_Y * 5 - 3, LETTER_SIZE_X * 8 + 6, LETTER_SIZE_Y * 7 + 1, OLED_STROKE);
  }
  else {
    screen.rect(LETTER_SIZE_X * 17 - 3, LETTER_SIZE_Y * 5 - 3, LETTER_SIZE_X * 21 + 4, LETTER_SIZE_Y * 7 + 1, OLED_STROKE);
  }
  screen.update();

  if (button_up.isClick() || button_down.isClick()) restartQ = !restartQ;
  if (button_center.isClick()){
    switchMode(restartQ ? 1 : 0);
  }
}
#define POINTS_NUMBER 7

void fileSystem() {
  screen.setScale(1);

  for (uint8_t i = 0; i <= FILE_AMOUNT - 1; i++) {
    screen.setCursor(LETTER_SIZE_X + 1, i + 1);
    screen.print(FPSTR(pgm_read_word(fileNames + i + (chosenFile > 6 ? chosenFile - 6 : 0))));
  }
  screen.setCursor(0, chosenFile + 1 - (chosenFile > 6 ? chosenFile - 6 : 0));
  screen.print(F(">"));

  screen.update();

  if (button_up.isClick()) {
    chosenFile = constrain(chosenFile - 1, 0, FILE_AMOUNT - 1);

  }
  if (button_down.isClick()) {
    chosenFile = constrain(chosenFile + 1, 0, FILE_AMOUNT - 1);

  }
  if (button_center.isClick()) {
    switchMode(12);
  }

}

void reader() {
  static int8_t page = 0;
  screen.autoPrintln(true);
  screen.setScale(settings.scale);

  if (loadingFlag) {
    loadingFlag = false;
    page = 0;
  }

  uint8_t page_number = (uint16_t)strlen_P(pgm_read_word(files + chosenFile)) / ONE_SCREEN_LETTER_AMOUNT + 1;
  screen.setCursor(LETTER_SIZE_X * 6, 0);
  screen.print(F("Page "));
  screen.print(page + 1);
  screen.print(F(" of "));
  screen.print(page_number);

  screen.setCursor(0, 1);

  screen.print(FPSTR(pgm_read_word(files + chosenFile) + (ONE_SCREEN_LETTER_AMOUNT - 1) * page));

  screen.update();

  if (button_up.isClick()) {
    if (--page < 0) page = page_number - 1;
  }
  if (button_down.isClick()) {
    if (++page >= page_number) page = 0;
  }
  if (button_center.isClick()) {
    switchMode(2);
  }
}

void reboot() {
  asm volatile("jmp 0x0000");
}

#define MENU_SETTINGS 3
void preferences() {
  screen.autoPrintln(false);
  screen.setScale(1);
  static int8_t selected = 0;
  static bool chosen = false;
  if (loadingFlag) {
    loadingFlag = false;
    selected = 0;
  }

  screen.setCursor(0, 1);
  screen.println(F(" Right_hand:"));
  screen.println(F(" Scale:"));
  screen.println(F(" Brightness:"));
  screen.println(F(" Service"));

  screen.setCursor(SCREEN_SIZE_X - LETTER_SIZE_X * 4, 1);
  screen.print(settings.rightHand);
  screen.setCursor(SCREEN_SIZE_X - LETTER_SIZE_X * 4, 2);
  screen.print(settings.scale);
  screen.setCursor(SCREEN_SIZE_X - LETTER_SIZE_X * 4, 3);
  screen.print(settings.brightness);

  if (chosen) {
    screen.setCursor(SCREEN_SIZE_X - LETTER_SIZE_X, selected + 1);
    screen.print(F("<"));
  }
  else {
    screen.setCursor(0, selected + 1);
    screen.print(F(">"));

  }


  screen.update();

  if (button_center.isClick()) {
    chosen = !chosen;
    if (chosen && selected == 3) {
      switchMode(11);
    }
  }
  if (button_up.isClick()) {
    if (chosen) {
      switch (selected) {
        case 0:
          button_up.set_pin(button_up.get_pin() == B_UP ? B_DOWN : B_UP);
          button_down.set_pin(button_down.get_pin() == B_DOWN ? B_UP : B_DOWN);
          settings.rightHand = !settings.rightHand;
          break;
        case 1: settings.scale = constrain(settings.scale + 1, 1, 4); break;
        case 2: settings.brightness = constrain(settings.brightness + 1, 1, 255); break;

      }
      eepromFlag = true;
      eepromTimer = millis();
    }
    else {
      if (--selected < 0) selected = MENU_SETTINGS;
    }

  }
  if (button_down.isClick()) {
    if (chosen) {
      switch (selected) {
        case 0: settings.rightHand = !settings.rightHand;
          button_up.set_pin(button_up.get_pin() == B_UP ? B_DOWN : B_UP);
          button_down.set_pin(button_down.get_pin() == B_DOWN ? B_UP : B_DOWN); break;
        case 1: settings.scale = constrain(settings.scale - 1, 0, 4); break;
        case 2: settings.brightness = constrain(settings.brightness - 1, 0, 255); break;
      }
      eepromFlag = true;
      eepromTimer = millis();
    }
    else {
      if (++selected > MENU_SETTINGS) selected = 0;
    }
  }
  if (button_down.isHold() && selected == 2 && chosen) {

    settings.brightness = constrain(settings.brightness - 5, 0, 255);
  }
  if (button_up.isHold() && selected == 2 && chosen) {

    settings.brightness = constrain(settings.brightness + 5, 0, 255);
  }
}

void service() {
  static uint16_t vcc = 2810;
  static uint16_t internal = 0;
  screen.setScale(2);


  internal = getVref(vcc);


  screen.home();

  screen.print(F("VCC: "));
  screen.println(vcc);

  screen.print(F("Ref: "));
  screen.println(settings.internal_ref);

  screen.println(F("Charge: "));
  screen.print(constrain(map(getVcc(), 2000, 3000, 0, 12), 0, 12));
  screen.print(F(" = "));
  screen.print(getVcc());
  screen.print(F("v"));


  if (button_up.isClick() or button_up.isHold()) {
    vcc = constrain(vcc + 1, 2000, 3500);
  }
  if (button_down.isClick() or button_down.isHold()) {
    vcc = constrain(vcc - 1, 2000, 3500);
  }
  if (button_center.isClick()) {
    settings.internal_ref = internal;
    EEPROM.put(1, settings);

  }
  screen.update();
}
