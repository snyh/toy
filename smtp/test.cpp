#include "libamail.hpp"
#include <boost/function.hpp>
#include <iostream>
using namespace std;

void list_handler(aMail::MailList m)
{
  std::cout << "\nHandler: ";
  for(aMail::MailList::iterator i=m.begin(); i!=m.end(); ++i){
      std::cout << i->second << "\n";
  }
}

void send_handler(string s)
{
  std::cout << "\nHandler: "
	<< s;
}

int main()
{

  aMail::UserAgent ua("smtp.qq.com", "pop.qq.com",
					  "1399611909@qq.com", "密码");

  ua.async_listmail(list_handler);
  std::cout << "end\n";

  aMail::Mail m("1399611909@qq.com", "snyh@snyh.org", 
				"test_title", "data:test");
  std::cout << ua.sendmail(m) << "\n";

  aMail::UserAgent ua2("smtp.gmail.com", "snyh1010@gmail.com", 
					   "snyh1010", "密码",
					   "995", "465", true);
  aMail::Mail m2("snyh1010@gmail.com", "1399611909@qq.com", 
				 "test_title", "data:test");

  ua2.async_sendmail(m2, send_handler);
  std::cout << "test start\n";
  sleep(10);
}
