#include "config.h"
#include "lcd.h"
#include <math.h>


uchar ReadState()
{
  uchar temp;
  LCD_DATA = 0xff;
  LCD_CD = 1;
  LCD_RD = 0;
  temp = LCD_DATA;
  LCD_RD = 1;
  return temp;
}

void LcdEnable()
{
#if 0
  uchar i;
  for (i=10; i>0; i--)
	if ((ReadState() & 0x03) == 0x03)
	  break;
#endif
}

void WriteCmd(unsigned char value)
{
  LcdEnable();
  LCD_CD = 1;
  LCD_DATA = value;
  LCD_WR = 0;
  LCD_WR = 1;
}

void WriteCmd1(uchar data1, uchar cmd)
{
  LcdEnable();
  LCD_CD = 0;
  LCD_DATA = data1;
  LCD_WR = 0;
  LCD_WR = 1;
  LcdEnable();
  LCD_CD = 1;
  LCD_DATA = cmd;
  LCD_WR = 0;
  LCD_WR = 1;
}

void WriteCmd2(uchar d1, uchar d2, uchar cmd)
{
  LcdEnable();
  LCD_CD = 0;
  LCD_DATA = d1;
  LCD_WR = 0;
  LCD_WR = 1;

  LcdEnable();
  LCD_CD = 0;
  LCD_DATA = d2;
  LCD_WR = 0;
  LCD_WR = 1;

  LcdEnable();
  LCD_CD = 1;
  LCD_DATA = cmd;
  LCD_WR = 0;
  LCD_WR = 1;
}

void DrawInit()
{
  WriteCmd2(0x0, 0x00, 0x42);
  WriteCmd2(0x14, 0x0, 0x43);
  WriteCmd(0x98); //graph & text
}

void CleanRectangle(int x, int y, int width, int height)
{
  int i, j, addr;
  y = y * 8;
  for (i=0; i < 8*height; i++) {

	  addr = (y+i) * LCD_CHAR + x;
	  WriteCmd2(addr&0xff, addr/256, 0x24);

	  for (j=0; j<width; j++) {
		  WriteCmd1(0x0, 0xc0);
	  }
  }
}

void DrawSquare(int x, int y)
{
  int i, addr;
  y = y * 8;
  for (i=0; i < 8; i++) {
	  addr = (i+y) * LCD_CHAR + x;
	  WriteCmd2(addr&0xff, addr/256, 0x24);
	  WriteCmd1(0xff, 0xc4);
  }
}
