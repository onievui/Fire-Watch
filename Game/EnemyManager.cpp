#include "EnemyManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager() 
	: enemies() {
	initialize();
}

/// <summary>
/// 初期化処理
/// </summary>
void EnemyManager::initialize() {
	enemies.clear();
	enemies.shrink_to_fit();

	//テストコード
	enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_1, Vector2(500, 500)));
}

/// <summary>
/// 更新処理
/// </summary>
void EnemyManager::update() {
	for (const auto& enemy : enemies) {
		enemy->update();
	}
	destroyEnemy();
}

/// <summary>
/// 描画処理
/// </summary>
void EnemyManager::draw() {
	for (const auto& enemy : enemies) {
		enemy->draw();
	}
}

/// <summary>
/// メッセージの受け取り
/// </summary>
/// <param name="_type">メッセージタイプ</param>
/// <param name="_out">出力</param>
/// <param name="_in">入力</param>
/// <returns>
/// 有効なメッセージを受け取ったかどうか
/// </returns>
bool EnemyManager::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::GET_ENEMIES:
		*(std::vector<std::unique_ptr<Enemy>>**)_out = &enemies;
		return true;
	default:
		break;
	}
	return false;
}

/// <summary>
/// 敵の削除
/// </summary>
void EnemyManager::destroyEnemy() {
	for (auto it = enemies.begin(); it != enemies.end();) {
		//未使用なら削除する
		if (it->get()->isDestroy()) {
			it = enemies.erase(it);
			continue;
		}
		++it;
	}
}

