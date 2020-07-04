#ifndef CHAT_ROOM_H
#define Chat_ROOM_H

#include <utility>

#include "room.h"
#include "room_model.h"

class Chat_Room : Room{
private:

    std::vector<Chat_User::user_ptr> connections;
    std::string name;
    Model::model_ptr model_ptr;

    Chat_Room(const std::string& name, Model::model_ptr model_ptr): name(name), model_ptr(std::move(model_ptr)){

        // check for any existing rooms using sql query

        // otherwise proceed to insert room into table

        std::cout << "You created the room: " << name << std::endl;
    }

public:

    void broadcast(const std::string& msg) override {
        std::cout << connections.size() << std::endl;
        for (auto & connection : connections) {
            connection->write("<" + name + ">: " + msg);
        }
    }

    static room_ptr create_room(const std::string& room_name, Model::model_ptr model_ptr) {
        // need to check if room name already exists
        return room_ptr((Room *)(new Chat_Room(room_name, std::move(model_ptr))));

    }

    void add_user(const boost::shared_ptr<Chat_User>& client_ptr) override {
        connections.push_back(client_ptr);
    }
//
//    room_ptr get_shared() {
//        return shared_from_this();
//    }




    std::string get_name() {
        return name;
    }

//    void move_room(Connection::conn_ptr client, std::string room_name) {
//        // call remove_user() for current room
//
//        // proceed to add user to new room
//
//        room_ptr room = server.get_room(room_name);
//        room->add_user(client);
//    }

//    void create_room) {
//        // need to check if room name already exists
//        Chat_Room::room_ptr new_room(new Chat_Room(room_name, server));
//
//        room_map[new_room->get_name()] = new_room;
//
//        remove_user(client);
//        new_room->add_user(client);
//    }



    void remove_user(Connection::conn_ptr client) {

        // for (int i = 0; i < connections.size(); i++) {
        //     if (connections[i] == client) {
        //         connections[i].pop();
        //     }
        // }
    }


};
#endif