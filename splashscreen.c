/* 
 Advanced PCX to GameBoy converter v2.15

 Tiles data
 Original PCX File : "SPLASH~1.PCX"

 Number of Tiles   : 206
 TileMap Size      : 20x18
*/ 

const unsigned char splashscreendata[] =  {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3E,0xFF,0xF7,0x0E,0xFB,0x06,0xFF,0xE2,0xFF,0xE2,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x23,0xFF,0xDD,0x23,0xDE,0x21,0xEF,0x30,0xEF,0x30,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0xFF,0xBE,0xC7,0xBD,0xC6,0xF7,0xCC,0xF7,0x4C,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0xFF,0xFB,0x07,0xFD,0x03,0xAF,0x71,0xF6,0x79,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0x7F,0x98,0xEF,0x90,0xFF,0x91,0xDE,0xB1,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x7F,0xFC,0xFB,0xFC,0xFF,0xF8,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0xFF,0xFE,0x07,0xFF,0x03,0xFF,0x61,0xFF,0xF1,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFE,0x01,0xFE,0x01,0xFD,0x1F,0xFD,0x03,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xFE,0x01,0xFF,0x00,0xFC,0x1F,0xFC,0x03,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0x1E,0xDF,0x3E,0xDE,0x3F,0xDE,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x23,0xFF,0xDD,0x23,0xDE,0x21,0xCF,0x30,0xCF,0x30,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC4,0xFF,0xBB,0xC4,0xBF,0xC4,0xF7,0xCC,0xF7,0x4C,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0xFF,0xF7,0x0F,0xFF,0x07,0xFF,0x7F,0xF7,0x0F,
0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,
0xED,0xF2,0xFF,0xE2,0xFF,0xE2,0xFB,0x06,0xF7,0x0E,0x3E,0xFF,0xFF,0xFF,0xFF,0xFF,
0xED,0x32,0xEF,0x32,0xEF,0x33,0xDF,0x23,0xDF,0x23,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,
0xB3,0x4C,0xF7,0x0C,0xF7,0x0C,0xF7,0x8E,0xB7,0xCF,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x76,0xF9,0xF6,0x79,0xCF,0x31,0xFD,0x03,0xFB,0x07,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xBF,0xF8,0xFF,0xFC,0xF3,0xFC,0xFF,0xF0,0xF6,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x7F,0xF8,0xFF,0x78,0xFB,0x7C,0x7F,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF1,0x7F,0xF1,0x9D,0x63,0xFE,0x03,0xFE,0x07,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x01,0xE1,0x1F,0xFF,0x1F,0xFE,0x1F,0xFE,0x1F,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFE,0x01,0xE0,0x1F,0xFE,0x1F,0xFE,0x1F,0xFE,0x1F,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xDE,0x3F,0xDE,0x3F,0xDA,0x3F,0xFD,0x02,0xFD,0x02,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,
0xCD,0x32,0xCF,0x32,0xCF,0x33,0xDF,0x23,0xDF,0x23,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,
0xB7,0x4C,0xF7,0x0C,0xF7,0x0C,0xF3,0x8C,0xB3,0xCC,0xCC,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF7,0x0F,0x8F,0x7F,0xF7,0x7F,0xFF,0x07,0xFF,0x07,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFE,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xF0,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0xFE,0xBC,0x7E,0x0C,0x1E,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0x1F,0x0F,0x1F,0x1F,0x0F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x36,0xCC,0x0C,0x04,0x0C,0x04,0x06,0x04,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xF1,0x60,0x60,0x20,0x60,0x60,0x20,0xB0,0x60,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFC,0xFC,0xFC,0x7C,0x3C,0x7C,0x3C,0x3C,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x20,0x30,0x30,0x20,0x30,0x20,0x3E,0x20,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0xFF,0x03,0x87,0x03,0x87,0x87,0x07,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xDF,0xC1,0x83,0xC3,0x83,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x39,0x87,0x80,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x3F,
0xFB,0xFD,0xE1,0xE0,0xC0,0xE0,0xC0,0xE0,0xE0,0xC0,0xE0,0xC0,0xC2,0xC0,0xC1,0xC2,
0xFC,0xFE,0xFE,0xFE,0x7E,0xFE,0x7E,0x7E,0x3F,0x3E,0x3E,0x1F,0x0E,0x1F,0x0F,0x0F,
0x00,0x00,0x06,0x00,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x07,0x0F,0x07,0x0F,0x0F,0x07,
0x0E,0x06,0x02,0x06,0x02,0x82,0xC1,0x82,0xC3,0xC1,0xC3,0xC1,0xC3,0xC1,0xC3,0xC1,
0x1F,0x0F,0x1F,0x0F,0x0F,0x0F,0x06,0x0F,0x07,0x06,0x06,0x82,0xC0,0x80,0xC0,0xC0,
0x06,0x04,0x06,0x04,0x0E,0x04,0x04,0x0E,0x0C,0x0E,0x1C,0x0E,0x1C,0x1E,0x3E,0x1E,
0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x1F,0x0F,0x1F,0x0F,0x00,
0xF0,0xE0,0xF0,0x60,0x70,0x60,0x71,0x60,0x71,0x60,0xF1,0xE0,0xF1,0xE0,0xF1,0x20,
0x1C,0x1C,0x1C,0x0C,0x00,0x0C,0x80,0x04,0x80,0x80,0xC0,0xC0,0xC0,0xE0,0xF0,0xE0,
0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x3C,0x3E,0x3C,0x3E,0x3C,0x3E,0x7C,0x3E,
0x1F,0x0F,0x1F,0x0F,0x1F,0x0F,0x0F,0x1F,0x0F,0x1F,0x0F,0x1F,0x1F,0x1F,0x1E,0x1F,
0x87,0x07,0x87,0x07,0x07,0x07,0x07,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x07,
0x83,0x83,0x83,0x83,0x87,0x83,0x86,0x83,0x02,0x87,0x03,0x86,0x87,0x06,0x86,0x06,
0x00,0x00,0x00,0x00,0x08,0x06,0x07,0x0F,0x0F,0x0F,0x0A,0x07,0x00,0x00,0x00,0x00,
0x0E,0x0E,0x0E,0x06,0x04,0x06,0x86,0x04,0x86,0x04,0x04,0x04,0x04,0x0C,0x18,0x0C,
0x6F,0x1F,0x01,0x00,0x00,0x00,0x00,0x00,0x0C,0x10,0x1F,0x1F,0x0D,0x03,0x00,0x00,
0xFF,0xFF,0xBF,0x7F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0xBF,0xFF,0xFF,0xFF,0xFF,0x7F,
0xC3,0xC3,0x83,0xC3,0x80,0xC0,0xC0,0x80,0xC0,0x80,0x81,0x80,0x87,0x83,0x87,0x83,
0x0F,0x07,0x83,0x07,0x03,0x03,0x03,0x01,0x01,0x01,0x60,0xE0,0xF2,0xE1,0xFF,0xFF,
0x07,0x07,0x87,0x07,0x82,0x00,0x00,0x80,0x80,0x80,0x86,0x81,0xFF,0xFF,0xFF,0xFF,
0x81,0xC3,0x03,0x83,0x03,0x07,0x07,0x0F,0x3F,0x1F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC0,0xE0,0xF0,0xE0,0xF0,0xF0,0xF0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x1E,0x3E,0x3E,0x3E,0x3E,0x7E,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x31,0x20,0x31,0x20,0x30,0x21,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF0,0xF0,0xF0,0xF8,0xFC,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x7E,0x3C,0x7E,0x3C,0x7E,0x3C,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0xDF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x05,0x02,0x00,0x00,0x80,0x00,0x80,0xC0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x06,0x06,0x0E,0x06,0x0C,0x0E,0x0E,0x1C,0x7E,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x0C,0x18,0x0C,0x1C,0x1C,0x1C,0x1E,0x1C,0x5C,0xBE,0xFE,0xFF,0xFF,0xFF,
0x3C,0x18,0x1C,0x38,0x38,0x18,0x18,0x18,0x10,0x18,0x08,0x10,0xE8,0x10,0xF9,0xFE,
0x00,0x00,0x20,0x00,0x3A,0x3D,0x7F,0x3F,0x27,0x1F,0x01,0x00,0x00,0x00,0x00,0x01,
0xEF,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xE0,0xFF,0xC0,0xFF,0xC7,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0x7F,0xFF,0xC0,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0xFF,0x0F,0xFF,0x87,0xFF,0xFF,0xFF,
0xED,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xE3,0xFF,0x81,0xFF,0x81,0xFF,0x06,0xFF,0x0D,0xFE,0x1B,0xFC,0xBF,0xF0,0xFF,0xE0,
0xFC,0xFF,0xE7,0xF8,0xBE,0xC1,0x71,0x8E,0xEF,0x10,0xDF,0x20,0xFB,0x07,0xE9,0x1C,
0xFF,0x00,0xFF,0x00,0x7F,0x80,0xCF,0x30,0xFF,0x00,0xFF,0x00,0x9F,0xE0,0x6F,0xF0,
0xCF,0x3F,0xFB,0x07,0xFE,0x01,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0x7F,0xDF,0x3F,0xEF,0x1F,0xFF,0x07,0xFF,0x03,
0xFF,0xFF,0xF9,0xFF,0xE1,0xFF,0xE1,0xFF,0xC3,0xFF,0xC2,0xFF,0xC3,0xFE,0xC7,0xFE,
0xDF,0xE0,0xBF,0xC0,0x7F,0x80,0x7F,0x80,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFC,0x18,0xDC,0x38,0xF8,0x3C,0xFC,0x3F,0xFF,0x3F,0xFF,0x3F,0xFF,0x3F,0xDF,0x3F,
0x37,0x78,0x3F,0x78,0xBB,0x7C,0xFF,0xFC,0xFF,0xFC,0xFF,0xFC,0xFB,0xFC,0xFB,0xFC,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFF,0x01,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0x7F,0xDF,0x3F,0xEF,0x1F,0xFF,0x0F,0xF7,0x0F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,
0xE5,0xFE,0xFD,0xFE,0xFF,0xFC,0x8B,0xFC,0x0B,0xFC,0x1F,0xF8,0x17,0xF8,0x17,0xF8,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xF1,0x0F,0xF7,0x0E,0xFC,0x0E,
0xDF,0x3F,0xEF,0x1F,0xF7,0x0F,0xFC,0x03,0xFF,0x00,0x80,0xFF,0x0F,0xFF,0x02,0x01,
0xFF,0xF8,0xFF,0xF0,0xDF,0xE0,0x7F,0x80,0xFF,0x00,0xFF,0x00,0xC7,0xF8,0xFE,0xFF,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x7F,0x80,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xF6,0x0F,0xEB,0x1F,0xDB,0x31,0xF3,0x31,0xB1,0x7F,
0xFF,0x07,0xFB,0x07,0xFB,0x07,0xFF,0x03,0x7D,0x83,0xBD,0xC3,0xBD,0xC3,0xFD,0xC3,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xF8,0xFF,0xF8,0xFF,0xF8,0xFF,
0x3F,0xF0,0xBF,0xF0,0xEF,0xF0,0xEF,0xF0,0x7F,0xE0,0x7F,0xE0,0x5F,0xE0,0x5F,0xE0,
0xEC,0x1E,0xFC,0x1E,0xDC,0x3E,0xDC,0x3E,0xFE,0x3E,0xBF,0x7E,0xBF,0x7E,0xB0,0x7F,
0x02,0x01,0x06,0x02,0x0C,0x06,0x0E,0x0E,0x0E,0x1F,0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,
0x9B,0x07,0x01,0x00,0x04,0x60,0x5E,0xEE,0xFF,0xFE,0xFE,0xFF,0xFE,0xFF,0xFF,0xFF,
0xCF,0xF0,0x3B,0xFC,0x16,0x0F,0x25,0x03,0x38,0x30,0x70,0x39,0x75,0xFB,0xFF,0xFF,
0xBF,0x7F,0xDF,0x3F,0x6F,0x9F,0xB9,0xC6,0xAF,0x70,0x2B,0x9C,0xC9,0x86,0xC6,0xC3,
0xFD,0xC3,0xFD,0xC3,0x7D,0x83,0xFD,0x03,0xFD,0x03,0xFF,0x03,0xFB,0x07,0xFB,0x07,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFD,0xC3,0xFF,0x80,0x7F,0x80,0xFF,0x00,0xFF,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0x7F,0xBF,0x7F,
0xFC,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xAF,0xDF,
0x5F,0xE0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xBF,0xC0,0xBF,0xC0,0xBF,0xC0,0xBF,0xC0,
0xEE,0x71,0x6E,0xF1,0x6F,0xF0,0x6F,0xF0,0x6F,0xF0,0x6F,0xF0,0x7F,0xE0,0x7C,0xE3,
0xEF,0x3F,0xD9,0xE7,0x3F,0xC0,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xDF,0x3F,0xEF,0x1F,0xF7,0x0F,0xFB,0x07,0xFB,0x07,
0xE2,0xC7,0xC1,0xE6,0xCD,0xE6,0xCF,0xFC,0xFB,0xFC,0xFB,0xFC,0xFF,0xF8,0xF7,0xF8,
0x7F,0x87,0xFF,0x07,0xF7,0x0F,0xF7,0x0F,0xFF,0x0F,0xFF,0x0F,0xEF,0x1F,0xEE,0x1F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xFC,0xF7,0xF8,0x9F,0xE0,0xFF,0x00,
0xFE,0xFF,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xBF,0x7E,0xDD,0x3E,0xDD,0x3E,0xDD,0x3E,
0xFF,0x3F,0xFF,0x3E,0xDD,0x3E,0xDF,0x3C,0xDF,0x3C,0xDF,0x3C,0xDF,0x3C,0xDF,0x3C,
0x6F,0x9F,0xFF,0x0F,0xF7,0x0F,0xF7,0x0F,0xFF,0x07,0xFF,0x07,0xFF,0x07,0xFB,0x07,
0xF7,0x8F,0x7B,0x87,0x7F,0x83,0x7D,0x83,0x7E,0x81,0xFF,0x80,0xBF,0xC0,0xBF,0xC0,
0xBF,0xC0,0xBF,0xC0,0xBF,0xC0,0xFF,0xC0,0xFF,0xC0,0xDF,0xE0,0x5F,0xE0,0x7F,0xE0,
0x78,0xE7,0x78,0xE4,0xF4,0x68,0xA0,0x78,0xB0,0x78,0xF0,0x38,0xC1,0x3E,0xFD,0x03,
0x7F,0x80,0x7F,0x80,0x7F,0x80,0xBF,0x40,0xBF,0x40,0xBF,0x40,0xA0,0x5F,0xFF,0xFF,
0xFF,0x03,0xFD,0x03,0xFD,0x03,0xFD,0x03,0xFD,0x03,0x9D,0x63,0xDD,0xE3,0xAD,0xD3,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,
0xF7,0xF8,0xF7,0xF8,0xFF,0xF0,0xFF,0xF0,0xEF,0xF0,0xEF,0xF0,0xEF,0xF0,0xAF,0xF0,
0xEF,0x1C,0xFF,0x18,0xF7,0x18,0xDF,0x30,0xCF,0x30,0xCF,0x30,0xCF,0x30,0xEF,0x30,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xDF,0x20,0xDF,0x60,
0xDD,0x3E,0xFD,0x1E,0xFD,0x1E,0xFF,0x1C,0xFF,0x1C,0xFF,0x1C,0xFF,0x1C,0xFF,0x1C,
0xDF,0x3C,0xDF,0x3C,0xDF,0x3C,0xDF,0x3C,0xFF,0x3C,0xFF,0x3C,0xFF,0x3C,0xDF,0x3C,
0xFB,0x07,0xFB,0x07,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,
0xFF,0xC0,0xDF,0xE0,0xFF,0xE0,0xEF,0xF0,0xF7,0xF8,0xFF,0xF8,0xFF,0xFC,0xFD,0xFE,
0xAF,0x70,0xF7,0x38,0xDB,0x3C,0xED,0x1E,0xF1,0x0E,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0x3F,0xFF,0xE7,0x1F,0xFC,0x03,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0x85,0x08,0x00,0xF8,0x78,0xFF,0xF0,0x0F,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xC7,0xEF,0xEE,0xC7,0xD6,0xEF,0x00,0xFF,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xAF,0x30,0x2F,0x10,0xEF,0x10,0x0F,0xF0,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xEE,0x31,0xED,0x33,0xFB,0x37,0xF7,0x3F,0xBF,0x7F,0xBF,0x7F,0xBF,0x7F,0xBF,0x7F,
0xDF,0xE0,0xDF,0xE0,0xDF,0xE0,0xDF,0xE0,0xDF,0xE0,0xDF,0xE0,0xDF,0xE0,0xDF,0xE0,
0xFF,0x1C,0xFF,0x1C,0xFF,0x1C,0xFF,0x1C,0xFF,0x1C,0xFB,0x0C,0xFF,0x00,0xFF,0x00,
0xF7,0x18,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFB,0x07,0xFB,0x07,0xFF,0x07,0xF7,0x0F,0xEF,0x1F,
0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFF,0xE2,0xFF,0xC7,0xFE,
0xFF,0x00,0x7F,0x80,0xBF,0xC0,0xFF,0xC0,0x7F,0x80,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xE0,0x1F,0xB0,0x7F,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x7F,0x80,0xCF,0xF0,
0xBF,0x7F,0xBF,0x7F,0xBF,0x7F,0xBF,0x7F,0xBF,0x7F,0xBF,0x7F,0xBF,0x7F,0xFF,0x7F,
0xDF,0xE0,0xFF,0xE0,0xFF,0xE0,0xEF,0xF0,0xF7,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xCF,0xF0,0xFF,0xF8,
0xFF,0x00,0xFF,0x03,0xF7,0x0F,0xFF,0x0F,0xEF,0x1F,0xFF,0x1F,0xFF,0x1F,0xFF,0x1F,
0xBF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFE,0x8F,
0xC7,0xFF,0xBF,0xC3,0xFD,0x83,0xFF,0x01,0xFE,0x01,0xFE,0x01,0xFF,0x00,0xFF,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFF,0xE1,0xDF,0xE1,0xDF,0xE1,
0xE5,0xFE,0xE5,0xFE,0xFD,0xFE,0xFD,0xFE,0xFD,0xFE,0xBD,0xFE,0x06,0xFF,0x0F,0xFF,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFE,0x01,0xFE,0x01,0xFF,0xFF,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x9F,0xE0,0xF7,0xF8,0xFF,0xFF,
0xFE,0x01,0xFD,0x03,0xFA,0x07,0xFC,0x07,0xF4,0x0F,0xF8,0x0F,0xE8,0x1F,0xDF,0xFF,
0x80,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0xFF,0xFF,
0x17,0xF8,0x07,0xFC,0x03,0xFE,0x00,0xFF,0x01,0xFF,0x00,0xFF,0x00,0xFF,0xF3,0xFF,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x7F,0x80,0x7F,0x80,0xFF,0x80,0xF7,0xF8,
0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,
0xFF,0xFC,0xFD,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFF,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x5D,0xBE,
0xFF,0x1F,0xFE,0x1F,0xFF,0x1E,0xFF,0x1E,0xFF,0x1E,0xFF,0x1E,0xFD,0x1E,0x3F,0xFF,
0xF6,0x0F,0xF6,0x0F,0xF7,0x0E,0xF7,0x0E,0xFF,0x06,0xFF,0x06,0xFF,0x06,0xCF,0xFF,
0xFF,0x00,0xFF,0x00,0xFE,0x01,0xFE,0x01,0xFE,0x01,0xFE,0x01,0xFE,0x01,0xFE,0xFF,
0xDE,0xE1,0xDE,0xE1,0xFE,0xC1,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xF3,0xFC,
0xFF,0xFF,0xDE,0xFF,0x8E,0xFF,0x0F,0xFF,0x3C,0xFF,0xE7,0xF8,0x3F,0xC0,0xFF,0x00,
0x3E,0xFF,0x1F,0xFF,0x79,0xFE,0xCF,0xF0,0x7F,0x80,0xFF,0x00,0xFF,0x00,0xFF,0x00,
0xFD,0xFF,0x9D,0xE3,0xFF,0x03,0xFB,0x07,0xFB,0x07,0xFB,0x07,0xFB,0x07,0xFB,0x07,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xC0,0x8E,0xCC,0x8C,0xCE,0x8E,0xCC,0x80,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x40,0xE0,0x47,0x67,0x47,0x67,0x46,0x67,0xC0,0xE0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x70,0x30,0x11,0x33,0x31,0x13,0x11,0x33,0x30,0x70,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0E,0x1C,0xF8,0xF9,0xF9,0xF9,0xF8,0xF8,0x1E,0x1C,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x1E,0x8C,0xCC,0xEC,0xCC,0x7C,0x3C,0x1F,0x0E,
0xFD,0xFE,0xFE,0xFF,0xFF,0xFF,0x07,0x0F,0x47,0xE7,0xF7,0xE7,0x3F,0x1F,0x0F,0x07,
0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0xF9,0xF8,0xF0,0xF8,0xF0,0xF0,0xF0,0xF2,0xF6,0xE2,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xF1,0xF0,0xF1,0xF0,0x70,0x70,0x70,0x30,0x72,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE9,0xCC,0xC4,0xCC,0xC6,0xCC,0xC7,0x4E,0x07,0x4F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xE7,0xC7,0x67,0x4F,0x07,0x0F,0x0F,0x1F,0x1F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCE,0xCF,0xC4,0xCE,0xC0,0xCC,0xC8,0xC1,0xC0,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x30,0x30,0x31,0x73,0x71,0xF3,0xF1,0xF3,0xF0,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x13,0xF9,0xF1,0xF8,0xF8,0xF8,0xFC,0x1E,0x1C,
0xFD,0xFE,0xFE,0xFF,0xFF,0xFF,0xCF,0xCF,0x9F,0x8F,0x9F,0x1F,0x1F,0x3F,0x7F,0x3F,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x8F,0xF0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xC0,0xFF,0xFF,0xFF,
0xFB,0x07,0xFB,0x07,0xFB,0x07,0xFB,0x07,0xFF,0x03,0xFD,0x03,0xFD,0x03,0xFF,0xFF,
0x8F,0xCF,0x8F,0xCF,0x8F,0xCF,0x9F,0xCF,0xFF,0xFF,0xFE,0xFF,0xFD,0xFE,0xFC,0xFF,
0xC6,0xE4,0xC7,0xE6,0xC7,0xE7,0xCF,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,
0x71,0x73,0x31,0x33,0x11,0x33,0xB0,0x10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xF1,0xF9,0xF8,0xF9,0x1C,0x0C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC7,0x8F,0xE8,0xC4,0x8C,0xCC,0x0E,0x1E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xE3,0xC7,0xF7,0xE3,0x47,0xE7,0x07,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFC,0xFF,
0xE3,0xE6,0xE0,0xC0,0xC7,0xCF,0xCF,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFA,0xFD,
0x32,0x33,0x13,0x33,0xB3,0x13,0x9B,0x93,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x07,0x0F,0x87,0x0F,0x87,0x8F,0x8F,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xBF,0x1F,0xBF,0x1F,0xBF,0x1F,0x3F,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC0,0xC4,0xC4,0xCE,0xC7,0xCE,0xCF,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF1,0x73,0x31,0x73,0x31,0x33,0x10,0x30,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x1E,0x0E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0xFF,
0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFF};