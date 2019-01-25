#include "Crossbow.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MessageManager.h"
#include "ArrowManager.h"
#include "Vector2.h"


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

}

/// <summary>
/// 攻撃処理
/// </summary>
/// <param name="_pos">攻撃位置</param>
void Crossbow::attack(const Vector2& _pos, const float _angle) {
	//発射した直後、リロード中なら攻撃できない
	if (wait_shot <= 0.0f && wait_reload <= 0.0f) {
		//矢を発射
		ArrowManager* arrow_manager = MessageManager::getIns()->sendMessage<ArrowManager*>(MessageType::GET_ARROW_MANAGER);
		arrow_manager->createArrow(_pos, _angle);
		--bullets;
		wait_shot = SHOT_DELAY;
		if (bullets == 0) {
			wait_reload = RELOAD_TIME;
		}
	}
}
