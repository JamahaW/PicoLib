#include "PicoOLED.hpp"
#include "Wire.h"

static const uint32_t font[] PROGMEM = {
  0x00000000,  //   (32)
  0x00000df7,  // ! (33)
  0x40007007,  // " (34)
  0xd2fd2fd2,  // # (35)
  0xc60dec18,  // $ (36)
  0xf1c8c4e3,  // % (37)
  0xe06e59b8,  // & (38)
  0x00000007,  // ' (39)
  0x4002185e,  // ( (40)
  0x4001e861,  // ) (41)
  0x40014214,  // * (42)
  0x40008708,  // + (43)
  0x00000638,  // , (44)
  0x40008208,  // - (45)
  0x00000618,  // . (46)
  0x40003330,  // / (47)
  0xde86d85e,  // 0 (48)
  0x8083f880,  // 1 (49)
  0xe6a69a72,  // 2 (50)
  0xda965852,  // 3 (51)
  0xd0fd2518,  // 4 (52)
  0xd9965963,  // 5 (53)
  0xd0a69a9c,  // 6 (54)
  0xc3159841,  // 7 (55)
  0xda96595a,  // 8 (56)
  0xdea69a46,  // 9 (57)
  0x000006db,  // : (58)
  0x000006fb,  // ; (59)
  0x40011284,  // < (60)
  0x8028a28a,  // = (61)
  0x40004291,  // > (62)
  0xc7165b41,  // ? (63)
  0xefa6d87f,  // @ (64)
  0xfe24927e,  // A (65)
  0xfa96597f,  // B (66)
  0xd286185e,  // C (67)
  0xde86187f,  // D (68)
  0xe186597f,  // E (69)
  0xc114517f,  // F (70)
  0xd8a6985e,  // G (71)
  0xff20823f,  // H (72)
  0x40021fe1,  // I (73)
  0x4003d870,  // J (74)
  0xf128413f,  // K (75)
  0xe082083f,  // L (76)
  0xff0840bf,  // M (77)
  0xff2040bf,  // N (78)
  0xde86185e,  // O (79)
  0xc624927f,  // P (80)
  0xee46985e,  // Q (81)
  0xf624927f,  // R (82)
  0xd2a69952,  // S (83)
  0xc107f041,  // T (84)
  0xdf82081f,  // U (85)
  0xc7620607,  // V (86)
  0xdf81c81f,  // W (87)
  0xf12842b1,  // X (88)
  0xc3138103,  // Y (89)
  0xe3965a71,  // Z (90)
  0x4002187f,  // [ (91)
  0x40030303,  // \ (92)
  0x4003f861,  // ] (93)
  0xc4081084,  // ^ (94)
  0xc4210204,  // _ (95)
  0x40004081,  // ` (96)
  0xdcaaaa90,  // a (97)
  0xd892493f,  // b (98)
  0xd48a289c,  // c (99)
  0xff924918,  // d (100)
  0xccaaaa9c,  // e (101)
  0x8027e200,  // f (102)
  0xdcaaaa84,  // g (103)
  0xf810413f,  // h (104)
  0x00000f40,  // i (105)
  0x00000760,  // j (106)
  0xe250823f,  // k (107)
  0x0000081f,  // l (108)
  0xfc0bc0be,  // m (109)
  0xfc0820be,  // n (110)
  0xdc8a289c,  // o (111)
  0xc428a2bc,  // p (112)
  0xfc28a284,  // q (113)
  0xc210423e,  // r (114)
  0xd2aaaaa4,  // s (115)
  0x400247c4,  // t (116)
  0xde82081e,  // u (117)
  0xce42040e,  // v (118)
  0xde81881e,  // w (119)
  0xe2508522,  // x (120)
  0xdea28a06,  // y (121)
  0xe6aaaab2,  // z (122)
  0x40021ccc,  // { (123)
  0x00000fc0,  // | (124)
  0x4000cce1,  // } (125)
  0x80108108,  // ~ (126)
  0xf85915b8,  // А (192)
  0xf996597f,  // Б (193)
  0xfa96597f,  // В (194)
  0xc104107f,  // Г (195)
  0xf07d17b0,  // Д (196)
  0xf3869a7f,  // Е (197)
  0xfb11e13b,  // Ж (198)
  0xda961852,  // З (199)
  0xff08423f,  // И (200)
  0xff10943f,  // Й (201)
  0xf128413f,  // К (202)
  0xff042330,  // Л (203)
  0xff0840bf,  // М (204)
  0xff10413f,  // Н (205)
  0xde86185e,  // О (206)
  0xff04107f,  // П (207)
  0xc624927f,  // Р (208)
  0xd286185e,  // С (209)
  0xc107f041,  // Т (210)
  0xdf924903,  // У (211)
  0xde4bf49e,  // Ф (212)
  0xf12842b1,  // Х (213)
  0xff41041f,  // Ц (214)
  0xff104103,  // Ч (215)
  0xff83e83f,  // Ш (216)
  0xff41e41f,  // Щ (217)
  0xd8924fc1,  // Ъ (218)
  0xff62493f,  // Ы (219)
  0xd892493f,  // Ь (220)
  0xde965852,  // Э (221)
  0xff87f23f,  // Ю (222)
  0xff249276,  // Я (223)
  0xfcaaaa90,  // а (224)
  0xd0a69a9c,  // б (225)
  0xf4aaaabe,  // в (226)
  0xc20820be,  // г (227)
  0xdcaa9a50,  // д (228)
  0xccaaaa9c,  // е (229)
  0xf621c236,  // ж (230)
  0xd4aaa894,  // з (231)
  0xfe10843e,  // и (232)
  0xfe10943e,  // й (233)
  0xe250823e,  // к (234)
  0xf0302330,  // л (235)
  0xfe10813e,  // м (236)
  0xfe20823e,  // н (237)
  0xdc8a289c,  // о (238)
  0xfe0820be,  // п (239)
  0xc428a2be,  // р (240)
  0xd48a289c,  // с (241)
  0xc20be082,  // т (242)
  0xdea28a06,  // у (243)
  0xc853e508,  // ф (244)
  0xe2508522,  // х (245)
  0xfe41041e,  // ц (246)
  0xfe208206,  // ч (247)
  0xfe83883e,  // ш (248)
  0xfe41c41e,  // щ (249)
  0xd0a28f82,  // ъ (250)
  0xfe428a3e,  // ы (251)
  0xd0a28a3e,  // ь (252)
  0xdcaaa894,  // э (253)
  0xdc89c23e,  // ю (254)
  0xfe4924ac,  // я (255)
};

