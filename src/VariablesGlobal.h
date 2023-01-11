#include <Arduino.h>

const int lcd_Rows=4;           // ilość lini wyświetlacza
const int lcd_Columns=20;       // ilość kolumn wyświetlacza

//const int submenuCount=5;       // głębokość podmenu
//int lastIndexMenu[submenuCount];// tablice z indeksami menu poziom wyższy


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

