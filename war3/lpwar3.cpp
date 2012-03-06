#include "pre.h"

in_addr _fetch_my_ip(void);
wxString FetchMyIP();
inline wxString FetchMyIP()
{
  in_addr ip = _fetch_my_ip();
  return wxString(inet_ntoa(ip), wxConvUTF8);
}
inline wxString inet_itos(in_addr_t ip)
{
  struct in_addr i;
  i.s_addr = ip;
  return wxString(inet_ntoa(i), wxConvUTF8);
}
enum 
{
  QUIT_ID,
  CLEAR_ID,
  LISTPEERS_ID,
  TIMER_ID,
  SOCKET_ID = 100,
};

class War3 {
public:
  War3(){
      ver=0x18;
      local_ip = _fetch_my_ip();

#ifdef __WIN32__
      WORD wVersionRequested;
      WSADATA wsaData;
      int err;

      wVersionRequested = MAKEWORD( 1, 1 );

      err = WSAStartup( wVersionRequested, &wsaData );
#endif
  }
  bool send_request(std::map<in_addr_t, int> hosts);
private:
  int ver;
  in_addr local_ip;
};



class MyClient : public wxEvtHandler
{
public:
  MyClient(int p);
  ~MyClient(){SendBye(); delete timer; delete socket;}
  void OnRecive(wxSocketEvent& event);
  void OnTimer(wxTimerEvent& event);
  void SendHello();
  void SendBye();

  void StartWar3(){timer->Start(5000);}
  void StopWar3(){timer->Stop();}
private:
  wxDatagramSocket *socket;
  wxTimer *timer;
  War3 *war3;
  int port;
  DECLARE_EVENT_TABLE()
};
BEGIN_EVENT_TABLE(MyClient, wxEvtHandler)
	EVT_SOCKET(SOCKET_ID, MyClient::OnRecive)
	EVT_TIMER(TIMER_ID, MyClient::OnTimer)
END_EVENT_TABLE()

class MyHosts
{
public:
  MyHosts(wxString s, int z)
    : server(s), zone(z)
    {
      Download();
      Reg();
    }
  ~MyHosts(){
      Unreg();
  }
  void Download();
  void Reg();
  void Unreg();
  void Add(in_addr_t ip){hosts[ip]=1;}
  void Del(in_addr_t ip){hosts.erase(ip);}
  std::map<in_addr_t, int> List(){return hosts;}

  wxString Server() const {return server;}
private:
  wxString server;
  int zone;
  std::map<in_addr_t, int> hosts;
};

class MyFrame : public wxFrame
{
public:
  MyFrame();

  /* event handlers */
  void OnQuit(wxCommandEvent& event) {Close(false);}

  /*-------------client functions-------------*/
  void OnClearText(wxCommandEvent& event);
  void OnListPeers(wxCommandEvent& event);



private:
  wxTextCtrl	*m_text;

  DECLARE_EVENT_TABLE()
};
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(QUIT_ID, MyFrame::OnQuit)
EVT_MENU(CLEAR_ID, MyFrame::OnClearText)
EVT_MENU(LISTPEERS_ID, MyFrame::OnListPeers)
END_EVENT_TABLE()

class MyApp : public wxApp {
public:
  virtual bool OnInit();
  virtual int OnExit();

  MyFrame *frame;
  MyHosts *hosts;
  MyClient *client;
};
DECLARE_APP(MyApp)


MyClient::MyClient(int p)
:port(p)
{
  wxIPV4address addr;
  addr.Service(p);
  socket = new wxDatagramSocket(addr);

  if(! socket ->Ok()) {
	  std::cerr << _("Could not listen at the specified port !\n\n");
	  return;
  } else {
	  std::cout <<_("Server listening.\n\n");
  }

  socket->SetEventHandler(*this, SOCKET_ID);
  socket->SetNotify(wxSOCKET_INPUT_FLAG);
  socket->Notify(true);

  timer = new wxTimer(this, TIMER_ID);
  war3 = new War3();

}
void MyClient::OnRecive(wxSocketEvent& event)
{
  wxChar *buf = new wxChar[1000];
  wxSocketBase *s = event.GetSocket();
  s->Read(buf, 1000);

  if (memcmp(buf, "hello", 5) == 0) {
	  wxIPV4address addr;
	  s->GetPeer(addr);

	  wxGetApp().hosts->Add( inet_addr(addr.IPAddress().mb_str()) );
  } else if (memcmp(buf, "bye", 3) == 0) {
	  wxIPV4address addr;
	  s->GetPeer(addr);

	  wxGetApp().hosts->Del( inet_addr(addr.IPAddress().mb_str()) );
  }

  delete buf;
}
void MyClient::SendHello()
{
  std::map<in_addr_t, int> hosts = wxGetApp().hosts->List();
  std::map<in_addr_t, int>::iterator i;
  wxIPV4address addr;
  addr.Service(port);
  for(i=hosts.begin(); i!=hosts.end(); i++){
	  std::cout << "test: sendhello()" << (inet_itos(i->first)).fn_str()<< "\n";
	  addr.Hostname(inet_itos(i->first));
	  socket->SendTo(addr, "hello", 5);
  }
}
void MyClient::SendBye()
{
  std::map<in_addr_t, int> hosts = wxGetApp().hosts->List();
  std::map<in_addr_t, int>::iterator i;
  wxIPV4address addr;
  addr.Service(port);
  for(i=hosts.begin(); i!=hosts.end(); i++){
	  addr.Hostname(inet_itos(i->first));
	  socket->SendTo(addr, "bye", 3);
  }
}
void MyClient::OnTimer(wxTimerEvent& event)
{
  std::map<in_addr_t, int> h = wxGetApp().hosts->List();
  war3->send_request(h);
}



