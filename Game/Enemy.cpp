#include "Enemy.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MessageManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_AI">AIタイプ</param>
/// <param name="_hp">出現座標</param>
/// <param name="_pos">出現座標</param>
/// <param name="_collider_offset">コライダーのオフセット</param>
/// <param name="_collider_size">コライダーのサイズ</param>
/// <param name="_texture">テクスチャ</param>
/// <param name="_texture_area_index">テクスチャ内の使用範囲インデックス</param>
Enemy::Enemy(std::unique_ptr<EnemyAI>&& _AI, const int _hp, const Vector2& _pos,  const Vector2& _collider_offset, const Vector2& _collider_size,
	const std::shared_ptr<TextureResource>& _texture, const int _texture_area_index)
	: Character(_pos, RectCollider(&pos, _collider_offset, &vel, _collider_size.x, _collider_size.y), _texture)
	, myAI(std::move(_AI))
	, isDestroyFlag(false)
	, isFire(false)
	, hp(_hp)
	, textureAreaIndex(_texture_area_index) {
	initialize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Enemy::initialize() {
	myAI->initialize(this);
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::update() {
	//生きている間のみ処理
	if (isAliveFlag) {
		pos += vel;
		vel = { 0,0 };
		myAI->update();
		animate();
	}
	//死んでいる間のみ処理
	else {
		if (animeCount >= (isFire ? 120 : 60)) {
			isDestroyFlag = true;
		}
		++animeCount;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::draw() {
	int texture_index = (textureIndex % 3) + (textureIndex / 3) * 12 + (textureAreaIndex < 4 ? textureAreaIndex * 3 : 48 + (textureAreaIndex - 4) * 3);
	//死んでいる間は色を暗くする
	if (!isAliveFlag) {
		RenderManager* render_manager = RenderManager::getIns();
		int r, g, b;
		GetDrawBright(&r, &g, &b);
		float rate = animeCount / (isFire ? 120.0f : 60.0f);
		if (!isFire) {
			SetDrawBright((int)(r*(1.0f - (0.75f)*rate)), (int)(g*(1.0f - (0.9f)*rate)), (int)(b*(1.0f - (0.75f)*rate)));
		}
		else {
			SetDrawBright(r, (int)(g*(1.0f - (0.9f)*rate)), (int)(b*(1.0f - (0.9f)*rate)));
		}
		render_manager->drawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, texture->getResource(texture_index), true);
		SetDrawBright(r, g, b);
		if (isFire) {
			render_manager->changeScreen(ScreenType::LightAlphaScreen);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			render_manager->drawRotaGraphF(pos.x, pos.y, 0.8f*(1.0f-rate) + 0.4f, 0.0f,
				ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			render_manager->changeScreen(ScreenType::MapScreen);
		}
	}
	else {
		RenderManager::getIns()->drawRotaGraph(pos.x, pos.y, 1.0f, 0.0f, texture->getResource(texture_index), true);
	}
	//当たり判定確認用
	//Vector2 offset = pos + collider.offset - RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	//DrawBoxAA(offset.x - collider.width / 2, offset.y - collider.height / 2, offset.x + collider.width / 2, offset.y + collider.height / 2, ColorCode::COLOR_BLUE, 0);
}

/// <summary>
/// アニメーション処理
/// </summary>
void Enemy::animate() {
	//速度から向きを算出
	float face = Vector2::vector2ToAngle(vel) + PI / 4;

	//右向き
	if (face >= 0.0f && face < PI / 2) {
		direction = Direction::DIRECTION_RIGHT;
		textureIndex = 3;
	}
	//下向き
	else if (face >= 0.0f && face < PI) {
		direction = Direction::DIRECTION_DOWN;
		textureIndex = 6;
	}
	//上向き
	else if (face < 0.0f && face >= -PI / 2) {
		direction = Direction::DIRECTION_UP;
		textureIndex = 0;
	}
	//左向き
	else {
		direction = Direction::DIRECTION_LEFT;
		textureIndex = 9;
	}

	textureIndex += (animeCount % 45) / 15;

	//動いている間アニメーションをする
	if (FloatEqual(vel.x, 0.0f) && FloatEqual(vel.y, 0.0f)) {
		animeCount = 0;
	}
	else {
		++animeCount;
	}
}

/// <summary>
/// 矢との衝突処理
/// </summary>
/// <param name="_damage">ダメージ</param>
/// <param name="_isFireArrow">矢が燃焼状態かどうか</param>
void Enemy::hitArrow(const int _damage, const bool _isFireArrow) {
	hp -= _damage;
	if (hp <= 0) {
		animeCount = 0;
		isAliveFlag = false;
		if (_isFireArrow) {
			isFire = true;
		}
	}
	
}

bool Enemy::isDestroy() {
	return isDestroyFlag;
}
