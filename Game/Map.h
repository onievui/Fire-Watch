#pragma once

#include <array>
#include <memory>
#include "Vector2.h"

class MapChip;

class Map {
public:
	static const int GRID_COLS    = 30;	//�������̃O���b�h��
	static const int GRID_ROWS	  = 30;	//�c�����̃O���b�h��
	static const int NUM_MAPCHIPS = 2;	//�}�b�v�`�b�v�̐�

	static const int DEFAULT_GRID_SIZE;	//�����O���b�h�T�C�Y

private:
	std::array<std::array<int,GRID_COLS>,GRID_ROWS>   cells;    //�}�b�v�f�[�^
	std::array<std::unique_ptr<MapChip>,NUM_MAPCHIPS> mapchips;	// �}�b�v�`�b�v���X�g
	int												  gridSize;	//�O���b�h�̑傫��

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
