void draw_menu() {

  screen.home();
  for (uint8_t i = 0; i <= MODE_AMOUNT; i++) {
    screen.setCursorXY(SCREEN_SIZE_Y + 1 - (strlen_P(pgm_read_word(modeNames + i)) * LETTER_SIZE_X * 2) / 2, i * LETTER_SIZE_Y * 2);
    screen.print(FPSTR(pgm_read_word(modeNames + i)));

  }

  screen.roundRect(0, pointer * LETTER_SIZE_Y * 2, SCREEN_SIZE_X, (pointer + 1) * LETTER_SIZE_Y * 2, OLED_STROKE);
  screen.update();
}

uint8_t get_x(uint8_t number) {
  while (number > 3) number -= 3;
  return number - 1;
}
uint8_t get_y( uint8_t number) {
  return (number - 1) / 3;
}

void toMainMenu() {
  if (button_center.isHolded()) {
    switchMode(0);
  }
}

void switchMode(uint8_t mode_number){
  loadingFlag = true;
  mode = mode_number;
}

uint16_t getVref(uint16_t vcc) {
  uint16_t buf = 0;
  ADC_startConvert();
  for (int i = 0; i < 8; i++) {
    buf += ADC_readWhenAvailable();
  }
  buf /= 8;
  return ((uint32_t)vcc * buf) / 1024;
}

void adcInit() {
  ADMUX = DEFAULT << 6 | 0b1110;      // Опорное - AVCC, вход АЦП к внутреннему опорному
  ADCSRA = 1 << ADEN | 0b101;         // Вкл. АЦП + средн. скорость АЦП
  for (uint8_t i = 0; i < 8; i++) {   // Несколько ложных преобразований - отфильтровать мусор
    ADCSRA |= 1 << ADSC;              // Запускаем преобразование
    while (ADCSRA & (1 << ADSC));     // Ждем окончания
  }
}

uint16_t getVcc() {
  ADCSRA |= 1 << ADSC;                // Запускаем преобразование
  while (ADCSRA & (1 << ADSC));       // Ждем
  return (settings.internal_ref * 1024UL) / ADC;
}

void drawBattery(uint8_t charge) {
  screen.rect(SCREEN_SIZE_X - 14, 0, SCREEN_SIZE_X - 1, 6, OLED_STROKE);
  screen.rect(SCREEN_SIZE_X - 14, 0, SCREEN_SIZE_X - (14 - charge), 6, OLED_FILL);
  screen.fastLineV(SCREEN_SIZE_X, 1, 5, OLED_FILL);

}

void switchScreen(bool state) {


  if (state) {
    pinMode(OLED_PWR1, OUTPUT);
    pinMode(OLED_PWR2, OUTPUT);
    digitalWrite(OLED_PWR1, state);
    digitalWrite(OLED_PWR2, state);
    screen.init();
    screen.setPower(true);
  }
  else {
    digitalWrite(OLED_PWR1, state);
    digitalWrite(OLED_PWR2, state);
    pinMode(OLED_PWR1, INPUT);
    pinMode(OLED_PWR2, INPUT);

    screen.setPower(false);
  }
}

void goToSleep() {
  switchScreen(false);
  power.sleep(SLEEP_FOREVER);
}
void wakeup() {
}