/*--------------deal with server-------------*/
void MyHosts::Reg()
{
  wxString ip = FetchMyIP();
  std::cout << "Registting " << ip.fn_str() << "to server\n";
  wxURL url(server + _("?action=reg&ip=") + ip + _("&zone=") + wxString()<<zone);
  if (url.GetError() != wxURL_NOERR) {
	  std::cerr << "GetFromURL() : url invalide\n";
	  return;
  }
  (void)url.GetInputStream();
}
void MyHosts::Unreg()
{
  wxString ip = FetchMyIP();

  std::cout << "Unregistting " << ip.fn_str() << "to server\n";
  wxURL url(server + _("?action=del&ip=") + ip + _("&zone=") + wxString()<<zone);
  if (url.GetError() != wxURL_NOERR) {
	  std::cerr << "GetFromURL() : url invalide\n";
	  return;
  }
  (void)url.GetInputStream();
}

void MyHosts::Download()
{
  wxBeginBusyCursor();
  wxURL url(server + _("?action=download&zone=") + wxString()<<zone);
  if (url.GetError() != wxURL_NOERR) {
	  std::cerr << _("GetFromURL() : url invalide\n");
	  return;
  }
  wxInputStream *data = url.GetInputStream();
  if (!data) {
	  std::cerr << _("Failed download list of peers\n");
	  return;
  }

  char *buf = new char[10000];
  data->Read(buf, 10000);

  wxStringTokenizer hs(wxString::FromAscii(buf), _T("\n"));
  while(hs.HasMoreTokens()) {
	  wxString token = hs.GetNextToken();
	  hosts[inet_addr(token.mb_str())] = 1;
  }

  delete[] buf;
  delete data;
  wxEndBusyCursor();
}


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{

  wxString server;
  int port = 6789;
  int zone = 0;

  SetVendorName(_T("snyh"));
  SetAppName(_T("LPWar3"));

  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetRecordDefaults();
  if (!pConfig->Read(_T("/Server/url"), &server)) {
	  server = wxGetTextFromUser( _("LPWar3 is the first time run.\nPlease set a server"),
								  _("Setting Server"),
								  _("http://lpwar3.appspot.com/war3.py"));
	  wxURL url(server);
	  if (url.GetError() != wxURL_NOERR) {
		  server = wxString(_T("http://lpwar3.appspot.com/war3.py"));
		  url.SetURL(server);
	  }
	  wxInputStream *data = url.GetInputStream();
	  if (!data) {
		  std::cerr << _("Failed download list of peers\n");
		  wxMessageBox(_("Cann't connect to Server or Server is down!"));
	  } else {
		  char *buf = new char[100];
		  data->Read(buf, 10000);
		  if (memcpy(buf, "Not Support action", 18))
			wxMessageBox(_("This is not a LPWar3 Server"));
		  delete buf;
	  }

  }
  if (!pConfig->Read(_T("/port"), &port)) {
	  port = 6789;
  }
  if (!pConfig->Read(_T("/zone"), &zone)) {
	  zone = 0;
  }

  MyFrame *frame = new MyFrame();
  frame->Show(true);
  SetTopWindow(frame);


  hosts = new MyHosts(server, zone);
  client = new MyClient(port);
  client->SendHello();
  client->StartWar3();


  return true;
}
int MyApp::OnExit()
{
  wxConfigBase *pConfig = wxConfigBase::Get();
  if (pConfig == NULL)
	return 0;
  pConfig->Write(_T("/Server/url"), hosts->Server());
  delete hosts;
  delete wxConfigBase::Set((wxConfigBase *) NULL);
  return 0;
}


MyFrame::MyFrame() 
	 : wxFrame((wxFrame *)NULL, wxID_ANY,
			   _("LAN War3 Platform"),
			   wxDefaultPosition, wxSize(400, 300))

