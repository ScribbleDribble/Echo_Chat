
#include <iostream>
#include <boost/asio.hpp>
#include "connection.h"
#include "chat_room.h"
#include <boost/bind.hpp>
#include <thread>

using boost::asio::ip::tcp;

class Server {
private:
    boost::asio::io_context& io_context;
    tcp::acceptor listening_socket;

    std::vector<Connection::conn_ptr> connections;
    

public:
    Server(boost::asio::io_context& io_context, unsigned int port_no): io_context(io_context), listening_socket(io_context, tcp::endpoint(tcp::v4(), port_no)) {};
    

    void accept() {
        try {
            while(true) {
                boost::system::error_code ec;

                Connection::conn_ptr client = Connection::create_connection(io_context);
                listening_socket.accept(client->get_socket());
                Connection::conn_ptr c = client->get_shared();
                connections.push_back(c);

                if (!ec) {
                    std::thread (boost::bind(&Connection::start_read, c)).detach();
                }
            } 
        }

        catch(std::exception& e) {
            std::cout<< "Error: " << e.what() << std::endl;       
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

    return 0;
}

