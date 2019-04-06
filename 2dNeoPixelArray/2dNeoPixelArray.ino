// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN      6
#define GRID_SIZE_X 6
#define GRID_SIZE_Y 10
#define N_LEDS 60
#define SERIAL_RX 0
#define SERIAL_TX 1

uint32_t pixelArray[GRID_SIZE_Y][GRID_SIZE_X];
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(124); //max is 255

  for (int x = 0; x < GRID_SIZE_X; x++) {
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        pixelArray[y][x] = strip.Color(x * 10, y*10, 0);
    }
  }
  updateDisplay();

}

void loop() {
  char temp;
  if (Serial.available()) {
    temp = Serial.read();
  }
  if (temp == 'a') {
      setPixel(strip.Color(0, 0, 255), 2, 4);
  }
//  setPixel(strip.Color(0, 0, 255), 2, 4);
//  updateDisplay();
  
  delay(25);
}

static void updateDisplay() {
  for (int x = 0; x < GRID_SIZE_X; x++) {
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        setPixel(pixelArray[y][x], x, y);
    }
  }
  strip.show();
}
//static void chase(uint32_t c) {
//  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
//      strip.setPixelColor(i  , c); // Draw new pixel
//      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
//      strip.show();
//      delay(25);
//  }
//}

static void setPixel(uint32_t color, int x, int y) {
  int convertedPixelNum = 0;

  if (y % 2 == 0) { //even row
    convertedPixelNum = x + GRID_SIZE_X * y;
  } else {
    convertedPixelNum = (GRID_SIZE_X - (x+1)) + GRID_SIZE_X * y;
  }
  strip.setPixelColor(convertedPixelNum, color);
  strip.show();
}
