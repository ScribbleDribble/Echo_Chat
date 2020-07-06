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

                if (msg[0] == '/' && m.command_exists(msg)) {
                    run_command(msg);
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
            // boost::asio::async_read_until(socket, read_buffer, "#", boost::bind(&Connection::start_read shared_from_this());
            }
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}

void Connection::run_command(const std::string &cmd) {
    std::string last_cmd = m.get_last_command();
    if (last_cmd == "move") {
        move_room(Message::find_name(cmd));
    }

    else if (last_cmd == "create_room") {
        create_room(Message::find_name(cmd));
    }

    else {
        write("<Server> Command not found");
    }

}
void Connection::move_room(const std::string& new_room_name) {
    Room::room_ptr temp = room->move_room(boost::static_pointer_cast<Chat_User>(shared_from_this()), new_room_name);
    if (temp != nullptr) {
        room = temp;
    }
    else {
        write("<Server> Room not found");
    }
}

void Connection::create_room(const std::string& new_room_name) {
    Room::room_ptr temp = room->create_room(boost::static_pointer_cast<Chat_User>(shared_from_this()), new_room_name);
    if (temp != nullptr) {
        room = temp;
    }
    else {
        write("<Server> Failed to create room");
    }
}

void Connection::write(std::string msg) {
    std::cout << msg << std::endl;
    boost::system::error_code ec;
    boost::asio::streambuf buf;
    std::ostream os(&buf);
    buf.consume(buf.size());


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