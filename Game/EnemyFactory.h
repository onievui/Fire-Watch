#pragma once
#include "Enemy.h"


/// <summary>
/// “GID
/// </summary>
enum class EnemyID {
	ENEMY_1,
	ENEMY_2,
	ENEMY_3,
};



/// <summary>
/// “G¶¬ƒNƒ‰ƒX
/// </summary>
class EnemyFactory {

public:
	static std::unique_ptr<Enemy> createEnemy(const EnemyID _id, const Vector2& _pos);

};

