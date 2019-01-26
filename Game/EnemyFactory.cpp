#include "EnemyFactory.h"
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
	switch (_id) {
	case EnemyID::ENEMY_1:
		return std::make_unique<Enemy>(_pos, Vector2{ 0,0 }, Vector2{ 48,64 }, resource_manager->getTexture(TextureID::TEXTURE_ENEMY1), 2);
	default:
		ErrorMessage("敵の生成で不正なIDが渡されました");
		return nullptr;
	}
}
