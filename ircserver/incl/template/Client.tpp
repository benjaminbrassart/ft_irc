#include "Server.hpp"
#include <iomanip>
#include <sstream>

class Server;

template< Reply code >
void Client::__replyRaw(std::string const& message)
{
	std::stringstream ss;
	std::string const nick = (this->nickname.empty() ? "(null)" : this->nickname);

	ss
		<< std::setfill('0') << std::setw(3) << code << " "
		<< this->nickname << " "
		<< std::setfill(' ') << std::setw(0) << message
		<< "\r\n";
	this->writeBuffer += ss.str();
	this->__log(DEBUG, "Replied with " + ReplyFactory<code>::NAME + ": '" + message + "'");
}

template< Reply code >
void Client::reply()
{
	this->__replyRaw<code>(ReplyFactory<code>::makeReply());
}

template< Reply code >
void Client::reply(std::string const& param)
{
	this->__replyRaw<code>(ReplyFactory<code>::makeReply(param));
}

template< Reply code >
void Client::reply(std::string const& param1, std::string const& param2)
{
	this->__replyRaw<code>(ReplyFactory<code>::makeReply(param1, param2));
}

template< Reply code >
void Client::reply(std::string const& param1, std::string const& param2, std::string const& param3)
{
	this->__replyRaw<code>(ReplyFactory<code>::makeReply(param1, param2, param3));
}
