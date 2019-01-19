#include "PlayScene.h"
#include "ShareDataManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "RenderManager.h"
#include "ScreenInfo.h"
#include "MessageManager.h"
#include "Collision.h"


/// <summary>
/// シーン切り替えインタフェースの登録
/// </summary>
/// <param name="_impl">リスナーへのポインタ</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
	RenderManager::getIns()->addScreen(ScreenType::MapScreen, MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE), Vector2(0, 0));
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
	map->initialize();
	message_manager->add(map.get());
	//プレイヤーの生成
	player = std::make_unique<Player>();
	player->initialize();
	message_manager->add(player.get());

}

/// <summary>
/// シーンの更新
/// </summary>
void PlayScene::update() {
	//各オブジェクトの更新
	map->update();
	player->update();

	//当たり判定処理
	Collision collision;
	collision.update();
}


/// <summary>
/// シーンの描画
/// </summary>
void PlayScene::render() {
	RenderManager* render_manager = RenderManager::getIns();
	//描画先をマップにする
	render_manager->changeScreen(ScreenType::MapScreen);
	map->draw();
	player->draw();
	render_manager->flipScreen();
	render_manager->clearScreen(ScreenType::MapScreen);


}

/// <summary>
/// シーンの終了処理
/// </summary>
void PlayScene::finalize() {
	ResourceManager::getIns()->release();
	SoundPlayer::getIns()->stopAll();
	SoundPlayer::getIns()->reset();
	RenderManager::getIns()->deleteScreen(ScreenType::MapScreen);
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
