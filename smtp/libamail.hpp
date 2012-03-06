#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>

namespace aMail{
    struct Mail {
	std::string from;
	std::string tos;
	std::string subject;
	std::string data;
    public:
	Mail(std::string from, std::string tos,
	     std::string subject="", std::string data="");
	std::string to_str();
    };

    typedef std::map<int, std::string> MailList;
    typedef boost::function<void(std::string)> SendHandler;
    typedef boost::function<void(MailList)> ListHandler;
    typedef boost::function<void(Mail)> FetchHandler;
      

    class UserAgent {
    public:
      UserAgent(std::string smtp_host, std::string pop_host,
		std::string user, std::string password,
		std::string pop_port="110", std::string smtp_port="25", bool tls=false);

      void async_sendmail(Mail& m, SendHandler  handle);
      std::string sendmail(Mail& m);

      void async_listmail(ListHandler handler);
      void listMail(MailList& l);

      void async_fetchmail(int n, FetchHandler);
      void fetchmail(int n, Mail& m);

    private:
      struct Impl;
      boost::shared_ptr<Impl> impl;
    };
}
