/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:
 * Created:
 * Copyright:
 * License:   	wxWidgets license (www.wxwidgets.org)
 *
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include "main.h"
#include "my_data.h"
#include "canvas.h"

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// application class implementation
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit() {
	SetTopWindow( new MainFrame( NULL ) );
	GetTopWindow()->Show();
	wxImage::AddHandler(new wxJPEGHandler);
	// true = enter the main loop
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation
////////////////////////////////////////////////////////////////////////////////


MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent ), m_isLoad(false){
}

MainFrame::~MainFrame() {
}

void MainFrame::OnCloseFrame(wxCloseEvent& event) {
	std::cout << "Close Frame\n";
	wxGetApp().ExitMainLoop();
}

void MainFrame::OnExitClick(wxCommandEvent& event) {
	std::cout << "Close Frame\n";
	wxGetApp().ExitMainLoop();
}

void MainFrame::m_loadfileOnMenuSelection(wxCommandEvent& event) {
	
	DialogNew dlg(this);
	if(wxID_OK == dlg.ShowModal()) {
		std::cout << "show see: " << dlg.m_name->GetValue().mb_str() << "\n";
		
		m_canvas->data.map_name = std::string(dlg.m_name->GetValue().mb_str());
		std::cout <<"In  Setting Title begin\n";
		this->SetTitle(dlg.m_name->GetValue());
		std::cout <<"In  Setting Title\n";
		dlg.m_scale->GetValue().ToDouble(&(m_canvas->data.scale));
		
		std::cout <<"In  Setting Image1\n";
		m_canvas->data.image = dlg.m_image->GetPath().mb_str();
		std::cout <<"In  Setting Image2\n";
		m_canvas->SetImage(new wxBitmap(dlg.m_image->GetPath(), wxBITMAP_TYPE_JPEG));
		
		std::cout << "map name: " << m_canvas->data.map_name << "\n";
		std::cout << "map scale: " << m_canvas->data.scale << "\n";
		std::cout << "map image path: " << m_canvas->data.image << "\n";
		
		SetMaxSize(wxSize(m_canvas->data.m_bit->GetWidth(), m_canvas->data.m_bit->GetHeight()));
		Fit();
		Refresh();
	} else {
		std::cout <<"No Ok\n";
	}
}

void MainFrame::m_loaddataOnMenuSelection(wxCommandEvent& event) {
	wxFileDialog *dialog = new wxFileDialog(this, _("Select the map data file"));
	//dialog->SetWildcard(_T("Map Data files(*.*)| *.*"));
	if(wxID_OK == dialog->ShowModal()) {
		wxString file_name = dialog->GetPath();
		DataLoadFrom(file_name, m_canvas->data);
		this->SetTitle(wxString(m_canvas->data.map_name.c_str(), wxConvLocal));
		//TODO shou drop into m_canvs::refresh();
		m_canvas->SetVirtualSize(m_canvas->data.m_bit->GetWidth(), m_canvas->data.m_bit->GetHeight());
		m_canvas->SetScrollRate(1,1);
		m_canvas->GetParent()->SetMaxSize(wxSize(m_canvas->data.m_bit->GetWidth(), m_canvas->data.m_bit->GetHeight()));
	}
}

void MainFrame::m_savedataOnMenuSelection(wxCommandEvent& event) {
	wxFileDialog *dialog = new wxFileDialog(this, _("Select the map data file"));
	//dialog->SetWildcard(_T("Map Data files(*.snyh)| *.snyh"));
	dialog->SetWindowStyle(wxFD_SAVE);
	if(wxID_OK == dialog->ShowModal()) {
		wxString file_name = dialog->GetPath();
		DataSaveTo(file_name, m_canvas->data);
	}
}
void MainFrame::m_aboutOnMenuSelection(wxCommandEvent& event) {
	DialogAbout dlg(NULL);
	dlg.ShowModal();
	dlg.Destroy();
}

