
void loop() {
  button_up.tick();
  button_center.tick();
  button_down.tick();

  screen.setContrast(settings.brightness);
  screen.flipV(!settings.rightHand);
  screen.flipH(!settings.rightHand);

  if (chargeTimer.isReady()) {
    charge = constrain(map(getVcc(), 2000, 3000, 0, 12), 0, 12);
  }

  screen.clear();
  drawBattery(charge);
  switch (mode) {
    case 0: main_menu(); break;
    case 1: pipka(); break;
    case 2: fileSystem(); break;
    case 3: preferences(); break;
    case 4: reboot(); break;
    case 10: winner(); break;
    case 11: service(); break;
    case 12: reader(); break;


  }
  if (millis() - eepromTimer >= 3000 && eepromFlag) {
    EEPROM.put(1, settings);
    eepromFlag = false;
  }

  if (button_up.isHold() && button_center.isHold()){
    goToSleep();
    switchScreen(true);
    delay(50);
  }
  toMainMenu();

}
