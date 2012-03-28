#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <8051.h>

#define LCD_DATA P0
#define LCD_RST P2_7
#define LCD_RD P3_2
#define LCD_WR P3_3
#define LCD_CD P2_5
#define LCD_CS P2_6
#define LCD_X_SIZE 128
#define LCD_Y_SIZE 160
#define LCD_CHAR 20

#define IR_IN P3_2
#define IR_RIGHT 0x01
#define IR_LEFT 0x02
#define IR_UP 0x04
#define IR_DOWN 0x08

#define BOARD_X_SIZE 14
#define BOARD_Y_SIZE 16

#define uchar unsigned char

#endif
