#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "msg.h"

using boost::asio::ip::tcp;
namespace ba = boost::asio;

class Session {
    public:
        Session(boost::asio::io_service& io_service)
            : m_socket(io_service)
        {
        }

        tcp::socket& socket() { 
            return m_socket;
        }

        void start() {
            ba::async_read(m_socket, 
                    ba::buffer(m_data, 24),
                    boost::bind(&Session::handle_auth, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }

        void handle_auth(const boost::system::error_code& error,
                size_t bytes_transferred) {
            uint32_t aid = *(uint32_t*)(m_data);
            uint32_t uid = *(uint32_t*)(m_data+4);
            UID key;
            memcpy(key.data, m_data+8, 16);
            printf("aid:%d  uid:%d\n",  aid, uid);

            start();

        }

        void handle_read(const boost::system::error_code& error,
                size_t bytes_transferred) {
            if (!error) {
                boost::asio::async_write(m_socket,
                        boost::asio::buffer(m_data, bytes_transferred),
                        boost::bind(&Session::handle_write, this,
                            boost::asio::placeholders::error));
            } else {
                delete this;
            }
        }

        void handle_write(const boost::system::error_code& error) {
            if (!error) {
                m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
                        boost::bind(&Session::handle_read, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
            } else {
                delete this;
            }
        }
    private:
        tcp::socket m_socket;
        enum { max_length = 1024 };
        char m_data[max_length];
};


class Server {
    public:
        Server(boost::asio::io_service& io_service, short port)
            : m_io_service(io_service),
            m_acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {
                Session* new_session = new Session(m_io_service);
                m_acceptor.async_accept(new_session->socket(),
                        boost::bind(&Server::handle_accept, this, new_session,
                            boost::asio::placeholders::error));
            }

        void handle_accept(Session* new_session,
                const boost::system::error_code& error) {
            if (!error) {
                new_session->start();
                new_session = new Session(m_io_service);
                m_acceptor.async_accept(new_session->socket(),
                        boost::bind(&Server::handle_accept, this, new_session,
                            boost::asio::placeholders::error));
            } else {
                delete new_session;
            }
        }

    private:
        boost::asio::io_service& m_io_service;
        tcp::acceptor m_acceptor;
};

int main(int argc, char* argv[])
{
    try {
        boost::asio::io_service io_service;
        Server s(io_service, 8011);
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

