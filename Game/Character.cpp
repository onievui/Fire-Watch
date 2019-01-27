#include "Character.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos"></param>
/// <param name="_collider"></param>
/// <param name="_texture"></param>
Character::Character(const Vector2& _pos, const RectCollider& _collider, const std::shared_ptr<TextureResource>& _texture) 
	: isAliveFlag(true)
	, pos(_pos)
	, vel()
	, collider(_collider)
	, texture(_texture)
	, direction(Direction::DIRECTION_DOWN)
	, textureIndex()
	, animeCount() {
}

/// <summary>
/// コライダーの取得
/// </summary>
/// <returns>
/// コライダー
/// </returns>
RectCollider* Character::getCollider() {
	return &collider;
}

/// <summary>
/// 生きているかどうかの取得
/// </summary>
/// <returns>
/// 生きているかどうか
/// </returns>
bool Character::isAlive() {
	return isAliveFlag;
}
