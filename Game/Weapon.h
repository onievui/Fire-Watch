#pragma once



/// <summary>
/// ����N���X
/// </summary>
class Weapon {
public:
	virtual void update() = 0;
	virtual void draw() = 0;

public:
	virtual void attack() = 0;
};

