#include "PlayScene.h"
#include "ShareDataManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "RenderManager.h"
#include "ScreenInfo.h"
#include "MessageManager.h"
#include "Collision.h"
#include "ShaderManager.h"
#include "MouseEventManager.h"



/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
	RenderManager::getIns()->addScreen(ScreenType::MapScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
	RenderManager::getIns()->addScreen(ScreenType::LightAlphaScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
	RenderManager::getIns()->changeScreen(ScreenType::MapScreen);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene() {
}

/// <summary>
/// シーンの初期化
/// </summary>
void PlayScene::initialize() {
	ResourceManager::getIns()->load(SCENE_PLAY);
	SoundPlayer::getIns()->reset();
	MessageManager* message_manager = MessageManager::getIns();
	//マップ管理クラスの生成
	map = std::make_unique<Map>();
	message_manager->add(map.get());
	//プレイヤーの生成
	player = std::make_unique<Player>();
	message_manager->add(player.get());
	//敵管理クラスの生成
	enemyManager = std::make_unique<EnemyManager>();
	message_manager->add(enemyManager.get());
	//フィールドオブジェクト管理クラスの生成
	fieldObjectManager = std::make_unique<FieldObjectManager>();
	message_manager->add(fieldObjectManager.get());
	//矢管理クラスの生成
	arrowManager = std::make_unique<ArrowManager>();
	message_manager->add(arrowManager.get());
	//マウスイベント管理クラスの生成
	mouseEventManager = std::make_unique<MouseEventManager>();
	//使用するシェーダーの設定
	ShaderManager::getIns()->setShader(ShaderID::SHADER_LIGHT);

}

/// <summary>
/// シーンの更新
/// </summary>
void PlayScene::update() {
	//各オブジェクトの更新
	player->update();
	enemyManager->update();
	fieldObjectManager->update();
	arrowManager->update();
	map->update();

	//マウスイベント処理
	mouseEventManager->update();

	//当たり判定処理
	Collision collision;
	collision.update();

	//シェーダーの更新
	ShaderManager::getIns()->update();
}


/// <summary>
/// シーンの描画
/// </summary>
void PlayScene::render() {
	RenderManager* render_manager = RenderManager::getIns();
	//描画先をマップにする
	render_manager->changeScreen(ScreenType::LightAlphaScreen);
	//DrawFillBox(0, 0, Map::GRID_COLS*Map::DEFAULT_GRID_SIZE, Map::GRID_ROWS*Map::DEFAULT_GRID_SIZE, ColorCode::COLOR_BLACK);
	render_manager->changeScreen(ScreenType::MapScreen);
	//ライティングに影響される描画
	map->draw();
	fieldObjectManager->draw();
	enemyManager->draw();
	arrowManager->draw();
	player->drawFlashLight();

	//シェーダーの使用(ライトの反映)
	ShaderManager::getIns()->draw();

	//ライトデータの更新
	map->updateLightData();

	//ライティングに影響しない描画
	player->draw();

	//マップを裏画面に反映
	render_manager->flipScreen();
	render_manager->clearScreen(ScreenType::MapScreen);
	render_manager->clearScreen(ScreenType::LightAlphaScreen);

	
}

/// <summary>
/// シーンの終了処理
/// </summary>
void PlayScene::finalize() {
	MessageManager::getIns()->reset();
	ResourceManager::getIns()->release();
	SoundPlayer::getIns()->stopAll();
	SoundPlayer::getIns()->reset();
	RenderManager::getIns()->deleteScreen(ScreenType::MapScreen);
	RenderManager::getIns()->deleteScreen(ScreenType::LightAlphaScreen);
	//使用するシェーダーの設定
	ShaderManager::getIns()->setShader(ShaderID::SHADER_NONE);
}

/// <summary>
/// シーン生成処理
/// </summary>
/// <param name="_impl">インタフェースへのポインタ</param>
/// <returns>
/// シーンオブジェクト
/// </returns>
std::unique_ptr<AbstractScene> PlayScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<PlayScene>(_impl));
}
