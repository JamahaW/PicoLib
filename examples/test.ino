#include <Arduino.h>
#include <PicoOLED.hpp>

pico::OLED sc;

void setup() {
  sc.init();
  sc.setAutoNextLine(true);
}

pico::Font fonts[] = {
  pico::Font::SINGLE,
  pico::Font::SINGLE_BOLD,
  pico::Font::DOUBLE_THIN,
  pico::Font::DOUBLE,
  pico::Font::DOUBLE_BOLD
};

int i = 0;

void loop() {
  sc.setFont(fonts[i++]);
  
  if (i == 5) i = 0;

  sc.clear();
  sc.print(F("1234567890()[]{}<>qwertyавБвГдЕЖз.!?"));
  
  delay(400);
}
