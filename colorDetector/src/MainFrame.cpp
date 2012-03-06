#include "MainFrame.h"
#include "Control.hpp"
#include <wx/dcclient.h>

MainFrame::MainFrame( wxWindow* parent )
:
ColorDetectFrame( parent )
{

}

void MainFrame::OnSliderScroll( wxScrollEvent& event )
{
  Control::getInstance()->setThreshold(event.GetPosition());
  // process the image
  Control::getInstance()->process();

  //show the result image;
  this->processed_image->SetBitmap(Control::getInstance()->getResult());
}

void MainFrame::OnColourChanged( wxColourPickerEvent& event )
{
  wxColour color = event.GetColour();
  Control::getInstance()->setTargetColor(color.Red(), color.Green(),
										 color.Blue());
  // process the image
  Control::getInstance()->process();

  //show the result image;
  this->processed_image->SetBitmap(Control::getInstance()->getResult());
}

void MainFrame::OnFileChanged( wxFileDirPickerEvent& event )
{
  wxString path = event.GetPath();
  Control::getInstance()->setTargetPath(path.char_str());

  //show the source image
  this->source_image->SetBitmap(wxBitmap(path));

  // process the image
  Control::getInstance()->process();

  //show the result image;
  this->processed_image->SetBitmap(Control::getInstance()->getResult());

  if (Control::getInstance()->isLoaded()) {
	  this->m_slider->Enable();
	  this->color_button->Enable();
  }
}

void MainFrame::OnLeftDown( wxMouseEvent& event )
{
  wxWindowDC dc(source_image);
  wxPoint point = event.GetLogicalPosition(dc);
  wxColour color;
  dc.GetPixel(point, &color);

  Control::getInstance()->setTargetColor(color.Red(), color.Green(),
										 color.Blue());
  // process the image
  Control::getInstance()->process();

  //show the result image;
  this->processed_image->SetBitmap(Control::getInstance()->getResult());

  //set the color button
  this->color_button->SetColour(color);
}

