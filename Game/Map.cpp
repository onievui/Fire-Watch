#include "Map.h"
#include "MapChip.h"
#include "ResourceManager.h"
#include "ErrorMessage.h"
#include <fstream>
#include <sstream>
#include <string>

const int Map::DEFAULT_GRID_SIZE = 64;



/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
	: cells()
	, mapchips()
	, gridSize(DEFAULT_GRID_SIZE) {
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map() {
	
}



/// <summary>
/// �}�b�v�̏�����
/// </summary>
void Map::initialize() {
	loadMapData("tes");
	loadMapChip();
}


/// <summary>
/// �}�b�v�̕`��
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

	// �O���b�h�̕`��(Debug�p)
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
/// �}�b�v�f�[�^�̓ǂݍ���
/// </summary>
/// <param name="_filename">�ǂݍ��ރt�@�C����</param>
/// <returns>
/// true : ����
/// false : ���s
/// </returns>
bool Map::loadMapData(const char* _filename) {
	// �t�@�C���̃I�[�v��
	std::ifstream ifs(_filename);
	if (!ifs.is_open()) {
		ErrorMessage("�}�b�v�f�[�^�̃��[�h�Ɏ��s���܂���");
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
/// �}�b�v�`�b�v�̓ǂݍ���
/// </summary>
void Map::loadMapChip() {
	//�}�b�v�`�b�v�̓ǂݍ���
	auto mapchip_texture = ResourceManager::getIns()->getTexture(TEXTURE_MAPCHIP);

	// �}�b�v�`�b�v�̐���
	for (int i = 0; i < NUM_MAPCHIPS; i++) {
		bool is_passable = (i == 0) ? true : false;
		HGRP texture     = mapchip_texture->getResource(i);
		mapchips[i] = std::make_unique<MapChip>(texture, is_passable);
	}
}





/// <summary>
/// �Z���̎擾
/// </summary>
/// <param name="_grid_x">�Z���̂w���W</param>
/// <param name="_grid_y">�Z���̂x���W</param>
/// <returns>�}�b�v�`�b�v</returns>
MapChip* Map::getCell(int _grid_x, int _grid_y) const {
	//�͈͊O�`�F�b�N
	if ((_grid_x >= 0) && (_grid_x < GRID_COLS) &&
		(_grid_y >= 0) && (_grid_y < GRID_ROWS)) {
		ErrorMessage("�̈�O�̃Z�����擾���悤�Ƃ��܂���");
		return nullptr;
	}

	int id = cells[_grid_y][_grid_x];

	return mapchips[id].get();
}



/// <summary>
/// �ʍs�\���ǂ����̊m�F
/// </summary>
/// <param name="_grid_x"></param>
/// <param name="_grid_y"></param>
/// <returns>
/// true : �ʍs�\
/// false : �ʍs�s��
/// </returns>
bool Map::isPassable(int _grid_x, int _grid_y) const {
	MapChip* mapchip = getCell(_grid_x, _grid_y);
	if (!mapchip) {
		return false;
	}
	return mapchip->isPassable();
}
