class Chat_Room : public boost::enable_shared_from_this<Chat_Room>, Room{
private:

    std::vector<Chat_User::user_ptr> connections;
    std::string name;

    Chat_Room(const std::string& name): name(name){
        std::cout << "You created the room: " << name << std::endl;
    }

public:


    void broadcast(const std::string& msg) override {
        std::cout << connections.size() << std::endl;
        for (auto & connection : connections) {
            std::cout << "done" << std::endl;
            connection->write("<" + name + ">: " + msg);
        }
    }

    static room_ptr create_room(const std::string& room_name) {
        Room* room = new Chat_Room(room_name);
        // need to check if room name already exists
        return room_ptr(room);

    }

    void add_user(const boost::shared_ptr<Chat_User>& client_ptr) {
        connections.push_back(client_ptr);
    }
//
//    room_ptr get_shared() {
//        return shared_from_this();
//    }


//    void add_user(Connection::conn_ptr client, int id): roomId(id){
//
//        connections.push_back(client);
//        client->set_room(*this);
//        std::cout << "You moved to: " << this->get_name() << std::endl;
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