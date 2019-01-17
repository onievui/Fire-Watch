#pragma once

#include <array>
#include <memory>
#include "Vector2.h"

class MapChip;

class Map {
public:
	static const int GRID_COLS    = 30;	//横方向のグリッド数
	static const int GRID_ROWS	  = 30;	//縦方向のグリッド数
	static const int NUM_MAPCHIPS = 2;	//マップチップの数

	static const int DEFAULT_GRID_SIZE;	//初期グリッドサイズ

private:
	std::array<std::array<int,GRID_COLS>,GRID_ROWS>   cells;    //マップデータ
	std::array<std::unique_ptr<MapChip>,NUM_MAPCHIPS> mapchips;	// マップチップリスト
	int												  gridSize;	//グリッドの大きさ

public:
	Map();
	~Map();

public:
	void initialize();
	void draw() const;

private:
	bool loadMapData(const char* _filename);
	void loadMapChip();

public:
	MapChip* getCell(int _grid_x, int _grid_y) const;
	bool isPassable(int _grid_x, int _grid_y) const;
};
