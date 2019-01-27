#include "EnemyFactory.h"
#include "EnemyAI.h"
#include "ErrorMessage.h"
#include "ResourceManager.h"


/// <summary>
/// �G�̐���
/// </summary>
/// <param name="_id">�GID</param>
/// <param name="_pos">�o�����W</param>
/// <returns>
/// ���� : �G�I�u�W�F�N�g
/// ���s : nullptr
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
	default:
		ErrorMessage("�G�̐����ŕs����ID���n����܂���");
		return nullptr;
	}
}
