#pragma once
#include "Singleton.h"
#include "Vector2.h"
#include <array>


/// <summary>
/// Mouseクラス用ID
/// </summary>
enum MouseCode {
	MOUSE_LEFT     = MOUSE_INPUT_LEFT,
	MOUSE_RIGHT    = MOUSE_INPUT_RIGHT,
	MOUSE_MIDDLE   = MOUSE_INPUT_MIDDLE,
	MOUSE_BUTTON_4 = MOUSE_INPUT_4,
	MOUSE_BUTTON_5 = MOUSE_INPUT_5,
	MOUSE_BUTTON_6 = MOUSE_INPUT_6,
	MOUSE_BUTTON_7 = MOUSE_INPUT_7,
	MOUSE_BUTTON_8 = MOUSE_INPUT_8,
};

class Mouse : public Singleton<Mouse> {

	friend Singleton<Mouse>;

private:
	const static int MOUSE_INPUT_NUM = 8;
	std::array<int, MOUSE_INPUT_NUM> mouseStatePress;	//マウスの入力状態
	Vector2 mousePos;
	int wheel;


private:
	Mouse();
	~Mouse() = default;

public:
	//マウスの入力状態の更新
	void update();

	//マウスの入力状態の更新
	void reset();

	//マウス座標の取得
	Vector2 getMousePos() const;

	//マウス座標の設定
	void setMousePos(const Vector2& _pos);

	//マウスホイールの回転量の取得
	int getMouseWheelRotVol() const;

	//特定ボタンの入力状態を返す
	int state(const MouseCode _id) const;

	//特定ボタンの押されている時間を返す
	int statePress(const MouseCode _id) const;

	//特定ボタンの押されていない時間を返す
	int stateRelease(const MouseCode _id) const;

	//特定のボタンを押していない状態から押したかどうかを返す
	bool isDown(const MouseCode _id) const;

	//特定のボタンを押した状態から離したかどうかを返す
	bool isUp(const MouseCode _id) const;

	//不特定のボタンを押していない状態から押したかどうかを返す
	bool isDownAny() const;

	//2つの特定ボタンの後から押されているほうを判別する
	int statePressLater(const MouseCode _id1, const MouseCode _id2) const;

	//4つの特定ボタンの後から押されているほうを判別する
	int statePressLater4(const MouseCode _id1, const MouseCode _id2, const MouseCode _id3, const MouseCode _id4) const;

};
