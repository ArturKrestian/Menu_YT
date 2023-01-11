#include <Arduino.h>

class Menu
{
private:
    int index = 0; // zmienna indeksu tablicy menuItem
    int lcdDisplayStart = 0;
    int lcdIndexStart = 0; // zmienna określa od którego indeksu tablicy menuItem ma być wyświetlana zawartość
                           // int submenuCountTmp = 0; // obecnagłębokość podmenu
    // bool isHeadSelect = false;

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
            if (index < lcdIndexStart)
            {
                index = lcdIndexStart;
            }
            Display();
        }
        if (_encValue == 1)
        {
            if (menuItem[index + 1].subMenu != -2 && (index + 1) < lcdIndexStart + menuStep)
            {
                index++;
                Display();
            }
        }
        if (encoder.ReadBtn() == 3)
        {
            MenuOk();
        }
    }
    void MenuOk()
    {
        extern void PrintLCD(String _input, int _line = 0);

        if (menuItem[index].subMenu > 0)
        {
            lcdIndexStart = menuItem[index].subMenu;
            lcdDisplayStart = lcdIndexStart;
            if (menuItem[index].subMenu > index)
            {
                index = lcdIndexStart + 1;
            }
            else
            {
                 index = lcdIndexStart;
            }
            Display();

            //   String _dataStr = (String)index + " " + (String)lcdDisplayStart + " " + (String)lcdIndexStart;
            //    PrintLCD(_dataStr, 3);
        }
    }

public:
    void Display()
    {
        extern void PrintLCD(String _input, int _line = 0);
        String _dataStr = "";

        /*Wyliczenie indeksu startowego do wyświetlenia*/

        if (lcdDisplayStart + lcd_Rows - 1 < index)
        {
            lcdDisplayStart = index - (lcd_Rows - 1);
        }
        if (lcdDisplayStart > index)
        {
            lcdDisplayStart--;
            if (lcdDisplayStart < lcdIndexStart)
                lcdDisplayStart = lcdIndexStart;
        }

        _dataStr = (String)lcdDisplayStart;
        PrintLCD(_dataStr);
        /* Generowanie kolejnych lini */

        for (int x = 0; x < lcd_Rows - 1; x++)
        {
            _dataStr = " ";

            if (index == lcdDisplayStart + x)
                _dataStr = ">";
            if (menuItem[lcdDisplayStart + x].subMenu > 0)
            {
                if (x != 0 || lcdIndexStart != lcdIndexStart)
                    _dataStr += "+";
            }

            _dataStr = _dataStr + menuItem[lcdDisplayStart + x].name + " " + String(lcdDisplayStart + x) + " " + String(index) + " " + String(menuItem[index].subMenu);
            if (menuItem[lcdDisplayStart + x].subMenu != -2)
                PrintLCD(_dataStr, x);
        }
        _dataStr = (String)index + " ";
        _dataStr += (String)lcdDisplayStart + " ";
        _dataStr += (String)lcdIndexStart + " ";
        _dataStr += (String)menuItem[index].subMenu;
        PrintLCD(_dataStr, 3);
    }
    MenuValue Tick()
    {
        GetEncoder();
        return MenuWork();
    }
};
