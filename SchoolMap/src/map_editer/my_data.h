#ifndef MYDATA_H
#define MYDATA_H

// link either with   -lboost_serialization-mt or -lboost_serialization

#include <wx/wx.h>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>





namespace boost {
	namespace serialization {
		template<class Archive> void serialize(Archive &ar, wxPoint& p, const unsigned int version) {
		ar & p.x & p.y ;
		}
	}
}
struct Edge {
	int begin;
	int end;
	long length;
	std::vector<wxPoint> points;
protected:
	friend class boost::serialization::access;
    template<class Archive> void serialize(Archive &ar, const unsigned int version) {
		ar & begin & end & length & points;
	}
};
struct PointInterpt {
	std::string name;
	std::string image;
	std::string value;
protected:
	friend class boost::serialization::access;
    template<class Archive> void serialize(Archive &ar, const unsigned int version) {
		ar & name & image & value;
    }
};
struct MyData {
   
    std::vector<Edge> edges;
    std::map<int, wxPoint> points;
	std::map<int, PointInterpt> interpts;

	void _genAdjTable();
	void dijkstra(int v1, int v2, std::list<int>& path);
	std::map<int, std::vector<Edge> > adjTable;
	
	
	std::string map_name;
	double scale;
	std::string image; //path;
	wxBitmap *m_bit;
	long count;  // used for, we can correctly generate Number  when load data and create new node 
protected:
    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive &ar, const unsigned int version) {
		ar & map_name & image & edges & points & interpts & count & scale;
    }
};
void DataSaveTo(const char *filename, MyData& data);
void DataLoadFrom(const char *filename, MyData& data);
int WhichPoint(std::map<int, wxPoint>& points, wxPoint p);
void DataRemovePointAndEdge(MyData& d, wxPoint p);
long CalEdgeLength (Edge& e);
void DataSaveTo(wxString filename, MyData& data);
void DataLoadFrom(wxString filename, MyData& data);
wxBitmap* Load4Zip(wxString filename, wxString entry_name);




#endif // MYDATA_H
