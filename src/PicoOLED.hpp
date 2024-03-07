#pragma once
#include <Arduino.h>
#include "PicoPrint.hpp"

namespace pico
{
    /// @brief Маркер шрифта
    enum Font {
        // HEIGHT | WIDTH
        SINGLE = 0x11,
        SINGLE_BOLD = 0x12,
        DOUBLE_THIN = 0x21,
        DOUBLE = 0x22,
        DOUBLE_BOLD = 0x23,
    };

    class OLED : public pico::I_Printer {

    private:

        uint8_t address;

        uint8_t text_mask = 0;

        uint8_t font_width = 1, font_height = 1;

        bool autoprintln = false;

        uint8_t cursor_x = 0;
        uint8_t cursor_y = 0;
        uint8_t writes = 0;

        void sendByte(uint8_t data);
        void sendCommand(uint8_t cmd1);
        void sendTwoCommands(uint8_t cmd1, uint8_t cmd2);
        void setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void beginData();
        void beginCommand();
        void beginOneCommand();
        void endTransm();
        void updateTextWindow();

    public:

        /// @brief 
        /// @param address адрес. по умолчанию 0x3C
        OLED(const uint8_t address = 0x3C);

        virtual void write(uint8_t data) override;

        /// @brief инициализация дисплея

        void init();

        /// @brief Очистить весь дисплей
        void clear();
        /// @brief Очистить область дисплея
        void clear(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t fill = 0);

        /// @brief установить положение курсора
        /// @param x позиция по горизонтали (пиксель 0..127)
        /// @param y позиция по вертикали (строка 0..7)
        void setCursor(uint8_t x, uint8_t y);
        /// @brief установить якрость
        /// @param value яркость (0-255), дисплей выключается при яркости 0
        void setBright(uint8_t value);
        /// @brief Установить инверсию цвета дисплея глобально
        void setInvertColor(bool mode);
        /// @brief Установить инверсию шрифта
        void setInvertText(bool mode);
        /// @brief Отразить дисплей по вертикали
        void setFlipV(bool mode);
        /// @brief Отразить дисплей по горизонтали
        void setFlipH(bool mode);
        /// @brief Разрешить автоматический перенос текста по завершению строки
        void setAutoNextLine(bool mode);
        /// @brief Установить режим вывода текста
        /// @param ft DOUBLE, SINGLE 
        void setFont(enum Font ft);
    };

} // namespace pico
