#pragma once



/// <summary>
/// �}�b�v�`�b�v�N���X
/// </summary>
class MapChip {
private:
	HGRP texture;			//�e�N�X�`��
	bool isPassableFlag;	//�ʍs�\���ǂ���

public:
	MapChip(const HGRP _texture, const bool _is_passable);
	~MapChip();

public:
	void render(int _x, int _y, int _grid_size) const;
	bool isPassable() const;
};
