#include <Arduino.h>

class Menu
{
private:
    int index = 1; // zmienna indeksu tablicy menuItem
    int indexResult = -1;
    int lcdDisplayStart = 0;
    int lcdIndexStart = 0; // zmienna określa od którego indeksu tablicy menuItem ma być wyświetlana zawartość
                          
    void GetEncoder()
    {
        extern Encoder encoder;
        int _encValue = encoder.ReadEnc();

        if (_encValue == -1)
        {
            index--;
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
        if (encoder.ReadBtn() == 1)
        {
            MenuOk();
        }
    }

    void MenuOk()
    {
        if (menuItem[index].subMenu > 0)
        {
            if (menuItem[index].subMenu > index)
            {
                lcdIndexStart = menuItem[index].subMenu;
                index = lcdIndexStart + 1;
                lcdDisplayStart = lcdIndexStart;
            }
            else
            {

                lcdIndexStart = menuItem[index].subMenu / menuStep;
                lcdIndexStart *= menuStep;
                index = menuItem[index].subMenu;
                lcdDisplayStart = index - 1;
                if (lcdDisplayStart < 0)
                    lcdDisplayStart = 0;
            }
            Display();
        }
        else
        {
            indexResult = index;
        }
    }

public:
    String FillSpace(String _dataStr)
    {
        for (int x = _dataStr.length(); x < lcd_Columns; x++)
        {
            _dataStr += " ";
        }
        if (_dataStr.length() > lcd_Columns)
            _dataStr = _dataStr.substring(0, lcd_Columns);
        return _dataStr;
    }
    String lcdValue[lcd_Rows];

    void Display()
    {
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
        if (index == 0)
            index = 1;
        /* Generowanie lini */

        for (int x = 0; x < lcd_Rows; x++)
        {
            _dataStr = " ";

            if (index == lcdDisplayStart + x)
                _dataStr = ">";
            if (menuItem[lcdDisplayStart + x].subMenu >= 0 && lcdIndexStart != lcdDisplayStart + x)
            {
                _dataStr += "+";
            }
            else
            {
                _dataStr += " ";
            }

            _dataStr += menuItem[lcdDisplayStart + x].name;
            if (menuItem[lcdDisplayStart + x].subMenu != -2)
            {
                lcdValue[x] = FillSpace(_dataStr);
            }
            else
            {
                lcdValue[x] = FillSpace(" ");
            }
        }
    }

    int Tick()
    {
        GetEncoder();
        int _indexResult = indexResult;
        indexResult = -1;
        return _indexResult;
    }
};
