#pragma once
#include "Character.h"
#include "EnemyAI.h"



class Enemy : public Character {
	friend EnemyAI;
private:
	bool                      isDestroyFlag;
	bool                      isFire;
	int                       hp;
	int		                  textureAreaIndex;
	std::unique_ptr<EnemyAI>  myAI;

public:
	Enemy(std::unique_ptr<EnemyAI>&& _AI, const int _hp, const Vector2& _pos,const Vector2& _collider_offset, const Vector2& _collider_size,
		const std::shared_ptr<TextureResource>& _texture, const int _texture_area_index);

public:
	void initialize() override;
	void update() override;
	void draw() override;

private:
	void animate();

public:
	void hitArrow(const int _damage, const bool _isFireArrow);
	bool isDestroy();
};