#define OLED_HEIGHT_32 0x02
#define OLED_HEIGHT_64 0x12
#define OLED_64 0x3F
#define OLED_32 0x1F

#define OLED_DISPLAY_OFF 0xAE
#define OLED_DISPLAY_ON 0xAF

#define OLED_COMMAND_MODE 0x00
#define OLED_ONE_COMMAND_MODE 0x80
#define OLED_DATA_MODE 0x40
#define OLED_ONE_DATA_MODE 0xC0

#define OLEDOLED_ADDRESSING_MODE 0x20
#define OLED_HORIZONTAL 0x00
#define OLED_VERTICAL 0x01

#define OLED_NORMAL_V 0xC8
#define OLED_FLIP_V 0xC0
#define OLED_NORMAL_H 0xA1
#define OLED_FLIP_H 0xA0

#define OLED_CONTRAST 0x81
#define OLED_SETCOMPINS 0xDA
#define OLED_SETVCOMDETECT 0xDB
#define OLED_CLOCKDIV 0xD5
#define OLED_SETMULTIPLEX 0xA8
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR 0x22
#define OLED_CHARGEPUMP 0x8D

#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7

#define OLED_MAX_ROW 7
#define OLED_MAX_X 127

static uint16_t T(uint8_t data) {
    static constexpr uint8_t R[4]{ 0x0, 0x3, 0xC, 0xF };

    uint16_t ret = 0;
    for (uint8_t i = 0; i < 8; i += 2) ret |= R[((0b11 << i) & data) >> i] << (i << 1);
    return ret;
}

static uint32_t getFont(uint8_t f) {
    f -= 32;  // перевод код символа из таблицы ASCII

    if (f <= 95)
        ;
    else if (f >= 96 && f <= 111) f += 47;
    else if (f <= 159) f -= 17;

    return pgm_read_dword(&(font[f]));
}

static const uint8_t oled_init_commands[] PROGMEM = {
  OLED_DISPLAY_OFF,
  OLED_CLOCKDIV,
  0x80,  // value
  OLED_CHARGEPUMP,
  0x14,  // value
  OLEDOLED_ADDRESSING_MODE,
  OLED_VERTICAL,
  OLED_NORMAL_H,
  OLED_NORMAL_V,
  OLED_CONTRAST,
  0x7F,  // value
  OLED_SETVCOMDETECT,
  0x40,  // value
  OLED_NORMALDISPLAY,
  OLED_DISPLAY_ON,
};

pico::OLED::OLED(const uint8_t _address) : address(_address) {}

#define OLED_FONT_WIDTH 6
#define OLED_FONT_GET_COL(f, col) (((f) >> (col)) & 0b111111)
#define OLED_FONT_GET_WIDTH(f) (((f) >> 30) & 0b11)
#define IN_RANGE(x, mi, ma) (((x) >= (mi)) && ((x) <= (ma)))

