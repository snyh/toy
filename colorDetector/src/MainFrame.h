#ifndef __MainFrame__
#define __MainFrame__

/**
@file
Subclass of ColorDetectFrame, which is generated by wxFormBuilder.
*/

#include "ColorDetectframe.h"

//// end generated include

/** Implementing ColorDetectFrame */
class MainFrame : public ColorDetectFrame
{
	protected:
		// Handlers for ColorDetectFrame events.
		void OnSliderScroll( wxScrollEvent& event );
		void OnColourChanged( wxColourPickerEvent& event );
		void OnFileChanged( wxFileDirPickerEvent& event );
		void OnLeftDown( wxMouseEvent& event );
	public:
		/** Constructor */
		MainFrame( wxWindow* parent );
	//// end generated class members
	
};

#endif // __MainFrame__