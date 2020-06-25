#ifndef CONNECTION_H
#define CONNECTION_H

class Server;
#include "server.h"
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "chat_message.h"
#include <boost/bind.hpp>
using boost::asio::ip::tcp;


class Connection : public boost::enable_shared_from_this<Connection> {


private:
    tcp::socket socket;
    boost::asio::io_context& io_context;
    Server& server;

    Connection(boost::asio::io_context& io_context, Server& server): socket(io_context), 
    io_context(io_context), server(server) {};

public:
    typedef boost::shared_ptr<Connection> conn_ptr;

    static conn_ptr create_connection(boost::asio::io_context& io_context, Server& server) {
        return conn_ptr(new Connection(io_context, server));
    }


    conn_ptr get_shared() {
        return shared_from_this();
    }

    tcp::socket& get_socket() {
        return socket;
    }

    
    void start_read();


    void write(std::string msg);       

    // void handle_read() {
    //     std::cout << Message::remove_delimiter(Message::get_string_from_buf(read_buffer)) << std::endl;
        
    // }

};

#endif

