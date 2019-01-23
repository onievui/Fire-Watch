#include "Map.h"
#include "MapChip.h"
#include "ResourceManager.h"
#include "ErrorMessage.h"
#include "RenderManager.h"
#include "MessageManager.h"
#include "ScreenInfo.h"


const int Map::DEFAULT_GRID_SIZE = 48;



/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
	: cells()
	, mapchips()
	, gridSize(DEFAULT_GRID_SIZE) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map() {
	
}

/// <summary>
/// ���b�Z�[�W�̎󂯎�菈��
/// </summary>
/// <param name="_type">���b�Z�[�W�̎��</param>
/// <param name="_out">�o��</param>
/// <param name="_in">����</param>
/// <returns>
/// �L���ȃ��b�Z�[�W����M�������ǂ���
/// </returns>
bool Map::getMessage(const MessageType _type, void* _out, void* _in) {
	switch (_type) {
	case MessageType::GET_MAP:
		*(Map**)_out = this;
		return true;
	case MessageType::GET_MAP_CENTER_GRID:
		*(Vector2*)_out = getCenterGrid();
		return true;
	case MessageType::GET_MAP_CENTER_POS:
		*(Vector2*)_out = getCenterPos();
		return true;
	case MessageType::GRID_TO_POS:
		*(Vector2*)_out = gridToPos((*(Vector2*)_in).x, (*(Vector2*)_in).y);
		return true;
	default:
		break;
	}
	return false;
}



/// <summary>
/// �}�b�v�̏�����
/// </summary>
void Map::initialize() {
	loadMapData();
	loadMapChip();
}

/// <summary>
/// �}�b�v�̍X�V
/// </summary>
void Map::update() {
	MessageManager* message_manager = MessageManager::getIns();
	//�}�b�v�̃I�t�Z�b�g�̍X�V
	Vector2 player_pos = message_manager->sendMessage<Vector2>(MessageType::GET_PLAYER_POS);
	Vector2 screen_pos;
	screen_pos.x = ClampT(player_pos.x - SCREEN_CENTER_X, 0.f, (float)GRID_COLS*DEFAULT_GRID_SIZE - SCREEN_WIDTH);
	screen_pos.y = ClampT(player_pos.y - SCREEN_CENTER_Y, 0.f, (float)GRID_ROWS*DEFAULT_GRID_SIZE - SCREEN_HEIGHT);

	RenderManager* render_manager = RenderManager::getIns();
	render_manager->setScreenOffset(ScreenType::MapScreen, screen_pos);
	render_manager->setScreenOffset(ScreenType::LightAlphaScreen, screen_pos);
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
	Vector2 screen_pos = RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	DrawFormatString(0, 10, ColorCode::COLOR_BLACK, "x=%f,y=%f", screen_pos.x, screen_pos.y);
}


/// <summary>
/// �}�b�v�f�[�^�̓ǂݍ���
/// </summary>
/// <returns>
/// �ǂݍ��݂ɐ����������ǂ���
/// </returns>
bool Map::loadMapData() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			if (i <= 1 || i >= GRID_ROWS - 2 ||
				j <= 1 || j >= GRID_COLS - 2) {
				cells[i][j] = GetRand(5);
			}
			else {
				cells[i][j] = GetRand(5);
			}
		}
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
		bool is_passable = (i <= 1) ? true : true;
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
	if ((_grid_x < 0) || (_grid_x >= GRID_COLS) ||
		(_grid_y < 0) || (_grid_y >= GRID_ROWS)) {
		ErrorMessage("�̈�O�̃Z�����擾���悤�Ƃ��܂���");
		return nullptr;
	}

	int id = cells[_grid_x][_grid_y];

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

Vector2 Map::getCenterGrid() const {
	return Vector2{ GRID_COLS*0.5f - 0.5f, GRID_ROWS*0.5f - 0.5f };
}

/// <summary>
/// ���S���W�̎擾
/// </summary>
/// <returns>
/// ���S���W
/// </returns>
Vector2 Map::getCenterPos() const {
	return gridToPos(GRID_COLS*0.5f - 0.5f, GRID_ROWS*0.5f - 0.5f);
}

/// <summary>
/// �O���b�h���W���烏�[���h���W�ɕϊ�
/// </summary>
/// <param name="_grid_x">�O���b�hX���W</param>
/// <param name="_grid_y">�O���b�hY���W</param>
/// <returns>
/// ���[���h���W
/// </returns>
Vector2 Map::gridToPos(float _grid_x, float _grid_y) const {
	return Vector2((_grid_x + 0.5f)*DEFAULT_GRID_SIZE, (_grid_y + 0.5f)*DEFAULT_GRID_SIZE);
}
