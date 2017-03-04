#include <Arduino.h>
#include "Game.h"

Game *g;

unsigned long previousMillis = 0;
long interval = 500;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));

    pinMode(L_PIN, INPUT_PULLUP);
    pinMode(C_PIN, INPUT_PULLUP);
    pinMode(R_PIN, INPUT_PULLUP);

    g = new Game();
    g->setup();
}

int lastLeftState = HIGH;
int lastCenterState = HIGH;
int lastRightState = HIGH;

void loop() {
    if (digitalRead(L_PIN) == LOW && lastLeftState == HIGH){
        lastLeftState = LOW;
        g->requestLeft();
    }

    if (digitalRead(C_PIN) == LOW  && lastCenterState == HIGH){
        lastCenterState = LOW;
        g->requestRotate();
    }

    if (digitalRead(R_PIN) == LOW  && lastRightState == HIGH){
        lastRightState = LOW;
        g->requestRight();
    }

    lastLeftState = digitalRead(L_PIN);
    lastCenterState = digitalRead(C_PIN);
    lastRightState = digitalRead(R_PIN);


    if(g->isCurrentPieceClashing()) {
        g->lost();
        if(digitalRead(L_PIN) == LOW || digitalRead(C_PIN) == LOW || digitalRead(R_PIN) == LOW) {
            g->reset();
        }
        return;
    }

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;

        g->requestDown();
    }

    g->deleteFullRows();

    g->drawBoard();
}
