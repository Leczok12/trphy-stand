#include <Arduino.h>
#include <QuickButton.h>
#include <Adafruit_NeoPixel.h>

#include "data-manager/data-manager.hpp"
#include "effect.hpp"

#include "./config.hpp"

int R = 0;
int G = 0;
int B = 0;
int MODE = 0;
int OLD_MODE = 0;
int SPEED = 0;
bool POWER = false;

float transition = 0;
unsigned long old_time = 0;

bool dataSave = false;
DataManager dataManager(R, G, B, MODE, OLD_MODE, SPEED, POWER);

QuickButton sw_enable(PIN_SETTINGS_ENABLE);
QuickButton sw_1(PIN_SW1);
QuickButton sw_2(PIN_SW2);
QuickButton sw_3(PIN_SW3);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_LENGTH, PIN_LED, NEO_GRB + NEO_KHZ800);

void onClick(int id)
{
  if (transition > 0)
    return;

  switch (id)
  {
  case 0:
  {
    if (POWER)
    {
      POWER = false;
      OLD_MODE = MODE;
      MODE = 0;
    }
    else
    {
      POWER = true;
      MODE = OLD_MODE;
      OLD_MODE = 0;
    }
  }
  break;
  case 1:
  {
    if (!POWER)
      return;
    OLD_MODE = MODE;
    MODE++;
    if (MODE > LED_MODES)
      MODE = 1;
  }
  break;
  case 2:
  {
    if (!POWER)
      return;
    OLD_MODE = MODE;
    MODE--;
    if (MODE < 1)
      MODE = LED_MODES;
  }
  break;
  default:
    break;
  }
  transition = 100;
  dataSave = true;
}

void setup()
{
  pinMode(PIN_SETTINGS_R, INPUT);
  pinMode(PIN_SETTINGS_G, INPUT);
  pinMode(PIN_SETTINGS_B, INPUT);
  pinMode(PIN_SETTINGS_SPEED, INPUT);
  pinMode(PIN_SETTINGS_REF, INPUT);

  dataManager.read();
  strip.begin();

  sw_1.onClick([](int v)
               { onClick(0); });

  sw_2.onClick([](int v)
               { onClick(1); });

  sw_3.onClick([](int v)
               { onClick(2); });
}

int mainArr[LED_LENGTH];
int helpArr[LED_LENGTH];

void loop()
{
  sw_enable.loop();
  sw_1.loop();
  sw_2.loop();
  sw_3.loop();

  if (sw_enable.isPressed())
  {
    sw_enable.reset();
    dataSave = true;
    R = map(analogRead(PIN_SETTINGS_R), 0, 1023, 0, 255);
    G = map(analogRead(PIN_SETTINGS_G), 0, 1023, 0, 255);
    B = map(analogRead(PIN_SETTINGS_B), 0, 1023, 0, 255);
    SPEED = map(analogRead(PIN_SETTINGS_SPEED), 0, 1023, 0, 100);
  }
  else if (dataSave)
  {
    dataManager.write();
    dataSave = false;
  }

  if (old_time + SPEED < millis())
  {
    old_time = millis();

    switch (MODE)
    {
    case 0:
      effect::off(mainArr);
      break;
    case 1:
      effect::solid(mainArr);
      break;
    case 2:
      effect::wave(mainArr);
      break;
    case 3:
      effect::pulse(mainArr);
      break;
    default:
      break;
    }

    switch (OLD_MODE)
    {
    case 0:
      effect::off(helpArr);
      break;
    case 1:
      effect::solid(helpArr);
      break;
    case 2:
      effect::wave(helpArr);
      break;
    case 3:
      effect::pulse(helpArr);
      break;
    default:
      break;
    }

    strip.clear();

    if (transition > 0)
      transition -= 3;
    if (transition < 0)
      transition = 0;

    for (int i = 0; i < LED_LENGTH; i++)
    {
      strip.setPixelColor(i, strip.Color(
                                 (R * (mainArr[i] / 100.0) * (100.0 - transition) / 100.0) + (R * (helpArr[i] / 100.0) * transition / 100.0),
                                 (G * (mainArr[i] / 100.0) * (100.0 - transition) / 100.0) + (G * (helpArr[i] / 100.0) * transition / 100.0),
                                 (B * (mainArr[i] / 100.0) * (100.0 - transition) / 100.0) + (B * (helpArr[i] / 100.0) * transition / 100.0)));
    }
    strip.show();
  }
}