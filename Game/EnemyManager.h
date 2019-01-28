#pragma once
#include "EnemyFactory.h"
#include "MessageInterface.h"
#include <vector>


/// <summary>
/// “GŠÇ—ƒNƒ‰ƒX
/// </summary>
class EnemyManager : public MessageInterface {
private:
	std::vector<std::unique_ptr<Enemy>> enemies;

public:
	EnemyManager();

public:
	void initialize();
	void update();
	void draw();

public:
	bool getMessage(const MessageType _type, void* _out, void* _in);

private:
	void spawnEnemy();
	void destroyEnemy();
};


