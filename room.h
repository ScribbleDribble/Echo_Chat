//
// Created by mke on 30/06/2020.
//

#ifndef CHAT_APP_ROOM_H
#define CHAT_APP_ROOM_H
#include <boost/asio.hpp>
#include "chat_user.h"


class Room {
private:
    virtual void save(const std::string& room_name) = 0;


public:
    typedef boost::shared_ptr<Room> room_ptr;
    virtual void broadcast(const std::string& msg) = 0;

    virtual void add_user(const Chat_User::user_ptr usr_ptr) = 0;

    virtual void remove_user(const Chat_User::user_ptr usr_ptr) = 0;

    virtual room_ptr move_room(Chat_User::user_ptr, const std::string& room_name) = 0;

    virtual room_ptr get_shared() = 0;

    virtual std::string get_name() = 0;
};


#endif //CHAT_APP_ROOM_H
