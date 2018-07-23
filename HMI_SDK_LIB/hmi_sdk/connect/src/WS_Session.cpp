/**
* @file			WS_Session
* @brief		hmi与sdl底层通信层，使用websocket方式进行数据交互，发送和接收原始数据
* @author		zenghuan
* @date			2018-7-19
* @version		A001
* @copyright	ford
*/

#include "WS_Session.h"

void fail_print(boost::system::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void CWebsocketSession::run(const char *host, const char *port)
{
    // Save these for later
    host_ = host;
    // Look up the domain name
    resolver_.async_resolve(
        host,
        port,
        std::bind(
            &CWebsocketSession::on_resolve,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}

void CWebsocketSession::on_resolve(boost::system::error_code ec, tcp::resolver::results_type results)
{
    if(ec)
        return fail_print(ec, "resolve");

    // Make the connection on the IP address we get from a lookup
    boost::asio::async_connect(
        ws_.next_layer(),
        results.begin(),
        results.end(),
        std::bind(
            &CWebsocketSession::on_connect,
            shared_from_this(),
            std::placeholders::_1));
}

void CWebsocketSession::on_connect(boost::system::error_code ec)
{
    if(ec)
        return fail_print(ec, "connect");

    // Perform the websocket handshake
    ws_.async_handshake(host_, "/",
        std::bind(
            &CWebsocketSession::on_handshake,
            shared_from_this(),
            std::placeholders::_1));
}

void CWebsocketSession::on_handshake(boost::system::error_code ec)
{
    if(ec)
        return fail_print(ec, "handshake");
    waitRecv();
}

void CWebsocketSession::on_write(boost::system::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail_print(ec, "write");
}

void CWebsocketSession::on_read(boost::system::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
    {
        buffer_.consume(buffer_.size());
        return fail_print(ec, "read");
    }

    std::string data = boost::beast::buffers_to_string(buffer_.data());
    pChannle->onReceiveData((void*)(data.c_str()),strlen(data.c_str()));
    buffer_.consume(buffer_.size());
    waitRecv();
}

void CWebsocketSession::on_close(boost::system::error_code ec)
{
    if(ec)
        return fail_print(ec, "close");
}

void CWebsocketSession::ConnectChannle(IChannel *Channel)
{
    pChannle = Channel;
}

void CWebsocketSession::waitRecv()
{
    ws_.async_read(
        buffer_,
        std::bind(
            &CWebsocketSession::on_read,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}

std::size_t CWebsocketSession::SendData(std::string& data)
{
    std::size_t ret = ws_.write(boost::asio::buffer(data));
    return ret;
}

void CWebsocketSession::close()
{
    // Close the WebSocket connection
    ws_.async_close(websocket::close_code::normal,
        std::bind(
            &CWebsocketSession::on_close,
            shared_from_this(),
            std::placeholders::_1));
}