void pico::OLED::write(uint8_t data) {
    if (data > 191) return;

    if ((data == '\n') || (autoprintln && cursor_x > OLED_MAX_X)) {
        setCursor(0, cursor_y + font_height);  // переставляем курсор
        return;
    }

    if (data == '\f') {
        text_mask ^= 0xFF;
        return;
    }

    if (cursor_y > OLED_MAX_ROW) return;  // дисплей переполнен

    if (autoprintln && data == ' ' && cursor_x == 0) return;

    if (!IN_RANGE(cursor_x, 0, OLED_MAX_X - OLED_FONT_WIDTH)) {
        cursor_x += OLED_FONT_WIDTH;  // пропускаем вывод "за экраном"
        return;
    }

    beginData();
    uint32_t bits = getFont(data);
    uint8_t width_6 = (2 * OLED_FONT_WIDTH) + OLED_FONT_GET_WIDTH(bits) * OLED_FONT_WIDTH;

    uint8_t col;

    for (uint8_t offset = 0; offset < width_6; offset += OLED_FONT_WIDTH, cursor_x += font_width) {
        col = OLED_FONT_GET_COL(bits, offset) ^ text_mask;

        for (uint8_t t = 0; t < font_width; t++) {

            if (font_height == 1) {
                sendByte(col);
            }
            else if (font_height == 2) {
                uint16_t f_data = T(col);
                sendByte(lowByte(f_data));
                sendByte(highByte(f_data));
            }
        }
    }

    for (uint8_t i = 0; i < font_height; i++)
        sendByte(text_mask);

    cursor_x++;

    endTransm();
}

#define OLED_WIRE_SPEED 200000UL

void pico::OLED::init() {
    Wire.begin(true);
    Wire.setClock(OLED_WIRE_SPEED);

    beginCommand();
    for (uint8_t i = 0; i < 15; i++) sendByte(pgm_read_byte(&oled_init_commands[i]));
    endTransm();

    beginCommand();
    sendByte(OLED_SETCOMPINS);
    sendByte(OLED_HEIGHT_64);
    sendByte(OLED_SETMULTIPLEX);
    sendByte(OLED_64);
    endTransm();

    clear();
}

void pico::OLED::clear() {clear(0, 0, OLED_MAX_X, OLED_MAX_ROW);}

void pico::OLED::clear(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t fill) {
    setWindow(x0, y0, x1, y1);
    beginData();

    for (uint16_t i = 0, end = (x1 - x0) * (y1 - y0 + 1); i < end; i++)
        sendByte(fill);

    endTransm();
    setCursor(0, 0);
}

void pico::OLED::setCursor(uint8_t x, uint8_t y) {
    cursor_x = x;
    cursor_y = y;
    updateTextWindow();
}

void pico::OLED::setBright(uint8_t value) {
    sendCommand((value > 0) ? OLED_DISPLAY_ON : OLED_DISPLAY_OFF);
    sendTwoCommands(OLED_CONTRAST, value);
}

void pico::OLED::setInvertColor(bool mode) {sendCommand(mode ? OLED_INVERTDISPLAY : OLED_NORMALDISPLAY);}

void pico::OLED::setInvertText(bool mode) {text_mask = mode * 255;}

void pico::OLED::setFlipV(bool mode) {sendCommand(mode ? OLED_FLIP_V : OLED_NORMAL_V);}

void pico::OLED::setFlipH(bool mode) {sendCommand(mode ? OLED_FLIP_H : OLED_NORMAL_H);}

void pico::OLED::setAutoNextLine(bool mode) {autoprintln = mode;}

void pico::OLED::setFont(Font ft) {
    font_height = (ft & 0xF0) >> 4;
    font_width = (ft & 0x0F);
    updateTextWindow();
}

void pico::OLED::sendByte(uint8_t data) {
    Wire.write(data);

    if (++writes >= 16) {
        endTransm();
        beginData();
    }
}

void pico::OLED::sendCommand(uint8_t cmd1) {
    beginOneCommand();
    Wire.write(cmd1);
    endTransm();
}

void pico::OLED::sendTwoCommands(uint8_t cmd1, uint8_t cmd2) {
    beginCommand();
    Wire.write(cmd1);
    Wire.write(cmd2);
    endTransm();
}

void pico::OLED::setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    beginCommand();
    Wire.write(OLED_COLUMNADDR);
    Wire.write(constrain(x0, 0, OLED_MAX_X));
    Wire.write(constrain(x1, 0, OLED_MAX_X));
    Wire.write(OLED_PAGEADDR);
    Wire.write(constrain(y0, 0, OLED_MAX_ROW));
    Wire.write(constrain(y1, 0, OLED_MAX_ROW));
    endTransm();
}

void pico::OLED::beginData() {
    Wire.beginTransmission(address);
    Wire.write(OLED_DATA_MODE);
}

void pico::OLED::beginCommand() {
    Wire.beginTransmission(address);
    Wire.write(OLED_COMMAND_MODE);
}

void pico::OLED::beginOneCommand() {
    Wire.beginTransmission(address);
    Wire.write(OLED_ONE_COMMAND_MODE);
}

void pico::OLED::endTransm() {
    Wire.endTransmission();
    writes = 0;
}

void pico::OLED::updateTextWindow() {setWindow(cursor_x, cursor_y, OLED_MAX_X, cursor_y + font_height - 1);}
