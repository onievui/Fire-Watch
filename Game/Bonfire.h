#pragma once
#include "FieldObject.h"


/// <summary>
/// •°‚«–ØƒNƒ‰ƒX
/// </summary>
class Bonfire: public FieldObject {
private:
	int lifeTime;
	float power;
	bool isFireFlag;

public:
	Bonfire(const Vector2& _pos, const int _life_time, const bool _is_fire_flag);

public:
	void initialize() override;
	void update() override;
	void draw() override;
	void clickEvent() override;

private:
	void animate();

public:
	void setFire(const bool _is_fire_flag);
	bool isFire() const;

};

