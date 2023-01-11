#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <PinDef.h>
#include <VariablesGlobal.h>
#include <MenuStruct.h>
#include <Encoder.h>
#include <Menu.h>

LiquidCrystal_I2C lcd(0x27, lcd_Columns, lcd_Rows);

HardwareTimer timer(TIM2);

Encoder encoder(encA_Pin, encB_Pin, encC_Pin, encBtn_Pin);

Menu menu;

void TimerInterrupt()
{
  encoder.IrqEncoder();
}

void PrintLCD(String _input, int _row = 0)
{
  _input = menu.FillSpace(_input);
  lcd.setCursor(0, _row);
  lcd.print(_input);
}

void PrintLCDTick()
{
  if (isMenuLock == true)
  {
    isLcdRefresh = true;
    return;
  }
  for (int x = 0; x < lcd_Rows; x++)
  {

    if (mainLcdValue[x] != menu.lcdValue[x] || isLcdRefresh == true)
    {
      mainLcdValue[x] = menu.lcdValue[x];
      menu.lcdValue[x];
      lcd.setCursor(0, x);
      lcd.print(mainLcdValue[x]);
    }
  }
  isLcdRefresh = false;
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(encA_Pin, INPUT_PULLUP);
  pinMode(encB_Pin, INPUT_PULLUP);
  pinMode(encC_Pin, OUTPUT);
  pinMode(encBtn_Pin, INPUT_PULLUP);

  timer.setPrescaleFactor(3200);
  timer.setOverflow(10);
  timer.attachInterrupt(TimerInterrupt);
  timer.refresh();
  timer.resume();

  lcd.init();
  lcd.backlight();

  encoder.On();
  menu.Display();
  // PrintLCD(menu.lcdValue[0]);
  //  menu.lcdValue[0];

  //  lcd.setCursor(0, 0);
  //  lcd.print("_input");
  // digitalWrite(ledPin,true);
}

void Demo1()
{
  int _enc = encoder.ReadEnc();
  if (_enc != 0)
  {
    demoSpeed += _enc;
    PrintLCD("", 0);
    PrintLCD("Speed=" + (String)demoSpeed, 1);
    PrintLCD("", 2);
    PrintLCD("", 3);
  }
}

void MenuDecode()
{
  switch (menuSelected)
  {
  case 0:
  {
    break;
  }
  case 6:
  {
    if (!isMenuLock)
    {
      isMenuLock = true;
    }
    else
    {
      Demo1();
      if (encoder.ReadBtn() == 1)
      {
        isMenuLock = false;
        menuSelected = -1;
      }
    }
    break;
  }
  default:
  {

    break;
  }
  }
}

void loop()
{

  if (isMenuLock == false)
    menuSelected = menu.Tick();
  MenuDecode();
  PrintLCDTick();
}