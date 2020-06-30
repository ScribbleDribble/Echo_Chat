//
// Created by mke on 29/06/2020.
//

#ifndef CHAT_APP_CHAT_USER_H
#define CHAT_APP_CHAT_USER_H

#include <boost/asio.hpp>

class Chat_User{

private:

public:
    typedef boost::shared_ptr<Chat_User> user_ptr;

    virtual void write(std::string msg) = 0;

    virtual void start_read() = 0;

};

#endif //CHAT_APP_CHAT_USER_H
