#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "config.hpp"

namespace effect
{
    inline void off(int *array)
    {
        for (size_t i = 0; i < LED_LENGTH; i++)
        {
            array[i] = 0;
        }
    }
    inline void solid(int *array)
    {
        for (size_t i = 0; i < LED_LENGTH; i++)
        {
            array[i] = 100;
        }
    }
    int wave_a = 0;
    inline void wave(int *array)
    {
        wave_a += 1;
        if (wave_a / 5 > LED_LENGTH)
        {
            wave_a = 0;
        }

        for (int i = 0; i < LED_LENGTH; i++)
            array[i] = 0;

        for (size_t i = 0; i < 5; i++)
        {
            int j = i + (wave_a / 5);
            if (j >= LED_LENGTH)
                j -= LED_LENGTH;

            switch (i)
            {
            case 0:
                array[j] = 15;
                break;
            case 1:
                array[j] = 50;
                break;
            case 2:
                array[j] = 100;
                break;
            case 3:
                array[j] = 50;
                break;
            case 4:
                array[j] = 15;
                break;
            
            default:
                break;
            }
        }
    }

    int pulse_a = 10;
    bool pulse_increase = true;
    inline void pulse(int *array)
    {
        if (pulse_increase)
            pulse_a++;
        else
            pulse_a--;

        if (pulse_a >= 100)
            pulse_increase = false;
        else if (pulse_a <= 10)
            pulse_increase = true;

        for (int i = 0; i < LED_LENGTH; i++)
            array[i] = pulse_a;
    }
}
