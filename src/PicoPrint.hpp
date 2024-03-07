#pragma once

#include <Arduino.h>

#ifdef BIN
#undef BIN
#endif

#ifdef OCT
#undef OCT
#endif

#ifdef DEC
#undef DEC
#endif

#ifdef HEX
#undef HEX
#endif

namespace pico
{
    enum Bases {
        BIN = 2,
        OCT = 8,
        DEC = 10,
        HEX = 16,
    };

    // Интерфейс вывода данных
    class I_Printer {

    public:

        virtual void write(uint8_t) = 0; // вывод байта
        void write(void* buffer, size_t len); // вывод буфера данной длины
        template <typename T> void write(T& obj); // вывести побайтово объект

        void print(int32_t number, enum Bases base = DEC); // вывести целое число
        void print(const char* str); // вывести SRAM строку
        void print(const __FlashStringHelper* str); // вывести FLASH строку

        /**
         * Форматированный вывод
         *
         * %f - flash string
         * %F - "flash string"
         *
         * %s - sram string
         * %S - "sram string"
         *
         * %c - char
         * %C - 'char'
         *
         * %d - int16
         * %l - int32
         *
         * %t - bool (true, false)
         * %T - bool (TRUE, FALSE)
         *
         * %y - bool (yes, no)
         * %Y - bool (YES, NO)
         *
         * %x - hex32 num
         * %X - 0Xnum
         *
         * %o - oct32 num
         * %O - 0Onum
         *
         * %b - bin32 num
         * %B - 0Bnum
         *
         * %% - %
        */
        void printf(const __FlashStringHelper* fmt, ...);

        void println();
        void println(int32_t number, enum Bases base = DEC);
        void println(const char* str);
        void println(const __FlashStringHelper* str);

    private:

        void print_string(uint8_t(*byte_reader) (uint8_t*), uint8_t* str);
        void print_boolean_literal(va_list& args, const __FlashStringHelper* on_true, const __FlashStringHelper* on_false);
        void print_number(va_list& args, enum pico::Bases base);
        void print_format_number(va_list& args, char prefix, enum pico::Bases base);
    };

    template<typename T> inline void I_Printer::write(T& obj) { write(&obj, sizeof(T)); }

} // namespace pico
