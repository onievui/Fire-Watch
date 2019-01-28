#include "EnemyManager.h"
#include "MessageManager.h"
#include "ErrorMessage.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyManager::EnemyManager() 
	: enemies() {
	initialize();
}

/// <summary>
/// ����������
/// </summary>
void EnemyManager::initialize() {
	enemies.clear();
	enemies.shrink_to_fit();

	//�e�X�g�R�[�h
	//enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_1, Vector2(500, 500)));
	//enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_2, Vector2(1300, 400)));
	//enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_3, Vector2(800, 1500)));
}

/// <summary>
/// �X�V����
/// </summary>
void EnemyManager::update() {
	for (const auto& enemy : enemies) {
		enemy->update();
	}
	spawnEnemy();
	destroyEnemy();
}

/// <summary>
/// �`�揈��
/// </summary>
void EnemyManager::draw() {
	for (const auto& enemy : enemies) {
		enemy->draw();
	}
}

/// <summary>
/// ���b�Z�[�W�̎󂯎��
/// </summary>
/// <param name="_type">���b�Z�[�W�^�C�v</param>
/// <param name="_out">�o��</param>
/// <param name="_in">����</param>
/// <returns>
/// �L���ȃ��b�Z�[�W���󂯎�������ǂ���
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
/// �G�̏o��
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
			ErrorMessage("�G�̏o���ŕs���Ȓl���n����܂���");
			break;
		}
	}

	++spawnCount;
}

/// <summary>
/// �G�̍폜
/// </summary>
void EnemyManager::destroyEnemy() {
	for (auto it = enemies.begin(); it != enemies.end();) {
		//���g�p�Ȃ�폜����
		if (it->get()->isDestroy()) {
			it = enemies.erase(it);
			continue;
		}
		++it;
	}
}

