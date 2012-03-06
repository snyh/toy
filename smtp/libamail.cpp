#include <string>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "libamail.hpp"
#include "base64.hpp"

using boost::asio::ip::tcp;


template<class sockType>
std::string send_command(sockType &s, std::string cmd, std::string delim="\r\n");

namespace aMail{

    struct UserAgent::Impl {
    public:
      Impl(std::string s_h, std::string p_h,
	   std::string u, std::string p, std::string pop, std::string smtp, bool t)
	: smtp_host(s_h), pop_host(p_h), user(u), password(p), pop_port(pop), smtp_port(smtp), tls(t)
	{}
      void _sendmail(Mail& m, std::string &err, bool async=false, SendHandler h=NULL);
      void _listmail(MailList& list, bool async=false, ListHandler handler=NULL);
      void _fetchmail(Mail &m, bool async=false, FetchHandler handler=NULL);
    public:
      bool tls;
      std::string smtp_host;
      std::string pop_host;
      std::string user;
      std::string password;
      std::string pop_port;
      std::string smtp_port;
    };

    UserAgent::UserAgent(std::string s_h, std::string p_h,
			 std::string user, std::string password,
			 std::string pop_port, std::string smtp_port, bool tls) :
      impl(new UserAgent::Impl(s_h, p_h, user, password, pop_port, smtp_port, tls))
    {
    }

    void UserAgent::async_sendmail(Mail& m, SendHandler handler) {
	std::string err;
	boost::thread t(boost::bind(&UserAgent::Impl::_sendmail, this->impl, m, err, true, handler));
	t.detach();
    }
    std::string UserAgent::sendmail(Mail& m) {
	std::string err;
	this->impl->_sendmail(m, err);
	return err;
    }

    void UserAgent::async_listmail(ListHandler handler) {
	MailList list;
	boost::thread t(boost::bind(&UserAgent::Impl::_listmail, this->impl,
								list, true, handler));
	t.detach();
    }















