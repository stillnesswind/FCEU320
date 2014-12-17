/*
font converted from zfont.txt included with zsnes
*/

#include "types.h"

uint8 font_zsnes_map[] = {
	' ','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E',
	'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
	'V','W','X','Y','Z','-','_','~','.','/','<','>','[',']',':','&',
	1  ,'#','=','\"','\\','*','?','%','+',',','(',')','@','\'','!','$',
	';','^','{','}',255,2   ,3  ,4  ,5  ,6  ,7  ,8  ,9  ,10 ,11, 12
};

uint8 font_zsnes_char_width = 5;
uint8 font_zsnes_char_height = 5;
uint8 font_zsnes[] = {
	0x00,0x00,0x00,0x00,0x00,0x0E,0x13,0x15,0x19,0x0E,0x04,0x0C,0x04,0x04,0x0E,0x0E,
	0x11,0x06,0x08,0x1F,0x0E,0x11,0x06,0x11,0x0E,0x0A,0x12,0x1F,0x02,0x02,0x1F,0x10,
	0x1E,0x01,0x1E,0x0E,0x10,0x1E,0x11,0x0E,0x1F,0x01,0x02,0x02,0x02,0x0E,0x11,0x0E,
	0x11,0x0E,0x0E,0x11,0x0F,0x01,0x0E,0x0E,0x11,0x1F,0x11,0x11,0x1E,0x11,0x1E,0x11,
	0x1E,0x0E,0x11,0x10,0x11,0x0E,0x1E,0x11,0x11,0x11,0x1E,0x1F,0x10,0x1E,0x10,0x1F,
	0x1F,0x10,0x1E,0x10,0x10,0x0F,0x10,0x13,0x11,0x0E,0x11,0x11,0x1F,0x11,0x11,0x1F,
	0x04,0x04,0x04,0x1F,0x0F,0x02,0x02,0x12,0x0C,0x12,0x14,0x1C,0x12,0x11,0x10,0x10,
	0x10,0x10,0x1F,0x1B,0x15,0x15,0x15,0x11,0x19,0x15,0x15,0x15,0x13,0x0E,0x11,0x11,
	0x11,0x0E,0x1E,0x11,0x1E,0x10,0x10,0x0E,0x11,0x15,0x12,0x0D,0x1E,0x11,0x1E,0x12,
	0x11,0x0F,0x10,0x0E,0x01,0x1E,0x1F,0x04,0x04,0x04,0x04,0x11,0x11,0x11,0x11,0x0E,
	0x11,0x11,0x0A,0x0A,0x04,0x11,0x15,0x15,0x15,0x0A,0x11,0x0A,0x04,0x0A,0x11,0x11,
	0x0A,0x04,0x04,0x04,0x1F,0x02,0x04,0x08,0x1F,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1F,0x0D,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x01,0x02,0x04,
	0x08,0x10,0x02,0x04,0x08,0x04,0x02,0x08,0x04,0x02,0x04,0x08,0x0E,0x08,0x08,0x08,
	0x0E,0x0E,0x02,0x02,0x02,0x0E,0x00,0x04,0x00,0x04,0x00,0x0C,0x13,0x0E,0x13,0x0D,
	0x04,0x04,0x15,0x0E,0x04,0x0A,0x1F,0x0A,0x1F,0x0A,0x00,0x1F,0x00,0x1F,0x00,0x09,
	0x12,0x00,0x00,0x00,0x10,0x08,0x04,0x02,0x01,0x15,0x0E,0x1F,0x0E,0x15,0x0E,0x11,
	0x06,0x00,0x04,0x11,0x02,0x04,0x08,0x11,0x04,0x04,0x1F,0x04,0x04,0x00,0x00,0x00,
	0x04,0x08,0x06,0x08,0x08,0x08,0x06,0x0C,0x02,0x02,0x02,0x0C,0x0E,0x13,0x17,0x10,
	0x0E,0x04,0x08,0x00,0x00,0x00,0x04,0x04,0x04,0x00,0x04,0x0F,0x14,0x0E,0x05,0x1E,
	0x00,0x04,0x00,0x04,0x08,0x08,0x04,0x00,0x00,0x00,0x04,0x0A,0x00,0x00,0x00,0x06,
	0x08,0x18,0x08,0x06,0x0C,0x02,0x03,0x02,0x0C,0x04,0x04,0x0E,0x0E,0x1F,0x1F,0x0E,
	0x0E,0x04,0x04,0x01,0x07,0x1F,0x07,0x01,0x10,0x1C,0x1F,0x1C,0x10,0x04,0x0C,0x1F,
	0x0C,0x04,0x07,0x04,0x06,0x01,0x16,0x1F,0x10,0x1F,0x00,0x00,0x00,0x1F,0x00,0x00,
	0x00,0x1F,0x11,0x11,0x11,0x1F,0x00,0x00,0x04,0x0A,0x04,0x0E,0x08,0x08,0x08,0x00,
	0x00,0x02,0x02,0x02,0x0E,0x00,0x00,0x00,0x08,0x04,0x00,0x04,0x0E,0x04,0x00,0x1F,
	0x01,0x1E,0x04,0x18,0x00,0x1F,0x0A,0x0C,0x08,0x00,0x02,0x04,0x1C,0x04,0x00,0x04,
	0x1F,0x11,0x06,0x00,0x00,0x1F,0x04,0x1F,0x00,0x02,0x1F,0x06,0x1A,0x00,0x08,0x1F,
	0x0A,0x08,0x00,0x00,0x1E,0x02,0x1F,0x00,0x1F,0x01,0x0F,0x1F,0x00,0x15,0x15,0x02,
	0x0C,0x00,0x10,0x0F,0x00,0x00,0x1F,0x05,0x06,0x04,0x18,0x01,0x06,0x1C,0x04,0x04,
	0x04,0x1F,0x11,0x02,0x0C,0x1F,0x04,0x04,0x04,0x1F,0x02,0x1F,0x06,0x0A,0x12,0x08,
	0x1F,0x09,0x09,0x13,0x04,0x1F,0x04,0x1F,0x04,0x08,0x0F,0x11,0x02,0x0C,0x08,0x0F,
	0x12,0x02,0x0C,0x1F,0x01,0x01,0x01,0x1F,0x0A,0x1F,0x0A,0x02,0x0C,0x08,0x15,0x09,
	0x02,0x1C,0x1F,0x01,0x02,0x06,0x19,0x08,0x1F,0x0A,0x08,0x07,0x11,0x09,0x01,0x02,
	0x0C,0x08,0x0F,0x19,0x06,0x0C,0x1F,0x04,0x1F,0x04,0x08,0x15,0x15,0x01,0x02,0x0C,
	0x1F,0x00,0x1F,0x04,0x18,0x08,0x08,0x0C,0x0A,0x08,0x04,0x1F,0x04,0x04,0x08,0x1E,
	0x00,0x00,0x00,0x1F,0x1F,0x01,0x05,0x02,0x0D,0x04,0x1F,0x01,0x0E,0x15,0x01,0x01,
	0x01,0x02,0x0C,0x0A,0x0A,0x0A,0x11,0x11,0x10,0x13,0x1C,0x10,0x0F,0x1F,0x01,0x01,
	0x02,0x0C,0x08,0x14,0x12,0x01,0x00,0x04,0x1F,0x0E,0x15,0x04,0x1F,0x01,0x12,0x0C,
	0x04,0x1F,0x00,0x1F,0x00,0x1F,0x04,0x08,0x08,0x12,0x1F,0x01,0x09,0x06,0x06,0x19,
	0x1F,0x04,0x1F,0x04,0x07,0x08,0x1F,0x09,0x04,0x04,0x1E,0x02,0x02,0x02,0x1F,0x1F,
	0x01,0x1F,0x01,0x1F,0x1F,0x00,0x1F,0x02,0x0C,0x11,0x11,0x11,0x02,0x0C,0x0C,0x0C,
	0x0D,0x0D,0x16,0x10,0x10,0x11,0x11,0x1E,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x11,0x01,
	0x02,0x0C,0x10,0x09,0x01,0x02,0x1C,0x14,0x14,0x00,0x00,0x00,0x08,0x14,0x08,0x00,
	0x00,
};
