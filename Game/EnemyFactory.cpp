#include "EnemyFactory.h"
#include "EnemyAI.h"
#include "ErrorMessage.h"
#include "ResourceManager.h"


/// <summary>
/// 敵の生成
/// </summary>
/// <param name="_id">敵ID</param>
/// <param name="_pos">出現座標</param>
/// <returns>
/// 成功 : 敵オブジェクト
/// 失敗 : nullptr
/// </returns>
std::unique_ptr<Enemy> EnemyFactory::createEnemy(const EnemyID _id, const Vector2& _pos) {
	ResourceManager* resource_manager = ResourceManager::getIns();
	std::unique_ptr<Enemy> enemy;
	std::unique_ptr<EnemyAI> AI;
	switch (_id) {
	case EnemyID::ENEMY_1:
		AI = std::make_unique<EnemyAIPlayerChase>();
		enemy = std::make_unique<Enemy>(std::move(AI), 2, _pos, Vector2{ 0,6 }, Vector2{ 48,42 }, resource_manager->getTexture(TextureID::TEXTURE_ENEMY1), 2);
		return enemy;
	case EnemyID::ENEMY_2:
		AI = std::make_unique<EnemyAIRandomTargetChase>();
		enemy = std::make_unique<Enemy>(std::move(AI), 2, _pos, Vector2{ 0,6 }, Vector2{ 48,42 }, resource_manager->getTexture(TextureID::TEXTURE_ENEMY1), 2);
		return enemy;
	case EnemyID::ENEMY_3:
		AI = std::make_unique<EnemyAIDashInLight>();
		enemy = std::make_unique<Enemy>(std::move(AI), 2, _pos, Vector2{ 0,6 }, Vector2{ 48,42 }, resource_manager->getTexture(TextureID::TEXTURE_ENEMY1), 2);
		return enemy;
	default:
		ErrorMessage("敵の生成で不正なIDが渡されました");
		return nullptr;
	}
}
