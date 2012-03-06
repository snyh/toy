#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WVBoxLayout>

#include "BoardWidget.h"


using namespace Wt;

class TetrisApp : public WApplication {
public:
  TetrisApp(const WEnvironment& env);
};

TetrisApp::TetrisApp(const WEnvironment& env)
     : WApplication(env)
{
  setTitle("Tetris Game C++ Web version");


  root()->setPadding(10);
  root()->setOverflow(WContainerWidget::OverflowAuto);


  WVBoxLayout *vLayout = new WVBoxLayout();
  BoardWidget *b = new BoardWidget();
  vLayout->addWidget(b);
  vLayout->addWidget(b->status_bar);


  root()->setLayout(vLayout, AlignCenter | AlignTop);

  b->start();

  //WHBoxLayout *hLayout = new WHBoxLayout();
}


WApplication *createApplication(const WEnvironment& env)
{
  return new TetrisApp(env);
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}
