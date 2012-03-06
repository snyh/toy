#include <vector>

#include <Wt/WPaintedWidget>
#include <Wt/WContainerWidget>
#include <Wt/WTimer>
#include <Wt/WPainter>
#include <Wt/WLineEdit>

#include "Shape.h"


class BoardWidget : public Wt::WPaintedWidget {
public:
  BoardWidget(Wt::WContainerWidget *parent = 0);
  void start();
  void pause();
  //void linesRemovedChanged(int numLines);
  Wt::WLineEdit *status_bar;
protected:
  virtual void paintEvent(Wt::WPaintDevice *paintDevice);
  void onKeyDown(const Wt::WKeyEvent&);
  void onTimer();
private:
  
  Tetrominoes& shapeAt(int x, int y) { return board[(y*board_width)+x]; }

  int squareWidth() { return width().toPixels() / board_width; }
  int squareHeight() { return height().toPixels() / board_height; }

  void clearBoard();
  void dropDown();
  void oneLineDown();
  void pieceDropped();
  void removeFullLines();
  void newPiece();
  bool tryMove(const Shape& new_piece, int new_x, int new_y);
  void drawSquare(Wt::WPainter &painter, int x, int y, Tetrominoes shape);

  Wt::WTimer *timer;

  bool is_started;
  bool is_paused;
  bool is_falling_finished;
  Shape cur_piece;
  int cur_x;
  int cur_y;
  int num_lines_removed;
  std::vector<Tetrominoes> board;

  int board_width;
  int board_height;

};
