#ifndef CONNECTION_H
#define CONNECTION_H

#include <utility>
#include <vector>
#include <map>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include "chat_message.h"
#include "chat_user.h"
#include "room.h"
#include <boost/bind.hpp>
#include <boost/array.hpp>
//#include "chat_room.h"
using boost::asio::ip::tcp;

class Connection : public boost::enable_shared_from_this<Connection>, public Chat_User{

private:

    tcp::socket socket;
    boost::asio::io_context& io_context;
    Room::room_ptr room;

    Connection(boost::asio::io_context& io_context, Room::room_ptr room): socket(io_context),
                                                                      io_context(io_context), room(std::move(room)){};

public:
    typedef boost::shared_ptr<Connection> conn_ptr;

    static conn_ptr create_connection(boost::asio::io_context& io_context, Room::room_ptr room) {
        return conn_ptr(new Connection(io_context, std::move(room)));
    }

    user_ptr get_shared() {
        // convert pointer from derived class (Connection) to base class (Chat User) so it can be used.
        return boost::static_pointer_cast<Chat_User>(shared_from_this());
    }

    tcp::socket& get_socket() {
        return socket;
    }

    void start_read() override ;

    void write(std::string msg) override;

    void write_success();

    ~Connection() {

//        room->remove_user(*this);
        socket.close();
    }

};

#endif


//#endif

