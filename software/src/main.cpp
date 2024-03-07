#include <Arduino.h>
#include <QuickButton.h>
#include <Adafruit_NeoPixel.h>

#include "./config.hpp"

QuickButton enable(PIN_SETTINGS_ENABLE);
QuickButton sw1(PIN_SW1);
QuickButton sw2(PIN_SW2);
QuickButton sw3(PIN_SW3);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_LENGTH, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  strip.begin();
  pinMode(PIN_SETTINGS_R, INPUT);
  pinMode(PIN_SETTINGS_G, INPUT);
  pinMode(PIN_SETTINGS_B, INPUT);
  pinMode(PIN_SETTINGS_SPEED, INPUT);
  pinMode(PIN_SETTINGS_REF, INPUT);

  sw1.onClick([](int)
              { Serial.println("sw1"); });
  sw2.onClick([](int)
              { Serial.println("sw2"); });
  sw3.onClick([](int)
              { Serial.println("sw3"); });
}

void loop()
{
  sw1.loop();
  sw2.loop();
  sw3.loop();
  enable.loop();

  if (enable.isPressed())
  {
    enable.reset();
    int R = map(analogRead(PIN_SETTINGS_R), 0, analogRead(PIN_SETTINGS_REF), 0, 255);
    int G = map(analogRead(PIN_SETTINGS_G), 0, analogRead(PIN_SETTINGS_REF), 0, 255);
    int B = map(analogRead(PIN_SETTINGS_B), 0, analogRead(PIN_SETTINGS_REF), 0, 255);
    Serial.print("R -> ");
    Serial.print(R);
    Serial.print(" G -> ");
    Serial.print(G);
    Serial.print("B -> ");
    Serial.print(B);
    Serial.print("S -> ");
    Serial.print(map(analogRead(PIN_SETTINGS_SPEED), 0, analogRead(PIN_SETTINGS_REF), 0, 255));
    Serial.print("\n");
    for (int i = 0; i < LED_LENGTH; i++)
    {
      strip.setPixelColor(i, strip.Color(R, G, B));
    }
    strip.show();
    delay(500);
  }
}