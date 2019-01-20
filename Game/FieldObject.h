#pragma once
#include "Vector2.h"
#include "Collider.h"
#include <memory>


class TextureResource;


class FieldObject {
protected:
	Vector2 pos;
	Vector2 vel;
	RectCollider collider;
	bool isPassableFlag;
	std::shared_ptr<TextureResource> texture;
	int textureIndex;
	int animeCount;

public:
	FieldObject(const Vector2& _pos, const RectCollider& _collider, const bool _is_passable, const std::shared_ptr<TextureResource>& _texture);

public:
	virtual void initialize() {}
	virtual void update() {}
	virtual void draw() {}
	virtual void clickEvent() {}

private:
	virtual void animate() {}

public:
	bool isPassabe() const;
	RectCollider* getCollider();
};













