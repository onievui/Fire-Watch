#include "EnemyManager.h"
#include "MessageManager.h"
#include "ErrorMessage.h"


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
	//enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_1, Vector2(500, 500)));
	//enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_2, Vector2(1300, 400)));
	//enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_3, Vector2(800, 1500)));
}

/// <summary>
/// 更新処理
/// </summary>
void EnemyManager::update() {
	for (const auto& enemy : enemies) {
		enemy->update();
	}
	spawnEnemy();
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
/// 敵の出現
/// </summary>
void EnemyManager::spawnEnemy() {
	static int spawnCount = 0;

	if (spawnCount % 360 == 0) {
		Vector2 pos = MessageManager::getIns()->sendMessage<Vector2>(MessageType::GET_MAP_RANDOM_OUTSIDE_POS);
		switch (GetRand(4)) {
		case 0:
		case 1:
			enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_1, pos));
			break;
		case 2:
			enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_2, pos));
			break;
		case 3:
			enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_3, pos));
			break;
		case 4:
			enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_1, pos));
			enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_1, MessageManager::getIns()->sendMessage<Vector2>(MessageType::GET_MAP_RANDOM_OUTSIDE_POS)));
			break;
		default:
			ErrorMessage("敵の出現で不正な値が渡されました");
			break;
		}
	}

	++spawnCount;
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

