#include "Arduboy2Ex.h"

Arduboy2Ext arduboy;

#include "game.h"

void setup() {
  arduboy.boot();
  arduboy.flashlight();
  arduboy.setFrameRate(60);
  arduboy.setTextColor(0);
  arduboy.setTextBackground(2);
}

void loop() {
  tick();
}

