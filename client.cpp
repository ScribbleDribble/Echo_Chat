#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include "chat_message.h"
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

class Client {
private:
    tcp::socket socket;
    std::string port_no;
    tcp::resolver resolver;
    tcp::resolver::results_type endpoint;
    
public:


    Client(boost::asio::io_context& io_context, std::string port_no): socket(io_context),
    port_no(port_no), resolver(io_context)
    {
        endpoint = resolver.resolve("127.0.0.1", port_no);
    }

    void connect() {
        boost::asio::connect(socket, endpoint);
    }

    void write(boost::asio::streambuf& buf) {
        boost::asio::async_write(socket, boost::asio::buffer(buf.data(), Message::max_body_size + 1), boost::bind(&Client::print, this));

    }

    void msg_read(boost::asio::streambuf& buf) {
        boost::system::error_code ec;
        if (!ec) {
            //        std::string s;
//        boost::asio::async_read(socket, buf, boost::bind(&Client::handle_read,
//                this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
//                this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)))
//        boost::asio::async_read_until(socket, buf, '#',boost::bind(&Client::handle_read,
//                this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

            auto read_len = boost::asio::read_until(socket, buf, "#");
            std::cout << Message::get_string_from_buf(buf) << std::endl;
            std::string msg = Message::remove_delimiter(Message::get_string_from_buf(buf));
//        buf.consume(buf.size());
//        std::cout << msg << std::endl;
        }
        return;

    }

    void print() {
    }

    void handle_read(boost::system::error_code ec, size_t bt) {
        std::cout << "read success" << std::endl;

    }
};

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: ./client <port_no>" << std::endl;
        exit(0);
    }
    
    try {

        boost::asio::io_context io_context;
        Client client(io_context, argv[1]);
        
        client.connect();
        std::cout << "Connected" << std::endl;

        std::string user_message;
        

        boost::asio::streambuf buf;
        boost::asio::streambuf read_buf;
        std::ostream os(&buf);
        std::istream istream(&read_buf);
        char msg[Message::max_body_size + 1];


        while (std::cin.getline(msg, Message::max_body_size + 1)) {
            boost::system::error_code ec;

            buf.consume(buf.size());
            read_buf.consume(read_buf.size());

            user_message = msg;

            os << user_message.append("#");

            client.write(buf);
            buf.consume(buf.size());

            client.msg_read(read_buf);
            
            io_context.run();

            if (ec == boost::asio::error::eof) {
                std::cerr << "eof error, closing." << std::endl;
            }
        }
    }

    catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }


}