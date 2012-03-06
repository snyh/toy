#include "BoardWidget.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include <Wt/WString>
#include <Wt/WColor>
#include <Wt/WPen>

using namespace Wt;
using namespace std;

BoardWidget::BoardWidget(WContainerWidget* parent)
     : WPaintedWidget(parent)
{
  //设置tabindex属性 否则无法接受键盘时间
  this->setAttributeValue("tabindex", "1");

  board_width = 10*3; 
  board_height = 22;
  resize(board_width*18, board_height*18);
  for(int i=0; i<board_width*board_height; ++i)
    board.push_back(NoShape);

  timer = new WTimer(parent);

  is_falling_finished = false;
  is_started = false;
  is_paused = false;
  num_lines_removed = 0;

  cur_x = 0;
  cur_y = 0;


  status_bar = new WLineEdit(parent);
  status_bar->setReadOnly(true);

  clearBoard();
  timer->timeout().connect(this, &BoardWidget::onTimer);

  this->keyWentDown().connect(this, &BoardWidget::onKeyDown);
}

void BoardWidget::start()
{
  if(is_paused)
    return;
  is_started = true;
  is_falling_finished = false;
  num_lines_removed = 0;
  clearBoard();

  newPiece();
  timer->setInterval(300);
  timer->start();
}

void BoardWidget::pause()
{
  if(!is_started)
    return;

  is_paused = !is_paused;
  if (is_paused) {
      timer->stop();
      status_bar->setText("Paused");
  } else {
      status_bar->setText("ReStarted");
      timer->start();
  }
  this->update();
}

void BoardWidget::paintEvent(WPaintDevice *paintDevice)
{
  WPainter painter(paintDevice);

  int board_top = this->height().toPixels() - board_height * squareHeight();

  for (int i=0; i < board_height; ++i) {
      for (int j=0; j < board_width; ++j) {
	  Tetrominoes shape = shapeAt(j, board_height - i - 1);
	  if (shape != NoShape)
	    drawSquare(painter, 
		       0 + j*squareWidth(), board_top+ i*squareHeight(),
		       shape);
      }
  }

  if (cur_piece.GetShape() != NoShape) {
      for (int i=0; i<4; ++i) {
	  int x = cur_x + cur_piece.x(i);
	  int y = cur_y - cur_piece.y(i);
	  drawSquare(painter, 0 + x*squareWidth(),
		     board_top + (board_height-y-1)*squareHeight(),
		     cur_piece.GetShape());
      }
  }
}

void BoardWidget::onKeyDown(const WKeyEvent& event)
{
  cout << "key down event...\n";
  if(!is_started || cur_piece.GetShape() == NoShape)
    return;

  Wt::Key key_code = event.key();

  if (key_code == Key_P) {
      pause();
      return;
  }

  if(is_paused)
    return;

  switch (key_code) {
    case Key_Left:
      tryMove(cur_piece, cur_x-1, cur_y); break;
    case Key_Right:
      tryMove(cur_piece, cur_x+1, cur_y); break;
    case Key_Down:
      tryMove(cur_piece.RotateRight(), cur_x, cur_y); break;
    case Key_Up:
      tryMove(cur_piece.RotateLeft(), cur_x, cur_y); break;
    case Key_Space:
      dropDown(); break;
    case Key_D:
      oneLineDown(); break;
  }
}

void BoardWidget::onTimer()
{
  if (is_falling_finished) {
      is_falling_finished = false;
      newPiece();
  } else {
      oneLineDown();
  }
}

void BoardWidget::clearBoard()
{
  for(int i=0; i<board_height*board_width; ++i) {
      board[i] = NoShape;
  }
}

void BoardWidget::dropDown()
{
  int new_y = cur_y;
  while (new_y > 0) {
      if(!tryMove(cur_piece, cur_x, new_y-1))
	break;
      --new_y;
  }
  pieceDropped();
}

void BoardWidget::oneLineDown()
{
  if(!tryMove(cur_piece, cur_x, cur_y-1))
    pieceDropped();
}

void BoardWidget::pieceDropped()
{
  for (int i=0; i<4; ++i) {
      int x = cur_x + cur_piece.x(i);
      int y = cur_y - cur_piece.y(i);
      shapeAt(x, y) = cur_piece.GetShape();
  }

  removeFullLines();

  if(!is_falling_finished)
    newPiece();
}

void BoardWidget::removeFullLines()
{
  int num_full_liens = 0;
  for (int i = board_height-1; i>=0; --i) {
      bool line_is_full = true;

      for (int j=0; j<board_width; ++j) {
	  if (shapeAt(j, i) == NoShape) {
	      line_is_full = false;
	      break;
	  }
      }

      if (line_is_full) {
	  ++num_full_liens;
	  for (int k=i; k<board_height-1; ++k) {
	      for(int j=0; j<board_width; ++j)
		shapeAt(j, k) = shapeAt(j, k+1);
	  }
      }
  }

  if (num_full_liens > 0) {
      num_lines_removed += num_full_liens;
      
      std::string s;
      s = boost::lexical_cast<string>(num_lines_removed);
      status_bar->setText(WString(s));

      is_falling_finished = true;
      cur_piece.SetShape(NoShape);

      this->update();
  }
}

void BoardWidget::newPiece()
{
  cur_piece.SetRandomShape();
  cur_x = board_width/2 + 1;
  cur_y = board_height-1 + cur_piece.MinY();

  if (!tryMove(cur_piece, cur_x, cur_y)) {
      cur_piece.SetShape(NoShape);
      timer->stop();
      is_started = false;
      status_bar->setText("game over");
  }

}

bool BoardWidget::tryMove(const Shape& new_piece, int new_x, int new_y)
{
  for (int i=0; i<4; ++i) {
      int x = new_x + new_piece.x(i);
      int y = new_y - new_piece.y(i);

      if(x<0 || x>=board_width || y<0 || y>=board_height){
	  return false;
      }

      if(shapeAt(x, y) != NoShape){
	  return false;
      }
  }

  cur_piece = new_piece;
  cur_x = new_x;
  cur_y = new_y;
  this->update();
  return true;
}


void BoardWidget::drawSquare(WPainter& painter, int x, int y, Tetrominoes shape)
{
  static WColor colors[] = { WColor(0,0,0), WColor(204, 102, 102),
      WColor(102,204,102), WColor(102,102,204), WColor(204,204,102),
      WColor(204,102, 204), WColor(102,204, 204), WColor(218, 170,0)};
  static WColor light[] = { WColor(0,0,0), WColor(248,159,171),
      WColor(121,252,121), WColor(121,121,252), WColor(252,252,121),
      WColor(252, 121, 252), WColor(121,252,252), WColor(252,198,0)};
  static WColor dark[] = { WColor(0,0,0), WColor(128,59, 59),
      WColor(59,128,59), WColor(59,59,128), WColor(128,128,59),
      WColor(128,59,128), WColor(59,128,128), WColor(128,98,0)};


  painter.setPen(WPen(light[int(shape)]));
  painter.drawLine(x, y+squareHeight()-1,
		   x, y);
  painter.drawLine(x, y,
		   x+squareWidth()-1, y);



  painter.setPen(WPen(dark[int(shape)]));
  painter.drawLine(x+1, y+squareHeight()-1,
		   x+squareWidth()-1, y+squareHeight()-1);
  painter.drawLine(x+squareWidth()-1, y+squareHeight()-1,
		   x+squareWidth()-1, y+1);



  painter.setPen(WPen(NoPen));
  painter.setBrush(WBrush(colors[int(shape)]));
  painter.drawRect(x+1, y+1, squareWidth()-2, squareHeight()-2);
}
