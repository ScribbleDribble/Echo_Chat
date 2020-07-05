#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;


class Message {
private:
public:

    enum {max_body_size = 256};

    static std::string get_string_from_buf(boost::asio::streambuf& streambuf) {
        return {buffers_begin(streambuf.data()), buffers_end(streambuf.data())};
    }

    static std::string find_name(std::string s) {
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