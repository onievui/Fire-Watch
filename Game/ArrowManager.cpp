#include "ArrowManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
ArrowManager::ArrowManager()
	: arrows() {
	initialize();
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
	case MessageType::CREATE_ARROW:
		struct AttackInfo {
			Vector2 pos;
			float angle;
		};
		createArrow(((AttackInfo*)_in)->pos, ((AttackInfo*)_in)->angle);
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
/// 初期化処理
/// </summary>
void ArrowManager::initialize() {
	arrows.clear();
	arrows.shrink_to_fit();
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

/// <summary>
/// 矢の削除
/// </summary>
void ArrowManager::destroyArrow() {
	for (auto it = arrows.begin(); it != arrows.end();) {
		//未使用なら削除する
		if (!it->get()->isAlive()) {
			it = arrows.erase(it);
			continue;
		}
		++it;
	}
}
