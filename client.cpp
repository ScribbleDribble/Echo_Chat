#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include "chat_message.h"
#include <boost/bind.hpp>
#include <thread>
#include <deque>


using boost::asio::ip::tcp;
typedef std::deque<Message> message_queue;

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

    void write() {
        std::cout << "write" << std::endl;
        boost::asio::post(io,
                          [this]()
                          {

                                do_write();

                          });
    }

    void do_write() {
        boost::system::error_code ec;

        boost::asio::async_write(socket, buf, boost::bind(&Client::do_write, this));
//        boost::asio::async_write(socket,
//                                 boost::asio::buffer(msg_queue.front().data(),
//                                                     msg_queue.front().length()),
//                                 [this](boost::system::error_code ec, std::size_t /*length*/)
//                                 {
//                                     if (!ec)
//                                     {
//                                         msg_queue.pop_front();
//                                         if (!msg_queue.empty())
//                                         {
//                                             do_write();
//                                         }
//                                     }
//                                     else
//                                     {
//                                         socket.close();
//                                     }
//                                 });



    }

    // TEMP
    std::ostream& get_ostream() {
        return os;
    }


    void handle_read() {
        boost::system::error_code ec;
        if(!ec) {
            buf.consume(buf.size());
            auto read_len = boost::asio::read_until(socket, buf, "#");
//            boost::asio::async_read(socket,
//                                    buf,
//                                    [this](boost::system::error_code ec, std::size_t /*length*/)
//                                    {
//                                        if (!ec)
//                                        {
////                                            std::cout.write(buf.data(), Message::max_body_size);
//                                            std::cout << Message::get_string_from_buf(buf) << std::endl;
//                                            std::string msg = Message::remove_delimiter(Message::get_string_from_buf(buf));
//                                            handle_read(ec, Message::max_body_size);
//                                        }
//                                        else
//                                        {
//
//                                        }
//                                    });

//            boost::asio::async_read(socket, buf, boost::bind(&Client::handle_read, this,boost::asio::placeholders::error,
//                                                             boost::asio::placeholders::bytes_transferred))
//                std::cout << Message::get_string_from_buf(buf) << std::endl;
//                std::string msg = Message::remove_delimiter(Message::get_string_from_buf(buf));
//            }
            /*Do Stuff*/
//            boost::asio::async_read_until(socket, buf, "#", boost::bind(&Client::handle_read, this,
//                                                                        boost::asio::placeholders::error,
//                                                                        boost::asio::placeholders::bytes_transferred));

            std::cout << Message::remove_delimiter("hey mate#") << std::endl;
            std::string msg = Message::get_string_from_buf(buf);
            std::cout << msg << std::endl;
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

//            client.queue_msg(user_message.append("#"));
            client.get_ostream() << user_message.append("#");
//            client.write();
            client.do_write();
//            client.handle_read(ec, Message::max_body_size);
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