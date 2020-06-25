#define BOOST_ASIO_NO_DEPRECATED

#ifndef SERVER_H
#define SERVER_H


#include <iostream>
#include <boost/asio.hpp>
#include "connection.h"
#include "chat_room.h"
#include <boost/bind.hpp>
#include <thread>
#include <boost/enable_shared_from_this.hpp>


using boost::asio::ip::tcp;

class Server{

private:

    boost::asio::io_context& io_context;
    tcp::acceptor listening_socket;

    std::vector<Connection::conn_ptr> connections;
    std::vector<Chat_Room::room_ptr> chat_rooms;
    std::vector<std::thread> threads;

public:
    typedef boost::shared_ptr<Server> server_ptr;

    Server(boost::asio::io_context& io_context, unsigned int port_no): io_context(io_context), listening_socket(io_context, tcp::endpoint(tcp::v4(), port_no)) {};

    void accept(Server& server);

    void print_connections();

    ~Server();
    // typedef boost::shared_ptr<Server> server_ptr;

    // Server(boost::asio::io_context& io_context, unsigned int port_no): io_context(io_context), listening_socket(io_context, tcp::endpoint(tcp::v4(), port_no)) {};

    // void accept(Server& server) {

    //     try {
    //         while(true) {
    //             boost::system::error_code ec;

    //             Connection::conn_ptr client = Connection::create_connection(io_context, server);
    //             listening_socket.accept(client->get_socket());
    //             Connection::conn_ptr c = client->get_shared();
    //             connections.push_back(c);

    //             if (!ec) {
    //                 std::thread (boost::bind(&Connection::start_read, c)).detach();
    //             }
    //         } 
    //     }

    
    //     catch(std::exception& e) {
    //         std::cout<< "Error: " << e.what() << std::endl;       
    //     }

    // }

    // void print_connections() {
    //     for (int i = 0; i < connections.size(); i++) {
    //         std::cout << connections[i] << std::endl;
    //     }
    // }

    // // server_ptr get_shared() {
    // //     return shared_from_this();
    // // }

    // ~Server() {
    //     std::cout << "Closing server" << std::endl;
    // }

};
#endif