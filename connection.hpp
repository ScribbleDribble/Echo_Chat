#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;


class Connection : public boost::enable_shared_from_this<Connection> {


private:
    tcp::socket socket;

    Connection(boost::asio::io_context& io_context): socket(io_context){};

public:
    typedef boost::shared_ptr<Connection> conn_ptr;

    static conn_ptr create_connection(boost::asio::io_context& io_context) {
        return conn_ptr(new Connection(io_context));
    }

    conn_ptr get_shared() {
        return shared_from_this();
    }

    tcp::socket& get_socket() {
        return socket;
    }



};