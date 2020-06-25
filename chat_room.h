#ifndef CHAT_ROOM_H
#define CHAT_ROOM_H

#include <iostream>
#include "connection.h"


class Chat_Room {
private:
    std::vector<Connection::conn_ptr> connections;
    std::string key; 

public:
    typedef boost::shared_ptr<Chat_Room> room_ptr;


    Chat_Room(std::string key, Connection::conn_ptr client): key(0) {
        connections.push_back(client);
    }

    void add_user(Connection::conn_ptr client) {
        connections.push_back(client);
    }

    void remove_user(Connection::conn_ptr client) {
        
        // for (int i = 0; i < connections.size(); i++) {
        //     if (connections[i] == client) {
        //         connections[i].pop();
        //     }
        // }
    }

    void broadcast(std::string msg) {
        for (int i = 0; i < connections.size(); i++) {
            connections[i]->write(msg);
        }
    }
};
#endif 