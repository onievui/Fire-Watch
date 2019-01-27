#include "Enemy.h"
#include "EnemyAI.h"
#include "MessageManager.h"


/// <summary>
/// ����������
/// </summary>
/// <param name="_enemy">�G�I�u�W�F�N�g�ւ̃|�C���^</param>
void EnemyAI::initialize(Enemy* _enemy) {
	pos = &_enemy->pos;
	vel = &_enemy->vel;
	targetPos = nullptr;
}

/// <summary>
/// ����������
/// </summary>
/// <param name="_enemy">�G�I�u�W�F�N�g�ւ̃|�C���^</param>
void EnemyAIPlayerChase::initialize(Enemy* _enemy) {
	this->EnemyAI::initialize(_enemy);
	targetPos = MessageManager::getIns()->sendMessage<Vector2*>(MessageType::GET_PLAYER_POS_PTR);
}

/// <summary>
/// �X�V����
/// </summary>
void EnemyAIPlayerChase::update() {
	*vel = Vector2::createWithAngleNorm(Vector2::atan2fbyVec2(*pos, *targetPos), 0.5f);
}


/// <summary>
/// ����������
/// </summary>
/// <param name="_enemy">�G�I�u�W�F�N�g�ւ̃|�C���^</param>
void EnemyAIRandomTargetChase::initialize(Enemy * _enemy) {
	this->EnemyAI::initialize(_enemy);
}

/// <summary>
/// �X�V����
/// </summary>
void EnemyAIRandomTargetChase::update() {
}

