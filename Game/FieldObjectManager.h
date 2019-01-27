#pragma once
#include "FieldObject.h"
#include "MessageInterface.h"
#include <vector>


/// <summary>
/// フィールドオブジェクト管理クラス
/// </summary>
class FieldObjectManager : public MessageInterface {
private:
	std::vector<std::unique_ptr<FieldObject>> fieldObjects;

public:
	FieldObjectManager();

public:
	void initialize();
	void update();
	void draw();

public:
	bool getMessage(const MessageType _type, void* _out, void* _in);

private:
	bool clickEvent(const Vector2& _click_pos);
	Vector2 getTentPos();
	Vector2* getRandomPosPtr();

};
