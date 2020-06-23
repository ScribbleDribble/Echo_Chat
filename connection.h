#ifndef CONNECTION_H
#define CONNECTION_H

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

    Connection(boost::asio::io_context& io_context): socket(io_context), 
    io_context(io_context){};

public:
    typedef boost::shared_ptr<Connection> conn_ptr;

    static conn_ptr create_connection(boost::asio::io_context& io_context) {
        return conn_ptr(new Connection(io_context));
    }

    conn_ptr get_shared() {
        return shared_from_this();
    }

    tcp::socket& get_socket() {
        return socket;
    }
    
    void start_read() {
        try {
            while (true) {
            boost::system::error_code ec;

            boost::asio::streambuf read_buffer;
            std::ostream os(&read_buffer);

            auto read_len = boost::asio::read_until(socket, read_buffer, "#");
            if (!ec) {
                std::cout << Message::remove_delimiter(Message::get_string_from_buf(read_buffer)) << std::endl;
            }
            
            if (ec == boost::asio::error::eof) {
                std::cout << "User disconnected" << std::endl;
            }
            // FREEZES
            // boost::asio::async_read_until(socket, read_buffer, "#", boost::bind(&Connection::handle_read, this));
            // io_context.run();
            }

        }
        catch(std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    
    }

    void write(std::string msg) {

    }        

    // void handle_read() {
    //     std::cout << Message::remove_delimiter(Message::get_string_from_buf(read_buffer)) << std::endl;
        
    // }

};

#endif

