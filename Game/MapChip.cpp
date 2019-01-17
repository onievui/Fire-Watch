#include "MapChip.h"
#include "RenderManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_texture">�^�C���摜</param>
/// <param name="_is_passable">�ʍs�\���ǂ���</param>
MapChip::MapChip(HGRP _texture, bool _is_passable) {
	texture = _texture;
	isPassableFlag = _is_passable;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MapChip::~MapChip() {

}


/// <summary>
/// �`�揈��
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="grid_size"></param>
void MapChip::render(int _x, int _y, int _grid_size) const {
	int x1 = _x * _grid_size;
	int y1 = _y * _grid_size;
	int x2 = x1 + _grid_size;
	int y2 = y1 + _grid_size;

	RenderManager::getIns()->drawExtendGraphF(x1, y1, x2, y2, texture, TRUE);
	DrawExtendGraph(x1, y1, x2, y2, texture, TRUE);
}



/// <summary>
/// �ʍs�\���ǂ����̊m�F
/// </summary>
/// <returns>
/// true : �ʍs�\
/// false : �ʍs�s��
/// </returns>
bool MapChip::isPassable() const {
	return isPassableFlag;
}

