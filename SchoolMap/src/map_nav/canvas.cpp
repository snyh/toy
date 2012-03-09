#include "canvas.h"
#include "gui.h"
#include "my_data.h"
#include <wx/effects.h>
#include <wx/scrolwin.h>
#include <wx/event.h>
#include <fstream>
#include <wx/filename.h>
#include <wx/window.h>
#include "build.xpm"
MyCanvas::MyCanvas(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id)
{

	s_select = S_SELECTED_NULL;
	s_show = S_SHOW_POINT;
	show_build = true;

	DialogHelp help(NULL);
	help.Centre();
	help.ShowModal();

	wxFileDialog d(this, _("Select Map Data"));
	if(wxID_OK == d.ShowModal()) {
		zip_name = d.GetPath();

		DataLoadFrom(zip_name, data);
		//remove "bad" points;
		/*
		int flag=true;
		for(std::map<int, wxPoint>::iterator i=data.points.begin(); i!=data.points.end(); ++i){
			for(std::vector<Edge>::iterator j=data.edges.begin(); j!=data.edges.end(); ++j){
				if(j->begin == i->first || j->end == i->first){
					flag =false;
				}
			}
			if(flag){
				data.points.erase(i->first);
			}
			flag = true;
		}
		*/
		//

		data._genAdjTable();
		data._genGraph();
		((wxFrame*)GetParent())->SetTitle( wxString(data.map_name.c_str(), wxConvLocal) );
		SetVirtualSize(data.m_bit->GetWidth(), data.m_bit->GetHeight());
		SetScrollRate(1,1);
		GetParent()->SetSize(800,600);
		GetParent()->SetMaxSize(wxSize(data.m_bit->GetWidth(), data.m_bit->GetHeight()));
	} else {
		GetParent()->Destroy();
	}
	build = new wxBitmap(build_xpm);



	for(std::map<int, PointInterpt>::iterator i = data.interpts.begin(); i!=data.interpts.end(); ++i) {
		bigPoints.push_back(i->first);
	}
	for(std::map<int, wxPoint>::iterator i=data.points.begin(); i!=data.points.end(); ++i) {
		littlePoints.push_back(i->first);
	}
	this->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MyCanvas::OnKeyDown ) );
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyCanvas::OnLeftDClick ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MyCanvas::OnLeftDown ) );
	this->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( MyCanvas::OnRightDClick ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( MyCanvas::OnPaint ) );
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( MyCanvas::OnLeftUp ) );
	
}
MyCanvas::~MyCanvas()
{
	this->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MyCanvas::OnKeyDown ) );
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyCanvas::OnLeftDClick ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MyCanvas::OnLeftDown ) );
	this->Disconnect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( MyCanvas::OnRightDClick ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MyCanvas::OnPaint ) );
	this->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( MyCanvas::OnLeftUp ) );
	if(data.m_bit)
		delete data.m_bit;
}


void MyCanvas::OnKeyDown( wxKeyEvent& event )
{
	switch(event.GetKeyCode()) {
	case 'p':
	case 'P':
		if(s_show == S_SHOW_POINT)
			s_show = S_SHOW_NULL;
		else
			s_show = S_SHOW_POINT;
		Refresh();
		break;
	case 'a' :
	case 'A' :
		if(s_show == S_SHOW_ALL)
			s_show = S_SHOW_NULL;
		else
			s_show = S_SHOW_ALL;
		Refresh();
		break;
	case 'f':
	case 'F':
		show_build = !show_build;
		Refresh();
		break;
	case 'H':
	case 'h':
		DialogHelp d(this);
		d.ShowModal();
		break;

	}
	event.Skip();
}

