/**
* @file			WS_Session
* @brief		hmi与sdl底层通信层，使用websocket方式进行数据交互，发送和接收原始数据
* @author		zenghuan
* @date			2018-7-19
* @version		A001
* @copyright	ford
*/

#ifndef WS_SESSION_H_
#define WS_SESSION_H_

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include "socket_manager_interface.h"


using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

class CWebsocketSession : public std::enable_shared_from_this<CWebsocketSession>
{
    tcp::resolver resolver_;
    websocket::stream<tcp::socket> ws_;
    boost::beast::multi_buffer buffer_;
    std::string host_;
    IChannel *pChannle;
public:
    explicit CWebsocketSession(boost::asio::io_context& ioc)
    : resolver_(ioc)
    , ws_(ioc)
{
}
void run(char const* host,char const* port);
void on_resolve(boost::system::error_code ec,tcp::resolver::results_type results);
void on_connect(boost::system::error_code ec);
void on_handshake(boost::system::error_code ec);
void on_write(boost::system::error_code ec,std::size_t bytes_transferred);
void on_read(boost::system::error_code ec,std::size_t bytes_transferred);
void on_close(boost::system::error_code ec);
void ConnectChannle(IChannel *Channel);
void waitRecv();
std::size_t SendData(std::string& data);
void close();
};

#endif // WS_SESSION_H_
