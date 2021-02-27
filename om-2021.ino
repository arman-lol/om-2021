// Adafruit_NeoMatrix example for single NeoPixel Shield.
// By Marc MERLIN <marc_soft@merlins.org>
// Contains code (c) Adafruit, license BSD

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

const int BUTTON_PIN = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// ESP8266 has an I2S neopixel library which can only use pin RX
// so it's recommended to use the same pin with Neopixel to avoid
// rewiring when changing libs
#ifdef ESP8266
#define PIN RX
#endif

#define BM32

#ifdef BM32
#include "google32.h"
// Anything with black does not look so good with the naked eye (better on pictures)
//#include "linux32.h"
#endif

// Max is 255, 32 is a conservative value to not overload
// a USB power supply (500mA) for 12x12 pixels.
#define BRIGHTNESS 32

// MATRIX DECLARATION:
// Parameter 1 = width of EACH NEOPIXEL MATRIX (not total display)
// Parameter 2 = height of each matrix
// Parameter 3 = number of matrices arranged horizontally
// Parameter 4 = number of matrices arranged vertically
// Parameter 5 = pin number (most are valid)
// Parameter 6 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the FIRST MATRIX; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs WITHIN EACH MATRIX are
//     arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns WITHIN
//     EACH MATRIX proceed in the same order, or alternate lines reverse
//     direction; pick one.
//   NEO_TILE_TOP, NEO_TILE_BOTTOM, NEO_TILE_LEFT, NEO_TILE_RIGHT:
//     Position of the FIRST MATRIX (tile) in the OVERALL DISPLAY; pick
//     two, e.g. NEO_TILE_TOP + NEO_TILE_LEFT for the top-left corner.
//   NEO_TILE_ROWS, NEO_TILE_COLUMNS: the matrices in the OVERALL DISPLAY
//     are arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_TILE_PROGRESSIVE, NEO_TILE_ZIGZAG: the ROWS/COLUMS OF MATRICES
//     (tiles) in the OVERALL DISPLAY proceed in the same order for every
//     line, or alternate lines reverse direction; pick one.  When using
//     zig-zag order, the orientation of the matrices in alternate rows
//     will be rotated 180 degrees (this is normal -- simplifies wiring).
//   See example below for these values in action.
// Parameter 7 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 pixels)
//   NEO_GRB     Pixels are wired for GRB bitstream (v2 pixels)
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA v1 pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)


// Define full matrix width and height.
#define mw 8
#define mh 32
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(8, mh, 
  mw/8, 1, 
  PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG + 
// progressive vs zigzag makes no difference for a 4 arrays next to one another
    NEO_TILE_TOP + NEO_TILE_LEFT +  NEO_TILE_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800 );


// This could also be defined as matrix->color(255,0,0) but those defines
// are meant to work for adafruit_gfx backends that are lacking color()
#define LED_BLACK		0

#define LED_RED_VERYLOW 	(3 <<  11)
#define LED_RED_LOW 		(7 <<  11)
#define LED_RED_MEDIUM 		(15 << 11)
#define LED_RED_HIGH 		(31 << 11)

#define LED_GREEN_VERYLOW	(1 <<  5)   
#define LED_GREEN_LOW 		(15 << 5)  
#define LED_GREEN_MEDIUM 	(31 << 5)  
#define LED_GREEN_HIGH 		(63 << 5)  

#define LED_BLUE_VERYLOW	3
#define LED_BLUE_LOW 		7
#define LED_BLUE_MEDIUM 	15
#define LED_BLUE_HIGH 		31

#define LED_ORANGE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW		(LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW	(LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW		(LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM	(LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH		(LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW	(LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW		(LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM		(LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH		(LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW		(LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)

static const uint8_t PROGMEM
    mono_bmp[][8] =
    {
	{   // 0: checkered 1
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
			},

	{   // 1: checkered 2
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
			},

	{   // 2: smiley
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10100101,
	    B10011001,
	    B01000010,
	    B00111100 },

	{   // 3: neutral
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10111101,
	    B10000001,
	    B01000010,
	    B00111100 },

	{   // 4; frowny
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10011001,
	    B10100101,
	    B01000010,
	    B00111100 },

{   // 5; laugh_part_1
      B00111100,
      B01000010,
      B10101001,
      B10000101,
      B10000101,
      B10101001,
      B01000010,
      B00111100 },
      
{   // 6; laugh_part_2
      B00111100,
      B01000010,
      B10101101,
      B10000011,
      B10000011,
      B10101101,
      B01000010,
      B00111100 },      
    };



void display_static_bitmap(uint8_t bmp_num, uint16_t color) { 
    uint16_t bmx = 0, bmy = 24;

    // Clear the space under the bitmap that will be drawn as
    // drawing a single color pixmap does not write over pixels
    // that are nul, and leaves the data that was underneath
    matrix->fillRect(bmx,bmy, bmx+8,bmy+8, LED_BLACK);
    matrix->drawBitmap(bmx, bmy, mono_bmp[bmp_num], 8, 8, color);
    matrix->show();
}

void smile_with_rotating_text()
{
    
    matrix->setTextSize(1);
    matrix->setTextColor(LED_GREEN_HIGH);
    
    for (int16_t x=32; x>=-24; x--)
    {
        matrix->clear();
        matrix->setRotation(3);
        matrix->setCursor(x, 0);
        matrix->print("Smile");
        matrix->setRotation(0);
        display_static_bitmap(5, LED_GREEN_HIGH);
        matrix->show();
  // note that on a big array the refresh rate from show() will be slow enough that
  // the delay become irrelevant. This is already true on a 32x32 array.
        delay(50);
    }
}

void laughing_with_text()
{
    matrix->setRotation(3);
    matrix->setCursor(12, 0);
    matrix->print("LOL");
    matrix->show();
    matrix->setRotation(0);
    
    for (uint8_t i=0; i<25; i++)
    {
      display_static_bitmap(5, LED_GREEN_HIGH);
      delay(200);
      display_static_bitmap(6, LED_GREEN_HIGH);
      delay(200);
    }
}

void loop() {

    buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == HIGH)
    {
        smile_with_rotating_text();
        delay(8000);
        matrix->clear();
        matrix->show();

        // Sleep between slides
        delay(1000);
    
        laughing_with_text();
        
        delay(2000);
        matrix->clear();
        matrix->show();
        
        delay(1000);
    }
    
    delay(50);
}

void setup() {
    Serial.begin(115200);

    // initialize the pushbutton pin as an input:
    pinMode(BUTTON_PIN, INPUT);
  
    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(BRIGHTNESS);  
    // Test full bright of all LEDs. If brightness is too high
    // for your current limit (i.e. USB), decrease it.
    matrix->show();
 
    matrix->clear();
}

// vim:sts=4:sw=4
