#pragma once
#include "Character.h"
#include "MessageInterface.h"
#include "FlashLight.h"
#include "Crossbow.h"



/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public Character, public MessageInterface {
private:
	static constexpr float MOVE_SPEED = 4.0f;	//プレイヤーの移動速度

private:
	FlashLight flashLight;
	Crossbow   crossbow;

public:
	Player();

public:
	bool getMessage(const MessageType _type, void* _out, void* _in) override;

public:
	void initialize() override;
	void update() override;
	void draw() override;
	void drawFlashLight();

public:
	bool attack(const Vector2* _mouse_pos);
	void hitEnemy();

private:
	void animate() override;
	void move();
	void controllFlashLight();
};













