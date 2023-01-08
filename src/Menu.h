#include <Arduino.h>

class Menu
{
private:
    int index=0;

    MenuValue MenuWork()
    {
        extern Encoder encoder;
        MenuValue _menuValue;




        return _menuValue;
    }

public:
    MenuValue Tick()
    {
        return MenuWork();
    }
};
