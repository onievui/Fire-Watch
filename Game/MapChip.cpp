#include "MapChip.h"
#include "RenderManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_texture">タイル画像</param>
/// <param name="_is_passable">通行可能かどうか</param>
MapChip::MapChip(HGRP _texture, bool _is_passable) {
	texture = _texture;
	isPassableFlag = _is_passable;
}

/// <summary>
/// デストラクタ
/// </summary>
MapChip::~MapChip() {

}


/// <summary>
/// 描画処理
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="grid_size"></param>
void MapChip::render(int _x, int _y, int _grid_size) const {
	float x1 = (float)_x * _grid_size;
	float y1 = (float)_y * _grid_size;
	float x2 = x1 + _grid_size;
	float y2 = y1 + _grid_size;

	RenderManager::getIns()->drawExtendGraphF(x1, y1, x2, y2, texture, TRUE);
}



/// <summary>
/// 通行可能かどうかの確認
/// </summary>
/// <returns>
/// true : 通行可能
/// false : 通行不可
/// </returns>
bool MapChip::isPassable() const {
	return isPassableFlag;
}

