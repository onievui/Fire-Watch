#include "Mouse.h"



/// <summary>
/// コンストラクタ
/// </summary>
Mouse::Mouse() {
	reset();
}



/// <summary>
/// マウスの入力状態の更新
/// </summary>
void Mouse::update() {
	int x, y, mouseInput, getWheel;

	//マウスの入力状態の取得
	mouseInput = GetMouseInput();
	//ホイールの入力状態の取得
	getWheel = GetMouseWheelRotVol();
	//マウス座標の取得
	GetMousePoint(&x, &y);
	//入力状態の更新
	for (int i = 0; i < MOUSE_INPUT_NUM; ++i) {
		if (mouseInput & MouseCode(i)) {
			if (mouseStatePress[i] < 0) {
				mouseStatePress[i] = 0;
			}
			++mouseStatePress[i];
		}
		else {
			if (mouseStatePress[i] > 0) {
				mouseStatePress[i] = 0;
			}
			--mouseStatePress[i];
		}
	}
	//マウス座標の更新
	mousePos = Vector2((float)x, (float)y);
}

/// <summary>
/// マウスの入力状態の初期化
/// </summary>
void Mouse::reset() {
	mouseStatePress.fill(-1);
	mousePos = { 0,0 };
	wheel = 0;
}

/// <summary>
/// マウスカーソルの表示設定
/// </summary>
/// <param name="_is_use">マウスカーソルを表示するかどうか</param>
/// <returns>
/// 0 : 成功
/// -1 : エラー
/// </returns>
int Mouse::setMouseDispFlag(const bool _is_use) {
	return SetMouseDispFlag(_is_use);
}

/// <summary>
/// マウス座標の取得
/// </summary>
/// <returns>
/// マウス座標
/// </returns>
Vector2 Mouse::getMousePos() const {
	return mousePos;
}

/// <summary>
/// マウス座標の設定
/// </summary>
/// <param name="_pos">移動先の座標</param>
void Mouse::setMousePos(const Vector2& _pos) {
	mousePos = _pos;
}

/// <summary>
/// マウスホイールの回転量の取得
/// </summary>
/// <returns>
/// マウスホイールの回転量
/// </returns>
int Mouse::getMouseWheelRotVol() const {
	return wheel;
}

/// <summary>
/// 特定ボタンの入力状態を返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// 特定ボタンの入力状態
/// </returns>
int Mouse::state(const MouseCode _id) const {
	return mouseStatePress[_id];
}

/// <summary>
/// 特定ボタンの押されている時間を返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// 特定ボタンの入力フレーム数
/// </returns>
int Mouse::statePress(const MouseCode _id) const {
	return mouseStatePress[_id] > 0 ? mouseStatePress[_id] : 0;
}

/// <summary>
/// 特定ボタンの押されていない時間を返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// 特定ボタンが入力されていないフレーム数
/// </returns>
int Mouse::stateRelease(const MouseCode _id) const {
	return mouseStatePress[_id] < 0 ? -mouseStatePress[_id] : 0;
}

/// <summary>
/// 特定のボタンを押していない状態から押したかどうかを返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// true：押した直後 false：押した直後でない
/// </returns>
bool Mouse::isDown(const MouseCode _id) const {
	return mouseStatePress[_id] == 1 ? true : false;
}

/// <summary>
/// 特定のボタンを押されている状態から離したかどうかを返す
/// </summary>
/// <param name="_id">特定ボタンのID</param>
/// <returns>
/// true：離した直後 false：離した直後でない
/// </returns>
bool Mouse::isUp(const MouseCode _id) const {
	return mouseStatePress[_id] == -1 ? true : false;
}

/// <summary>
/// 不特定のボタンを押していない状態から押したかどうかを返す
/// </summary>
/// <returns>
/// true：押した直後 false：押した直後でない
/// </returns>
bool Mouse::isDownAny() const {
	for (auto &mouse_state : mouseStatePress) {
		if (mouse_state == 1) {
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
int Mouse::statePressLater(const MouseCode _id1, const MouseCode _id2) const {
	//デフォルトは何も押されていない状態
	int later = 0;

	//各ボタンの入力状態
	int mouse_state1, mouse_state2;

	mouse_state1 = mouseStatePress[_id1];
	mouse_state2 = mouseStatePress[_id2];

	if (mouse_state1 > 0) {	//一番目が押されていたら
		if (mouse_state2 > 0 && mouse_state2 < mouse_state1) {		//二番目が後に押されていたら
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (mouse_state2 > 0) {	//二番目が押されていたら
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
int Mouse::statePressLater4(const MouseCode _id1, const MouseCode _id2, const MouseCode _id3, const MouseCode _id4) const {
	//デフォルトは何も押されていない状態
	int later = 0;

	//ボタンが押された時間
	int shortest = 999999;

	//各ボタンの入力状態
	int mouse_state[4];

	mouse_state[0] = mouseStatePress[_id1];
	mouse_state[1] = mouseStatePress[_id2];
	mouse_state[2] = mouseStatePress[_id3];
	mouse_state[3] = mouseStatePress[_id4];

	for (int i = 0; i < 4; i++) {
		if (mouse_state[i] > 0 && mouse_state[i] < shortest) {
			later = i + 1;
			shortest = mouse_state[i];
		}
	}
	return later;
}



