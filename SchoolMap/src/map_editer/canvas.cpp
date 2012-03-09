#include "canvas.h"
#include "gui.h"
#include "my_data.h"
#include <wx/effects.h>
#include <wx/scrolwin.h>
#include <wx/event.h>
#include <fstream>


class MyDialog : public InterBase {
public:
	MyDialog(wxWindow* parent, PointInterpt &p) : InterBase(parent), point(p) {
		m_image->SetPath(wxString(p.image.c_str(), wxConvLocal));
		m_name->SetValue(wxString(p.name.c_str(), wxConvLocal));
		m_value->SetValue(wxString(p.value.c_str(), wxConvLocal));
	}
	void ReWrite() {
		point.image = m_image->GetPath().mb_str(wxConvLocal);
		point.name =m_name->GetValue().mb_str(wxConvLocal);
		point.value = m_value->GetValue().mb_str(wxConvLocal);
	}

private:
	PointInterpt &point;
};




MyCanvas::MyCanvas(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id)
{
	isInEdge = false;
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MyCanvas::OnLeftDClick ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MyCanvas::OnLeftDown ) );
	this->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( MyCanvas::OnRightDClick ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( MyCanvas::OnPaint ) );
}



void MyCanvas::OnLeftDClick( wxMouseEvent& event )
{
	if(event.ControlDown()) {
		int n = WhichPoint(data.points, _p() + event.GetPosition());
		//	std::cout << n << ": " << bigPoints[n].x << "," << bigPoints[n].y << std::endl;
		if(n>=0) {
			if(!isInEdge) {
				isInEdge = true;
				m_tmp_edge.begin = n;
				m_tmp_edge.end = -1;

				m_tmp_edge.points.push_back(data.points[n]);
			} else {
				isInEdge = false;				
				m_tmp_edge.end = n;
				m_tmp_edge.points.push_back((data.points[n]));
				m_tmp_edge.length = CalEdgeLength(m_tmp_edge);
				data.edges.push_back(m_tmp_edge);
				
				m_tmp_edge.points.clear();
				m_tmp_edge.begin = -1;
				m_tmp_edge.end = -1;
			}
		}
	} else if(event.AltDown()) {
		DataRemovePointAndEdge(data, _p() + event.GetPosition());
	} else {
		data.points[data.count++] = _p() + event.GetPosition();
	}
	Refresh();
	
}
void MyCanvas::OnLeftDown( wxMouseEvent& event )
{
	if(event.ControlDown() && isInEdge) {
		m_tmp_edge.points.push_back(_p()+event.GetPosition());
		Refresh();
	}
}

void MyCanvas::OnPaint( wxPaintEvent& event )
{
	if(data.m_bit){
		wxPaintDC dc(this);
		int x, y;
		GetClientSize(&x, &y);
		wxRect r(_p().x, _p().y, x,y);
		wxBitmap tmp = (data.m_bit)->GetSubBitmap(r);
		
		dc.DrawBitmap(tmp, wxPoint(0,0));
		dc.SetDeviceOrigin(- _p().x, - _p().y);
	
		typedef std::map<int, wxPoint>::iterator i_type;
		std::map<int, wxPoint> &points = data.points;
		std::vector<Edge> &edges = data.edges;

		for(i_type i = points.begin(); i != points.end(); ++i) {
			dc.DrawCircle(i->second, 10);
		}
		if(isInEdge) {
			dc.SetBrush(wxBrush(*wxRED, wxSOLID));
			dc.DrawCircle(points[m_tmp_edge.begin], 10);
		}
		for(std::vector<Edge>::iterator i = edges.begin(); i != edges.end(); ++i) {
			dc.SetPen(wxPen(*wxGREEN, 5));
			dc.DrawLines(i->points.size(), &(i->points.at(0)));
		}
		if(m_tmp_edge.points.size()) {
			dc.SetPen(wxPen(*wxGREEN, 5));
			dc.DrawLines(m_tmp_edge.points.size(), &(m_tmp_edge.points[0]));
		}
	}
}
void MyCanvas::OnRightDClick( wxMouseEvent& event )
{
	int n = WhichPoint(data.points, _p() + event.GetPosition());
	if (n>=0) {
		std::cout << "Point: " << n << "\n";
		std::cout << "name: " << data.interpts[n].name << "\n";
		std::cout << "image: " << data.interpts[n].image << "\n";
		std::cout << "value: " << data.interpts[n].value << "\n";
		
		MyDialog dlg(NULL, this->data.interpts[n]);
		
		if(wxID_OK == dlg.ShowModal()){
			dlg.ReWrite();
		}
	}
	//show();
}

void MyCanvas::SetImage(wxBitmap *bit)
{
	if(!bit)return;
	if(!bit->IsOk()) {
		wxMessageDialog m(this, _("load picture file error"), _("error"), wxOK|wxICON_ERROR);
		m.ShowModal();
		return;
	}

	data.m_bit = bit;
	SetVirtualSize(data.m_bit->GetWidth(), data.m_bit->GetHeight());
	SetScrollRate(1,1);
	
	//GetParent()->SetSize(wxSize(m_bit->GetWidth(), m_bit->GetHeight()));
	
	GetParent()->SetMaxSize(wxSize(data.m_bit->GetWidth(), data.m_bit->GetHeight()));
	GetParent()->Layout();
	Refresh();
}


void MyCanvas::show()
{
	for(std::vector<Edge>::iterator i=data.edges.begin(); i != data.edges.end(); ++i) {
		std::cout << "Edge :(" << i->begin << "," << i->end << ")  length: " << i->length << "\n";
	}
	for(std::map<int, wxPoint>::iterator i=data.points.begin(); i != data.points.end(); ++i){
		std::cout << "P" << i->first << "(" << i->second.x << "," << i->second.y << ")\n";
	}
	std::cout << "map name: " << data.map_name << "\n";
	std::cout << "map scale: " << data.scale << "\n";
	std::cout << "map image path: " << data.image << "\n";
}