void MyCanvas::OnLeftDClick( wxMouseEvent& event )
{
	int n = WhichPoint(data.points, _p() + event.GetPosition());
	//	std::cout << n << ": " << bigPoints[n].x << "," << bigPoints[n].y << std::endl;
	if(n>=0) {
		std::cout << "point: " << n << std::endl;
		if(s_select == S_SELECTED_TREE) {
			s_select =S_SELECTED_NULL;
			tmp_points.clear();
		}

		if(s_select == S_SELECTED_NULL) {
			begin = n;
			s_select = S_SELECTED_BEGIN;
			Refresh();
		} else if(s_select == S_SELECTED_BEGIN) {
			end = n;
			s_select = S_SELECTED_END;

			std::list<int> path;
			long len = 0;
			data.dijkstra(path, begin, end);
			std::cout << " OK\n ";
			std::cout <<"dijkstra: ";
			for(std::list<int>::iterator i=path.begin(); i!=path.end(); ++i) {
				std::cout << *i << ", ";
			}
			std::cout << "\n";
			std::cout <<"path: ";
			std::list<int>::iterator i1=path.begin();
			if(i1 !=path.end())++i1;
			for(std::list<int>::iterator i2=path.begin(); i1!=path.end(); ++i2, ++i1) {

				std::cout << *i2 << ", ";
				std::vector<Edge>& e = data.adjTable[*i2];

				for(std::vector<Edge>::iterator j = e.begin(); j != e.end(); ++j) {
					std::cout << "curent i: " << *i1 << "  j: (" << j->begin << "," << j->end << "\n";
					if(  ((j->begin == *i1) && (j->end == *i2))  ||
					        ((j->end == *i1) && (j->begin == *i2))      ) {
						tmp_points.push_back(j->points);
						len+= j->length;
						break;
					}
				}
			}
			Refresh();
			Update();
			wxString s;
			s << _T("从\"") << wxString(data.interpts[begin].name.c_str(), wxConvLocal) <<
			  _T("\" 到 \"") << wxString(data.interpts[end].name.c_str(), wxConvLocal) << _T("\"  距离为:")
			  << len << _T(" pix \n (实际距离:") << len*data.scale/96 << _T("m.)\n")
			  << _T("当前比例尺: 1cm:") << data.scale << _T("m  DPI=96\n");
			wxMessageBox(s, _T(""), wxOK, this);
			std::cout <<"length: "<< len << std::endl;
		} else if(s_select == S_SELECTED_END) {
			s_select = S_SELECTED_BEGIN;
			begin = n;
			tmp_points.clear();
			Refresh();
		}

		if(event.ControlDown()) {
			typedef std::vector<std::pair<int, int> > _E;
			_E _e;
			data.primTree(n, _e);
			for(_E::iterator i = _e.begin(); i!=_e.end(); ++i) {
				std::vector<Edge>& e = data.adjTable[i->first];
				for(std::vector<Edge>::iterator j = e.begin(); j != e.end(); ++j) {
					if(  ((j->begin == i->first) && (j->end == i->second))  ||
					        ((j->end == i->first) && (j->begin == i->second))   ) {
						tmp_points.push_back(j->points);
						break;
					}
				}
			}
			s_select = S_SELECTED_TREE;
			Refresh();
		}
	}
}
void MyCanvas::OnLeftDown( wxMouseEvent& event )
{
	drag_begin = event.GetPosition();
}
void MyCanvas::OnLeftUp(wxMouseEvent& event)
{
}

