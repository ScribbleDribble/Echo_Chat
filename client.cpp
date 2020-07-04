#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include "chat_message.h"
#include <boost/bind.hpp>
#include <thread>
#include <deque>


using boost::asio::ip::tcp;

class Client {
private:
    tcp::socket socket;

    tcp::resolver::results_type endpoint;
    boost::asio::streambuf& buf;
    std::ostream os;
    boost::asio::io_context& io;


    std::deque<std::string> msg_queue;



public:


    Client(boost::asio::io_context& io_context, boost::asio::streambuf& buf, const tcp::resolver::results_type& endpoints):
    socket(io_context), buf(buf), os(&buf), io(io_context)
    {
        boost::system::error_code ec;
        boost::asio::async_connect(socket, endpoints,
                                   [this](boost::system::error_code ec, const tcp::endpoint&)
                                   {
                                       handle_read();
                                   });
    }


    void queue_msg(std::string msg) {
        msg_queue.push_back(msg);
    }


    void do_write() {
        boost::system::error_code ec;
        if (!ec) {
            boost::asio::async_write(socket, buf, boost::bind(&Client::do_write, this));
        }
        else {
            std::cout << "Something went wrong with the connection!" << std::endl;
        }
    }

    // TEMP
    std::ostream& get_ostream() {
        return os;
    }


    void handle_read() {
        boost::system::error_code ec;
        if(!ec) {
            buf.consume(Message::max_body_size);
            auto read_len = boost::asio::read_until(socket, buf, "#");


//            boost::asio::async_read(socket, buf, boost::bind(&Client::handle_read, this,boost::asio::placeholders::error,
//                                                             boost::asio::placeholders::bytes_transferred))
//                std::cout << Message::get_string_from_buf(buf) << std::endl;
//                std::string msg = Message::remove_delimiter(Message::get_string_from_buf(buf));
//            }
            /*Do Stuff*/
//            boost::asio::async_read_until(socket, buf, "#", boost::bind(&Client::handle_read, this));

            if (!msg_queue.empty()) {
                std::cout << "\n" << "<You> " << msg_queue[0] << std::endl;
                msg_queue.pop_front();
            }
            else {
                std::string msg = Message::get_string_from_buf(buf);
                std::cout << msg << std::endl;
            }
//
            handle_read();


        } else {
            /*Error handling*/
        }
    }
};



int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: ./client <port_no>" << std::endl;
        exit(0);
    }
    
    try {

        boost::asio::io_context io_context;
        boost::asio::streambuf buf;

        tcp::resolver resolver(io_context);

        auto endpoints = resolver.resolve("127.0.0.1", argv[1]);

        Client client(io_context, buf, endpoints);

        std::cout << "Connected" << std::endl;

        std::string user_message;


        char msg[Message::max_body_size + 1];
        boost::system::error_code ec;

        std::thread t([&io_context](){ io_context.run(); });
        while (std::cin.getline(msg, Message::max_body_size + 1)) {
            boost::system::error_code ec;

            buf.consume(buf.size());

            user_message = msg;
            client.queue_msg(user_message);

            client.get_ostream() << user_message.append("#");


//            client.write();
            client.do_write();
            if (ec == boost::asio::error::eof) {
                std::cerr << "eof error, closing." << std::endl;
            }
        }
        t.join();

    }


    catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }


}