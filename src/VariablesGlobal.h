#include <Arduino.h>

const int lcd_Rows=4;           // ilość lini wyświetlacza
const int lcd_Columns=20;       // ilość kolumn wyświetlacza

String mainLcdValue[lcd_Rows];

bool isMenuLock = false;
int menuSelected = -1;
bool isLcdRefresh = false;
int demoSpeed = 0;



