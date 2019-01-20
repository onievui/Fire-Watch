#pragma once
#include "MessageInterface.h"
#include "Vector2.h"
#include <array>
#include <memory>


class MapChip;


class Map : public MessageInterface {
public:
	static const int GRID_COLS    = 31;	//�������̃O���b�h��
	static const int GRID_ROWS	  = 31;	//�c�����̃O���b�h��
	static const int NUM_MAPCHIPS = 6;	//�}�b�v�`�b�v�̐�

	static const int DEFAULT_GRID_SIZE;	//�����O���b�h�T�C�Y

private:
	std::array<std::array<int,GRID_COLS>,GRID_ROWS>   cells;    //�}�b�v�f�[�^
	std::array<std::unique_ptr<MapChip>,NUM_MAPCHIPS> mapchips;	// �}�b�v�`�b�v���X�g
	int												  gridSize;	//�O���b�h�̑傫��

public:
	Map();
	~Map();

public:
	bool getMessage(const MessageType _type, void* _out, void* _in);

public:
	void initialize();
	void update();
	void draw() const;

private:
	bool loadMapData();
	void loadMapChip();

public:
	MapChip* getCell(int _grid_x, int _grid_y) const;
	bool isPassable(int _grid_x, int _grid_y) const;
	Vector2 getCenterGrid() const;
	Vector2 getCenterPos() const;
	Vector2 gridToPos(float _grid_x, float _grid_y) const;
};
