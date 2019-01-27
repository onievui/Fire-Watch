#include "FieldObject.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos">座標</param>
/// <param name="_collider">コライダー</param>
/// <param name="_is_passable">通過可能か</param>
/// <param name="_texture">テクスチャ</param>
FieldObject::FieldObject(const Vector2& _pos, const RectCollider& _collider, const bool _is_passable, const std::shared_ptr<TextureResource>& _texture) 
	: pos(_pos)
	, vel()
	, collider(_collider)
	, isPassableFlag(_is_passable)
	, texture(_texture)
	, textureIndex()
	, animeCount() {
}

/// <summary>
/// 通過可能かどうか
/// </summary>
/// <returns>
/// 通過可能かどうか
/// </returns>
bool FieldObject::isPassabe() const {
	return isPassableFlag;
}

/// <summary>
/// コライダー取得
/// </summary>
/// <returns>
/// コライダー
/// </returns>
RectCollider* FieldObject::getCollider() {
	return &collider;
}

/// <summary>
/// 座標のポインタの取得
/// </summary>
/// <returns>
/// 座標のポインタ
/// </returns>
Vector2* FieldObject::getPosPtr() {
	return &pos;
}
