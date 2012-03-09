///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include "canvas.h"
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/button.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menuBar;
		wxMenu* m_menuFile;
		wxMenu* m_help;
		wxStatusBar* m_statusBar;
		MyCanvas *m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
		virtual void m_loadfileOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_savedataOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_loaddataOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExitClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_aboutOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Map Editer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogAbout
///////////////////////////////////////////////////////////////////////////////
class DialogAbout : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrl3;
	
	public:
		
		DialogAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("关于"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 458,301 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogAbout();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class InterBase
///////////////////////////////////////////////////////////////////////////////
class InterBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText7;
		wxTextCtrl* m_name;
		wxStaticText* m_staticText8;
		wxFilePickerCtrl* m_image;
		wxStaticText* m_staticText9;
		wxTextCtrl* m_value;
		
		wxStdDialogButtonSizer* m_sdbSizer3;
		wxButton* m_sdbSizer3OK;
		wxButton* m_sdbSizer3Cancel;
	
	public:
		
		InterBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 509,386 ), long style = wxDEFAULT_DIALOG_STYLE );
		~InterBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogNew
///////////////////////////////////////////////////////////////////////////////
class DialogNew : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText7;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Cancel;
	
	public:
		wxTextCtrl* m_name;
		wxTextCtrl* m_scale;
		wxFilePickerCtrl* m_image;
		
		DialogNew( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 377,178 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogNew();
	
};

#endif //__gui__
