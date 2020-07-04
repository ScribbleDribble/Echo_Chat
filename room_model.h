//
// Created by mke on 04/07/2020.
//

#ifndef CHAT_APP_ROOM_MODEL_H
#define CHAT_APP_ROOM_MODEL_H

#endif //CHAT_APP_ROOM_MODEL_H

#include "model.h"
#include "room.h"
#include <map>

class Room_Model : public Model{
private:


    std::map<int, Room::room_ptr> house_map;

    std::string name;
    int id{};
    std::string passcode;
    Room_Model() noexcept ;

public:
    typedef boost::shared_ptr<Room_Model> room_model_ptr;

    void add(const std::string&) override ;
    void remove(const std::string&) override ;
    static Model::model_ptr create_model();

};