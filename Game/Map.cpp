#include "Map.h"
#include "MapChip.h"
#include "ResourceManager.h"
#include "ErrorMessage.h"
#include "RenderManager.h"
#include "MessageManager.h"
#include "ScreenInfo.h"


const int Map::DEFAULT_GRID_SIZE = 48;



/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
	: cells()
	, mapchips()
	, gridSize(DEFAULT_GRID_SIZE) {
	initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map() {
	
}

/// <summary>
/// メッセージの受け取り処理
/// </summary>
/// <param name="_type">メッセージの種類</param>
/// <param name="_out">出力</param>
/// <param name="_in">入力</param>
/// <returns>
/// 有効なメッセージを受信したかどうか
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
/// マップの初期化
/// </summary>
void Map::initialize() {
	loadMapData();
	loadMapChip();
}

/// <summary>
/// マップの更新
/// </summary>
void Map::update() {
	MessageManager* message_manager = MessageManager::getIns();
	//マップのオフセットの更新
	Vector2 player_pos = message_manager->sendMessage<Vector2>(MessageType::GET_PLAYER_POS);
	Vector2 screen_pos;
	screen_pos.x = ClampT(player_pos.x - SCREEN_CENTER_X, 0.f, (float)GRID_COLS*DEFAULT_GRID_SIZE - SCREEN_WIDTH);
	screen_pos.y = ClampT(player_pos.y - SCREEN_CENTER_Y, 0.f, (float)GRID_ROWS*DEFAULT_GRID_SIZE - SCREEN_HEIGHT);

	RenderManager* render_manager = RenderManager::getIns();
	render_manager->setScreenOffset(ScreenType::MapScreen, screen_pos);
	render_manager->setScreenOffset(ScreenType::LightAlphaScreen, screen_pos);
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
	Vector2 screen_pos = RenderManager::getIns()->getScreenOffset(ScreenType::MapScreen);
	DrawFormatString(0, 10, ColorCode::COLOR_BLACK, "x=%f,y=%f", screen_pos.x, screen_pos.y);
}


/// <summary>
/// マップデータの読み込み
/// </summary>
/// <returns>
/// 読み込みに成功したかどうか
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
/// マップチップの読み込み
/// </summary>
void Map::loadMapChip() {
	//マップチップの読み込み
	auto mapchip_texture = ResourceManager::getIns()->getTexture(TEXTURE_MAPCHIP);
	
	// マップチップの生成
	for (int i = 0; i < NUM_MAPCHIPS; i++) {
		bool is_passable = (i <= 1) ? true : true;
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
	if ((_grid_x < 0) || (_grid_x >= GRID_COLS) ||
		(_grid_y < 0) || (_grid_y >= GRID_ROWS)) {
		ErrorMessage("領域外のセルを取得しようとしました");
		return nullptr;
	}

	int id = cells[_grid_x][_grid_y];

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

Vector2 Map::getCenterGrid() const {
	return Vector2{ GRID_COLS*0.5f - 0.5f, GRID_ROWS*0.5f - 0.5f };
}

/// <summary>
/// 中心座標の取得
/// </summary>
/// <returns>
/// 中心座標
/// </returns>
Vector2 Map::getCenterPos() const {
	return gridToPos(GRID_COLS*0.5f - 0.5f, GRID_ROWS*0.5f - 0.5f);
}

/// <summary>
/// グリッド座標からワールド座標に変換
/// </summary>
/// <param name="_grid_x">グリッドX座標</param>
/// <param name="_grid_y">グリッドY座標</param>
/// <returns>
/// ワールド座標
/// </returns>
Vector2 Map::gridToPos(float _grid_x, float _grid_y) const {
	return Vector2((_grid_x + 0.5f)*DEFAULT_GRID_SIZE, (_grid_y + 0.5f)*DEFAULT_GRID_SIZE);
}
