#include <boost/asio.hpp>
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

    void print() {
        std::cout << "Write successful" << std::endl;
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
        std::ostream os(&buf);
        char msg[Message::max_body_size + 1];

        
        while (std::cin.getline(msg, Message::max_body_size + 1)) {
            boost::system::error_code ec;

            buf.consume(buf.size());
            
            user_message = msg;
            os << user_message.append("#");
            client.write(buf);
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