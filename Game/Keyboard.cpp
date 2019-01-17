#include "Keyboard.h"



/// <summary>
/// コンストラクタ
/// </summary>
Keyboard::Keyboard() {
	reset();
}

/// <summary>
/// キー受付の更新
/// </summary>
/// <returns>
///  true：正常終了
///  false：異常終了
/// </returns>
bool Keyboard::update() {
	char getAllKeyState[KEY_MAX];
	GetHitKeyStateAll(getAllKeyState);

	for (int i = 0; i < KEY_MAX; ++i) {
		if (getAllKeyState[i] == 1) {
			if (keyStatePress[i] < 0) {
				keyStatePress[i] = 0;
			}
			++keyStatePress[i];
		}
		else {
			if (keyStatePress[i] > 0) {
				keyStatePress[i] = 0;
			}
			--keyStatePress[i];
		}
	}
	return true;
}

/// <summary>
/// キー入力状態の初期化
/// </summary>
void Keyboard::reset() {
	keyStatePress.fill(0);
}

/// <summary>
/// 特定キーの入力状態を返す
/// </summary>
/// <param name="_handle">特定キーのハンドル</param>
/// <returns>
/// 特定キーの入力状態
/// </returns>
int Keyboard::state(const unsigned char _handle) const {
	return keyStatePress[_handle];
}

/// <summary>
/// 特定キーの押されている時間を返す
/// </summary>
/// <param name="_handle">特定キーのハンドル</param>
/// <returns>
/// 特定キーの入力フレーム数
/// </returns>
int Keyboard::statePress(const unsigned char _handle) const {
	return keyStatePress[_handle] > 0 ? keyStatePress[_handle] : 0;
}

/// <summary>
/// 特定キーの押されていない時間を返す
/// </summary>
/// <param name="_handle">特定キーのハンドル</param>
/// <returns>
/// 特定キーが入力されていないフレーム数
/// </returns>
int Keyboard::stateRelease(const unsigned char _handle) const {
	return keyStatePress[_handle] < 0 ? -keyStatePress[_handle] : 0;
}

/// <summary>
/// 特定のキーを押していない状態から押したかどうかを返す
/// </summary>
/// <param name="_handle">特定キーのハンドル</param>
/// <returns>
/// true：押した直後 false：押した直後でない
/// </returns>
bool Keyboard::isDown(const unsigned char _handle) const {
	return keyStatePress[_handle] == 1 ? true : false;
}

/// <summary>
/// 特定のキーを押されている状態から離したかどうかを返す
/// </summary>
/// <param name="_handle">特定キーのハンドル</param>
/// <returns>
/// true：離した直後 false：離した直後でない
/// </returns>
bool Keyboard::isUp(const unsigned char _handle) const {
	return keyStatePress[_handle] == -1 ? true : false;
}

/// <summary>
/// 不特定のキーを押していない状態から押したかどうかを返す
/// </summary>
/// <returns>
/// true：押した直後 false：押した直後でない
/// </returns>
bool Keyboard::isDownAny() const {
	for (auto &key_state : keyStatePress) {
		if (key_state == 1) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// 2つの特定キーの後から押されているほうを判別する
/// </summary>
/// <param name="_handle1">特定キー1のハンドル</param>
/// <param name="_handle2">特定キー2のハンドル</param>
/// <returns>
/// later 0:どちらも押されていない 1:第１引数 2:第２引数
/// </returns>
int Keyboard::statePressLater(const unsigned char _handle1, const unsigned char _handle2) const {
	//デフォルトは何も押されていない状態
	int later = 0;

	//各キーの入力状態
	int key_state1, key_state2;

	key_state1 = statePress(_handle1);
	key_state2 = statePress(_handle2);

	if (key_state1 > 0) {	//一番目が押されていたら
		if (key_state2 > 0 && key_state2 < key_state1) {		//二番目が後に押されていたら
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (key_state2 > 0) {	//二番目が押されていたら
		later = 2;
	}

	return later;
}

/// <summary>
/// 4つの特定キーの後から押されているほうを判別する
/// </summary>
/// <param name="_handle1">特定キー1のハンドル</param>
/// <param name="_handle2">特定キー2のハンドル</param>
/// <param name="_handle3">特定キー3のハンドル</param>
/// <param name="_handle4">特定キー4のハンドル</param>
/// <returns>
/// later 0:いずれも押されていない 1:第１引数 2:第２引数 3:第３引数 4:第４引数
/// </returns>
int Keyboard::statePressLater4(const unsigned char _handle1, const unsigned char _handle2, const unsigned char _handle3, const unsigned char _handle4) const {
	//デフォルトは何も押されていない状態
	int later = 0;

	//ボタンが押された時間
	int shortest = 999999;

	//各キーの入力状態
	int key_state[4];

	key_state[0] = statePress(_handle1);
	key_state[1] = statePress(_handle2);
	key_state[2] = statePress(_handle3);
	key_state[3] = statePress(_handle4);

	for (int i = 0; i < 4; i++) {
		if (key_state[i] && key_state[i] < shortest) {
			later = i + 1;
			shortest = key_state[i];
		}
	}
	return later;
}

