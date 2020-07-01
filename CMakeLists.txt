cmake_minimum_required(VERSION 3.16)

set(Boost_USE_STATIC_LIBS OFF) #enable dynamic linking

project(chat_app)

add_executable(
	server
	server.cpp
	connection.cpp
         connection.h room.h chat_room.h)
include_directories(${../libraries/boost_1_73_0})


TARGET_LINK_LIBRARIES(server pthread)


