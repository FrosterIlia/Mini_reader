void setup() {
  power.hardwareDisable(PWR_UART0 | PWR_TIMER1 | PWR_TIMER2 | PWR_USB | PWR_SPI);
  attachInterrupt(0, wakeup, FALLING);
  switchScreen(true);
  randomSeed(analogRead(PIN_A0));
  screen.autoPrintln(true);
  screen.clear();
  adcInit();


  if (EEPROM.read(0) != 'w') {
    EEPROM.write(0, 'w');
    EEPROM.put(1, settings);
  }

  EEPROM.get(1, settings);
  charge = constrain(map(getVcc(), 2000, 3000, 0, 12), 0, 12);
  if (!settings.rightHand) {
    button_up.set_pin(button_up.get_pin() == B_UP ? B_DOWN : B_UP);
    button_down.set_pin(button_down.get_pin() == B_DOWN ? B_UP : B_DOWN);
  }



}
