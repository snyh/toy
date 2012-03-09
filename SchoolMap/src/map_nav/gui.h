///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/cshelp.h>
#include <wx/intl.h>

#include <wx/string.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/valgen.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
		virtual void MainFrameBaseOnLeaveWindow( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("校园地图"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxCLIP_CHILDREN|wxTAB_TRAVERSAL|wxWANTS_CHARS );
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogHelp
///////////////////////////////////////////////////////////////////////////////
class DialogHelp : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStdDialogButtonSizer* m_sdbSizer3;
		wxButton* m_sdbSizer3OK;
	
	public:
		
		DialogHelp( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("帮助"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,400 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogHelp();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogShow
///////////////////////////////////////////////////////////////////////////////
class DialogShow : public wxDialog 
{
	private:
	
	protected:
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
	
	public:
		wxStaticBitmap* m_bitmap2;
		wxTextCtrl* m_textCtrl1;
		
		DialogShow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,500 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogShow();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogShow2
///////////////////////////////////////////////////////////////////////////////
class DialogShow2 : public wxDialog 
{
	private:
	
	protected:
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
	
	public:
		wxTextCtrl* m_textCtrl2;
		
		DialogShow2( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~DialogShow2();
	
};

#endif //__gui__
