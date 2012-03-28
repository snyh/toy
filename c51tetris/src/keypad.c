#include "config.h"
#include "tetris.h"

void delay014ms(uchar x);
void decode(uchar cmd);

/*
 * We  use NEC Protocol to communication (little modification in address code).
 * USE PWM encode 1 and 0.
 * detail information can google NEC Protocol and ht6221.
 */
uchar counter=0;
void IRDecode() 
{
  uchar IRCOM[4] = {0, 0, 0, 0};
  uchar j,k, n=0;
  EX0 = 0;  //close interrupt.
  P1 = counter++;

  P2_0 = 0;

  //we'll quit if the IR_IN's value is noise,
  //normal value should start with 9ms low voltage, and 4.5ms high voltage .
  delay014ms(15); //only 0.14ms*15=2.1ms 
  if (IR_IN) {
	  EX0 = 1;
	  P1 = 0x55;
	  return;
  }

  while (!IR_IN) //pass 9ms low voltage
	;
  P2_0 = 1;
  while (IR_IN) // pass 4.5ms  high voltage
	;
  P2_0 = 0;
  for (j=0; j<4; j++) {
	  for (k=0; k<8; k++) {
		  while (!IR_IN) // pass 0.56ms low voltage
			;

		  //count the high voltage time to dedicate 1(1.68ms) or 0(0.56ms)
		  while (IR_IN) {
			  delay014ms(1);
			  n++;
			  if (n >= 30) {  //high voltage time exceed 0.14*30=4.2ms
				  EX0 = 1;
				  return;
			  }
		  }
		  // the NEC Protocol is LSB in first, so we need right shift bit.
		  IRCOM[j] = IRCOM[j] >> 1;

		  if (n >= 8) { 
			  //high voltage time exceed 0.14ms*8=1.12ms,
			  //biger than 0.56ms so this value is 1.
			  IRCOM[j] = IRCOM[j] | 0x80;
		  } else {
			  // otherwise the value is 0, and in C there not need handle.
		  }
		  n = 0;
	  }
  }


  if (IRCOM[2] != ~IRCOM[3]) {
	  //byte 3 should inversely equal byte 2(command code) for reliabilty.
	  EX0 = 1;
	  return;
  }

  decode(IRCOM[3]); //we only use the command code.

  EX0 = 1; // open the interrupt for receiving next command.
}

void decode(uchar cmd)
{
  switch (cmd) {
	case IR_LEFT:	ShapeLeft(); break;
	case IR_RIGHT:	ShapeRight(); break; 
	case IR_UP:	ShapeRotate(); break;
	case IR_DOWN:	ShapeDown(); break;
  }
}
void delay014ms(uchar x)
{
  uchar i;
  while(x--) {
	  for (i=0; i<13;i++)
		;
  }
}

void delay20us(uchar x)
{
  unsigned char a, b, c;
  for (a=0; a<1; a++)
	for (b=0; b<1; b++)
	  for (c=0; c<8; c++);
}
