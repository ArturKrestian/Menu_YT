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

void PrintLCD(String _input, int _line = 0)
{
  for (int x = _input.length(); x < lcd_Columns; x++)
  {
    _input = _input + " ";
  }
  lcd.setCursor(0, _line);
  lcd.print(_input);
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
}

void loop()
{
   menu.Tick();
}