#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <8051.h>
#include "tetris.h"
#include "lcd.h"
#define false 0
#define true 1

struct Shape currentShape;
const struct Shape shapes[7] = {
	  {
		  {{0,-1}, {0,0}, {-1,0}, {-1,1}},
		  -1, -1,
		  0, 1,
	  },
	  {
		  {{0,-1},{0,0},{1,0},{1,1}},
		  0, -1,
		  1, 1,
	  },
	  {
		  {{0,-1},{0,0},{0,1},{0,2}},
		  0, -1,
		  0, 2,
	  },
	  {
		  {{-1,0},{0,0},{1,0},{0,1}},
		  -1, 0,
		  1, 1,
	  },
	  {
		  {{0,0},{1,0},{0,1},{1,1}},
		  0, 0,
		  1, 1,
	  },
	  {
		  {{-1,-1},{0,-1},{0,0},{0,1}},
		  -1, -1,
		  0, 1,
	  },
	  {
		  {{1,-1},{0,-1},{0,0},{0,1}},
		  0, -1,
		  1, 1,
	  }
};

unsigned char c_x, c_y;
unsigned char isFallingFinished;
unsigned char level;
unsigned char score;
unsigned char timer_counter;
unsigned char __idata board[14][2]; // 14*16 / 8;

void DrawShape(void);
void NewPiece();
void RemoveFullLines();
void OneLineDown();
int TryMove(int newX, int newY);
void RemoveFullLines();
int HasSquare(int x, int y);
void GameOver() { P1 = 0;}

int HasSquare(int x, int y)
{
  return board[x][y/8] & (0x1 << (7-y%8));
}

void main(void)
{
  isFallingFinished = false;
  level = 100;
  score = 0;
  timer_counter = 0;

  DrawInit();
  NewPiece();

  EA = 1;
  //timer 0 init.
  TMOD |= 0x01;
  TH0 = 175;
  TL0 = 60;
  ET0 = 1;
  TR0 = 1;

  //IR (EX0) init.
  IR_IN = 1;
  EX0 = 1;
  TCON |= 0x01;
}

void IRDecode(void);
void _IRDecode() __interrupt 0  __using 0
{
  IRDecode();
}

void OneLineDown()
{
  int i;
  signed char x,y;
  if (TryMove(c_x, c_y+1)) {
	  CleanRectangle(currentShape.minx + c_x,
					 currentShape.miny + c_y-1,
					 currentShape.maxx - currentShape.minx + 1,
					 currentShape.maxy - currentShape.miny + 1);
	  DrawShape();
  } else {
	  for (i=0; i<4; i++) {
		  x = c_x + currentShape.coords[i][0];
		  y = c_y + currentShape.coords[i][1];
		  board[x][y/8] |= 1 << (7-y%8);
	  }
	  NewPiece();
  }
  RemoveFullLines();
}
void RemoveFullLines()
{

}
void NewPiece()
{
  memcpy(&currentShape, &(shapes[rand()%6]), sizeof(struct Shape));
  c_x = X_LEN / 2;
  c_y = -currentShape.miny;
  if (TryMove(c_x, c_y)) {
	  DrawShape();
  } else {
	  TR0 = 0;
	  GameOver();
  }
}

int TryMove(int newX, int newY)
{
  signed char x, y;
  signed char i;
  for(i=3; i>=0; i--) {
	  x = currentShape.coords[i][0] + newX;
	  y = currentShape.coords[i][1] + newY;
	  if (x<0 || x>= X_LEN || y<0 || y>=Y_LEN || HasSquare(x,y))
		return false;
  }
  c_x = newX;
  c_y = newY;
  return true;
}

void DrawShape()
{
  DrawSquare(currentShape.coords[0][0]+c_x, currentShape.coords[0][1]+c_y);
  DrawSquare(currentShape.coords[1][0]+c_x, currentShape.coords[1][1]+c_y);
  DrawSquare(currentShape.coords[2][0]+c_x, currentShape.coords[2][1]+c_y);
  DrawSquare(currentShape.coords[3][0]+c_x, currentShape.coords[3][1]+c_y);
}

void Timer0(void) __interrupt 1
{
  timer_counter++;
  if (timer_counter*5 >= (level-score)) {
	  timer_counter=0;
	  if (isFallingFinished) {
		  isFallingFinished = false;
		  NewPiece();
	  } else {
		  OneLineDown();
	  }
  }
  TH0 = 175;
  TL0 = 60;
  TR0 = 1;
}

void ShapeLeft()
{
  TryMove(c_x-1, c_y);
}
void ShapeRight()
{
  TryMove(c_x+1, c_y);
}
void ShapeRotate()
{

}
void ShapeDown()
{
  TryMove(c_x, c_y+1);
}
