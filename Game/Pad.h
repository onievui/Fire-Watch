#pragma once

#include "Singleton.h"
#include <array>
#include <algorithm>


/// <summary>
/// Padクラス用ID
/// </summary>
enum PadCode {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Z,
	X,
	C,
	W,
	A,
	S,
	D,
	Q,
	E,
	SPACE,
	RETURN,
	LSHIFT,
	TAB,
};

/// <summary>
/// ジョイパッド及びキーボードの入力読み込みクラス
/// </summary>
class Pad final : public Singleton<Pad> {

	friend Singleton<Pad>;

private:
	static constexpr int PAD_KEY_NUM = 24;

private:
	std::array<int, PAD_KEY_NUM> padId;			//ボタンの割り当て
	std::array<int, PAD_KEY_NUM> padStatePress;	//パッドの入力状態

private:
	Pad();
	~Pad() = default;

	//パッドとキーボードの入力状態を合わせる
	void mergeKeyboardAll();

	//入力状態を合わせる処理
	void mergeKeyboard(const PadCode _id, const unsigned char _handle);

public:
	//パッドの入力状態の更新
	bool update();

	//パッドの入力状態の初期化
	void reset();

	//特定ボタンの入力状態を返す
	int state(const PadCode _id) const;

	//特定ボタンの押されている時間を返す
	int statePress(const PadCode _id) const;

	//特定ボタンの押されていない時間を返す
	int stateRelease(const PadCode _id) const;

	//特定のボタンを押していない状態から押したかどうかを返す
	bool isDown(const PadCode _id) const;

	//特定のボタンを押した状態から離したかどうかを返す
	bool isUp(const PadCode _id) const;

	//不特定のボタンを押していない状態から押したかどうかを返す
	bool isDownAny() const;

	//2つの特定ボタンの後から押されているほうを判別する
	int statePressLater(const PadCode _id1, const PadCode _id2) const;

	//4つの特定ボタンの後から押されているほうを判別する
	int statePressLater4(const PadCode _id1, const PadCode _id2, const PadCode _id3, const PadCode _id4) const;

};