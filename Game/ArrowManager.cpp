#include "ArrowManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
ArrowManager::ArrowManager()
	: arrows() {
}

/// <summary>
/// メッセージの受け取り
/// </summary>
/// <param name="_type">メッセージの種類</param>
/// <param name="_out">出力</param>
/// <param name="_in">入力</param>
/// <returns>
/// 有効なメッセージを受け取ったかどうか
/// </returns>
bool ArrowManager::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::GET_ARROW_MANAGER:
		*(ArrowManager**)_out = this;
		return true;
	case MessageType::GET_ARROWS:
		*(std::vector<std::unique_ptr<Arrow>>**)_out = &arrows;
		return true;
	default:
		break;
	}
	return false;
}

/// <summary>
/// 更新処理
/// </summary>
void ArrowManager::update() {
	for (const auto& arrow : arrows) {
		arrow->update();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ArrowManager::draw() {
	for (const auto& arrow : arrows) {
		arrow->draw();
	}
}

/// <summary>
/// 矢の生成
/// </summary>
/// <param name="_pos">出現する座標</param>
/// <param name="_angle">進行方向</param>
void ArrowManager::createArrow(const Vector2& _pos, const float _angle) {
	arrows.emplace_back(std::make_unique<Arrow>(_pos, _angle));
}
