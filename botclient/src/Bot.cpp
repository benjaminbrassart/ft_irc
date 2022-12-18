/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:57:33 by estoffel          #+#    #+#             */
/*   Updated: 2022/12/19 00:42:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "InputContext.hpp"
#include <cstring>
#include <iostream>
#include <cerrno>
#include <unistd.h>

std::string const Bot::PREFIX = "!8ball";

Bot::Bot() :
	clientFd(-1),
	messageRegistry(),
	inputMap() {

	this->inputMap["ERROR"] = &Bot::onError;
	this->inputMap["INVITE"] = &Bot::onInvite;
	this->inputMap["PART"] = &Bot::onPart;
	this->inputMap["PRIVMSG"] = &Bot::onMessage;
}

Bot::Bot(Bot const& cpy) :
	clientFd(cpy.clientFd),
	messageRegistry(cpy.messageRegistry),
	inputMap(cpy.inputMap)
{}

Bot&	Bot::operator=(Bot const& asgn) {

	this->clientFd = asgn.clientFd;
	this->messageRegistry = asgn.messageRegistry;
	this->inputMap = asgn.inputMap;
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

	::addrinfo addr = {};
	::addrinfo *results;
	::addrinfo *record;
	addr.ai_family = AF_INET;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_protocol = IPPROTO_TCP;

	int	gai_codenbr;

	gai_codenbr = getaddrinfo(hostname, port, &addr, &results);
	if ( gai_codenbr != 0) {
		throw IOException("getaddrinfo", gai_strerror(gai_codenbr));
	}
	for (record = results; record != NULL; record = record->ai_next) {
		clientFd = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
		if (clientFd == -1)
			continue ;
		if (connect(clientFd, record->ai_addr, record->ai_addrlen) != -1)
			break ;
		close(clientFd);
	}
	freeaddrinfo(results);
	if (record == NULL) {
		throw IOException("connect", "unable to create or connect client socket");
	}
}

void Bot::onError(InputContext& ctx)
{
	std::cerr << "Received error";
	if (!ctx.args.empty())
		std::cerr << ": " << ctx.args[0];
	std::cerr << '\n';
	(void)ctx;
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
