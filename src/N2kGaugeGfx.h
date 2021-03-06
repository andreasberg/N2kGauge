#ifndef _INCLUDE_N2kGaugeGfx_H_
#define _INCLUDE_N2kGaugeGfx_H_

static const unsigned char PROGMEM exclamation[] =
{
0xff,0xfc,
0xff,0xfc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xe0,0x1c,
0xf0,0x3c,
0xf0,0x3c,
0xf0,0x3c,
0xf0,0x3c,
0xf0,0x3c,
0xf0,0x3c,
0xf0,0x3c,
0xf0,0x3c,
0xf0,0x3c,
0xff,0xfc,
0xff,0xfc,
0xff,0xfc,
0xff,0xfc,
0xff,0xfc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xc0,0xc,
0xff,0xfc,
0xff,0xfc
};

#define SPLASH_GLCD_HEIGHT 128
#define SPLASH_GLCD_WIDTH  64
static const unsigned char PROGMEM splash_glcd_bmp[] =
{
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xc0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xc0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xfe,0x7,0xff,0xff,0xff,0xff,0xff,0xff,
0xc0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xf8,0x7,0xff,0xff,0xff,0xff,0xff,0xff,
0xe0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xf0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,
0xe0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xc0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,
0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,
0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,
0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xe0,0x0,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xff,
0xff,0xe0,0x0,0x33,0xff,0xfc,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xff,0xff,0xff,
0xff,0xf0,0x0,0x1,0xff,0xfc,0x0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x1,0xf0,0x1f,0xc0,0x0,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x1,0xfe,0x1f,0x80,0x0,0x0,0x0,0xe0,0x3,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x1,0xff,0x8f,0x0,0x0,0x0,0x1,0xf0,0x1,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x3,0xff,0xcf,0x0,0x0,0x0,0x3,0xf0,0x0,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x3,0xff,0xcf,0x0,0x0,0x0,0x3,0xf0,0x0,0x7f,0xff,0xff,0xff,0xff,
0xff,0xff,0x3,0xff,0xdf,0x0,0x0,0x0,0x1,0xe0,0x0,0x3f,0xff,0xff,0xff,0xff,
0xff,0xfe,0x3,0xff,0xdf,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,
0xff,0xfe,0x3,0xff,0x9e,0x0,0xf,0x80,0x0,0x0,0x0,0x7,0xff,0xdf,0x8f,0xff,
0xff,0xfe,0x3,0xff,0x9e,0x10,0x7f,0xf0,0x0,0x60,0xf,0xfb,0xff,0xe,0x0,0x3f,
0xff,0xfe,0x0,0x0,0x1e,0x3c,0x10,0xf8,0x7,0xe0,0x3d,0xfd,0xf0,0x0,0x1c,0x3f,
0xff,0xfe,0x0,0x0,0x1e,0x7c,0x0,0x78,0x3f,0xe0,0xf0,0x7e,0xc0,0x1,0xfc,0x7f,
0xff,0xfe,0x0,0x0,0xe,0x78,0x1c,0x7c,0x3f,0xe1,0xe0,0x3f,0x0,0x8,0x7c,0xff,
0xff,0xfc,0x7,0xff,0x8c,0xf8,0x1e,0x7c,0x7,0xc3,0xc0,0x3f,0x18,0x0,0x7d,0xff,
0xff,0xfc,0x7,0xff,0x5,0xf8,0x1f,0x78,0x0,0x0,0x0,0x78,0x8,0x40,0x7b,0xff,
0xff,0xfc,0x7,0xff,0x1,0xf8,0x1c,0x38,0x78,0x0,0x30,0x60,0x0,0xc0,0x73,0xff,
0xff,0xfc,0x7,0xff,0x3,0xfe,0x0,0x18,0x78,0x0,0x0,0x0,0x7,0xc0,0x63,0xff,
0xff,0xfc,0xf,0xff,0x3,0xfc,0x0,0x0,0x38,0x20,0x1,0xf0,0x7,0xc0,0x43,0xff,
0xff,0xfc,0xf,0xff,0x3,0xf8,0x7,0x0,0x30,0x20,0x7,0xff,0x7,0xc0,0x7,0xff,
0xff,0xfc,0xf,0xff,0x3,0xf0,0x3e,0x0,0x10,0x20,0x3f,0xff,0xc7,0x80,0x7,0xff,
0xff,0xf8,0xf,0xff,0x3,0xe0,0x7e,0x4,0x10,0x20,0x3f,0xfd,0xf3,0x80,0x7,0xff,
0xff,0xf8,0xf,0xfe,0x3,0xe0,0x7e,0x7,0x10,0x20,0x1f,0xf8,0xf3,0x80,0x7,0xff,
0xff,0xf8,0xf,0xfe,0x3,0xe0,0x7c,0x6,0xd0,0x30,0x1f,0xf1,0xf1,0x80,0x7,0xff,
0xff,0xf0,0xf,0xfe,0x3,0xe0,0x78,0x4,0xf0,0x70,0xf,0xc1,0xe1,0x80,0x7,0xff,
0xff,0x0,0x1,0xe0,0x0,0x20,0x0,0x0,0xe0,0x70,0x0,0x7,0xe0,0x80,0x7,0xff,
0xfe,0x0,0x0,0x80,0x0,0x0,0x2,0x0,0xe0,0x78,0x0,0xe,0x0,0xe6,0x0,0xff,
0xfe,0x0,0x0,0x80,0x0,0x30,0x6,0x1,0xe0,0x7c,0x0,0x1e,0x0,0xee,0x0,0xff,
0xff,0xff,0xff,0xff,0xff,0xf8,0x1f,0x87,0xe0,0x7f,0x0,0xff,0x0,0x0,0x1,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,0xff,0xff,0x1,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xff,0xff,0xff,0xff,0x81,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc3,0xc1,0xff,0xff,0xff,0xff,0x81,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x83,0xc1,0xff,0xff,0xff,0xff,0xc1,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1,0x83,0xff,0xff,0xff,0xff,0xe1,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x7,0xff,0xff,0xff,0xff,0xe0,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0xf,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xff,0xf8,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x7f,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

static const unsigned char PROGMEM ico_empty_bmp[] =
{
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0,
0x0,0x0
};

static const unsigned char PROGMEM ico_e_bmp[] =
{
0x3f,0xe0,
0x7f,0xf0,
0xff,0xf8,
0xe0,0x38,
0xe0,0x38,
0xe7,0xf8,
0xe0,0x78,
0xe0,0x78,
0xe7,0xf8,
0xe0,0x38,
0xe0,0x38,
0xff,0xf8,
0x7f,0xf0,
0x3f,0xe0
};


static const unsigned char PROGMEM ico_s_bmp[] =
{
0x3f,0xe0,
0x7f,0xf0,
0xf8,0xf8,
0xf0,0x78,
0xe7,0x38,
0xe7,0xf8,
0xf0,0xf8,
0xf8,0x78,
0xff,0x38,
0xe7,0x38,
0xf0,0x78,
0xf8,0xf8,
0x7f,0xf0,
0x3f,0xe0
};

#endif // _INCLUDE_N2kGaugeGfx_H_