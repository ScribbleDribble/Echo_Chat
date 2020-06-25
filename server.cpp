#include "server.h"

    void Server::accept(Server& server) {

        try {
            while(true) {
                boost::system::error_code ec;

                Connection::conn_ptr client = Connection::create_connection(io_context, server);
                listening_socket.accept(client->get_socket());
                Connection::conn_ptr c = client->get_shared();
                connections.push_back(c);

                if (!ec) {
                    std::thread (boost::bind(&Connection::start_read, c)).detach();
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

    // server_ptr get_shared() {
    //     return shared_from_this();
    // }

    Server::~Server() {
        std::cout << "Closing server" << std::endl;
    }
    
    
    // void setup(int n_threads) {
    //     auto count = std::thread::hardware_concurrency() * 2;
    //     for (int i = 0; i < count; i++) {
    //         threads.emplace_back(boost::asio::io_context::run, io_context);
            
    //     }

    //     for(auto& thread : threads)
    //     {
    //         if(thread.joinable())
    //         {
    //             thread.join();
    //         }
    //     }
    // }

// void Server::accept(Server& server) {

//     try {
//         while(true) {
//             boost::system::error_code ec;

//             Connection::conn_ptr client = Connection::create_connection(io_context, server);
//             listening_socket.accept(client->get_socket());
//             Connection::conn_ptr c = client->get_shared();
//             connections.push_back(c);

//             if (!ec) {
//                 std::thread t(boost::bind(&Connection::start_read, c));
//             }
//         } 
//     }

//     catch(std::exception& e) {
//         std::cout<< "Error: " << e.what() << std::endl;       
//     }
// }



int main(int argc, char *argv[]) {
    boost::asio::io_context io;

    if (argc != 2) {
        std::cerr << "Usage ./server <port_number>" << std::endl;
        exit(0);
    }
    try {
        Server server(io, std::stoi(argv[1]));
        server.accept(server);
    }
    
    catch(std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}

