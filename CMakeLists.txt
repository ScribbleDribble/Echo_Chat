cmake_minimum_required(VERSION 3.16)

set(Boost_USE_STATIC_LIBS OFF) #enable dynamic linking

project(chat_app)

add_executable(
	server
	server.cpp
	connection.cpp
         connection.h room.h chat_room.h sqlite3.h room_model.cpp model.h room_model.h room_model.cpp)

add_executable(client client.cpp)
include_directories(${../libraries/boost_1_73_0})


TARGET_LINK_LIBRARIES(server pthread sqlite3)


