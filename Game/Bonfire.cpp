#include "Bonfire.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include <algorithm>
#include <functional>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos"></param>
/// <param name="_life_time"></param>
/// <param name="_is_fire_flag"></param>
Bonfire::Bonfire(const Vector2& _pos, const int _life_time, const bool _is_fire_flag)
	: FieldObject(_pos, RectCollider(&pos, { 0,0 }, &vel, 48, 48), false, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_FIRE))
	, lifeTime(_life_time)
	, power()
	, isFireFlag(_is_fire_flag) {
	initialize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Bonfire::initialize() {
	power = 60;
}

/// <summary>
/// 更新処理
/// </summary>
void Bonfire::update() {
	if (isFireFlag) {
		lifeTime -= 5;
		power = (std::min)(lifeTime, 1800) / 1800.0f * 0.8f + 0.2f;
		if (lifeTime <= 0) {
			isFireFlag = false;
		}
	}
	animate();
}

/// <summary>
/// 描画処理
/// </summary>
void Bonfire::draw() {
	RenderManager* render_manager = RenderManager::getIns();
	//画像の描画
	render_manager->drawRotaGraphF(pos.x, pos.y, 1.5f, 0.0f, texture->getResource(textureIndex), true);
	//ライトの描画
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	if (isFireFlag) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		render_manager->drawRotaGraphF(pos.x, pos.y, 4.5f * power, 0.0f, ResourceManager::getIns()->getTexture(TextureID::TEXTURE_LIGHT1)->getResource(), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	render_manager->drawCircleAA(pos.x, pos.y, 24, 24, ColorCode::COLOR_WHITE);
	render_manager->changeScreen(ScreenType::MapScreen);
}

/// <summary>
/// クリックイベント
/// </summary>
void Bonfire::clickEvent() {
}

/// <summary>
/// アニメーション処理
/// </summary>
void Bonfire::animate() {
	if (isFireFlag) {
		++animeCount;
		textureIndex = (animeCount / 10) % 3;
	}
	else {
		animeCount = 0;
		textureIndex = 3;
	}
}

/// <summary>
/// 火の点火状態を設定する
/// </summary>
/// <param name="_is_fire_flag">火の点火状態</param>
void Bonfire::setFire(const bool _is_fire_flag) {
	isFireFlag = _is_fire_flag;
}

/// <summary>
/// 点火中かどうか
/// </summary>
/// <returns>
/// 点火中かどうか
/// </returns>
bool Bonfire::isFire() const {
	return isFireFlag;
}
