#pragma once


/// <summary>
/// メッセージタイプ
/// </summary>
enum class MessageType {
	GET_MAP,
	GET_MAP_CENTER_GRID,
	GET_MAP_CENTER_POS,
	GRID_TO_POS,
	GET_PLAYER,
	GET_PLAYER_POS,
	GET_PLAYER_POS_PTR,
	PLAYER_ATTACK,
	GET_FIELDOBJECTS,
	CLICK_FIELDOBJECTS,
	CREATE_ARROW,
	GET_ARROWS,
};


/// <summary>
/// メッセージ受信インターフェイス
/// </summary>
class MessageInterface {
public:
	virtual bool getMessage(const MessageType _type, void* _out, void* _in) = 0;
};



