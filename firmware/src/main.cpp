#include "PCA9505.h"
#include <Arduino.h>
#include <Wire.h>

#define INT_PIN 0

PCA9505 left(0b000, Wire);
PCA9505 right(0b001, Wire);

bool interrupted = false;

void setup() {
    // put your setup code here, to run once:
    left.begin(SDA, SCL);
    right.begin(SDA, SCL);
    attachInterrupt(digitalPintToInterrupt(INT_PIN), interrupt, LOW);
}

void loop() {
    // put your main code here, to run repeatedly:
}

void interrupt() { interrupted = true; }