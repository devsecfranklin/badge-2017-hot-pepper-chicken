
/*
     ____  _           _       _         _     _
    / __ \(_)_ __   __| |_   _| |__  ___(_) __| | ___  ___
   / / _` | | '_ \ / _` | | | | '_ \/ __| |/ _` |/ _ \/ __|
  | | (_| | | | | | (_| | |_| | |_) \__ \ | (_| |  __/\__ \
   \ \__,_|_|_| |_|\__,_|\__, |_.__/|___/_|\__,_|\___||___/
    \____/               |___/

                H dlh dcaego uz aego ak.vol,vohs

   ESP8266-12E
   Pimoroni Blinkt

   D1 -> SCL on OLED
   D2 -> SDA on OLED
   D7 -> 
   D8 -> 
                
*/
#include <Wire.h>
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "ESP8266WiFi.h"

/* By default, the APA102 library uses pinMode and digitalWrite
   to write to the LEDs, which works on all Arduino-compatible
   boards but might be slow.  If you have a board supported by
   the FastGPIO library and want faster LED updates, then install
   the FastGPIO library and uncomment the next two lines: */
// #include <FastGPIO.h>
// #define APA102_USE_FAST_GPIO

#include <APA102.h>

SSD1306 display(0x3C, D2, D1);

// Define which pins to use for Blinkt strip.
const uint8_t dataPin = D8;
const uint8_t clockPin = D7;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;


// Set the number of LEDs to control.
const uint16_t ledCount = 8;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

// Set the brightness to use (the maximum is 31).
const uint8_t brightness = 1;

void setup() {
  //Serial.begin(115200);                   // diagnostic channel
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Judy's Kitchen");
  display.drawString(0, 10, "Hot Pepper Chicken");
  display.display();  
}

// This function sends a white color with the specified power,
// which should be between 0 and 7905.
void sendWhite(uint16_t power)
{
  // Choose the lowest possible 5-bit brightness that will work.
  uint8_t brightness5Bit = 1;
  while (brightness5Bit * 255 < power && brightness5Bit < 31)
  {
    brightness5Bit++;
  }

  // Uncomment this line to simulate an LED strip that does not
  // have the extra 5-bit brightness register.  You will notice
  // that roughly the first third of the LED strip turns off
  // because the brightness8Bit equals zero.
  //brightness = 31;

  // Set brightness8Bit to be power divided by brightness5Bit,
  // rounded to the nearest whole number.
  uint8_t brightness8Bit = (power + (brightness5Bit / 2)) / brightness5Bit;

  // Send the white color to the LED strip.  At this point,
  // brightness8Bit multiplied by brightness5Bit should be
  // approximately equal to power.
  ledStrip.sendColor(brightness8Bit, brightness8Bit, brightness8Bit, brightness5Bit);
}

/* Converts a color from HSV to RGB.
   h is hue, as a number between 0 and 360.
   s is the saturation, as a number between 0 and 255.
   v is the value, as a number between 0 and 255. */
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  return rgb_color(r, g, b);
}


void loop() {
  uint8_t time = millis() >> 4;
  for (uint16_t i = 0; i < ledCount; i++)
  {
    uint8_t p = time - i * 3;
    colors[i] = hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
  }
  ledStrip.write(colors, ledCount, brightness);
}
/**
   The MIT License (MIT)

   Copyright (c) 2016 by Daniel Eichhorn

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

*/
