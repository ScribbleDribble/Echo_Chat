#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <boost/asio.hpp>
#include <string>
#include <map>

using boost::asio::ip::tcp;


class Message {
private:
    std::map<std::string, int> cmd_map;
    std::string last_command;
public:

    Message() {
        cmd_map["move"] = 1;
        cmd_map["create_room"] = 1;
    }

    enum {max_body_size = 256};

    static std::string get_string_from_buf(boost::asio::streambuf& streambuf) {
        return {buffers_begin(streambuf.data()), buffers_end(streambuf.data())};
    }

    bool command_exists(const std::string& s) {
        std::string result;
        for(auto it = s.begin()+1; it != s.end(); it++) {
            if (*it == ' ') {
                break;
            }
            result += *it;
        }
        last_command = result;

        return cmd_map.count(result) == 1;
    }

    std::string get_last_command() {
        std::string result;

        if (!last_command.empty()) {
            result = last_command;
            last_command = "";

            return result;
        }
        else {
            std::cerr << "Must only use Chat_Message::get_last_command() after command_exists() is true" << std::endl;
        }

    }

    static std::string find_name(const std::string& s) {
        std::string result;
        bool build_string = false;

        for(auto it = s.begin(); it != s.end(); it++) {
            if (*it == '#' || (build_string && *it == ' ')) {
                break;
            }

            else if (*it == ' ' && !build_string) {
                build_string = true;
                continue;
            }

            else if (build_string) {
                result += *it;
            }
        }
        return result;
    }


    static std::string remove_delimiter(const std::string& s) {
        std::string result;
        for(char c : s) {
            if (c == '#') {
                break;
            }
            result += c;
        }
        return result;
    }

};

#endif