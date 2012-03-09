#include "my_data.h"

#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/zipstrm.h>
#include <wx/datstrm.h>
#include <wx/wfstream.h>
#include <wx/filefn.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>
#include <queue>
#include <climits>

struct DistanceTo{
	int i;
	long length;
	bool operator< (const DistanceTo& d) const {
		return length > d.length;
	}
};
void MyData::dijkstra(int v1, int v2, std::list<int>& path)
{
  path.clear();
  if(v1==v2) { path.push_back(v1); return; }
  std::vector<long> dist(this->points.size(), std::numeric_limits<long>::max());   
  dist[v1] = 0;
   
  std::priority_queue<DistanceTo> queue;
  DistanceTo d_cur;      d_cur.i = v1;      d_cur.length = 0;
  queue.push(d_cur);

  while(!queue.empty()) {
      int k = queue.top().i;  
      long l = queue.top().length; 
      queue.pop();
      path.push_back(k);
      if(k==v2)break;

    //  if(k==v2) break;
      if(dist[k] != l) continue;
      std::vector<Edge> &e = adjTable[k];
      for(std::vector<Edge>::const_iterator i=e.begin(); i!=e.end(); ++i){
	  int j = (k == i->begin) ? i->end : i->begin;
	  long _l = i->length;
	  if(dist[k]+_l < dist[j]){
	      dist[j] = dist[k]+_l;
	      d_cur.i = j;
	      d_cur.length = dist[j];
	      queue.push(d_cur);
	  }
      }
  }
  std::cout <<" modify begin: ";
  for(std::list<int>::iterator i=path.begin(); i!=path.end(); ++i)
    std::cout << *i << ", ";
  std::cout << std::endl;

  if(path.back() != v2){
      path.clear();
      d_cur.length = 0;
  } else {
      path.reverse();
      std::list<int>::iterator i_cur, offset;
      i_cur = path.begin(); offset = path.begin(); offset++;

      while(offset != path.end()){
		  bool is_in;
		  for(std::vector<Edge>::iterator i=adjTable[*i_cur].begin();
			  i!=adjTable[*i_cur].end(); ++i){
			  if(i->begin == *offset || i->end == *offset){
				is_in = true;
				break;
			  } else {
				is_in = false;
			  }
		  }
		  
		  if(!is_in)
			offset = path.erase(offset);
		  else{
			i_cur = offset; offset++;
		  }
      }
      path.reverse();
  }
  return ;
}
void MyData::_genAdjTable()
{
  for(std::map<int, wxPoint>::iterator i=points.begin(); i!=points.end(); ++i){
      std::cout << "point " << i->first << ": ";
      for(std::vector<Edge>::iterator j=edges.begin(); j!=edges.end(); ++j){
	  if(j->begin == i->first || j->end == i->first){
	      adjTable[i->first].push_back(*j);
	      	      std::cout << (j->begin == i->first ? j->end : j->begin)
	      		<< "(" << j->length << "), ";
	  }
      }
      std::cout << std::endl;
  }
}



int WhichPoint(std::map<int, wxPoint>& points, wxPoint p) {
	for(std::map<int, wxPoint>::const_iterator i=points.begin(); i != points.end(); ++i) {
		int x = i->second.x;
		int y = i->second.y;
		for(int j=-5; j <=5; j++) {
			for(int z=-5; z<=5; z++) {
				if((p.x == x+j) && (p.y == y+z))
					return  i->first;
			}
		}
	}
	return -1;
}
void DataRemovePointAndEdge(MyData& d, wxPoint p)
{
	std::map<int, wxPoint>& points = d.points;
	for(std::map<int, wxPoint>::iterator i=points.begin(); i != points.end(); ++i) {
		int x = i->second.x;
		int y = i->second.y;
		for(int j=-5; j <=5; j++) {
			for(int z=-5; z<=5; z++) {
				if((p.x == x+j) && (p.y == y+z)) {
					for(std::vector<Edge>::iterator l=d.edges.begin(); l != d.edges.end(); ++l){
						if(l->begin == i->first || l->end == i->first) {
							std::cout << "p: " << i->first << "edge(" << l->begin << "," << l->end << ") \n";
							l = d.edges.erase(l);
							l--;
						}
					}
					points.erase(i);
					d.interpts.erase(i->first);
					return;
				}
			}
		}
	}
}
long CalEdgeLength (Edge& e)
{
	double length = 0;
	for(std::vector<wxPoint>::const_iterator i=e.points.begin(); i != e.points.end()-1; i++) {
		length += sqrt( (i->x - (i+1)->x) * (i->x - (i+1)->x) + (i->y - (i+1)->y) * (i->y - (i+1)->y) );
	}
	return long(length);
}


