#include <Arduino.h>
#include <FastLED.h>
//
//  "Pacifica"
//  Gentle, blue-green ocean waves.
//  December 2019, Mark Kriegsman and Mary Corey March.
//  For Dan.
//

#define FASTLED_ALLOW_INTERRUPTS 0

FASTLED_USING_NAMESPACE
// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    17
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    600
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         160
#define FRAMES_PER_SECOND  120

void nextPattern();
void rainbow();
void rainbowWithGlitter();
void addGlitter( fract8 chanceOfGlitter);
void confetti();
void whiteConfetti();
void redConfetti();
void blueConfetti();
void purpleConfetti();
void greenConfetti();
void sinelon();
void redSinelon();
void bpm();
void juggle();
void glitter();
void redSnake();
void blueSnake();
void purpleSnake();
void greenSnake();


void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
// SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
SimplePatternList gPatterns = {redSnake, redConfetti, greenSnake, greenConfetti, blueSnake, blueConfetti, purpleSnake, purpleConfetti, whiteConfetti, confetti};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint16_t gPos = 0; // absolute position
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates

  
  EVERY_N_MILLISECONDS( 12 ) {
    if ( gPos <= NUM_LEDS){gPos++; } // slowly increase absolute position
    gHue++;
  }

  EVERY_N_SECONDS( 23 ) { 
    nextPattern();
    gPos = 0;
  } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void glitter()
{
  addGlitter(20);
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void redSnake() 
{
  // run from start to finish and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 15);
  leds[gPos] += CHSV( 1, 200, 255);
  int pos = random16(gPos);
  leds[pos] += CHSV( 1 + random8(16), 200, 255); //redish
}

void greenSnake() 
{
  // run from start to finish and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 15);
  leds[gPos] += CHSV( 96, 200, 255);
  int pos = random16(gPos);
  leds[pos] += CHSV( 96 + random8(32), 200, 255); //greenish
}

void blueSnake() 
{
  // run from start to finish and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 15);
  leds[gPos] += CHSV( 136, 200, 255);
  int pos = random16(gPos);
  leds[pos] += CHSV( 136 + random8(32), 200, 255); //blueish
}

void purpleSnake() 
{
  // run from start to finish and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 15);
  leds[gPos] += CHSV( 192, 200, 255);
  int pos = random16(gPos);
  leds[pos] += CHSV( 192 + random8(32), 200, 255); //blueish
}

void whiteConfetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  //leds[pos] += CHSV( gHue + random8(64), 200, 255);
  leds[pos] += CRGB::White;
}

void redConfetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( 1 + random8(16), 200, 255); //reddish
}

void greenConfetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( 96 + random8(32), 200, 255); //greenish
}

void blueConfetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( 136 + random8(32), 200, 255); //blueish
}

void purpleConfetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( 192 + random8(32), 200, 255); //purpleish
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void redSinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = beatsin16( 1, 0, NUM_LEDS);
  leds[pos] += CHSV( 1, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}