{
  /*-------------GUI -------------------*/
  wxMenu	*m_menuFile;
  wxMenu	*m_menuSet;
  wxMenuBar	*m_menuBar;

  CreateStatusBar(2);

  m_text = new wxTextCtrl(this, wxID_ANY,
						  _("This is a test version\n"),
						  wxDefaultPosition, wxDefaultSize,
						  wxTE_MULTILINE | wxTE_READONLY);
  m_menuFile = new wxMenu();
  m_menuFile->Append(QUIT_ID, _("E&xit\tAlt-X"), _("Quit app"));
  m_menuSet= new wxMenu();
  m_menuSet->Append(CLEAR_ID, _("&CLear"), _("Clear the textctrl"));
  m_menuSet->Append(LISTPEERS_ID, _("&ListPeers"), _("List all peers"));


  m_menuBar = new wxMenuBar();
  m_menuBar->Append(m_menuFile, _("&File"));
  m_menuBar->Append(m_menuSet, _("SET"));
  SetMenuBar(m_menuBar);
}




/*-------------deal with other peers-----------------------*/
void MyFrame::OnClearText(wxCommandEvent& event)
{
  m_text->Clear();
}
void MyFrame::OnListPeers(wxCommandEvent& event)
{

  std::map<in_addr_t, int>::iterator i;
  std::map<in_addr_t, int> hosts = wxGetApp().hosts->List();
  for(i=hosts.begin(); i != hosts.end(); i++) {
	  *m_text << inet_itos(i->first) << _("\n");
  }
}


//--------------------------war3.cpp---------------------------------------------



struct _UDP {
	/*----------UDP Header-------------*/
	unsigned short int	s_port;
	unsigned short int	d_port;
	unsigned short int	udp_len;
	unsigned short int	udp_chksum;

	/*---------UDP Payload------------*/
	char payload[16];
};
struct _Packet {
	/*-----------Pseudo Header----------*/
	unsigned int s_ip;

	unsigned int d_ip;

	unsigned char zero;
	unsigned char proto;
	unsigned short len;
	/*----------UDP Packet------------*/
	struct _UDP udp;
};
void _fill_packet(_Packet *p, int ver);
in_addr _fetch_my_ip(void);




bool War3::send_request(std::map<in_addr_t, int> hosts)
{

  int s = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

#ifdef __WIN32__
  if (s == INVALID_SOCKET) {
	  std::cerr << "Can't create raw socket!\n";
	  std::cerr <<WSAGetLastError()<<"\n";
  }
#else
  if (s == -1) {
	  std::cerr << "Can't create raw socket!\n";
  }
#endif


  std::map<in_addr_t,int>::iterator i;
  for(i=hosts.begin(); i != hosts.end(); i++) {

	  _Packet p = {0};

	  p.d_ip = i->first;
	  p.proto = IPPROTO_UDP;
	  p.len = htons(8+16);
	  p.s_ip = *(unsigned *)&this->local_ip;

	  _fill_packet(&p, this->ver);

	  sockaddr_in dest = {0};
	  dest.sin_family = AF_INET;
	  dest.sin_port = htons(6112);
	  dest.sin_addr.s_addr = i->first;

	  ssize_t r = sendto(s, (char*)&(p.udp), sizeof(p.udp), 0, (sockaddr*)&dest, sizeof(dest));
#ifdef __WIN32__
	  if (r == SOCKET_ERROR) {
		  std::cerr << "Sendto() failed!\n" ;
	  }
#else
	  if ( r == -1) {
		  std::cerr << inet_ntoa(*(struct in_addr*)&p.d_ip) << "\n";
		  std::cerr << "Sendto() failed!\n" ;
	  }
#endif
  }
#ifdef __WIN32__
  closesocket(s);
#else
  close(s);
#endif
  return true;
}

unsigned short checksum(unsigned short *buffer, int size)
{
  unsigned long cksum = 0;
  while(size>1){
	  cksum+=*buffer++;
	  size-=sizeof(unsigned short);
  }
  if(size){
	  cksum += *(unsigned char*)buffer;
  }
  while(cksum>>16)
	cksum=(cksum>>16)+(cksum&0xffff);
  return (unsigned short)(~cksum);
}

void _fill_packet(_Packet *p, int ver)
{
  char payload[16] = {
	  0xf7, 0x2f, 0x10, 0x00, 0x50, 0x58, 0x33, 0x57,
	  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  /*War3 Version number, default 1.24(0x18)*/
  };
  payload[8] = ver;
  memcpy(p->udp.payload, payload, 16);

  p->udp.s_port = htons(6112);
  p->udp.d_port = htons(6112);
  p->udp.udp_len = htons(sizeof(p->udp));
  p->udp.udp_chksum = checksum((unsigned short*)p,sizeof(*p));
}

in_addr _fetch_my_ip(void)
{
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  sockaddr_in dest = {0};
  dest.sin_family=AF_INET;
  dest.sin_addr.s_addr=inet_addr("8.8.8.8");
  dest.sin_port=htons(80);

  connect(sock, (sockaddr*)&dest, sizeof(dest));
  sockaddr_in source = {0};
  socklen_t  len = sizeof(sockaddr_in);
  getsockname(sock, (sockaddr*)&source, &len);

  return source.sin_addr;
}
