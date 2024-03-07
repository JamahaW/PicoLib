#include "PicoRead.hpp"

void pico::I_Reader::read(void* data, size_t len) {
    for (uint8_t* p = (uint8_t*)data, *end = (uint8_t*)data + len; p < end; p++) *p = read();
}
