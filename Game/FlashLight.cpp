#include "FlashLight.h"
#include "ResourceManager.h"
#include "RenderManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
FlashLight::FlashLight() 
	: battery() 
	, isLighting() 
	, texture(ResourceManager::getIns()->getTexture(TextureID::TEXTURE_FLASHLIGHT)->getResource()) {
	initialize();
}

/// <summary>
/// 初期化処理
/// </summary>
void FlashLight::initialize() {
	battery = MAX_BATTERY;
	isLighting = false;
}

/// <summary>
/// 更新処理
/// </summary>
void FlashLight::update() {
	if (isLighting && battery > 0.0f) {
		battery -= BATTERY_DRAIN_SPEED;
		if (battery <= 0.0f) {
			isLighting = false;
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="_pos">フラッシュライトの座標</param>
/// <param name="_angle">フラッシュライトの角度</param>
void FlashLight::draw(const Vector2& _pos, const float _angle) {
	//オフなら描画しない
	if (!isLighting) {
		return;
	}
	RenderManager* render_manager = RenderManager::getIns();
	render_manager->changeScreen(ScreenType::LightAlphaScreen);

	float light_power = 1.0f - (1.0f - battery / 100.0f)*(1.0f - battery / 100.0f);
	Vector2 draw_pos = _pos + Vector2::createWithAngleNorm(_angle, 172 + 10);

	SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(255*light_power));
	render_manager->drawRotaGraphF(draw_pos.x, draw_pos.y, 1.5f, _angle, texture, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	render_manager->changeScreen(ScreenType::MapScreen);
}

/// <summary>
/// オンオフの切り替え
/// </summary>
void FlashLight::switchLight() {
	if (battery <= 0.0f) {
		isLighting = false;
		return;
	}
	isLighting = !isLighting;
}

/// <summary>
/// バッテリーの追加
/// </summary>
/// <param name="_add_battery">追加するバッテリー量</param>
void FlashLight::addBattery(const float _add_battery) {
	battery += _add_battery;
	if (battery > MAX_BATTERY) {
		battery = MAX_BATTERY;
	}
}
