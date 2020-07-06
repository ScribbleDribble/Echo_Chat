//
// Created by mke on 03/07/2020.
//

#include "sqlite3.h"
#include <string>
#include <iostream>
#include "room_model.h"

#define PATH "/home/mke/projects/c++/chat_app/db/room.db"


Room_Model::Room_Model() noexcept {
    DB::create_db(PATH);
    DB::create_table(PATH);
}

void Room_Model::add(const std::string& room_name) {
    DB::insert_data(PATH, std::string("INSERT INTO ROOM (NAME) VALUES ('" + room_name + "');"));
}

void Room_Model::map_insert(const std::string& room_name, Room::room_ptr room) {
    house_map[room_name] = std::move(room);
}

void Room_Model::remove(const std::string& room_name)  {
    DB::insert_data(PATH, std::string("INSERT INTO ROOM (NAME) VALUES ('" + room_name + "');"));
}

bool Room_Model::exists(const std::string& room_name) {
    return house_map.count(room_name) == 1;
}

Room::room_ptr Room_Model::get_room(const std::string& room_name) {
    return house_map[room_name];
}

Model::model_ptr Room_Model::create_model() {
    return boost::static_pointer_cast<Model>(room_model_ptr(new Room_Model()));
}