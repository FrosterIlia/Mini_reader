const char modeName1[] PROGMEM = "Play";
const char modeName2[] PROGMEM = "Read";
const char modeName3[] PROGMEM = "Settings";
const char modeName4[] PROGMEM = "REBOOT";

const char* const modeNames[] PROGMEM = {
  modeName1, modeName2, modeName3, modeName4
};


const uint8_t win_conditions[8][3] PROGMEM = {
  {1, 4, 7},
  {2, 5, 8},
  {3, 6, 9},
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {1, 5, 9},
  {3, 5, 7}
};

#define FILE_AMOUNT 10

const char file1[] PROGMEM = "This is a small pcb with microcontroller, battery, 3 buttons and oled screen, on which you can play some games and read any text, uploaded here)";
const char file2[] PROGMEM = "Some File 2 text";
const char file3[] PROGMEM = "Some File 3 text";
const char file4[] PROGMEM = "Some File 4 text";
const char file5[] PROGMEM = "Some File 5 text";
const char file6[] PROGMEM = "Some File 6 text";
const char file7[] PROGMEM = "Some File 7 text";
const char file8[] PROGMEM = "Some File 8 text";
const char file9[] PROGMEM = "Some File 9 text";
const char file10[] PROGMEM = "Some File 10 text";




const char* const files[] PROGMEM = {
  file1, file2, file3, file4, file5, file6, file7, file8, file9, file10
};

const char file1Name[] PROGMEM = "Intro";
const char file2Name[] PROGMEM = "File2";
const char file3Name[] PROGMEM = "File3";
const char file4Name[] PROGMEM = "File4";
const char file5Name[] PROGMEM = "File5";
const char file6Name[] PROGMEM = "File6";
const char file7Name[] PROGMEM = "File7";
const char file8Name[] PROGMEM = "File8";
const char file9Name[] PROGMEM = "File9";
const char file10Name[] PROGMEM = "File10";

const char* const fileNames[] PROGMEM = {
  file1Name, file2Name, file3Name, file4Name, file5Name, file6Name, file7Name, file8Name, file9Name, file10Name
};
