#pragma once
#include "Vector2.h"
#include "Collider.h"
#include <memory>


class TextureResource;


/// <summary>
/// –îƒNƒ‰ƒX
/// </summary>
class Arrow {
private:
	enum class ArrowState {
		NORMAL_ARROW,
		FIRE_ARROW,
		DESTROYED
	};

private:
	ArrowState                       state;
	Vector2                          pos;
	Vector2                          vel;
	float                            angle;
	int                              textureIndex;
	int                              animeCount;
	RectRotateCollider               collider;
	std::shared_ptr<TextureResource> texture;

public:
	Arrow(const Vector2& _pos, const float _angle);

public:
	void update();
	void draw();

public:
	RectRotateCollider* getCollider();
	int getPower();
	bool isAlive();
	bool isFire();
	void hitEnemy();
	void hitFire();


private:
	void insideAreaCheck();
};
