//
// Created by mke on 29/06/2020.
//

#include "chat_user.h"
// todo: replace with std::move
void Client_Handler::send(std::string room_name, std::string msg) {
    Chat_Room::room_ptr room = room_map[room_name];
    room->broadcast(msg);
}

void Client_Handler::add_room(std::string room_name) {
    room_map[room_name] = Chat_Room::create_room(room_name);
}
