
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include "connection.h"
#include "chat_room.h"
#include <boost/bind.hpp>
#include <thread>
#include <memory>


using boost::asio::ip::tcp;

class Server{

private:

    boost::asio::io_context& io_context;
    tcp::acceptor listening_socket;

    std::vector<Connection::conn_ptr> connections;
    

public:

    Server(boost::asio::io_context& io_context, unsigned int port_no): io_context(io_context), listening_socket(io_context, tcp::endpoint(tcp::v4(), port_no)) {};

    void accept();

    void print_connections();


    ~Server();
    

};


#endif