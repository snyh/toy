#include "MainFrame.h"

#include <wx/wx.h>
class MyApp: public wxApp {
public:
  virtual bool OnInit() {
	  MainFrame *frame = new MainFrame(NULL);
	  frame->Show(true);
	  return true;
  }
};
DECLARE_APP(MyApp);

IMPLEMENT_APP(MyApp);
