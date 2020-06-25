#include "connection.h"


void Connection::start_read() {
    try {
        while (true) {
        boost::system::error_code ec;

        boost::asio::streambuf read_buffer;
        std::ostream os(&read_buffer);

        auto read_len = boost::asio::read_until(socket, read_buffer, "#");
        if (!ec) {
            std::string msg = Message::remove_delimiter(Message::get_string_from_buf(read_buffer));
            std::cout << msg << std::endl;
            server.print_connections();
        }
    
        if (ec == boost::asio::error::eof) {
            std::cout << "User disconnected" << std::endl;
        }
        // FREEZES
        // boost::asio::async_read_until(socket, read_buffer, "#", boost::bind(&Connection::handle_read, this));
        // io_context.run();
        }
        // room.broadcast(msg);

        // we now want to broadcast this message to other users in the same room
        
        

    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
};