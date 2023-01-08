#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <PinDef.h>
#include <VariablesGlobal.h>
#include <MenuStruct.h>
#include <Encoder.h>
#include <Menu.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

HardwareTimer timer(TIM2);

Encoder encoder(encA_Pin, encB_Pin, encC_Pin, encBtn_Pin);

Menu menu;

bool ledOn = false;

void TimerInterrupt()
{
  encoder.IrqEncoder();
  ledOn = !ledOn;
  digitalWrite(ledPin, ledOn);
}

void PrintLCD(String _input, int _line = 0)
{
  lcd.setCursor(0, _line);
  lcd.print(_input);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode (encA_Pin,INPUT_PULLUP);
  pinMode (encB_Pin,INPUT_PULLUP);
  pinMode (encC_Pin,OUTPUT);
  pinMode (encBtn_Pin,INPUT_PULLUP);

  timer.setPrescaleFactor(32000);
  timer.setOverflow(20);
  timer.attachInterrupt(TimerInterrupt);
  timer.refresh();
  timer.resume();

  lcd.init(); // initialize the lcd
              // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3, 0);
  PrintLCD("cnchobby.pl");
 // PrintLCD(menuItem[0].name,1);
  //PrintLCD(menuItem[1].name,2);

  encoder.On();

}
void loop()
{
  menu.Tick();
}