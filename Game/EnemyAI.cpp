#include "Enemy.h"
#include "EnemyAI.h"
#include "MessageManager.h"


/// <summary>
/// 初期化処理
/// </summary>
/// <param name="_enemy">敵オブジェクトへのポインタ</param>
void EnemyAI::initialize(Enemy* _enemy) {
	pos = &_enemy->pos;
	vel = &_enemy->vel;
	targetPos = nullptr;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="_enemy">敵オブジェクトへのポインタ</param>
void EnemyAIPlayerChase::initialize(Enemy* _enemy) {
	this->EnemyAI::initialize(_enemy);
	targetPos = MessageManager::getIns()->sendMessage<Vector2*>(MessageType::GET_PLAYER_POS_PTR);
}

/// <summary>
/// 更新処理
/// </summary>
void EnemyAIPlayerChase::update() {
	*vel = Vector2::createWithAngleNorm(Vector2::atan2fbyVec2(*pos, *targetPos), 0.5f);
}


/// <summary>
/// 初期化処理
/// </summary>
/// <param name="_enemy">敵オブジェクトへのポインタ</param>
void EnemyAIRandomTargetChase::initialize(Enemy * _enemy) {
	this->EnemyAI::initialize(_enemy);
}

/// <summary>
/// 更新処理
/// </summary>
void EnemyAIRandomTargetChase::update() {
}

