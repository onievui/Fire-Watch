#pragma once


enum class MessageType {
	GET_MAP,
	GET_MAP_CENTER_POS,
	GET_PLAYER,
	GET_PLAYER_POS,
};


class MessageInterface {
public:
	virtual bool getMessage(const MessageType _type, void** _ret) = 0;
};