void MyCanvas::OnPaint( wxPaintEvent& event )
{
	if(data.m_bit) {
		wxPaintDC dc(this);
		int x, y;
		GetClientSize(&x, &y);
		wxRect r(_p().x, _p().y, x,y);
		wxBitmap tmp = (data.m_bit)->GetSubBitmap(r);
		dc.DrawBitmap(tmp, wxPoint(0,0));
		dc.SetDeviceOrigin(- _p().x, - _p().y);

		typedef std::map<int, wxPoint>::iterator i_type;
		std::map<int, wxPoint> &points = data.points;

		//draw what?
		dc.SetTextBackground(*wxRED);
		for(std::vector<int>::iterator  i = bigPoints.begin();  i != bigPoints.end(); ++i) {
			wxPoint p = data.points[*i];
			if(show_build) dc.DrawBitmap(*build, p.x-23, p.y-23, true);
			dc.DrawText(wxString(data.interpts[*i].name.c_str(), wxConvLocal), p.x-23, p.y+23);
		}


		if(s_show == S_SHOW_POINT || s_show == S_SHOW_ALL) {
			for(std::vector<int>::iterator  i = littlePoints.begin();  i != littlePoints.end(); ++i)
				dc.DrawCircle(data.points[*i], 5);

		}
		if(s_show == S_SHOW_ALL) {
			for(std::vector<Edge>::iterator i = data.edges.begin(); i != data.edges.end(); ++i) {
				dc.SetPen(wxPen(*wxGREEN, 5));
				dc.DrawLines(i->points.size(), &(i->points.at(0)));
			}
		}

		//draw shorest path.
		if(s_select == S_SELECTED_BEGIN) {
			dc.SetBrush(wxBrush(*wxRED, wxSOLID));
			dc.DrawCircle(points[begin], 10);
		} else if(s_select == S_SELECTED_END) {
			dc.SetBrush(wxBrush(*wxBLUE, wxSOLID));
			dc.DrawCircle(points[begin], 10);
			dc.DrawCircle(points[end], 10);
			if(!tmp_points.empty()) {
				for(std::vector<std::vector<wxPoint> >::iterator i=tmp_points.begin(); i!=tmp_points.end(); ++i) {
					dc.SetPen(wxPen(*wxGREEN, 5));
					dc.DrawLines(i->size(), &(i->at(0)));
				}
			}
		} else if(s_select == S_SELECTED_TREE) {
			if(!tmp_points.empty()) {
				for(std::vector<std::vector<wxPoint> >::iterator i=tmp_points.begin(); i!=tmp_points.end(); ++i) {
					dc.SetPen(wxPen(*wxGREEN, 5));
					dc.DrawLines(i->size(), &(i->at(0)));
				}
			}
		}
	}
}
void MyCanvas::OnRightDClick( wxMouseEvent& event )
{
	show();
	int n = WhichPoint(data.points, _p() + event.GetPosition());
	if(data.interpts.find(n) != data.interpts.end()) {
		PointInterpt p = data.interpts[n];


		wxString _path;
		_path << _T("image") << wxFileName::GetPathSeparator() << n << _T(".jpg");
		wxBitmap *bit = Load4Zip(zip_name,  _path);
		if(bit) {
			DialogShow dlg(NULL, wxID_ANY, wxString(p.name.c_str(), wxConvLocal));
			dlg.m_textCtrl1->SetValue(wxString(p.value.c_str(), wxConvLocal));
			dlg.m_bitmap2->SetBitmap(*bit);
			dlg.Fit();
			dlg.Center();
			dlg.ShowModal();
			delete bit;
		} else {
			DialogShow2 dlg(NULL, wxID_ANY, wxString(p.name.c_str(), wxConvLocal));
			dlg.m_textCtrl2->SetValue(wxString(p.value.c_str(), wxConvLocal));
			dlg.ShowModal();
		}
	}
}


void MyCanvas::SetImage(wxBitmap *bit)
{
	if(!bit->IsOk()) {
		wxMessageDialog m(this, _("load picture file error"), _("error"), wxOK|wxICON_ERROR);
		m.ShowModal();
		return;
	}

	data.m_bit = bit;
	SetVirtualSize(data.m_bit->GetWidth(), data.m_bit->GetHeight());
	SetScrollRate(1,1);

	//GetParent()->SetSize(wxSize(m_bit->GetWidth(), m_bit->GetHeight()));
	wxWindow *t = wxTheApp->GetTopWindow();
	t->SetMaxSize(wxSize(data.m_bit->GetWidth(), data.m_bit->GetHeight()));
	t->Layout();
	Refresh();
}

void MyCanvas::show()   //used for debuge
{
	for(std::vector<Edge>::iterator i=data.edges.begin(); i != data.edges.end(); ++i) {
		std::cout << "Edge :(" << i->begin << "," << i->end << ")  length: " << i->length <<
		          "  points: ";
		for(std::vector<wxPoint>::iterator j=i->points.begin(); j!= i->points.end(); ++j) {
			std::cout << "(" << j->x << "," << j->y << ") ";
		}
		std::cout << std::endl;
	}
	for(std::map<int, wxPoint>::iterator i=data.points.begin(); i != data.points.end(); ++i) {
		std::cout << "P" << i->first << "(" << i->second.x << "," << i->second.y << ")\n";
	}
	std::cout << "BigPoint: ";
	for(std::vector<int>::iterator i=bigPoints.begin(); i != bigPoints.end(); ++i) {
		std::cout << *i << ", ";
	}
	std::cout << "\n";


	std::cout << "LittlePoint: ";
	for(std::vector<int>::iterator i=littlePoints.begin(); i != littlePoints.end(); ++i) {
		std::cout << *i << ", ";
	}
	std::cout << "\n";

	std::cout << "PointInter: ";
	for(std::map<int, PointInterpt>::iterator i=data.interpts.begin(); i!=data.interpts.end(); ++i) {
		std::cout << i->first << ", ";
	}
	std::cout << "\n";
}
