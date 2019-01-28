#include "ErrorMessage.h"
#include "RenderManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
RenderManager::RenderManager() 
	: screens()
	, offsets()
	, currentScreenType((ScreenType)DX_SCREEN_BACK) {
	screensIndex.fill(-1);
}

/// <summary>
/// スクリーンの追加
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
/// <param name="_screen">スクリーン</param>
/// <param name="_offset">オフセット</param>
/// <returns>
/// 追加に成功したかどうか
/// </returns>
bool RenderManager::addScreen(const ScreenType _screen_type, const int _screen, const Vector2& _offset) {
	//範囲外かどうか
	if (_screen_type < 0 || _screen_type >= ScreenType::Num) {
		return false;
	}
	//追加済みかどうか
	if (screensIndex[_screen_type] != -1) {
		return false;
	}
	//追加処理
	screensIndex[_screen_type] = screens.size();
	screens.emplace_back(_screen);
	offsets.emplace_back(_offset);
	return true;
}

/// <summary>
/// スクリーンの切り替え
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
/// <returns>
/// 切り替えに成功したかどうか
/// </returns>
bool RenderManager::changeScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("スクリーンの切り替えに失敗しました");
		return false;
	}
	SetDrawScreen(screens[screensIndex[_screen_type]]);
	currentScreenType = _screen_type;
	return true;
}

/// <summary>
/// 画面の反映
/// </summary>
void RenderManager::flipScreen() {
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, screens[screensIndex[currentScreenType]], TRUE);
	SetDrawScreen(screens[screensIndex[currentScreenType]]);
}

/// <summary>
/// スクリーンの取得
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
/// <returns>
/// スクリーン
/// </returns>
int RenderManager::getScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("スクリーンの取得に失敗しました");
		return -1;
	}
	return screens[screensIndex[_screen_type]];
}

/// <summary>
/// オフセットの設定
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
/// <param name="_offset">オフセット</param>
/// <returns>
/// オフセットの設定に成功したかどうか
/// </returns>
bool RenderManager::setScreenOffset(const ScreenType _screen_type, const Vector2& _offset) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("オフセットの設定に失敗しました");
		return false;
	}
	offsets[screensIndex[_screen_type]] = _offset;
	return true;
}

/// <summary>
/// オフセットの取得
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
/// <returns>
/// オフセット
/// </returns>
Vector2 RenderManager::getScreenOffset(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("オフセットの取得に失敗しました");
		return Vector2();
	}
	return offsets[screensIndex[_screen_type]];
}

/// <summary>
/// 画面のクリア
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
void RenderManager::clearScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("有効でないスクリーンをクリアしようとしました");
	}
	else {
		if (currentScreenType == _screen_type) {
			ClearDrawScreen();
		}
		else {
			ScreenType pre_screen_type = currentScreenType;
			if (changeScreen(_screen_type)) {
				ClearDrawScreen();
				currentScreenType = pre_screen_type;
			}
		}
	}
}

/// <summary>
/// スクリーンの削除
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
/// <returns>
/// 削除に成功したかどうか
/// </returns>
bool RenderManager::deleteScreen(const ScreenType _screen_type) {
	if (!canUseScreenType(_screen_type)) {
		ErrorMessage("有効でないスクリーンを削除しようとしました");
		return false;
	}
	if (screens[screensIndex[_screen_type]] == DX_SCREEN_BACK) {
		return false;
	}

	DeleteGraph(screens[screensIndex[_screen_type]]);
	//最後尾のデータを削除する場合
	//if (screensIndex[_screen_type] == screens.size() - 1) {
	//	screensIndex[_screen_type] = -1;
	//	screens.erase(screens.end());
	//	offsets.erase(offsets.end());
	//}
	////最後尾でないデータを削除する場合
	//else {
		int delete_index = screensIndex[_screen_type];
		//位置をずらす
		for (auto& index : screensIndex) {
			if (index > delete_index) {
				--index;
			}
		}
		screensIndex[_screen_type] = -1;
		screens.erase(screens.begin() + delete_index);
		offsets.erase(offsets.begin() + delete_index);
	//}

	//選択中のスクリーンを削除した場合の処理
	if (currentScreenType == _screen_type) {
		currentScreenType = ScreenType(-1);
		SetDrawScreen(DX_SCREEN_BACK);
	}
	return true;
}

/// <summary>
/// 使用可能ななスクリーンタイプかどうか
/// </summary>
/// <param name="_screen_type">スクリーンタイプ</param>
/// <returns>
/// 使用可能かどうか
/// </returns>
bool RenderManager::canUseScreenType(const ScreenType _screen_type) {
	if (_screen_type < 0 || _screen_type >= ScreenType::Num) {
		return false;
	}
	if (screensIndex[_screen_type] == -1) {
		return false;
	}
	return true;
}


void RenderManager::drawCircleAA(const float _x, const float _y, const float _r, const int _pos_num, const unsigned int _color, const int _fill_flag, const float _thickness) {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawCircleAA(_x - offset.x, _y - offset.y, _r, _pos_num, _color, _fill_flag, _thickness);
}

void RenderManager::drawExtendGraphF(const float _x1, const float _y1, const float _x2, const float _y2, const int _handle, const int _trans_flag) const {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawExtendGraphF(_x1 - offset.x, _y1 - offset.y, _x2 - offset.x, _y2 - offset.y, _handle, _trans_flag);
}

void RenderManager::drawRotaGraphF(const float _x, const float _y, const float _exrate, const float _angle, int _handle, const int _trans_flag, const int _reverse_x_flag, const int _reverse_y_flag) const {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawRotaGraphF(_x - offset.x, _y - offset.y, _exrate, _angle, _handle, _trans_flag, _reverse_x_flag, _reverse_y_flag);
}

void RenderManager::drawRotaGraph(const float _x, const float _y, const float _exrate, const float _angle, int _handle, const int _trans_flag, const int _reverse_x_flag, const int _reverse_y_flag) const {
	Vector2 offset = offsets[screensIndex[currentScreenType]];
	DrawRotaGraph((int)(_x - offset.x), (int)(_y - offset.y), _exrate, _angle, _handle, _trans_flag, _reverse_x_flag, _reverse_y_flag);
}