    void UserAgent::Impl::_sendmail(Mail& m, std::string &err, bool async, SendHandler handler) {
	try {
	    boost::asio::io_service io_service;
	    tcp::resolver resolver(io_service);
	    tcp::resolver::query query(smtp_host, smtp_port);
	    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	    tcp::resolver::iterator end;



	    if (tls) {
		boost::asio::ssl::context ctx(io_service,
					      boost::asio::ssl::context::sslv23);
		ctx.set_verify_mode(boost::asio::ssl::context::verify_none);
		boost::asio::ssl::stream<tcp::socket> ssl_socket(io_service, ctx);


		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
		    ssl_socket.lowest_layer().close();
		    ssl_socket.lowest_layer().connect(*endpoint_iterator++, error);
		    ssl_socket.handshake(boost::asio::ssl::stream_base::client);
		}
		if(error)
		  throw boost::system::system_error(error);

		boost::asio::streambuf b;
		boost::asio::read_until(ssl_socket, b, std::string("\r\n"));

		err = send_command(ssl_socket, "EHLO 127.0.0.1\r\n");
		err = send_command(ssl_socket, "AUTH LOGIN\r\n");
		err = send_command(ssl_socket, 
				   base64_encode((const unsigned char*)user.c_str(),
						 user.length()) + "\r\n"
				  );
		err = send_command(ssl_socket, 
				   base64_encode((const unsigned char*)password.c_str(),
						 password.length()) + "\r\n"
				  );

		err = send_command(ssl_socket, "MAIL FROM:<" + user+ ">\r\n");
		err = send_command(ssl_socket, "RCPT TO:<" + m.tos + ">\r\n");

		err = send_command(ssl_socket, "DATA\r\n");
		err = send_command(ssl_socket, m.to_str());

	    } else {
		tcp::socket socket(io_service);


		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
		    socket.close();
		    socket.connect(*endpoint_iterator++, error);
		}
		if(error)
		  throw boost::system::system_error(error);

		boost::asio::streambuf b;
		boost::asio::read_until(socket, b, std::string("\r\n"));

		err = send_command(socket, "EHLO 127.0.0.1\r\n");
		err = send_command(socket, "AUTH LOGIN\r\n");
		err = send_command(socket, 
				   base64_encode((const unsigned char*)user.c_str(),
						 user.length()) + "\r\n"
				  );
		err = send_command(socket, 
				   base64_encode((const unsigned char*)password.c_str(),
						 password.length()) + "\r\n"
				  );

		err = send_command(socket, "MAIL FROM:<" + user+ ">\r\n");
		err = send_command(socket, "RCPT TO:<" + m.tos + ">\r\n");

		err = send_command(socket, "DATA\r\n");
		err = send_command(socket, m.to_str());
	    }
	    if(async)handler(err);
	} catch (boost::system::system_error &e) {
	    if(async)handler(e.what() + err);
	    std::cout << "Exception:" << e.what() << "\n";
	}
    }

    void UserAgent::Impl::_listmail(MailList& list, bool async, ListHandler handler) {
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(pop_host, pop_port);
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::resolver::iterator end;

	try {
	    if (tls) {
		boost::asio::ssl::context ctx(io_service,
					      boost::asio::ssl::context::sslv23);
		ctx.set_verify_mode(boost::asio::ssl::context::verify_none);
		boost::asio::ssl::stream<tcp::socket> ssl_socket(io_service, ctx);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
		    ssl_socket.lowest_layer().close();
		    ssl_socket.lowest_layer().connect(*endpoint_iterator++, error);
		    ssl_socket.handshake(boost::asio::ssl::stream_base::client);
		}
		if(error)
		  throw boost::system::system_error(error);
		boost::asio::streambuf b;
		boost::asio::read_until(ssl_socket, b, std::string("\r\n"));

		send_command(ssl_socket, "USER " + user + "\r\n");
		send_command(ssl_socket, "PASS " + password+ "\r\n");

		std::string str = send_command(ssl_socket, "STAT\r\n");

		size_t p1 = str.find(" ");
		size_t p2 = str.find(" ", p1+1);
		int nums = atoi((str.substr(p1, p2-p1)).c_str());
		std::cout << "Num: " << nums << "\n";

		for (int i=1; i<=nums; i++) {
		      std::string str = send_command(ssl_socket, 
					     "TOP " + boost::lexical_cast<std::string>(i) 
					     + " 0\r\n", "\r\n.\r\n");
		      size_t p1 = str.find("Subject:") + 8;
		      if(p1 != std::string::npos) {
			  size_t p2 = str.find("\r\n", p1);
			  list[i] = str.substr(p1, p2-p1);
		      }

		}
		send_command(ssl_socket, "QUIT");
	    } else {
		tcp::socket socket(io_service);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
		    socket.close();
		    socket.connect(*endpoint_iterator++, error);
		}
		if(error)
		  throw boost::system::system_error(error);

		boost::asio::streambuf b;
		boost::asio::read_until(socket, b, std::string("\r\n"));

		send_command(socket, "USER " + user + "\r\n");
		send_command(socket, "PASS " + password+ "\r\n");

		std::string str = send_command(socket, "STAT\r\n");

		size_t p1 = str.find(" ");
		size_t p2 = str.find(" ", p1+1);
		int nums = atoi((str.substr(p1, p2-p1)).c_str());
		std::cout << "Num: " << nums << "\n";

		for (int i=1; i<=nums; i++) {
		      std::string str = send_command(socket, 
					     "TOP " + boost::lexical_cast<std::string>(i) 
					     + " 0\r\n", "\r\n.\r\n");
		      size_t p1 = str.find("Subject:") + 8;
		      if(p1 != std::string::npos) {
			  size_t p2 = str.find("\r\n", p1);
			  list[i] = str.substr(p1, p2-p1);
		      } else {
			  list[i] = "";
		      }
		}
		send_command(socket, "QUIT");
	    }

	    if(async)handler(list);

	} catch (boost::system::system_error &e) {
	    std::cout << "Exception:" << e.what() << "\n";
	    if(async)handler(list);
	}

    }
    void UserAgent::Impl::_fetchmail(Mail &m, bool async, FetchHandler handler){
    }



    Mail::Mail(std::string f, std::string t,
	       std::string s, std::string d):
      from(f), tos(t), subject(s), data(d)
    {}

    std::string Mail::to_str(){
	return "From:" + from + "\r\n" +
	  "To:" + tos + "\r\n" +
	  "Subject:" + subject + "\r\n" +
	  "MIME-Version: 1.0\r\n\r\n" + 
	  data +
	  "\r\n.\r\n";
    }

}

template<class sockType>
std::string send_command(sockType &s, std::string cmd, std::string delim) {
    std::cout << "Send:" << cmd << "\n";

    boost::asio::write(s, boost::asio::buffer(cmd),
		       boost::asio::transfer_all());
    boost::asio::streambuf b;
    boost::asio::read_until(s, b, delim);
    std::istream is(&b);
    std::string r;
    std::string tmp;
    while(getline(is, tmp)){
	r.append(tmp);
    }
    std::cout << "Recive:" << r << "\n";
    return r;
}
