#pragma once
#include "Singleton.h"


/// <summary>
/// シーン間のデータ共有用クラス
/// </summary>
class ShareDataManager : public Singleton<ShareDataManager> {

	friend Singleton<ShareDataManager>;

private:
	int score;		//今回のスコア
	int highscore;	//ハイスコア

private:
	ShareDataManager();
	~ShareDataManager() = default;

	
public:
	
	void initialize();	//初期化

	int getScore() const;
	void setScore(const int _score);
	int getHighscore() const;
	void setHighscore(const int _highscore);

};







