///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ColorDetectframe__
#define __ColorDetectframe__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/slider.h>
#include <wx/clrpicker.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/statline.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ColorDetectFrame
///////////////////////////////////////////////////////////////////////////////
class ColorDetectFrame : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxSlider* m_slider;
		wxColourPickerCtrl* color_button;
		wxFilePickerCtrl* file_button;
		wxStaticBitmap* source_image;
		wxStaticLine* m_staticline1;
		wxStaticBitmap* processed_image;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSliderScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnColourChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnFileChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		ColorDetectFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OpenCV Demo color Detecter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~ColorDetectFrame();
	
};

#endif //__ColorDetectframe__
