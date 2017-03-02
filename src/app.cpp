#include <Arduino.h>
#include "Game.h"

Game *g;

unsigned long previousMillis = 0;
long interval = 700;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));

    g = new Game();
    g->setup();
}

void loop() {
    if(g->isCurrentPieceClashing()) {
        g->lost();
        while(1){}
    }

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;

        g->requestDown();
    }

    g->drawBoard();
}
