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
	map = nullptr;
	killCount = -1;
	liveTime = -1;
}

/// <summary>
/// マップの保存
/// </summary>
/// <param name="_map">マップオブジェクト</param>
void ShareDataManager::setMap(std::unique_ptr<Map>&& _map) {
	map = std::move(_map);
}

/// <summary>
/// マップの取得
/// </summary>
/// <returns></returns>
std::unique_ptr<Map> ShareDataManager::getMap() {
	return std::move(map);
}

/// <summary>
/// プレイデータの保存
/// </summary>
/// <param name="_kill_count">キル数</param>
/// <param name="_live_time">生存時間</param>
void ShareDataManager::setPlayData(const int _kill_count, const int _live_time) {
	killCount = _kill_count;
	liveTime = _live_time;
}

int ShareDataManager::getKillCount() {
	return killCount;
}

int ShareDataManager::getLiveTime() {
	return liveTime;
}
