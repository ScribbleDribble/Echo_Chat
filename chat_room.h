#ifndef CHAT_ROOM_H
#define CHAT_ROOM_H


#include <iostream>
#include "connection.h"


class Chat_Room {
private:
    std::vector<Connection::conn_ptr> connections;
    typedef boost::shared_ptr<Chat_Room> rooms;
    std::string key; 

public:
    Chat_Room(std::string key, Connection::conn_ptr user): key(0) {
        connections.push_back(user);
    }

    void add_user() {}

    void remove_user();

    void broadcast(std::string msg) {
        for (int i = 0; i < connections.size(); i++) {
            connections[i]->write(msg);
        }
    }
};
#endif 