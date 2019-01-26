#include "Enemy.h"
#include "RenderManager.h"
#include "ResourceManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos">出現座標</param>
/// <param name="_collider_offset">コライダーのオフセット</param>
/// <param name="_collider_size">コライダーのサイズ</param>
/// <param name="_texture">テクスチャ</param>
/// <param name="_texture_area_index">テクスチャ内の使用範囲インデックス</param>
Enemy::Enemy(const Vector2& _pos, const Vector2& _collider_offset, const Vector2& _collider_size,
	const std::shared_ptr<TextureResource>& _texture, const int _texture_area_index)
	: Character(_pos, RectCollider(&pos, _collider_offset, &vel, _collider_size.x, _collider_size.y), _texture)
	, textureAreaIndex(_texture_area_index)
	, targetPos() {
}

/// <summary>
/// 初期化処理
/// </summary>
void Enemy::initialize() {
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::update() {
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::draw() {
	int texture_index = textureIndex + (textureAreaIndex < 4 ? textureAreaIndex * 4 : 48 + (textureAreaIndex - 4) * 12);
	RenderManager::getIns()->drawRotaGraphF(pos.x, pos.y, 2.0f, 0.0f, texture->getResource(texture_index), true);
}
