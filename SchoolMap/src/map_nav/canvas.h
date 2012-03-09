#ifndef CANVAS_H
#define CANVAS_H
#include "gui.h"
#include "wx/wx.h" 
#include "my_data.h"
enum S_SELECT {S_SELECTED_NULL, S_SELECTED_BEGIN, S_SELECTED_END, S_SELECTED_TREE};
enum S_SHOW {S_SHOW_NULL, S_SHOW_ALL, S_SHOW_POINT, S_SHOW_GOOD_PATH};

class MyCanvas : public wxScrolledWindow {
public:
	MyCanvas(wxWindow* parent, wxWindowID id);
	~MyCanvas();

	void SetImage(wxBitmap *bit);
protected:
	void OnLeftDClick( wxMouseEvent& event );
	void OnLeftDown( wxMouseEvent& event );
	void OnLeftUp(wxMouseEvent& event);
	void OnRightDClick( wxMouseEvent& event );
	void OnPaint( wxPaintEvent& event );
	void OnKeyDown( wxKeyEvent& event );
	
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
	S_SELECT s_select;
	S_SHOW s_show;
	int begin, end;
	wxBitmap *build;
	bool show_build;
	std::vector<std::vector<wxPoint> > tmp_points; //used for  draw Edge of any two point
	std::vector<int>  bigPoints; // falgs which point is an big point;
	std::vector<int>  littlePoints;
	
	wxPoint drag_begin;
public:
	wxString zip_name;
	MyData data;
};


#endif // CANVAS_H
