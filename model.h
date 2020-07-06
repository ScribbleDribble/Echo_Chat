//
// Created by mke on 03/07/2020.
//

#ifndef CHAT_APP_MODEL_H
#define CHAT_APP_MODEL_H

#endif //CHAT_APP_MODEL_H
#include "sqlite3.h"
#include <boost/shared_ptr.hpp>
#include "room.h"

class DB {
private:

public:

    static int create_db(const char* filepath) {
        sqlite3* DB;
        int exit = 0;

        exit = sqlite3_open(filepath, &DB);

        sqlite3_close(DB);

        return 0;
    }

    static int create_table(const char* filepath) {
        sqlite3* DB;

        std::string sql = "CREATE TABLE IF NOT EXISTS ROOM("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "NAME TEXT NOT NULL);";
//                      ")"";";

        try {
            int exit = 0;
            exit = sqlite3_open(filepath, &DB);

            char* err;
            exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &err);

            if (exit != SQLITE_OK) {
                std::cerr << "Error creating table" << std::endl;
                sqlite3_free(err);
            }

            else {
                std::cout << "Table created successfully" << std::endl;
            }
            sqlite3_close(DB);
        }

        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }

        return 0;

    }

    static int insert_data(const char *filepath, std::string sql) {
        sqlite3* DB;
        char* err;

        int exit = sqlite3_open(filepath, &DB);

        if (exit != SQLITE_OK) {
            std::cerr << "Error inserting data" << std::endl;
            sqlite3_free(err);
        }

        else {
            std::cout << "Record added successfully" << std::endl;
        }
        return 0;
    }
};

class Model {

private:
public:

    typedef boost::shared_ptr<Model> model_ptr;

    virtual void add(const std::string&) = 0;
    virtual void remove(const std::string&) = 0;
    virtual void map_insert(const std::string& room_name, Room::room_ptr room) = 0;
    virtual bool exists(const std::string& room_name) = 0;
    virtual Room::room_ptr get_room(const std::string&) = 0;
};