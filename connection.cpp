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
            room->broadcast(msg);
            read_buffer.consume(read_buffer.size());
        }
    
        if (ec == boost::asio::error::eof) {
            std::cout << "User disconnected" << std::endl;
        }


        // FREEZES
        // boost::asio::async_read_until(socket, read_buffer, "#", boost::bind(&Connection::handle_read, this));
        // io_context.run();

        // POTENTIAL FIX?
        // boost::asio::async_read_until(socket, read_buffer, "#", boost::bind(&Connection::handle_read, shared_from_this());
        }
        // room.broadcast(msg);

        // we now want to broadcast this message to other users in the same room
        
        

    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}

void Connection::write(std::string msg) {
//    std::cout<< msg << std::endl;

    boost::system::error_code ec;
    boost::asio::streambuf buf;
    std::ostream os(&buf);

    buf.consume(buf.size());
    os << msg.append("#");
    boost::asio::async_write(socket, boost::asio::buffer(buf.data(),
            Message::max_body_size + 1),boost::bind(&Connection::write_success, this));

}

void Connection::write_success() {
    std::cout << "write success" << std::endl;


}

//void House::send(const std::string& room_name, const std::string& msg) {
//    Chat_Room::room_ptr room = room_map[room_name];
////    room.broadcast(msg);
//}
//
//void House::add_room(const std::string& room_name) {
////    room_map[room_name] = Chat_Room::create_room(room_name);
//}