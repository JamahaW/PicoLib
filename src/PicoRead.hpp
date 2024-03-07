#pragma once
#include <Arduino.h>

namespace pico
{
    class I_Reader {
        virtual uint8_t read() = 0; // прочесть данные из потока
        void read(void* data, size_t len); // считать в указатель данное число байт
        template <typename T> void read(T& dest); // считать тип
    };
    template<typename T> inline void I_Reader::read(T& dest) { read(&dest, sizeof(T)); }
} // namespace pico
