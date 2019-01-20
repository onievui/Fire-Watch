#pragma once
#include "Character.h"
#include "MessageInterface.h"


class TextureResource;



class Player : public Character, public MessageInterface {
private:
	static const float MOVE_SPEED;

public:
	Player();

public:
	virtual bool getMessage(const MessageType _type, void* _out, void* _in);

public:
	void initialize() override;
	void update() override;
	void draw() override;

private:
	void animate() override;
	void move();
};













