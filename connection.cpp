#include "connection.h"

void Connection::start_read() {
    try {
        while (true) {
            boost::system::error_code ec;

            boost::asio::streambuf read_buffer;
            std::ostream os(&read_buffer);

            auto read_len = boost::asio::read_until(socket, read_buffer, "#");
            if (!ec) {
                std::string msg = Message::get_string_from_buf(read_buffer);

                // TODO dedicated function for initiating user commands
                if(msg.substr(0,5) == std::string("/move")) {
                    Message::remove_delimiter(msg);
                    room = room->move_room(boost::static_pointer_cast<Chat_User>(shared_from_this()), Message::find_name(msg));
                    std::cout << "MADE IT" << std::endl;
                }

                else {
                    Message::remove_delimiter(msg);
                    room->broadcast(msg);
                }

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

    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}

void Connection::write(std::string msg) {
    boost::system::error_code ec;
    boost::asio::streambuf buf;
    std::ostream os(&buf);
    buf.consume(buf.size());


    std::cout <<"| "<< msg << std::endl;
    os << msg.append("#");
    boost::asio::async_write(socket, boost::asio::buffer(buf.data(),
            msg.size()),boost::bind(&Connection::write_success, shared_from_this()));

}

void Connection::write_success() {
    std::cout << "write success" << std::endl;


}

Chat_User::user_ptr Connection::get_parent_shared() {
    return boost::static_pointer_cast<Chat_User>(shared_from_this());
}


//void House::send(const std::string& room_name, const std::string& msg) {
//    Chat_Room::room_ptr room = room_map[room_name];
////    room.broadcast(msg);
//}
//
//void House::add_room(const std::string& room_name) {
////    room_map[room_name] = Chat_Room::create_room(room_name);
//}