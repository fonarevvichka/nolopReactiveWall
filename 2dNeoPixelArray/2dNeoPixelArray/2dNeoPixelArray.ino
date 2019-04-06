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
        pixelArray[y][x] = strip.Color(10, 10, 10);
    }
  }
  pinMode(13, OUTPUT);
  updateDisplay();
}

int counter = 0;
int data = -1;
int dataa, datab;
void loop() {
  if (data == -1) {
    counter = 0;
  }
  String tempa, tempb, tempc;
  if (Serial.available()) {
    tempa = Serial.read();
    data = tempa.toInt();
    tempb = Serial.read();
    dataa = tempb.toInt();
    tempc = Serial.read();
    datab = tempc.toInt();
    if (data != -1) {
      setPixel(strip.Color(data,dataa,datab),counter / (GRID_SIZE_Y-1), counter % (GRID_SIZE_Y));
    }

    counter++;
  }
  delay(1);
}

static void updateDisplay() {
  for (int x = 0; x < GRID_SIZE_X; x++) {
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        setPixel(pixelArray[y][x], x, y);
    }
  }
  strip.show();
}

static void setPixel(uint32_t color, int x, int y) {
  int convertedPixelNum = 0;

  if (y % 2 == 0) { //even row
    convertedPixelNum = x + GRID_SIZE_X * y;
  } else {
    convertedPixelNum = (GRID_SIZE_X -(x+1)) + GRID_SIZE_X * y;
  }
  strip.setPixelColor(convertedPixelNum, color);
  strip.show();
}
