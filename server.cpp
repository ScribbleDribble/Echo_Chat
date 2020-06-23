#include <iostream>
#include <boost/asio.hpp>
#include "connection.hpp"

using boost::asio::ip::tcp;

class Server {
private:
    boost::asio::io_context& io_context;
    tcp::acceptor listening_socket;
    

public:
    Server(boost::asio::io_context& io_context, unsigned int port_no): io_context(io_context), listening_socket(io_context, tcp::endpoint(tcp::v4(), port_no)) {};

    void accept() {
        
        while(true) {
            Connection::conn_ptr client = Connection::create_connection(io_context);
            Connection::conn_ptr c = client->get_shared();
            listening_socket.accept(client->get_socket());
        }        
    }
};

int main(int argc, char *argv[]) {
    boost::asio::io_context io;

    if (argc != 2) {
        std::cerr << "Usage ./server <port_number>" << std::endl;
        exit(0);
    }
    try {
        Server server(io, std::stoi(argv[1]));
        server.accept();
    }
    
    catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}