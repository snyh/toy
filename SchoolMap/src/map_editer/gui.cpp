///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	this->SetExtraStyle( wxWS_EX_PROCESS_UI_UPDATES );
	
	m_menuBar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_loadfile;
	m_loadfile = new wxMenuItem( m_menuFile, wxID_ANY, wxString( _("新建地图数据") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_loadfile );
	
	wxMenuItem* m_savedata;
	m_savedata = new wxMenuItem( m_menuFile, wxID_ANY, wxString( _("保存地图") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_savedata );
	
	wxMenuItem* m_loaddata;
	m_loaddata = new wxMenuItem( m_menuFile, wxID_ANY, wxString( _("载入地图") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_loaddata );
	
	wxMenuItem* menuFileExit;
	menuFileExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( _("退出") ) + wxT('\t') + wxT("Alt+X"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuFileExit );
	
	m_menuBar->Append( m_menuFile, _("文件") ); 
	
	m_help = new wxMenu();
	wxMenuItem* m_about;
	m_about = new wxMenuItem( m_help, wxID_ANY, wxString( _("关于") ) , wxEmptyString, wxITEM_NORMAL );
	m_help->Append( m_about );
	
	m_menuBar->Append( m_help, _("帮助") ); 
	
	this->SetMenuBar( m_menuBar );
	
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new MyCanvas(this, wxID_ANY);
	bSizer12->Add( m_canvas, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer12 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	this->Connect( m_loadfile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_loadfileOnMenuSelection ) );
	this->Connect( m_savedata->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_savedataOnMenuSelection ) );
	this->Connect( m_loaddata->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_loaddataOnMenuSelection ) );
	this->Connect( menuFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) );
	this->Connect( m_about->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_aboutOnMenuSelection ) );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_loadfileOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_savedataOnMenuSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_loaddataOnMenuSelection ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::m_aboutOnMenuSelection ) );
	
}

DialogAbout::DialogAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl3 = new wxTextCtrl( this, wxID_ANY, _("使用方式:\n        1,直接双击地图一点 建立一个目的地。\n        2,按住ctrl不放的同时双击一个目的地(此点变红)，单击道路引导程序绘制出两点间弯曲曲线，双击另外一点结束此路径绘制。（此过程中单击或双击时都需要按住ctrl）\n        3,按住alt键的同时双击一点，删除一个已经建立好的目的地，和此点有关的边也会同时被删除.\n        4, 右键双击一目的地，编辑此点 介绍。\n\n\n说明:\n      已知bug, windows环境下未载入数据时，关闭程序会比较困难；双击左键时刷屏。   linux下均无问题。\n \n                                                  计科S1021"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer6->Add( m_textCtrl3, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer6 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

DialogAbout::~DialogAbout()
{
}

InterBase::InterBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("地点名"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer8->Add( m_staticText7, 0, wxALL, 5 );
	
	m_name = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_name, 1, wxALL, 5 );
	
	bSizer7->Add( bSizer8, 0, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("图片  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer9->Add( m_staticText8, 0, wxALL, 5 );
	
	m_image = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.jpg"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer9->Add( m_image, 0, wxALL, 5 );
	
	bSizer7->Add( bSizer9, 0, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("简介  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer10->Add( m_staticText9, 0, wxALL, 5 );
	
	m_value = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer10->Add( m_value, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizer7->Add( bSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer19->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( this, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer3->AddButton( m_sdbSizer3Cancel );
	m_sdbSizer3->Realize();
	bSizer19->Add( m_sdbSizer3, 0, wxALIGN_BOTTOM, 5 );
	
	bSizer7->Add( bSizer19, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

InterBase::~InterBase()
{
}

DialogNew::DialogNew( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("地图名"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer12->Add( m_staticText5, 0, wxALL, 5 );
	
	m_name = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_name, 1, wxALL|wxEXPAND, 5 );
	
	bSizer11->Add( bSizer12, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("比例尺"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer13->Add( m_staticText6, 0, wxALL, 5 );
	
	m_scale = new wxTextCtrl( this, wxID_ANY, _("50"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_scale, 1, wxALL, 5 );
	
	bSizer11->Add( bSizer13, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("图片  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer14->Add( m_staticText7, 0, wxALL, 5 );
	
	m_image = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.jpg"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer14->Add( m_image, 1, wxALL, 5 );
	
	bSizer11->Add( bSizer14, 1, wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	bSizer11->Add( m_sdbSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

DialogNew::~DialogNew()
{
}
