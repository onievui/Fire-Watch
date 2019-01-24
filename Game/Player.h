#pragma once
#include "Character.h"
#include "MessageInterface.h"
#include "FlashLight.h"



class Player : public Character, public MessageInterface {
private:
	static constexpr float MOVE_SPEED = 4.0f;	//プレイヤーの移動速度

private:
	FlashLight flashLight;

public:
	Player();

public:
	virtual bool getMessage(const MessageType _type, void* _out, void* _in);

public:
	void initialize() override;
	void update() override;
	void draw() override;
	void drawFlashLight();

private:
	void animate() override;
	void move();
	void controllFlashLight();
};













