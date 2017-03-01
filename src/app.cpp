#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#define ROWS 10
#define COLUMNS 7

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(ROWS, COLUMNS, 6,
                                               NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                                               NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

void setup() {
    // put your setup code here, to run once:


    matrix.begin();
    matrix.setBrightness(30);
    matrix.show(); // Initialize all pixels to 'off'
}

void loop() {
    uint32_t red = matrix.Color(0, 255, 0);
    //matrix.drawPixel(0, 0, red);
    //matrix.show();


    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            matrix.fillScreen(0);
            matrix.drawPixel(r, c, red);
            matrix.show();
            delay(100);
        }
    }
}
