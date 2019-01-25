#pragma once
#include "Weapon.h"



class Crossbow : public Weapon {
private:
	static constexpr int   MAX_BULLETS = 6;
	static constexpr float RELOAD_TIME = 300.0f;
	static constexpr float SHOT_DELAY  = 60.0f;

private:
	int   bullets;
	float wait_shot;
	float wait_reload;
	HGRP  texture;

public:
	Crossbow();

public:
	void update() override;
	void draw() override;

public:
	void attack(const Vector2& _pos, const float _angle) override;

};



