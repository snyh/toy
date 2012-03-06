#ifndef __PRE_H__
#define __PRE_H__

#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/url.h>
#include <wx/wfstream.h>
#include <wx/tokenzr.h>
#include <wx/config.h>
#include <wx/timer.h>



#include <stdio.h>

#include <string.h>
#include <iostream>
#include <list>
#include <map>


#ifdef __WIN32__
typedef unsigned long in_addr_t;
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#endif

#endif
