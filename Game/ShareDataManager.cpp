#include "ShareDataManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
ShareDataManager::ShareDataManager() {
	initialize();
}

/// <summary>
/// データの初期化
/// </summary>
void ShareDataManager::initialize() {
	score = 0;
	highscore = 0;
}

int ShareDataManager::getScore() const {
	return score;
}

void ShareDataManager::setScore(const int _score) {
	score = _score;
}

int ShareDataManager::getHighscore() const {
	return highscore;
}

void ShareDataManager::setHighscore(const int _highscore) {
	highscore = _highscore;
}
