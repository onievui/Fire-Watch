#include "EnemyManager.h"


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
	enemies.emplace_back(EnemyFactory::createEnemy(EnemyID::ENEMY_1, Vector2(500, 500)));
}

/// <summary>
/// �X�V����
/// </summary>
void EnemyManager::update() {
	for (const auto& enemy : enemies) {
		enemy->update();
	}
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
	return false;
}