#include <Arduino.h>

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

const MenuItem  menuItem[]{
    {"Menu0", -1},        // 0
    {"Menu1", 10},        // 1
    {"Menu2", 20},        // 2
    {"Menu3", -1},        // 3
    {"Menu4", 30},        // 4
    {"Menu5", -1},        // 5
    {"", -2},             // 6
    {"", -2},             // 7
    {"", -2},             // 8
    {"", -2},             // 9
    {"SubMenu1_0", 40},   // 10
    {"SubMenu1_1", -1},   // 11
    {"SubMenu1_2", -1},   // 12
    {"", -2},             // 13
    {"", -2},             // 14
    {"", -2},             // 15
    {"", -2},             // 16
    {"", -2},             // 17
    {"", -2},             // 18
    {"", -2},             // 19
    {"SubMenu2_0", -1},   // 20
    {"SubMenu2_1", -1},   // 21
    {"SubMenu2_2", -1},   // 22
    {"SubMenu2_3", -1},   // 23
    {"SubMenu2_4", -1},   // 24
    {"SubMenu2_5", -1},   // 25
    {"SubMenu2_6", -1},   // 26
    {"SubMenu2_7", -1},   // 27
    {"SubMenu2_8", -1},   // 28
    {"SubMenu2_9", -1},   // 29
    {"SubMenu4_0", 50},   // 30
    {"SubMenu4_1", -1},   // 31
    {"SubMenu4_2", -1},   // 32
    {"SubMenu4_3", -1},   // 33
    {"SubMenu4_4", -1},   // 34
    {"SubMenu4_5", -1},   // 35
    {"", -2},             // 36
    {"", -2},             // 37
    {"", -2},             // 38
    {"", -2},             // 39
    {"SubMenu1_0_0", -1}, // 40
    {"SubMenu1_0_1", -1}, // 41
    {"SubMenu1_0_2", -1}, // 42
    {"SubMenu1_0_3", -1}, // 43
    {"SubMenu1_0_4", -1}, // 44
    {"SubMenu1_0_5", -1}, // 45
    {"SubMenu1_0_6", -1}, // 46
    {"", -2},             // 47
    {"", -2},             // 48
    {"", -2},             // 49
    {"SubMenu4_0_0", -1}, // 50
    {"SubMenu4_0_1", -1}, // 51
    {"SubMenu4_0_2", -1}, // 52
    {"SubMenu4_0_3", -1}, // 53
    {"SubMenu4_0_4", -1}, // 54
    {"SubMenu4_0_5", -1}, // 55
    {"", -2},             // 56
};