#ifndef __TETRIS_H__
#define __TETRIS_H__

#define BOARD_X 8
#define BOARD_Y 8
#define X_LEN 14
#define Y_LEN 16

struct Shape {
	signed char coords[4][2];
	signed char minx, miny, maxx,maxy;
};

void TetrisStart();
void TetrisPause();

void ShapeLeft();
void ShapeRight();
void ShapeUp();
void ShapeDown();
void ShapeRotate();


#endif
