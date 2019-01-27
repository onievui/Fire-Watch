#pragma once
#include "Singleton.h"
#include "Vector2.h"
#include <vector>
#include <array>


/// <summary>
/// 描画先スクリーンID
/// </summary>
enum ScreenType : int {
	BackScreen,
	MapScreen,
	LightAlphaScreen,
	Num
};


/// <summary>
/// 描画制御クラス
/// </summary>
class RenderManager : public Singleton<RenderManager> {

	friend Singleton<RenderManager>;

private:
	std::array<int, ScreenType::Num> screensIndex;			//スクリーンタイプとスクリーンの対応用
	std::vector<int>                 screens;				//スクリーン
	std::vector<Vector2>             offsets;				//オフセット
	ScreenType                       currentScreenType;		//現在使用中のスクリーン

public:
	RenderManager();

public:
	bool addScreen(const ScreenType _screen_type, const int _screen, const Vector2& _offset);
	bool changeScreen(const ScreenType _screen_type);
	void flipScreen();
	int getScreen(const ScreenType _screen_type);
	bool setScreenOffset(const ScreenType _screen_type, const Vector2& _offset);
	Vector2 getScreenOffset(const ScreenType _screen_type);
	void clearScreen(const ScreenType _screen_type);
	bool deleteScreen(const ScreenType _screen_type);

private:
	bool canUseScreenType(const ScreenType _screen_type);

public:
	void drawCircleAA(const float _x, const float _y, const float _r, const int _pos_num, const unsigned int _color, const int _fill_flag = 1, const float _thickness = 1.0f);
	void drawExtendGraphF(const float _x1, const float _y1, const float _x2, const float _y2, const int _handle, const int _trans_flag) const;
	void drawRotaGraphF(const float _x, const float _y, const float _exrate, const float _angle, int _handle, const int _trans_flag, const int _reverse_x_flag = 0, const int _reverse_y_flag = 0) const;
	void drawRotaGraph(const float _x, const float _y, const float _exrate, const float _angle, int _handle, const int _trans_flag, const int _reverse_x_flag = 0, const int _reverse_y_flag = 0) const;
};







