#include "PicoPrint.hpp"

void pico::I_Printer::write(void* buffer, size_t len) {
    void* end = (uint8_t*)buffer + len;
    for (uint8_t* p = (uint8_t*)buffer; p < end; p++) write(*p);
}

void pico::I_Printer::print(int32_t number, enum Bases base) {

    // если число отрицательное, то выводит знак минус и меняем знак
    if (number < 0) {
        write('-');
        number = -number;
    }

    // выделение буфера под запись числа
    char number_buffer[16];
    char* str = &number_buffer[sizeof(number_buffer) - 1];
    *str = 0;

    // заполнение буфера

    do {
        char c = number % base;
        number /= base;
        *(--str) = (c < 10) ? (c + '0') : (c + 'A' - 10);
    } while (number);

    // вывод буфера

    print((const char*)str);
}

void pico::I_Printer::print_string(uint8_t(*byte_reader)(uint8_t*), uint8_t* str) {
    uint8_t* p = (uint8_t*)str;
    uint8_t c;

    while (true) {
        c = byte_reader(p++);
        if (!c) break;
        write(c);
    }
}

static uint8_t __byte_reader_sram(uint8_t* p) { return *p; }

void pico::I_Printer::print(const char* str) {
    print_string(__byte_reader_sram, (uint8_t*)str);
}

static uint8_t __byte_reader_frash(uint8_t* p) { return pgm_read_byte(p); }

void pico::I_Printer::print(const __FlashStringHelper* str) {
    print_string(__byte_reader_frash, (uint8_t*)str);
}

void pico::I_Printer::print_boolean_literal(va_list& args, const __FlashStringHelper* on_true, const __FlashStringHelper* on_false) { print(va_arg(args, int) ? on_true : on_false); }

void pico::I_Printer::print_number(va_list& args, pico::Bases base) {
    print(va_arg(args, long), base);
}

void pico::I_Printer::print_format_number(va_list& args, char prefix, pico::Bases base) {
    write('0');
    write(prefix);
    print_number(args, base);
}

void pico::I_Printer::printf(const __FlashStringHelper* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    PGM_P p = reinterpret_cast<PGM_P>(fmt);  // Преобразование типа
    char c, spec;

    while (true) {
        c = pgm_read_byte(p++);  // Чтение символа из flash memory

        if (c == '\0') break;  // Конец строки формата

        if (c != '%') {
            write(c);
            continue;
        }

        spec = pgm_read_byte(p++);

        // Обработка спецификаторов формата
        switch (spec) {

            /* flash string */
        case 'f':
            print(va_arg(args, const __FlashStringHelper*));
            break;

            /* "flash string" */
        case 'F':
            write('"');
            print(va_arg(args, const __FlashStringHelper*));
            write('"');
            break;

            /* sram string */
        case 's':
            print(va_arg(args, const char*));
            break;

            /* "sram string" */
        case 'S':
            write('"');
            print(va_arg(args, const char*));
            write('"');
            break;

            /* char */
        case 'c':
            write(va_arg(args, int));
            break;

        case 'C': /* 'char' */
            write('\'');
            write(va_arg(args, int));
            write('\'');
            break;

            /* int16 */
        case 'd':
            print(va_arg(args, int), pico::DEC);
            break;

            /* int32 */
        case 'l':
            print(va_arg(args, long), pico::DEC);
            break;

            /* bool (true, false) */
        case 't':
            print_boolean_literal(args, F("true"), F("false"));
            break;

            /* bool (TRUE, FALSE) */
        case 'T':
            print_boolean_literal(args, F("TRUE"), F("FALSE"));
            break;

            /* bool (yes, no) */
        case 'y':
            print_boolean_literal(args, F("yes"), F("no"));
            break;

            /* bool (YES, NO) */
        case 'Y':
            print_boolean_literal(args, F("YES"), F("NO"));
            break;

            /* hex32 num */
        case 'x':
            print_number(args, pico::HEX);
            break;

            /* 0Xnum */
        case 'X':
            print_format_number(args, 'x', pico::HEX);
            break;

            /* oct32 num */
        case 'o':
            print_number(args, pico::OCT);
            break;

            /* 0Onum */
        case 'O':
            print_format_number(args, 'o', pico::OCT);
            break;

            /* bin32 num */
        case 'b':
            print_number(args, pico::BIN);
            break;

            /* 0Bnum */
        case 'B':
            print_format_number(args, 'b', pico::BIN);
            break;

            /* % */
        case '%':
            write('%');
            break;

        }
    }

    va_end(args);
}

void pico::I_Printer::println() { write('\n'); }

void pico::I_Printer::println(int32_t number, enum pico::Bases base) {
    print((int32_t)number, base);
    println();
}

void pico::I_Printer::println(const char* str) {
    print((const char*)str);
    println();
}

void pico::I_Printer::println(const __FlashStringHelper* str) {
    print((const __FlashStringHelper*)str);
    println();
}

