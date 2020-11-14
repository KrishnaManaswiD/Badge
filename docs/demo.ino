/* Demo code to run on the badge
 *  Author: Krishna Manaswi Digumarti
 *  Date: Sep 2020
 *  Based on Adafruit's neopixel code
 */

#include <Adafruit_NeoPixel.h>

#define PIN 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

int redlED = 7;
int badgeLED = 13;
bool start = false;

void setup()
{
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  pinMode(redlED, OUTPUT); 
  pinMode(badgeLED, OUTPUT);
}

void loop()
{

  if (start == false)
  {
    digitalWrite(redlED, HIGH);   // turn the LED ON
    delay(500);                   // wait for half a second
    digitalWrite(redlED, LOW);    // turn the LED OFF
    delay(500); 
  
    rainbowCycle(20);
    start = true;
  }
  else
  {
    strip.clear();
    strip.show();
    delay(100);
    digitalWrite(badgeLED, HIGH);
  }
}

void rainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for(j=0; j<256*2; j++) // 2 cycles of all colors on wheel
  { 
    for(i=0; i< strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85)
  {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if(WheelPos < 170)
  {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else 
  {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