void write2zip(wxString zip_file, wxString entry_path, wxString entry_name)
{
  wxFFileOutputStream out(zip_file);
  wxZipOutputStream zip(out);
  wxDataOutputStream entry(zip);
  zip.PutNextEntry(entry_name);

  std::ifstream ifs(entry_path.mb_str(), std::ios::binary);
  std::string tmp((std::istreambuf_iterator<char>(ifs)),
		   std::istreambuf_iterator<char>());
  entry.Write8((wxUint8*)tmp.data(), tmp.size());
  zip.Close();
}

void DataSaveTo(wxString filename, MyData& data) {
	std::ostringstream ofs;
	boost::archive::text_oarchive ar(ofs);
	ar << data;
	wxFFileOutputStream out(filename);
	wxZipOutputStream zip(out);
	wxDataOutputStream entry(zip);
	zip.PutNextEntry(_T("/map.data"));
	entry.Write8((wxUint8*)ofs.str().data(), ofs.str().size());

	zip.PutNextEntry(_T("/map.jpg"));
	
	std::ifstream ifs(data.image.c_str(), std::ios::binary);
	
	std::string tmp((std::istreambuf_iterator<char>(ifs)),
						std::istreambuf_iterator<char>());
	
    entry.Write8((wxUint8*)tmp.data(), tmp.size());
	ifs.close();
	tmp.clear();

	for(std::map<int, PointInterpt>::iterator i=data.interpts.begin(); i!= data.interpts.end(); ++i){
		if(wxFileExists(wxString((i->second).image.c_str(), wxConvLocal))){ //TODO: if save to other zip file, and no image file, 
			wxString p;
			p << _T("/image/") << i->first << _T(".jpg");
			zip.PutNextEntry(p);
			std::ifstream ifs((i->second).image.c_str(), std::ios::binary);
			std::string tmp((std::istreambuf_iterator<char>(ifs)),
								std::istreambuf_iterator<char>());
			entry.Write8((wxUint8*)tmp.data(), tmp.size());
			ifs.close();
			tmp.clear();
		}
	}
	 zip.Close();
}
wxBitmap* Load4Zip(wxString filename, wxString entry_name)
{
	wxZipEntry* entry;
	wxFFileInputStream in(filename);
	wxZipInputStream zip(in);
	wxDataInputStream stream(zip);

	while((entry = zip.GetNextEntry()) != NULL){
	
		if(entry->GetName() == entry_name){
			size_t sz = entry->GetSize();
			char* buf = new char[sz];
			stream.Read8((wxUint8*) buf, sz);
			wxMemoryInputStream s(buf, sz);
			wxImage image(s, wxBITMAP_TYPE_JPEG);
		    wxBitmap* b = new wxBitmap(image);
			return b;
		}
	}
	return NULL;		
}


void DataLoadFrom(wxString filename, MyData& data) {
	  wxZipEntry* entry;

	  wxFFileInputStream in(filename);
	  wxZipInputStream zip(in);
	  wxDataInputStream stream(zip);
	  int flag = 0;
	  while((entry = zip.GetNextEntry()) != NULL){
		  if(entry->GetName() == _T("map.data")){
			  size_t sz = entry->GetSize();
			  char* buf = new char[sz];
			  stream.Read8((wxUint8*) buf, sz);
			  std::istringstream is(buf);
			  boost::archive::text_iarchive ar(is);
			  ar >> data;
			  delete[] buf;
			  flag++;
		  } else if(entry->GetName() == _T("map.jpg")){
			size_t sz = entry->GetSize();
			char* buf = new char[sz];
			stream.Read8((wxUint8*) buf, sz);
			wxMemoryInputStream s(buf, sz);
			wxImage image(s, wxBITMAP_TYPE_JPEG);
		    data.m_bit = new wxBitmap(image);
			flag++;
		  } else if(flag == 2){
			  return ;
		  }
	  }
	  return;
}
