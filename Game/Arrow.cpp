#include "Arrow.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "Map.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos">出現座標</param>
/// <param name="_angle">進行方向</param>
Arrow::Arrow(const Vector2& _pos, const float _angle)
	: state(ArrowState::NORMAL_ARROW)
	, pos(_pos)
	, vel(Vector2::createWithAngleNorm(_angle, 12))
	, angle(_angle)
	, textureIndex()
	, animeCount()
	, collider(RectRotateCollider(&pos, { 0,0 }, &vel, 36, 6, &angle))
	, texture(ResourceManager::getIns()->getTexture(TextureID::TEXTURE_ARROW)) {
	 
}

/// <summary>
/// 更新処理
/// </summary>
void Arrow::update() {
	pos += vel;
	//燃焼状態ならアニメーションを行う
	if (state == ArrowState::FIRE_ARROW) {
		++animeCount;
		textureIndex = (animeCount % 30 < 15 ? 1 : 2);
	}

	//ステージ内にいるかの判定
	insideAreaCheck();
}

/// <summary>
/// 描画処理
/// </summary>
void Arrow::draw() {
	//破壊されていなければ描画する
	if (state != ArrowState::DESTROYED) {
		RenderManager* render_manager = RenderManager::getIns();
		render_manager->drawRotaGraphF(pos.x, pos.y, 1.5f, angle + PI * 3 / 4, texture->getResource(textureIndex), true);
		//燃焼状態なら明りを出す
		if (state == ArrowState::FIRE_ARROW) {
			render_manager->changeScreen(ScreenType::LightAlphaScreen);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			render_manager->drawRotaGraphF(pos.x, pos.y, 0.8f, 0.0f, 
				ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			render_manager->changeScreen(ScreenType::MapScreen);
		}
	}
}

/// <summary>
/// コライダーの取得
/// </summary>
/// <returns>
/// コライダー
/// </returns>
RectRotateCollider* Arrow::getCollider() {
	return &collider;
}

/// <summary>
/// 攻撃力の取得
/// </summary>
/// <returns></returns>
int Arrow::getPower() {
	//通常状態なら1ダメージ
	if (state == ArrowState::NORMAL_ARROW) {
		return 1;
	}
	//燃焼状態なら1ダメージ
	else if (state == ArrowState::FIRE_ARROW) {
		return 1;
	}
	return 0;
}

/// <summary>
/// 残っているかどうかの確認
/// </summary>
/// <returns>
/// 残っているかどうか
/// </returns>
bool Arrow::isAlive() {
	return (state != ArrowState::DESTROYED ? true : false);
}

/// <summary>
/// 敵と衝突した時の処理
/// </summary>
void Arrow::hitEnemy() {
	state = ArrowState::DESTROYED;
}

/// <summary>
/// 炎と衝突した時の処理
/// </summary>
void Arrow::hitFire() {
	if (state == ArrowState::NORMAL_ARROW) {
		state = ArrowState::FIRE_ARROW;
	}
}

/// <summary>
/// ステージ内にいるかの判定
/// </summary>
void Arrow::insideAreaCheck() {
	//ステージ外なら消す
	if (pos.x < 0.0f || pos.x > Map::GRID_COLS*Map::DEFAULT_GRID_SIZE ||
		pos.y < 0.0f || pos.y > Map::GRID_ROWS*Map::DEFAULT_GRID_SIZE) {
		state = ArrowState::DESTROYED;
	}
}
