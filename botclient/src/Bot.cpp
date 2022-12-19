/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:33 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/19 13:43:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "InputContext.hpp"
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <unistd.h>

std::string const Bot::PREFIX = "!8ball";

Bot::Bot() :
	clientFd(-1),
	readBuffer(),
	messageRegistry(),
	inputMap(),
	alive(true),
	loginState(0) {

	this->inputMap["ERROR"] = &Bot::onError;
	this->inputMap["INVITE"] = &Bot::onInvite;
	this->inputMap["PART"] = &Bot::onPart;
	this->inputMap["PRIVMSG"] = &Bot::onMessage;
}

Bot::Bot(Bot const& cpy) :
	clientFd(cpy.clientFd),
	readBuffer(cpy.readBuffer),
	messageRegistry(cpy.messageRegistry),
	inputMap(cpy.inputMap),
	alive(cpy.alive),
	loginState(cpy.loginState)
{}

Bot&	Bot::operator=(Bot const& asgn) {

	this->clientFd = asgn.clientFd;
	this->readBuffer = asgn.readBuffer;
	this->messageRegistry = asgn.messageRegistry;
	this->inputMap = asgn.inputMap;
	this->alive = asgn.alive;
	this->loginState = asgn.loginState;
	return *this;
}

Bot::~Bot() {}

Bot::IOException::IOException(std::string const& syscallName, int errnum) :
	_reason(syscallName + ": " + std::strerror(errnum)) {}

Bot::IOException::~IOException() throw() {}

char const* Bot::IOException::what() const throw()
{
	return this->_reason.c_str();
}

Bot::IOException::IOException(std::string const& syscallName, std::string const& msg) :
	_reason(syscallName + ": " + msg) {}

void	Bot::connectClient(const char* hostname, const char* port) {

	::addrinfo addr = {}; // hint
	::addrinfo *results;
	::addrinfo *record; // iterator

	addr.ai_family = AF_INET;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_protocol = IPPROTO_TCP;

	int	gai_codenbr;

	// resolve hostname:port into a list of record
	gai_codenbr = getaddrinfo(hostname, port, &addr, &results);

	// unable to resolve
	if (gai_codenbr != 0) {
		throw IOException("getaddrinfo", gai_strerror(gai_codenbr));
	}

	// loop on every record
	for (record = results; record != NULL; record = record->ai_next) {
		// attempt to create a socket with the parameters of this record
		clientFd = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
		if (clientFd == -1)
			continue ;
		// attempt to connect to the target
		if (connect(clientFd, record->ai_addr, record->ai_addrlen) != -1)
			break ;
		// the socket was created but unable to connect
		close(clientFd);
	}

	// release addrinfo resources
	freeaddrinfo(results);

	// no record was able to create or connect socket, abort
	if (record == NULL) {
		throw IOException("connect", "unable to create or connect client socket");
	}
}

void Bot::onError(InputContext& ctx)
{
	std::cerr << "Received ERROR";
	if (!ctx.args.empty())
		std::cerr << ": " << ctx.args[0];
	std::cerr << '\n';
}

void Bot::onInvite(InputContext& ctx)
{
	if (ctx.args.size() < 3)
		return;

	(void)ctx;
}

void Bot::onPart(InputContext& ctx)
{
	(void)ctx;
}

void Bot::onMessage(InputContext& ctx)
{
	std::string const& message = ctx.message;
	std::string::const_iterator prefix_it = Bot::PREFIX.begin();
	std::string::const_iterator ctx_it = message.begin();

	// check if the beginning of the message matches the prefix
	for (; prefix_it != Bot::PREFIX.end(); ++prefix_it)
	{
		if (ctx_it == message.end() || *ctx_it != *prefix_it)
			return;
		++ctx_it;
	}

	// skip spaces
	while (ctx_it != message.end() && *ctx_it != ' ')
		++ctx_it;

	if (ctx_it == message.end())
	{
		// TODO respond with rules
		return;
	}

	std::string const prefixlessMessage = std::string(ctx_it, message.end());
	std::string const target = "TODO"; // TODO parse target's nickname

	if (this->checkSimilarMessage(prefixlessMessage))
	{
		// TODO maybe print which question was asked and also by whom
		this->respond(target, "a similar question was already asked.");
		return;
	}

	std::string const answer = this->messageRegistry.getRandomMessage();

	this->respond(target, answer);
}

bool Bot::checkSimilarMessage(std::string const& message)
{
	// TODO @ShuBei33 add levenshtein's distance algorithm
	(void)message;
	return false;
}

void Bot::respond(std::string const& target, std::string const& message)
{
	// TODO format and call this->send with
	(void)target;
	(void)message;
}

void Bot::receive()
{
	char buffer[512];
	int res;

	res = ::recv(this->clientFd, buffer, sizeof (buffer), 0);

	if (res == -1)
		throw IOException("recv", errno);
	if (res == 0)
	{
		::close(this->clientFd);
		this->clientFd = -1;
		std::cout << "Connection closed by peer.\n";
		return;
	}

	// append data to read buffer
	this->readBuffer += std::string(buffer, res);

	std::string::size_type offset;
	std::string::iterator it;
	std::string line;

	do
	{
		it = this->readBuffer.begin();
		offset = this->readBuffer.find("\r\n");
		if (offset == std::string::npos)
			break;
		line = std::string(it, it + offset);
		this->readBuffer = this->readBuffer.substr(offset + 2);
		this->__processLine(line);
	} while (it != this->readBuffer.end());
}

void Bot::__processLine(std::string const& line)
{
	std::string::const_iterator it = line.begin();
	std::string::const_iterator fast;
	std::string arg;
	std::string origin;

	// process prefixes
	while (it != line.end() && *it != ':')
	{
		fast = std::find(it, line.end(), ' ');
		arg = std::string(it, fast);

		// try to find a '!', which indicates this is the origin of the message
		fast = std::find(arg.begin(), arg.end(), '!');
		if (fast != arg.end())
			origin = arg;

		it = fast;
		if (it != line.end())
			++it;
	}

	// command without prefixes
	// ':bbrassar!Benjamin@10.0.4.4 JOIN #channel' becomes 'JOIN #channel'
	std::string cmd = std::string(it, line.end());
	int reply = 0;
	int i = 0;

	it = cmd.begin();

	// parse 3 numbers and a space => response
	while (i < 3 && it != cmd.end())
	{
		if (*it < '0' || *it > '9')
			break;
		reply = reply * 10 + ('0' - *it);
		++it;
		++i;
	}

	if (i == 3 && it != cmd.end() && *it == ' ')
	{
		// no need to check bounds or whatever, value is between 0 and 999
		int code = std::atoi(cmd.c_str());

		switch (code)
		{

		}
	}
	else
	{
		// not a numeric reply
	}
}

void Bot::authenticate(std::string const& password)
{
	this->send("PASS " + password);
	this->send("NICK FlexBot");
	this->send("USER FlexBot 0 * :Flex Bot");
}

void Bot::send(std::string const& str)
{
	int res;

	res = ::send(this->clientFd, (str + "\r\n").c_str(), str.size() + 2, 0);
	if (res == -1)
		throw IOException("send", errno);
}
