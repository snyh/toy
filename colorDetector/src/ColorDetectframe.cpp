///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ColorDetectframe.h"

///////////////////////////////////////////////////////////////////////////

ColorDetectFrame::ColorDetectFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Threshold"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_slider = new wxSlider( this, wxID_ANY, 100, 1, 255, wxDefaultPosition, wxDefaultSize, wxSL_LABELS|wxSL_VERTICAL );
	m_slider->Enable( false );
	
	bSizer2->Add( m_slider, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	color_button = new wxColourPickerCtrl( this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	color_button->Enable( false );
	
	bSizer2->Add( color_button, 0, wxALL, 5 );
	
	file_button = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a image for Process"), wxT("All image file (*.jpg;*.gif;*.png;*.bmp)|*.jpg;*.gif;*.png;*.bmp|ALL file (*.*)|*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	bSizer2->Add( file_button, 0, wxALL, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	source_image = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( source_image, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer3->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	processed_image = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( processed_image, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_slider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	color_button->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ColorDetectFrame::OnColourChanged ), NULL, this );
	file_button->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( ColorDetectFrame::OnFileChanged ), NULL, this );
	source_image->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ColorDetectFrame::OnLeftDown ), NULL, this );
}

ColorDetectFrame::~ColorDetectFrame()
{
	// Disconnect Events
	m_slider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	m_slider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( ColorDetectFrame::OnSliderScroll ), NULL, this );
	color_button->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ColorDetectFrame::OnColourChanged ), NULL, this );
	file_button->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( ColorDetectFrame::OnFileChanged ), NULL, this );
	source_image->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( ColorDetectFrame::OnLeftDown ), NULL, this );
	
}
