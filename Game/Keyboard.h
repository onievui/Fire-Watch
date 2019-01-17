#pragma once

#include "Singleton.h"
#include <array>


/// <summary>
/// キー入力読み込みクラス
/// </summary>
class Keyboard final : public Singleton<Keyboard> {

	friend Singleton<Keyboard>;

private:
	const static int KEY_MAX = 256;
	std::array<int, KEY_MAX> keyStatePress;	//キーの入力状態

private:
	Keyboard();

public:
	//キー入力状態の更新
	bool update();

	//キー入力状態の初期化
	void reset();

	//特定キーの入力状態を返す
	int state(const unsigned char _handle) const;

	//特定キーの押されている時間を返す
	int statePress(const unsigned char _handle) const;

	//特定キーの押されていない時間を返す
	int stateRelease(const unsigned char _handle) const;

	//特定のキーを押していない状態から押したかどうかを返す
	bool isDown(const unsigned char _handle) const;

	//特定のキーを押した状態から離したかどうかを返す
	bool isUp(const unsigned char _handle) const;

	//不特定のキーを押していない状態から押したかどうかを返す
	bool isDownAny() const;

	//2つの特定キーの後から押されているほうを判別する
	int statePressLater(const unsigned char _handle1, const unsigned char _handle2) const;

	//4つの特定キーの後から押されているほうを判別する
	int statePressLater4(const unsigned char _handle1, const unsigned char _handle2, const unsigned char _handle3, const unsigned char _handle4) const;

};