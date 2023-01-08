#include <Arduino.h>

const int lcd_Rows=4;
const int lcd_Columns=20;

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

