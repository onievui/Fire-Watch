#pragma once
#include "Arrow.h"
#include "MessageInterface.h"
#include <memory>
#include <vector>


class ArrowManager : public MessageInterface {
private:
	std::vector<std::unique_ptr<Arrow>> arrows;

public:
	ArrowManager();

public:
	bool getMessage(const MessageType _type, void* _out, void* _in) override;

public:
	void initialize();
	void update();
	void draw();

public:
	void createArrow(const Vector2& _pos, const float _angle);
	void destroyArrow();

};


