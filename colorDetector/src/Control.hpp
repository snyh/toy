#ifndef __CONTROL_HPP__
#define __CONTROL_HPP__

#include "Model.hpp"
#include <wx/bitmap.h>
#include <wx/image.h>

class Control {
public:
  static Control* getInstance();
  void setTargetColor(unsigned char red, unsigned char gree,
					  unsigned char blue);

  bool isLoaded() { return Loaded; }
  void process();

  void setTargetPath(const char* filepath);
  wxBitmap getResult();

  void setThreshold(int distance);
  int getThreshold();

private:
  Control(): Loaded(false) { model_ = new Model;}
  static Control* singleton_;
  Model* model_;
  bool Loaded;
  wxImage result;
};

#endif
