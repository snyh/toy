#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <assert.h>
#include <fstream>
#include <openssl/md5.h>
#include <bitset>
#include "msg.h"

using namespace std;
namespace ba = boost::asio;
using namespace boost::asio::ip;

class proxy;

class Session {
    public:
        Session(ba::io_service& ios)
            : m_ios(ios), 
            m_socket(ios) {
            } 
        tcp::socket& socket() { return m_socket; }
        void start() {
            ba::async_read(m_socket,
                    ba::buffer(&m_header, 4),
                    boost::bind(&Session::handle_header, this,
                        ba::placeholders::error,
                        ba::placeholders::bytes_transferred)
                    );
        }
        
        void handle_result(UID, char* result) {
        }
        void handle_timeout(UID) {
        }

    private:
        void handle_header(const boost::system::error_code& error,
                size_t bytes_transferred) {
            switch (m_header) {
                case REG_APP:
                    ba::async_read(m_socket,
                            ba::buffer(m_body, 4),
                            boost::bind(&Session::handle_reg_app, this,
                                ba::placeholders::error,
                                ba::placeholders::bytes_transferred));
                    break;
                case CAP_RESPONSE_OK:
                    ba::async_read(m_socket,
                            ba::buffer(m_body, 16),
                            boost::bind(&Session::handle_response_ok, this,
                                ba::placeholders::error,
                                ba::placeholders::bytes_transferred));
                    break;
                case CAP_RESPONSE_ERR:
                    ba::async_read(m_socket,
                            ba::buffer(m_body, 16),
                            boost::bind(&Session::handle_response_err, this,
                                ba::placeholders::error,
                                ba::placeholders::bytes_transferred));
                    break;
                case CAP_REQUEST:
                    ba::async_read(m_socket,
                            ba::buffer(m_body, 4),
                            boost::bind(&Session::handle_fetch_cap_size, this,
                                ba::placeholders::error,
                                ba::placeholders::bytes_transferred));
                    break;
                default:
                    char* buf = (char*)&m_header;
                    printf("(%d, %d, %d, %d\n", buf[0], buf[1], buf[2], buf[3]);
                    cout << "Not Support Operaion " << m_header << endl;
                    //send_error("Not Support Operation!");
            }
        }

        void handle_fetch_cap_size(const boost::system::error_code& error,
                size_t bytes_transferred) {
            m_cap_size = *(size_t*)(m_body);

            ba::async_read(m_socket,
                    ba::buffer(m_body, m_cap_size),
                    boost::bind(&Session::handle_cap_request, this,
                        ba::placeholders::error,
                        ba::placeholders::bytes_transferred));
        }

        void handle_cap_request(const boost::system::error_code& error,
                size_t bytes_transferred) {
            if (!error) {
                cout << this << " handle_cap_request size: " << m_cap_size << endl;

                ofstream  test("test.jpg");
                test.write(m_body, m_cap_size);

                //m_proxy->handle_captcha(m_cap_size, m_data);

                assert(bytes_transferred == m_cap_size);
            } else {
                cout << this << "  ERRRRR" << endl;
            }
        }

        void handle_response_ok(const boost::system::error_code& error,
                size_t bytes_transferred) {
            assert(bytes_transferred == 16);
            UID uid;
            memcpy(uid.data, m_body, 16);
            cout << "handle_response_ok";
            for (int i=0; i<16; i++) {
                cout << " " << int(uid.data[i]);
            }
            cout << endl;
        }

        void handle_response_err(const boost::system::error_code& error,
                size_t bytes_transferred) {
            assert(bytes_transferred == 16);
            UID uid;
            memcpy(uid.data, m_body, 16);
            cout << "handle_response_err";
            for (int i=0; i<16; i++) {
                cout << " " << int(uid.data[i]);
            }
            cout << endl;
        }

        void handle_reg_app(const boost::system::error_code& error,
                size_t bytes_transferred) {
            if (!error) {
                uint32_t uid = *(uint32_t*)(m_body);
                cout << "handle_reg_app :" << uid << endl;
                assert(bytes_transferred == 4);
            } else {
                cout << error << endl;
            }
        }

        void send_error(const char* message) {
            cout << "ERROR: " << message << endl;
        }

    private:
        uint32_t m_header;
        char m_body[800*1024]; // 800k is enough?
        size_t m_cap_size;
        tcp::socket m_socket;
        ba::io_service& m_ios;
};

class Proxy {
    enum { InQueue, VerifyFailed, Successful } State;
    private:
    State state;
    int blance;
    public:
        Proxy(ba::io_service& ios, short port) 
            : m_ios(ios),
            m_socket(ios),
            m_acceptor(ios, tcp::endpoint(tcp::v4(), port)),
            m_verified(false) {
                start_proxy();
                UID uid;
                verify(123, 32, uiuidd);
            }

        void verify(uint32_t aid, uint32_t uid, UID key) {
            char verify_info[24];
            memcpy(verify_info, &aid, 4);
            memcpy(verify_info + 4, &uid, 4);
            memcpy(verify_info + 8, key.data, 16);


            uint32_t result;
            tcp::resolver resolver(m_ios);
            tcp::resolver::query query(tcp::v4(), "localhost", "8011");
            tcp::resolver::iterator iterator = resolver.resolve(query);

            ba::connect(m_socket, iterator);

            ba::write(m_socket, ba::buffer(verify_info));
            ba::read(m_socket, ba::buffer(&result, 4));
            bitset<32> bits(result);
            if (bits[31]) {
                m_state = InQueue;
            } else if (bits[30]) {
                m_state = VerifyFailed;
            } else if (bits[29]) {
                m_state = VerifyFailed;
            } else if (bits[28]) {
                m_state = VerifyFailed;
            } else {
                m_state = VerifySucc;
                m_blance = result;
            }
        }

        void handle_captcha(Session* session, char* data) {
            ba::async_send(m_socket, ba::buffer(data));
            UID uid = UID(data);
            m_captcha_infos[uid] = session;
        }

        Map<UID, Session*> m_captcha_infos;


    private:
        void start_proxy() {
            Session* new_session = new Session(m_ios);
            m_acceptor.async_accept(new_session->socket(),
                    boost::bind(&Proxy::handle_accept, this, new_session,
                        boost::asio::placeholders::error));
        }

        void handle_accept(Session* new_session,
                const boost::system::error_code& error) {
            if (!error) {
                new_session->start();
            } else {
                cout << "error..." <<error<< endl;
                delete new_session;
            }
            start_proxy();
        }

    private:
        ba::io_service& m_ios;
        long m_aid;
        long m_uid;
        UID m_key;
        bool m_verified;
        tcp::acceptor m_acceptor;
        tcp::socket m_socket;

};

int main()
{
    ba::io_service ios;
    Proxy proxy(ios, 8010);
    ios.run();
    return 0;
}
