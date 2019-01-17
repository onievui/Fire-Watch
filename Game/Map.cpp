#include "Map.h"
#include "MapChip.h"
#include "ResourceManager.h"
#include "ErrorMessage.h"
#include <fstream>
#include <sstream>
#include <string>

const int Map::DEFAULT_GRID_SIZE = 64;



/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
	: cells()
	, mapchips()
	, gridSize(DEFAULT_GRID_SIZE) {
	
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map() {
	
}



/// <summary>
/// マップの初期化
/// </summary>
void Map::initialize() {
	loadMapData("tes");
	loadMapChip();
}


/// <summary>
/// マップの描画
/// </summary>
void Map::draw() const {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			int id = cells[i][j];
			if (mapchips[id]) {
				mapchips[id]->render(i, j, gridSize);
			}
		}
	}

	// グリッドの描画(Debug用)
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			int x1 = j * gridSize - 0;
			int y1 = i * gridSize - 0;
			int x2 = x1 + gridSize;
			int y2 = y1 + gridSize;
			DrawBox(x1, y1, x2, y2, COLOR_GRAY, FALSE);
		}
	}
}


/// <summary>
/// マップデータの読み込み
/// </summary>
/// <param name="_filename">読み込むファイル名</param>
/// <returns>
/// true : 成功
/// false : 失敗
/// </returns>
bool Map::loadMapData(const char* _filename) {
	// ファイルのオープン
	std::ifstream ifs(_filename);
	if (!ifs.is_open()) {
		ErrorMessage("マップデータのロードに失敗しました");
		return false;
	}

	std::string line;
	int grid_y = 0;
	while (getline(ifs, line)) {
		std::istringstream data(line);
		std::string field;
		int grid_x = 0;
		while (getline(data, field, ',')) {
			cells[grid_y][grid_x] = atoi(field.c_str());
			grid_x++;
		}
		grid_y++;
	}
	return true;
}

/// <summary>
/// マップチップの読み込み
/// </summary>
void Map::loadMapChip() {
	//マップチップの読み込み
	auto mapchip_texture = ResourceManager::getIns()->getTexture(TEXTURE_MAPCHIP);

	// マップチップの生成
	for (int i = 0; i < NUM_MAPCHIPS; i++) {
		bool is_passable = (i == 0) ? true : false;
		HGRP texture     = mapchip_texture->getResource(i);
		mapchips[i] = std::make_unique<MapChip>(texture, is_passable);
	}
}





/// <summary>
/// セルの取得
/// </summary>
/// <param name="_grid_x">セルのＸ座標</param>
/// <param name="_grid_y">セルのＹ座標</param>
/// <returns>マップチップ</returns>
MapChip* Map::getCell(int _grid_x, int _grid_y) const {
	//範囲外チェック
	if ((_grid_x >= 0) && (_grid_x < GRID_COLS) &&
		(_grid_y >= 0) && (_grid_y < GRID_ROWS)) {
		ErrorMessage("領域外のセルを取得しようとしました");
		return nullptr;
	}

	int id = cells[_grid_y][_grid_x];

	return mapchips[id].get();
}



/// <summary>
/// 通行可能かどうかの確認
/// </summary>
/// <param name="_grid_x"></param>
/// <param name="_grid_y"></param>
/// <returns>
/// true : 通行可能
/// false : 通行不可
/// </returns>
bool Map::isPassable(int _grid_x, int _grid_y) const {
	MapChip* mapchip = getCell(_grid_x, _grid_y);
	if (!mapchip) {
		return false;
	}
	return mapchip->isPassable();
}
