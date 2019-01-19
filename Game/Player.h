#pragma once
#include "Character.h"
#include "MessageInterface.h"


class TextureResource;



class Player : public Character, public MessageInterface {
private:
	static const float MOVE_SPEED;

private:
	int animeCount;

public:
	Player();

public:
	virtual bool getMessage(const MessageType _type, void** _ret);

public:
	void initialize() override;
	void update() override;
	void draw() override;

private:
	void move();
	void animate();
};













