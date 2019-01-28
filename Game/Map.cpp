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
	, lightCells()
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
	case MessageType::POS_TO_LIGHTDATA:
		*(int*)_out = posToLightData(*(Vector2*)_in);
		return true;
	case MessageType::GET_MAP_RANDOM_OUTSIDE_POS:
		*(Vector2*)_out = getRandomOutsidePos();
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
	//オフセットの初期設定
	RenderManager* render_manager = RenderManager::getIns();
	Vector2 screen_pos = getCenterGrid();
	screen_pos.y += 2.0f;
	screen_pos = gridToPos(screen_pos.x, screen_pos.y);
	screen_pos.x = ClampT(screen_pos.x - SCREEN_CENTER_X, 0.f, (float)GRID_COLS*DEFAULT_GRID_SIZE - SCREEN_WIDTH);
	screen_pos.y = ClampT(screen_pos.y - SCREEN_CENTER_Y, 0.f, (float)GRID_ROWS*DEFAULT_GRID_SIZE - SCREEN_HEIGHT);
	render_manager->setScreenOffset(ScreenType::MapScreen, screen_pos);
	render_manager->setScreenOffset(ScreenType::LightAlphaScreen, screen_pos);
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
/// ライトデータの更新処理
/// </summary>
void Map::updateLightData() {
	static int row = 0;
	RenderManager* render_manager = RenderManager::getIns();
	Vector2 off = render_manager->getScreenOffset(ScreenType::LightAlphaScreen);
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	for (int j = 0; j < GRID_COLS / 2; j++) {
		render_manager->changeScreen(ScreenType::LightAlphaScreen);
		int x = j * DEFAULT_GRID_SIZE * 2 + DEFAULT_GRID_SIZE - (int)off.x;
		int y = row * DEFAULT_GRID_SIZE*2 + DEFAULT_GRID_SIZE - (int)off.y;
		if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
			unsigned int color = GetPixel(x, y);
			int r, g, b;
			GetColor2(color, &r, &g, &b);
			//2*2マスに分割して、中心の色を明るさとして扱う
			render_manager->changeScreen(ScreenType::MapScreen);
			for (int i2 = row*2; i2 < GRID_ROWS && i2 < row*2 + 2; i2++) {
				for (int j2 = j*2; j2 < GRID_COLS  && j2 < j*2 + 2; j2++) {
					lightCells[i2][j2] = b;
					//DrawFormatStringF((j2 + 0.5f)*DEFAULT_GRID_SIZE, (i2 + 0.5f)*DEFAULT_GRID_SIZE, ColorCode::COLOR_WHITE, "%d", b);
				}
			}
		}
		//見えない部分は明るさ0として扱う
		else {
			lightCells[row][j] = 0;
		}
	}
	//処理が重いため遅延して行う
	row = (row + 1) % GRID_ROWS;
	render_manager->changeScreen(ScreenType::MapScreen);
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
		//ErrorMessage("領域外のセルを取得しようとしました");
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

/// <summary>
/// ワールド座標からマスの明るさを取得する
/// </summary>
/// <param name="_pos">ワールド座標</param>
/// <returns>
/// 明るさ
/// </returns>
int Map::posToLightData(const Vector2& _pos) const {
	int grid_x = (int)(_pos.x / DEFAULT_GRID_SIZE);
	int grid_y = (int)(_pos.y / DEFAULT_GRID_SIZE);
	//範囲外チェック
	if ((grid_x < 0) || (grid_x >= GRID_COLS) ||
		(grid_y < 0) || (grid_y >= GRID_ROWS)) {
		return 0;
	}
	return lightCells[grid_y][grid_x];
}

/// <summary>
/// マップの外側のランダムな座標の取得
/// </summary>
/// <returns>
/// ランダムな座標
/// </returns>
Vector2 Map::getRandomOutsidePos() const {
	if (GetRand(GRID_ROWS + GRID_COLS) < GRID_ROWS) {
		return gridToPos((float)(GetRand(1) ? -1 : (GRID_COLS + 1)), (float)GetRand(GRID_ROWS));
	}
	else {
		return gridToPos((float)GetRand(GRID_COLS), (float)(GetRand(1) ? -1 : (GRID_ROWS + 1)));
	}
}
