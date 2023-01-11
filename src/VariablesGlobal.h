#include <Arduino.h>

const int lcd_Rows=4;           // ilość lini wyświetlacza
const int lcd_Columns=20;       // ilość kolumn wyświetlacza

String mainLcdValue[4];
bool isMenuLock = false;
int menuSelected = -1;
bool isLcdRefresh = false;
int demoSpeed = 0;

volatile int sec = 0;
volatile int miliSec = 0;

struct MenuItem
{
    const char * name;
    int subMenu;
};

struct MenuValue
{
    String name[4];
    int indexSelect;
    bool isOk;
    bool isDisplay;
};

