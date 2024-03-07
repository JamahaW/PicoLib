#pragma once

#include <Arduino.h>
#include <PicoPrint.hpp>
#include <PicoRead.hpp>

namespace pico {

    class UART : public I_Printer, public I_Reader{
    public:
        void init(uint32_t baudrate);
        
        void write(uint8_t data) override;
        uint8_t read() override;

        void quit();
        bool available();
    };

} // namespace pico
