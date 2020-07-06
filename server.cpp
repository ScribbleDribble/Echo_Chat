#include "server.h"

    void Server::accept() {
        // init landing room
        Model::model_ptr model_ptr = Room_Model::create_model();

        Chat_Room::chat_room_ptr room = Chat_Room::create_room("Index", model_ptr);
        Room::room_ptr rm = room->get_shared();

        try {
            
            while(true) {
                boost::system::error_code ec;

                // give connection access to IO and rooms
                Connection::conn_ptr client_ptr = Connection::create_connection(io_context, room);
                listening_socket.accept(client_ptr->get_socket());

                Chat_User::user_ptr c_ptr = client_ptr->get_shared();

                //add user to ground chat room
                room->add_user(c_ptr);

                if (!ec) {
                    std::thread ([client_ptr] { client_ptr->start_read(); }).detach();
                }
            } 
        }

        catch(std::exception& e) {
            std::cout<< "Error: " << e.what() << std::endl;       
        }

    }

    void Server::print_connections() {
        std::cout << connections.size() << std::endl;
    }

    Server::~Server() {
        std::cout << "Closing server" << std::endl;
    }


int main(int argc, char *argv[]) {
    boost::asio::io_context io;

    if (argc != 2) {
        std::cerr << "Usage ./server <port_number>" << std::endl;
        exit(0);
    }
    try {
        Server server(io, std::stoi(argv[1]));
        io.run();
        server.accept();
    }
    
    catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}

