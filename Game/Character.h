#pragma once
#include "Vector2.h"
#include "Collider.h"
#include <memory>


class TextureResource;



enum Direction {
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP
};


class Character {
protected:
	bool                             isAlive;
	Vector2                          pos;
	Vector2                          vel;
	RectCollider                     collider;
	std::shared_ptr<TextureResource> texture;
	Direction                        direction;
	int                              textureIndex;
	int                              animeCount;

public:
	Character(const Vector2& _pos, const RectCollider& _collider, const std::shared_ptr<TextureResource>& _texture);

public:
	virtual void initialize() {}
	virtual void update() {}
	virtual void draw() {}

private:
	virtual void animate() {}

public:
	RectCollider* getCollider();
};













