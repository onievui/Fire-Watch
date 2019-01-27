#include "Crossbow.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MessageManager.h"
#include "ArrowManager.h"
#include "Vector2.h"
#include "ScreenInfo.h"



/// <summary>
/// コンストラクタ
/// </summary>
Crossbow::Crossbow() 
	: bullets(MAX_BULLETS)
	, wait_shot(0)
	, wait_reload(0)
	, texture(ResourceManager::getIns()->getTexture(TextureID::TEXTURE_CROSSBOW)->getResource()) {

}

/// <summary>
/// 更新処理
/// </summary>
void Crossbow::update() {
	//1回発射ごとのインターバル
	if (wait_shot > 0.0f) {
		wait_shot -= 1.0f;
		if (wait_shot <= 0.0f) {
			wait_shot = 0.0f;
		}
	}
	//リロード待ち
	if (wait_reload > 0.0f) {
		wait_reload -= 1.0f;
		if (wait_reload <= 0.0f) {
			wait_reload = 0.0f;
			bullets = MAX_BULLETS;
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Crossbow::draw() {
	DrawRotaGraphF(SCREEN_WIDTH / 10.0f, SCREEN_HEIGHT*7.5f / 8.0f, 3.5f, 0.0f, texture, true);
	DrawRotaGraphF(SCREEN_WIDTH *1.8f / 10.0f, SCREEN_HEIGHT*7.7f / 8.0f, 2.0f, 0.0f,
		ResourceManager::getIns()->getTexture(TextureID::TEXTURE_ARROW)->getResource(), true);
	if (wait_reload == 0) {
		DrawFormatStringF(SCREEN_WIDTH *1.8f / 10.0f + 30, SCREEN_HEIGHT*7.5f / 8.0f, ColorCode::COLOR_WHITE, "× %d", bullets);
	}
	else {
		DrawFormatStringF(SCREEN_WIDTH *1.8f / 10.0f + 30, SCREEN_HEIGHT*7.5f / 8.0f, ColorCode::COLOR_RED, "reloading");
	}
}

/// <summary>
/// 攻撃処理
/// </summary>
/// <param name="_pos">攻撃位置</param>
void Crossbow::attack(const Vector2& _pos, const float _angle) {
	//発射した直後、リロード中なら攻撃できない
	if (wait_shot <= 0.0f && wait_reload <= 0.0f) {
		//矢を発射
		struct AttackInfo {
			Vector2 pos;
			float angle;
		};
		AttackInfo attack_info{ _pos,_angle };
		MessageManager::getIns()->sendMessage(MessageType::CREATE_ARROW, &attack_info);
		//arrow_manager->createArrow(_pos, _angle);
		--bullets;
		wait_shot = SHOT_DELAY;
		if (bullets == 0) {
			wait_reload = RELOAD_TIME;
		}
	}
}
