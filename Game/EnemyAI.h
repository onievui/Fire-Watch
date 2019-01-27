#pragma once


class Enemy;
class Vector2;



/// <summary>
/// �GAI���ۃN���X
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
/// �v���C���[���i�ǐ�AI
/// </summary>
class EnemyAIPlayerChase : public EnemyAI {
public:
	void initialize(Enemy* _enemy) override;
	void update() override;
};

/// <summary>
/// �����_���^�[�Q�b�g���i�ǐ�AI
/// </summary>
class EnemyAIRandomTargetChase : public EnemyAI {
public:
	void initialize(Enemy* _enemy) override;
	void update() override;
};

