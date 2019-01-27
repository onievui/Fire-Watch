#pragma once


class Enemy;
class Vector2;



/// <summary>
/// 敵AI抽象クラス
/// </summary>
class EnemyAI {
protected:
	Vector2* pos;
	Vector2* vel;
	Vector2* targetPos;

public:
	virtual void initialize(Enemy* _enemy);
	virtual void update() = 0;
};


/// <summary>
/// プレイヤー直進追跡AI
/// </summary>
class EnemyAIPlayerChase : public EnemyAI {
public:
	void initialize(Enemy* _enemy) override;
	void update() override;
};

/// <summary>
/// ランダムターゲット直進追跡AI
/// </summary>
class EnemyAIRandomTargetChase : public EnemyAI {
public:
	void initialize(Enemy* _enemy) override;
	void update() override;
};

