///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

// Using the construction of a static object to ensure that the help provider is set
class wxFBContextSensitiveHelpSetter
{
public:
wxFBContextSensitiveHelpSetter()
{
wxHelpProvider::Set( new wxHelpControllerHelpProvider );
}
};

static wxFBContextSensitiveHelpSetter s_wxFBSetTheHelpProvider;
///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	this->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MainFrameBase::MainFrameBaseOnLeaveWindow ) );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	this->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MainFrameBase::MainFrameBaseOnLeaveWindow ) );
	
}

DialogHelp::DialogHelp( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("键盘:  \n      A  显示/隐藏   所有线路\n      P  显示/隐藏   道路拐角(非景点点)\n      F  显示/隐藏   景点点\n      H  显示/隐藏   本面板\n\n鼠标:\n     1, 单击 任意一点  标记为起始点 此点变红,  选择另外任意结束点 两点变蓝 并且绘\n制出最短道路，同时根据地图比例尺以及DPI为96 计算出实际距离\n     2, 按住CTRL的同时 单击任意一点 绘制出从此点开始遍历全图的路径\n     \n     3, 右键双击景点后显示次景点图片(如果有)和简介(如果有)\n\n\n提示  按H可打开此面板.  启动程序后,选择地图数据.\n      景点 点使用\"房子\"图片标出\n \n                                      计科S1021 \n                                        2011 1 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( 400 );
	bSizer3->Add( m_staticText1, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( this, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3->Realize();
	bSizer3->Add( m_sdbSizer3, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

DialogHelp::~DialogHelp()
{
}

DialogShow::DialogShow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 300,100 ), wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap2 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer2->Add( m_bitmap2, 1, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer2->Add( m_textCtrl1, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1->Realize();
	bSizer2->Add( m_sdbSizer1, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

DialogShow::~DialogShow()
{
}

DialogShow2::DialogShow2( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,300 ), wxTE_MULTILINE|wxTE_READONLY );
	bSizer2->Add( m_textCtrl2, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();
	bSizer2->Add( m_sdbSizer2, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );
	
	this->Centre( wxBOTH );
}

DialogShow2::~DialogShow2()
{
}
