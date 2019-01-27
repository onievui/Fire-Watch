#pragma once
#include "Singleton.h"
#include "Map.h"
#include <memory>



/// <summary>
/// シーン間のデータ共有用クラス
/// </summary>
class ShareDataManager : public Singleton<ShareDataManager> {

	friend Singleton<ShareDataManager>;

private:
	std::unique_ptr<Map> map;
	int killCount;
	int liveTime;

private:
	ShareDataManager();
	~ShareDataManager() = default;

public:
	void initialize();	//初期化

public:
	void setMap(std::unique_ptr<Map>&& _map);
	std::unique_ptr<Map> getMap();
	void setPlayData(const int _kill_count, const int _live_time);
	int getKillCount();
	int getLiveTime();
};







