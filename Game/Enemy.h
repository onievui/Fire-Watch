#pragma once
#include "Character.h"




class Enemy : public Character {
private:
	int      textureAreaIndex;
	Vector2* targetPos;

public:
	Enemy(const Vector2& _pos, const Vector2& _collider_offset, const Vector2& _collider_size, 
		const std::shared_ptr<TextureResource>& _texture, const int _texture_area_index);

public:
	void initialize() override;
	void update() override;
	void draw() override;


};