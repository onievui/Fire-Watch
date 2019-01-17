#pragma once
#include "Singleton.h"
#include "Vector2.h"
#include <vector>
#include <array>


enum ScreenType : int {
	BackScreen,
	MapScreen,
	LightAlphaScreen,
	Num
};


class RenderManager : public Singleton<RenderManager> {

	friend Singleton<RenderManager>;

private:
	std::array<int, ScreenType::Num> screensIndex;	//�X�N���[���^�C�v�ƃX�N���[���̑Ή��p
	std::vector<int> screens;                       //�X�N���[��
	std::vector<Vector2> offsets;                   //�I�t�Z�b�g
	ScreenType currentScreenType;                              //���ݎg�p���̃X�N���[��

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
	void drawExtendGraphF(const float _x1, const float _y1, const float _x2, const float _y2, const int _handle, const int _trans_flag);
};







