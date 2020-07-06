#ifndef CHAT_ROOM_H
#define Chat_ROOM_H

#include <utility>

#include "room.h"
#include "room_model.h"

class Chat_Room : public boost::enable_shared_from_this<Chat_Room>, public Room{
private:

    std::vector<Chat_User::user_ptr> connections;
    std::string name;
    Model::model_ptr room_model_ptr;

    Chat_Room(const std::string& name, Model::model_ptr model_ptr): name(name), room_model_ptr(std::move(model_ptr)){

        room_model_ptr->add(name);

        // check for any existing rooms

        // otherwise proceed to insert room into table

        std::cout << "You created the room: " << name << std::endl;
    }

    void save(const std::string& room_name) override {
        room_model_ptr->map_insert(room_name, shared_from_this());
        room_model_ptr->add(room_name);
    }


public:

    typedef boost::shared_ptr<Chat_Room> chat_room_ptr;

    void broadcast(const std::string& msg) override {
        std::cout << connections.size() << std::endl;
        for (auto & connection : connections) {
            connection->write("<" + name + ">: " + msg);
        }
    }

    static void pipe(Chat_User::user_ptr user,const std::string& msg)  {
        std::move(user)->write(msg);
    }

    static chat_room_ptr create_room(const std::string& room_name, Model::model_ptr model_ptr) {
        chat_room_ptr c(new Chat_Room(room_name, std::move(model_ptr)));
        c->save(room_name);
        return c;
    }

    Chat_Room::room_ptr create_room(const Chat_User::user_ptr user, const std::string& room_name) override {
        // room creation based on user cmd
        if (room_model_ptr->exists(room_name)) {
            return nullptr;
        }
        create_room(room_name, room_model_ptr);
        return move_room(user, room_name);
    }

    void add_user(const boost::shared_ptr<Chat_User> client_ptr) override {
        broadcast("A new user has joined " + name + "!");
        pipe(client_ptr, "<" + name + ">" + " You have joined " + name + "!");
        connections.push_back(client_ptr);
    }

    std::string get_name() override {
        return name;
    }

    Room::room_ptr move_room(Chat_User::user_ptr client, const std::string& room_name) override {
        if (room_model_ptr->exists(room_name)) {
            remove_user(client);

            room_ptr room = room_model_ptr->get_room(room_name);
            room->add_user(client);
            return room;
        }

        return nullptr;
    }


    Room::room_ptr get_shared() override {
        return boost::static_pointer_cast<Room>(shared_from_this());
    }

    void remove_user(const Chat_User::user_ptr client) override {

        for (auto it = connections.begin(); it != connections.end(); it++) {
            if (*it == client) {
                connections.erase(it);
                break;
            }
        }
    }


};
#endif