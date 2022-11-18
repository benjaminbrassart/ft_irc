template< Reply code >
void Client::reply() {
	this->__replyRaw(code, ReplyFactory<code>::makeReply());
}

template< Reply code >
void Client::reply(std::string const& param) {
	this->__replyRaw(code, ReplyFactory<code>::makeReply(param));
}

template< Reply code >
void Client::reply(std::string const& param1, std::string const& param2) {
	this->__replyRaw(code, ReplyFactory<code>::makeReply(param1, param2));
}

template< Reply code >
void Client::reply(std::string const& param1, std::string const& param2, std::string const& param3) {
	this->__replyRaw(code, ReplyFactory<code>::makeReply(param1, param2, param3));
}
