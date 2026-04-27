#include <boost/asio.hpp>
#include <iostream>

using boost::asio::buffer;
using boost::asio::io_context;
using boost::asio::ip::tcp;
using boost::system::error_code;

static const int buf_len = 1000;

auto main() -> int
{
    try
    {
        io_context ctx;
        tcp::acceptor ator(ctx, tcp::endpoint(tcp::v4(), 6666));
        
        while(true)
        {
            tcp::socket peer_socket(ctx);
            ator.accept(peer_socket);

            std::array<char, buf_len> buf;

            while(true)
            {
                error_code error;
                std::size_t len = peer_socket.read_some(buffer(buf), error);
                
                if (error == boost::asio::error::eof)
                    break;

                write(peer_socket, buffer(buf, len));
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception" << e.what() << '\n';
    }
}
