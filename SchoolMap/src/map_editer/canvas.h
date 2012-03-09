#ifndef CANVAS_H
#define CANVAS_H
#include "wx/wx.h" 
#include "my_data.h"

class MyCanvas : public wxScrolledWindow {

public:
	MyCanvas(wxWindow* parent, wxWindowID id) ;
	~MyCanvas(){
		if(data.m_bit)
			delete data.m_bit;
	};

	void SetImage(wxBitmap *bit);
protected:
	void OnLeftDClick( wxMouseEvent& event );
	void OnLeftDown( wxMouseEvent& event );
	void OnRightDClick( wxMouseEvent& event );
	void OnPaint( wxPaintEvent& event );
	
private:
	wxPoint _p() {
		int startX, startY, ppuX, ppuY;
		GetViewStart(&startX, &startY);
		GetScrollPixelsPerUnit(&ppuX, &ppuY);
		wxPoint t(startX*ppuX, startY*ppuY);
		return t;
	}
	void show();
private:
	bool isInEdge;
	Edge m_tmp_edge;

public:
	MyData data;
};

#endif // CANVAS_H
