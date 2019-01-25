#pragma once

class Vector2;

/// <summary>
/// •ŠíƒNƒ‰ƒX
/// </summary>
class Weapon {
public:
	virtual void update() = 0;
	virtual void draw() = 0;

public:
	virtual void attack(const Vector2& _pos, const float _angle) = 0;
};

