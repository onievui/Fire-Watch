#include "Pad.h"
#include "Keyboard.h"
#include <algorithm>

using namespace std;


/// <summary>
/// パッドの初期化
/// </summary>
Pad::Pad() {
	padId[PadCode::DOWN]    = 0;
	padId[PadCode::LEFT]    = 1;
	padId[PadCode::RIGHT]   = 2;
	padId[PadCode::UP]      = 3;
	padId[PadCode::Z]       = 4;
	padId[PadCode::X]       = 5;
	padId[PadCode::C]       = 6;
	padId[PadCode::W]       = 7;
	padId[PadCode::A]       = 8;
	padId[PadCode::S]       = 9;
	padId[PadCode::D]       = 10;
	padId[PadCode::SPACE]   = 11;
	padId[PadCode::RETURN]  = 12;
	padId[PadCode::LSHIFT]  = 13;
	padId[PadCode::TAB]     = 14;

	reset();
}

/// <summary>
/// パッドの入力状態の更新
/// </summary>
/// <returns>
/// true：正常終了
/// false：異常終了
/// </returns>
bool Pad::update()
{
	int padInput;
	padInput = GetJoypadInputState(DX_INPUT_PAD1);
	for (int i = 0; i<16; i++) {
		if (padInput & (1 << i)) {
			if (padStatePress[i] < 0) {
				padStatePress[i] = 0;
			}
			++padStatePress[i];
		}
		else {
			if (padStatePress[i] > 0) {
				padStatePress[i] = 0;
			}
			--padStatePress[i];
		}
	}
	Keyboard::getIns()->update();
	mergeKeyboardAll();

	return false;
}

/// <summary>
/// パッドの入力状態の初期化
/// </summary>
void Pad::reset() {
	padStatePress.fill(0);
	Keyboard::getIns()->reset();
}

/// <summary>
/// パッドとキーボードの入力状態を合わせる
/// </summary>
void Pad::mergeKeyboardAll() {
	mergeKeyboard(PadCode::LEFT,   KEY_INPUT_LEFT);
	mergeKeyboard(PadCode::RIGHT,  KEY_INPUT_RIGHT);
	mergeKeyboard(PadCode::UP,     KEY_INPUT_UP);
	mergeKeyboard(PadCode::DOWN,   KEY_INPUT_DOWN);
	mergeKeyboard(PadCode::Z,      KEY_INPUT_Z);
	mergeKeyboard(PadCode::X,      KEY_INPUT_X);
	mergeKeyboard(PadCode::C,      KEY_INPUT_C);
	mergeKeyboard(PadCode::W,      KEY_INPUT_W);
	mergeKeyboard(PadCode::A,      KEY_INPUT_A);
	mergeKeyboard(PadCode::S,      KEY_INPUT_S);
	mergeKeyboard(PadCode::D,      KEY_INPUT_D);
	mergeKeyboard(PadCode::Q,      KEY_INPUT_Q);
	mergeKeyboard(PadCode::E,      KEY_INPUT_E);
	mergeKeyboard(PadCode::SPACE,  KEY_INPUT_SPACE);
	mergeKeyboard(PadCode::RETURN, KEY_INPUT_RETURN);
	mergeKeyboard(PadCode::LSHIFT, KEY_INPUT_LSHIFT);
	mergeKeyboard(PadCode::TAB,    KEY_INPUT_TAB);
}

/// <summary>
/// 入力状態を合わせる処理
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <param name="_handle">特定キーのハンドル</param>
void Pad::mergeKeyboard(const PadCode _id, const unsigned char _handle) {
	int pad_state = padStatePress[padId[_id]];
	int key_state = Keyboard::getIns()->state(_handle);
	padStatePress[padId[_id]] = max(pad_state, key_state);
}

/// <summary>
/// 特定ボタンの入力状態を返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// 特定ボタンの入力状態
/// </returns>
int Pad::state(const PadCode _id) const {
	return padStatePress[padId[_id]];
}

/// <summary>
/// 特定ボタンの押されている時間を返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// 特定ボタンの入力フレーム数
/// </returns>
int Pad::statePress(const PadCode _id) const {
	return padStatePress[padId[_id]] > 0 ? padStatePress[padId[_id]] : 0;
}

/// <summary>
/// 特定ボタンの押されていない時間を返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// 特定ボタンが入力されていないフレーム数
/// </returns>
int Pad::stateRelease(const PadCode _id) const {
	return padStatePress[padId[_id]] < 0 ? -padStatePress[padId[_id]] : 0;
}

/// <summary>
/// 特定のボタンを押していない状態から押したかどうかを返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// true：押した直後 false：押した直後でない
/// </returns>
bool Pad::isDown(const PadCode _id) const {
	return padStatePress[padId[_id]] == 1 ? true : false;
}

/// <summary>
/// 特定のボタンを押されている状態から離したかどうかを返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// true：離した直後 false：離した直後でない
/// </returns>
bool Pad::isUp(const PadCode _id) const {
	return padStatePress[padId[_id]] == -1 ? true : false;
}

/// <summary>
/// 不特定のボタンを押していない状態から押したかどうかを返す
/// </summary>
/// <returns>
/// true：押した直後 false：押した直後でない
/// </returns>
bool Pad::isDownAny() const {
	for (auto &pad_state : padStatePress) {
   		if (pad_state == 1) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// 2つの特定ボタンの後から押されているほうを判別する
/// </summary>
/// <param name="_id1">特定ボタン1のID</param>
/// <param name="_id2">特定ボタン2のID</param>
/// <returns>
/// later 0:どちらも押されていない 1:第１引数 2:第２引数
/// </returns>
int Pad::statePressLater(const PadCode _id1, const PadCode _id2) const {
	//デフォルトは何も押されていない状態
	int later = 0;

	//各ボタンの入力状態
	int pad_state1, pad_state2;

	pad_state1 = padStatePress[padId[_id1]];
	pad_state2 = padStatePress[padId[_id2]];

	if (pad_state1 > 0) {	//一番目が押されていたら
		if (pad_state2 > 0 && pad_state2 < pad_state1) {		//二番目が後に押されていたら
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (pad_state2 > 0) {	//二番目が押されていたら
		later = 2;
	}

	return later;
}

/// <summary>
/// 4つの特定ボタンの後から押されているほうを判別する
/// </summary>
/// <param name="_id1">特定ボタン1のID</param>
/// <param name="_id2">特定ボタン2のID</param>
/// <param name="_id3">特定ボタン3のID</param>
/// <param name="_id4">特定ボタン4のID</param>
/// <returns>
/// later 0:いずれも押されていない 1:第１引数 2:第２引数 3:第３引数 4:第４引数
/// </returns>
int Pad::statePressLater4(const PadCode _id1, const PadCode _id2, const PadCode _id3, const PadCode _id4) const {
	//デフォルトは何も押されていない状態
	int later = 0;

	//ボタンが押された時間
	int shortest = 999999;

	//各ボタンの入力状態
	int pad_state[4];

	pad_state[0] = padStatePress[padId[_id1]];
	pad_state[1] = padStatePress[padId[_id2]];
	pad_state[2] = padStatePress[padId[_id3]];
	pad_state[3] = padStatePress[padId[_id4]];

	for (int i = 0; i < 4; i++) {
		if (pad_state[i] > 0 && pad_state[i] < shortest) {
			later = i + 1;
			shortest = pad_state[i];
		}
	}
	return later;
}

