#pragma once
#include "Vector2.h"


/// <summary>
/// フラッシュライトクラス
/// </summary>
class FlashLight {
public:
	static constexpr float MAX_BATTERY         = 100.0f;
	static constexpr float BATTERY_DRAIN_SPEED = MAX_BATTERY / (60.0f * 90.0f);

private:
	float battery;
	bool  isLighting;
	HGRP  texture;

public:
	FlashLight();
	~FlashLight() = default;

public:
	void initialize();
	void update();
	void draw(const Vector2& _pos, const float _angle);

public:
	void switchLight();
	void addBattery(const float _add_battery);
};


