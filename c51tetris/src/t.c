#include <8051.h>

unsigned char key;

void DetectKey();
void HandleKey();
void send(char v, char time);

void delay()
{
  int j=900;
  while(j--);
}

void main()
{
  delay();
  do {
	  key = 0x2;
	  P1_0 = 1;
	  //DetectKey();
	  HandleKey();
  } while (0);
}

void HandleKey()
{
  unsigned char t = key;
  unsigned char i;
  if (key) {
	  P3 = key;
	  send(0, 48);
	  send(1, 28);
	  for (i=0; i<8; i++) {
		  send(0, 1);
		  send(1, 1);
	  }
	  for (i=0; i<8; i++) {
		  send(0, 1);
		  send(1, 3);
	  }
	  for (i=0; i<8; i++) {
		  send(0, 1);
		  send(1, (t & (0x1 <<i)) ? 3 : 1);
	  }
	  t = ~t;
	  for (i=0; i<8; i++) {
		  send(0, 1*1);
		  send(1, (t & (0x1 <<i)) ? 3 : 1);
	  }
  }
}


void DetectKey()
{
  if (P2_0 == 0) {
	  while (!P2_0)
		;
	  key = 1;
  } else if (P2_1 == 0) {
	  while (!P2_1)
		;
	  key = 2;
  } else if (P2_2 == 0) {
	  while (!P2_2)
		;
	  key = 4;
  } else if (P2_3 == 0) {
	  while (!P2_3)
		;
	  key = 8;
  }
}

void send(char v, char time)
{
  int i;
  while(time--) {
	  for (i=0; i<48; i++) {
		  P1_0 = v;
	  }
  }
}
