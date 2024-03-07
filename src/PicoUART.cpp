#include "PicoUART.hpp"

static volatile uint8_t __rx_buffer = 0;
static volatile bool __available_flag = false;

// прерывание на приём
ISR(USART_RX_vect) {
    if ((UCSR0A & (1 << UPE0))) return;
    __rx_buffer = UDR0;
    __available_flag = true;
}

void pico::UART::init(uint32_t baudrate)
{
    UBRR0 = (F_CPU / (baudrate << 3)) - 1;  // скорость
    UCSR0A = (1 << U2X0);                                   // скорость
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);   // подрубаем rx tx и rx isr
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);                 // 8 бит байт
}

void pico::UART::write(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = data;  // пишем
}

uint8_t pico::UART::read() {
    __available_flag = false;
    return __rx_buffer;
}

void pico::UART::quit() { UCSR0B = 0; }

bool pico::UART::available() { return __available_flag; }

