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

    static std::string remove_delimiter(std::string str) {
        str[strlen(str.c_str()) - 1] = '\0';
        std::string s = str;
        return s;
    }

};

#endif