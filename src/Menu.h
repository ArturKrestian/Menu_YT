#include <Arduino.h>

class Menu
{
private:
    int index = 0;         // zmienna indeksu tablicy menuItem
    int lcdIndexStart = 0; // zmienna określa od którego indeksu tablicy menuItem ma być wyświetlana zawartość

    MenuValue MenuWork()
    {

        MenuValue _menuValue;

        return _menuValue;
    }
    void GetEncoder()
    {
        extern Encoder encoder;
        int _encValue = encoder.ReadEnc();

        if (_encValue == -1)
        {
            index = index - 1;
            if (index < 0)
                index = 0;
            Display();
        }
        if (_encValue == 1)
        {
            if (menuItem[index + 1].subMenu != -2)
            {
                index++;
                Display();
            }
        }
        if(encoder.ReadBtn()==3)
        {
            MenuOk();
        }
    }
    void  MenuOk()
    {
        if(menuItem[index].subMenu>0)
        {
            index=menuItem[index].subMenu;
            Display();
        }
    }

public:
    void Display()
    {
        extern void PrintLCD(String _input, int _line = 0);
        String _dataStr = "";
        int _menuLcdRows = lcd_Rows - 1;

        /*Wyliczenie indeksu startowego do wyświetlenia*/

        if (lcdIndexStart + _menuLcdRows - 1 < index)
        {
            lcdIndexStart=index-(_menuLcdRows - 1);
        }
        if (lcdIndexStart > index)
        {
            lcdIndexStart--;
            if (lcdIndexStart < 0)
                lcdIndexStart = 0;
        }

        /* Wyświetlenia nagłówka */

        _dataStr = " ";
        if (index < menuStep)
        {
            _dataStr = mainMenu;
        }
        PrintLCD(_dataStr, 0);

        /* Generowanie kolejnych lini */

        for (int x = _menuLcdRows; x > 0; x--)
        {
            _dataStr = " ";
            if (index == lcdIndexStart + (x - 1))
                _dataStr = ">";

            if (menuItem[lcdIndexStart + x - 1].subMenu == -2)
            {
                PrintLCD(_dataStr, x);
            }
            else
            {
                if(menuItem[lcdIndexStart + x - 1].subMenu>0) _dataStr+="+";
                _dataStr = _dataStr + menuItem[lcdIndexStart + x - 1].name + " " + String(index) + " " + String(lcdIndexStart) + " " + String(lcdIndexStart + x - 1);
                PrintLCD(_dataStr, x);
            }
        }
    }
    MenuValue Tick()
    {
        GetEncoder();
        return MenuWork();
    }
};
