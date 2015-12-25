/**
 * Drum lights: Trigger-driven drum illumination
 * Alec Smecher, 2014
 * http://www.cassettepunk.com
 */

#include <Adafruit_NeoPixel.h>

/**
 * Pin configuration
 */
#define STRIP_PIN 4 // The digital pin # for the neopixel output
#define PIEZO_DIG_PIN 3 // The digital pin # for the piezo input
#define PIEZO_ANALOG_PIN A3 // The analog pin # for the piezo input

uint32_t Wheel(byte WheelPos, float intensity = 1);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, STRIP_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(PIEZO_DIG_PIN, INPUT);
  strip.begin();
}

unsigned char n=0; // Counter for colour wheel effect

void loop() {
  // Perform the pixel chase
  for (int i=strip.numPixels(); i>0; i--) {
    strip.setPixelColor(i, strip.getPixelColor(i-1));
  }

  // Set the first pixel using the current piezo value
  switch (random(400)) {
    case 0: // Random high-intensity snowdrop
      strip.setPixelColor(0, Wheel(random(256), 1));
      break;
    default: // Read from piezo
      strip.setPixelColor(0, Wheel(n++, analogRead(PIEZO_ANALOG_PIN)/1024.0));
      break;
  }

  // Update the strip
  strip.show();
  delay(20);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// This function adapted from Adafruit's demo code to add intensity.
uint32_t Wheel(byte WheelPos, float intensity) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color((255 - WheelPos * 3) * intensity, 0, WheelPos * 3 * intensity);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3 * intensity, (255 - WheelPos * 3) * intensity);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3 * intensity, (255 - WheelPos * 3) * intensity, 0);
  }
}

